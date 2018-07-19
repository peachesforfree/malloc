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

void		*excess_bytes_avail(t_chunk *chunk, size_t size)
{
	//compares current chunk_start and the next_chunk pointer,
	//checks if the memory size is equivalent to ;size;
	// if extra space is equivalent return 1
}

void		*expand_zone(t_chunk *chunk, size_t size)
{
	//reset data in chunk->size to what ever 'size' is
}

void		*ft_realloc(void *ptr, size_t size)
{
	int		index;
	t_chunk *chunk;
	t_head  *head;

	if (ptr == NULL)
		return (NULL);
	head == find_zone(ptr, &index);
	if (head == NULL)
		return (NULL);
	chunk = find_chunk(head, ptr);
	if (chunk == NULL)
		return (NULL);
	if(excess_bytes_avail(chunk, size))
		return(expand_zone(chunk, size));
	else
	{
		new = ft_malloc(size);	//allocate new memory block of size
		ft_memcpy(ptr, new, size);		//copies the old to the new;
		ft_free(ptr);
		return (new);
	}
	return (NULL);
}