/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 23:15:07 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/18 23:15:09 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

int			excess_bytes_avail(t_chunk *chunk, size_t size)
{
	void	*start;
	void	*end;

	start = chunk->chunk_start;
	end = chunk->next_chunk;
	if ((size_t)(start - end) >= size)
	{
		chunk->size = size;
		return (1);
	}
	return (0);
}

void		*realloc(void *ptr, size_t size)
{
	int		index;
	t_chunk	*chunk;
	t_head	*head;
	void	*new;

	if (ptr == NULL || (head = find_zone(ptr, &index)) == NULL)
		return (NULL);
	if ((chunk = find_chunk(head, ptr)) == NULL)
		return (NULL);
	if (excess_bytes_avail(chunk, size))
		return (ptr);
	if (chunk->size <= size)
		return (ptr);
	else
	{
		new = malloc(size);
		ft_memcpy(ptr, new, size);
		free(ptr);
		return (new);
	}
	return (NULL);
}
