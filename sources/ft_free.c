/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:04:17 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/17 17:04:21 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void	*evaluate_zone(t_head *header, void *ptr)
{
	t_chunk	*chunk;

	chunk = header->meta_start;
	while (chunk != NULL)
	{
		if (chunk->chunk_start == ptr && (chunk->used == 1))
			return (ptr);
		chunk = chunk->next_chunk;
	}
	return (NULL);
}

void	*find_ptr(void *ptr, int *index)
{
	t_head		*header;
	void		*test;

	while (*index <= INDEX_COUNT)
	{
		header = g_slabs[*index];
		while (header)
		{
			test = (void*)header;
			test += header->bytes_per_zone;
			if (((void*)header < ptr) && (ptr < test))
				return (evaluate_zone(header, ptr));
			header = header->next_zone;
		}
		*index += 1;
	}
	return (NULL);
}

void	ft_free(void *ptr)
{
	void	*result;
	int		index;

	index = 0;
	if (ptr == NULL)
		return ;
	result = find_ptr(ptr, &index);
	//dealocate(result);
	printf("\t\t\t\tINDEX: %d\tresult: %p\n", index, result);
}
