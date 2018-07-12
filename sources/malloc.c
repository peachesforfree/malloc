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
	buffer.chunk_start = (result + sizeof(t_head) + 1);
	ft_memcpy(result, &buffer, sizeof(t_head));
}

void			init_meta_data(void *start, size_t chunk_size)
{
	t_chunk		buffer;

	buffer.size = chunk_size;
	buffer.used = 0;
	buffer.chunk_start = (start + sizeof(t_chunk) + 1);
	buffer.next_chunk = NULL;
	ft_memcpy(start, &buffer, sizeof(t_chunk));
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
	init_meta_data(head->chunk_start, chunk_size);
	return (result);
}

void		*check_slab(int index, size_t size)
{
	void	*result = NULL;

	if (g_slabs[index] == NULL)
		g_slabs[index] = create_slab(get_page_req(index, size), getpagesize(), size);
	if (g_slabs[index] == NULL)
		return (NULL);
/*	result = cut_chunk_from_slab();
	if (result == NULL)
		stack_new_slab();
	//maybe check here for errors ?*/
	printf("\t\tPages_req: %zu\n", get_page_req(index, size));
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
