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

#include "../includes/malloc.h"

size_t			get_page_req(int index, size_t size)
{
	int	pagesize;

	pagesize = getpagesize();
	if (index == TINY_INDEX)
		return (((TINY_ZONE + sizeof(t_chunk)) * MAX_ALLOCATIONS) / pagesize);
	if (index == SMALL_INDEX)
		return (((SMALL_ZONE + sizeof(t_chunk)) * MAX_ALLOCATIONS) / pagesize);
	return ((size + sizeof(t_chunk)) / pagesize);
}

void		init_zone(void *result, size_t p_count, size_t p_size)
{
	t_head	buffer;

	buffer.page_size = p_size;
	buffer.bytes_per_zone = (p_count * p_size);
	buffer.meta_start = (result + sizeof(t_head) + 1);
	buffer.next_zone = NULL;
	ft_memcpy(result, &buffer, sizeof(t_head));
}

void			*init_meta_data(void *start, size_t chunk_size)
{
	t_chunk		buffer;

	buffer.size = chunk_size;
	buffer.used = 0;
	buffer.chunk_start = (start + sizeof(t_chunk) + 1);
	buffer.next_chunk = NULL;
	ft_memcpy(start, &buffer, sizeof(t_chunk));
	return (&start);
}

void		*create_slab(size_t page_count, size_t page_size, size_t chunk_size)
{
	void	*result;
	t_head	*head;

	result = mmap(NULL, (page_count * page_size), PROT_ALL, FT_MAP_ANON, -1, 0);
	if (result == NULL)
		return (NULL);
	init_zone(result, page_count, page_size);
	head = result;
	init_meta_data(head->meta_start, chunk_size);
	return (result);
}

void		address_testing(int index)
{
	t_head	*head;
	t_chunk	*chunk;

	head = g_slabs[index];
	chunk = head->meta_start;
	printf("\nAddress:\t%p\n\tzone_start:%p\tmeta start:%p\tchunk start:%p\n",
	g_slabs[index], head, head->meta_start, chunk->chunk_start);
	printf("zone meta:%lu\tchunk meta:%lu\n", sizeof(t_head), sizeof(t_chunk));
}

t_chunk		*look_for_free(t_head *top_slab, size_t size)
{
	t_chunk	*chunk;

	chunk = top_slab->meta_start;
	while (chunk->used == 1 && (chunk->size < size) && (chunk->next_chunk != NULL))
		chunk = (t_chunk*)chunk->next_chunk;
	if (chunk->used == 1 && chunk->next_chunk == NULL)
	{
		if (top_slab + top_slab->bytes_per_zone > (chunk + sizeof(chunk) + size))
			chunk->next_chunk = init_meta_data(chunk + size + 1, size);
	}
	if (chunk->size <= size)
		chunk->used = 1;
	return(chunk);
}

t_chunk		*cut_new_chunk(t_head *top_slab)
{
	t_chunk	*chunk;

	chunk = top_slab->chunk_start;

	return (chunk);
}


/*
*this checks the slab for a free piece
*is no free chunks available , it will cut new one at end of used block
*
*/

void		*cut_chunk_from_slab(int index, size_t size)
{
	void	*result;
	t_chunk	*chunk;
	t_head	*top_slab;

//	if (index == LARGE_INDEX)
//	{
//		top_slab = add_slab();
//		chunk = cut_new_chunk(top_slab);
//		return (chunk);
//	}
	top_slab = g_slabs[index];
	chunk = look_for_free(top_slab, size);
	if (chunk == NULL)
		chunk = cut_new_chunk(top_slab);
/*	if (chunk == NULL) //no free chunks, nor chunk space
	{
		top_slab = create_slab(top_slab->bytes_per_zone /
		top_slab->pag_size, top_slab->page_size, size);
		chunk = top_slab->meta_start;
	}*/
	return (result->chunk_start);
}

void		*check_slab(int index, size_t size)
{
	void	*result = NULL;

	if (g_slabs[index] == NULL)
		g_slabs[index] = create_slab(get_page_req(index, size), getpagesize(), size);
	if (g_slabs[index] == NULL)
		return (NULL);
	result = cut_chunk_from_slab(index, size);
	if (result == NULL)
		stack_new_slab();
	//maybe check here for errors ?
	address_testing(index);
	return (result);
}

void		*malloc(size_t size)
{
	if (size == 0)
		size = 1;
	if (size <= TINY_ZONE)
		return (check_slab(TINY_INDEX, size));
	if (size <= SMALL_ZONE)
		return (check_slab(SMALL_INDEX, size));
	return (check_slab(LARGE_INDEX, size));
}
