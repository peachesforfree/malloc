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

int			get_page_req(int index, size_t size)
{
	int	pagesize;

	pagesize = getpagesize();
	if (index == TINY_INDEX)
		return (((TINY_ZONE + sizeof(t_table)) * MAX_ALLOCATIONS) / pagesize);
	if (index == SMALL_INDEX)
		return (((SMALL_ZONE + sizeof(t_table)) * MAX_ALLOCATIONS) / pagesize);
	return ((size + sizeof(t_table)) / pagesize);
}

void		*check_slab(int index, size_t size)
{
	void	*result = NULL;
	size_t	pages;

	pages = get_page_req(index, size);
	if (g_slabs[index] == NULL)
		g_slabs[index] = create_slab(index, pages);
/*	result = cut_chunk_from_slab();
	if (result == NULL)
		stack_new_slab();
	//maybe check here for errors ?*/
	printf("\t\tPages_req: %zu\n", pages);
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
