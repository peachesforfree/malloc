/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:05:24 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/10 13:05:25 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void	*g_slabs[3] = {	NULL, NULL, NULL};

size_t			get_page_req(int index, size_t size)
{
	int	pagesize;
	int large;

	pagesize = getpagesize();
	if (index == TINY_INDEX)
		return (((TINY_ZONE + sizeof(t_chunk)) * MAX_ALLOCATIONS) / pagesize);
	if (index == SMALL_INDEX)
		return (((SMALL_ZONE + sizeof(t_chunk)) * MAX_ALLOCATIONS) / pagesize);
	if (index == LARGE_INDEX)
	{
		large = ((size + sizeof(t_chunk)) / pagesize);
		if (large == 0)
			large = 1;
		return (large);
	}
	return (0);
}

void		init_zone(void *result, size_t p_count, size_t p_size)
{
	t_head	buffer;

	buffer.page_size = p_size;
	buffer.bytes_per_zone = (p_count * p_size);
	buffer.meta_start = (result + sizeof(t_head) + SAFEZONE);
	buffer.next_zone = NULL;
	ft_memcpy(result, &buffer, sizeof(t_head));
	//printf("\t\tHeadvar\tstart: %p\tmeta_start:%p\tnext_zone:%p\tend zone addr: %p\n\n", result, buffer.meta_start, buffer.next_zone, result + buffer.bytes_per_zone);
}

t_chunk			*init_meta_data(void *start, size_t chunk_size, t_chunk *last)
{
	t_chunk		buffer;

	buffer.size = chunk_size;
	buffer.used = 0;
	buffer.chunk_start = (start + (sizeof(t_chunk) + 1));
	buffer.next_chunk = NULL;
	if (last != NULL)
		last->next_chunk = start;
	ft_memcpy(start, &buffer, sizeof(t_chunk));
	//printf("\t\tmetavar\tloc: %p\tsize:%zu\tused: %d\tchunk_start: %p\tnext_chunk: %p\n", start, buffer.size, buffer.used, buffer.chunk_start, buffer.next_chunk);
	//printf("\t\tSizeof(t_chunk)=%zu\tnext_metaptr:%p\n\n", sizeof(t_chunk), buffer.chunk_start + (chunk_size + SAFEZONE));
	return (start);
}

void		*create_slab(size_t page_count, size_t page_size, size_t chunk_size)
{
	void	*result;
	t_head	*head;
	t_chunk *chunk;

//insert here if index is 2 (LARGE_INDEX) then need to make custom size allocation
	result = mmap(NULL, (page_count * page_size), PROT_ALL, FT_MAP_ANON, -1, 0);
	if (result == NULL)
		return (NULL);
	//printf("\tCreating new slab: %p\n", result);
	init_zone(result, page_count, page_size);
	head = result;
	chunk = init_meta_data(head->meta_start, chunk_size, NULL);
	chunk->used = 1;
	return (result);
}

void			*enough_space_in_zone(t_head *top_slab, t_chunk *chunk, size_t size)
{
	void	*zone_end;
	void	*new_chunk_start;
	void	*new_chunk_end;

	zone_end = top_slab;
	zone_end += top_slab->bytes_per_zone;
	new_chunk_start = chunk->chunk_start + (chunk->size + SAFEZONE);
	new_chunk_end = new_chunk_start + (sizeof(t_chunk) + size + SAFEZONE);
	if (new_chunk_end < zone_end)
		return (new_chunk_start);
	return (NULL);
}

/*
** Cycles thru all chunks on list
**	if no free chunk is available on slab
**	then next slab and cycle through
**	if no space at all, return NULL
**	else pointer to next chunk is returned
*/

t_chunk		*look_for_free(t_head *top_slab, size_t size)
{
	t_chunk	*chunk;
	void	*new_meta;

	//cycle through all zones
	while (top_slab != NULL)
	{
		chunk = top_slab->meta_start;
		//cycle through all chunks in zone
		while ((chunk->next_chunk != NULL) && chunk->used == 1)
			chunk = (t_chunk*)chunk->next_chunk;
		//if current pointed to chunk is open and good size
		if (chunk->used == 0 && size <= chunk->size)
		{
			chunk->used = 1;
			return (chunk->chunk_start);
		}
		//if at end of chunks but still space in zone
		//takes current chunk addres, adds all numbers for soon to be chunk
		else if (chunk->used == 1 && (new_meta = enough_space_in_zone(top_slab, chunk, size)) != NULL)
		{
			//below, change this to a function that will automatically jump ahead of current meta data pointer and set the new one in place, and return it
			chunk = init_meta_data(new_meta, size, chunk);
			chunk->used = 1;
			return (chunk->chunk_start);
		}
		top_slab = top_slab->next_zone;
	}
	return (NULL);
}

//void		*create_slab(size_t page_count, size_t page_size, size_t chunk_size)
void		*allocate_new_zone(size_t page_req, t_head *head, size_t size)
{
	t_head		*new_zone;
	t_chunk		*chunk;

	while (head->next_zone != NULL)
		head = head->next_zone;
	new_zone = (t_head*)create_slab(page_req, head->page_size, size);
	head->next_zone = new_zone;
	chunk = new_zone->meta_start;
	return (chunk->chunk_start);
}

/*
*this checks the slab for a free piece
*is no free chunks available , it will cut new one at end of used block
*
*/

void		*allocate_large_slab(t_head *head, int index, size_t size)
{
	t_chunk	*chunk;

	if (head != NULL)
	{
		while (head != NULL && head->next_zone != NULL)
			head = head->next_zone;
		head->next_zone = (t_head*)create_slab(get_page_req(index, size), getpagesize(), size);
		if (head->next_zone != NULL)
			head = head->next_zone;
		else 
			return (NULL); //error with allocating memory
	}
	else
	{
		head = (t_head*)create_slab(get_page_req(index, size), getpagesize(), size);
		chunk = head->meta_start;
	}
	chunk = head->meta_start;
	return (chunk->chunk_start);
}

void		*cut_chunk_from_slab(int index, size_t size)
{
	t_chunk	*chunk;
	t_head	*top_slab;

	if (index == LARGE_INDEX)
	{
		top_slab = allocate_large_slab(g_slabs[index], index, size);
		chunk = top_slab->meta_start;
		return (chunk->chunk_start);
	}
	//looks for free chunk, return null if out of memory in the zone
	top_slab = g_slabs[index];
	chunk = look_for_free(top_slab, size);
	if (chunk == NULL)
		return(NULL);	//there was an error with mmap
	return (chunk);
}

void		*check_slab(int index, size_t size)
{
	void	*result = NULL;

	if (g_slabs[index] == NULL)
		g_slabs[index] = create_slab(get_page_req(index, size), getpagesize(), size);
	else if (g_slabs[index] == NULL)
		return (NULL);
	result = look_for_free(g_slabs[index], size);
	//make sure above is returning chunk_start pointer
	if (result == NULL && size > 0)
		result = allocate_new_zone(get_page_req(index, size), g_slabs[index], size);
	//maybe check here for errors ?
	return (result);
}

void		*ft_malloc(size_t size)
{
	if (size == 0)
		return (NULL);
	if (size <= TINY_ZONE)
		return (check_slab(TINY_INDEX, size));
	if (size <= SMALL_ZONE)
		return (check_slab(SMALL_INDEX, size));
	return (check_slab(LARGE_INDEX, size));
}