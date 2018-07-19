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

int	empty_zone(t_head *head)
{
	t_chunk	*chunk;

	chunk = head->meta_start;
	while (chunk != NULL)
	{
		if (chunk->used == 1)
			return (0);
		if (chunk->next_chunk == NULL)
			return (1);
		chunk = chunk->next_chunk;
	}
	if (chunk != NULL && chunk->next_chunk != NULL && chunk->used == 0)
		return (1);
	head = head->next_zone;
	return (0);
}

void	deallocate_zone(int index, t_head *head)
{
	t_head	*next;
	t_head	*prev;

	prev = g_slabs[index];
	if (prev != head)
	{
		while (prev->next_zone != head)
			prev = prev->next_zone;
	}
	else 
		prev = NULL;
	next = head->next_zone;
	//printf("pref zone: %p\tafter zone: %p\t g_slab[%d]=%p ", prev, next, index, &g_slabs[index]);
	if (prev != NULL)
		prev->next_zone = next;
	else if (prev == NULL && next != NULL)
		g_slabs[index] = next;
	else if (head == NULL && next == NULL)
		g_slabs[index] = NULL;
	munmap(head, head->bytes_per_zone);
}

t_head		*find_zone(void *ptr, int *index)
{
	t_head		*header;
	void		*zone_end;

	while (*index <= INDEX_COUNT)
	{
		header = g_slabs[*index];
		while (header)
		{
			zone_end = (void*)header;
			zone_end += header->bytes_per_zone;
			if (((void*)header < ptr) && (ptr < zone_end))
				return (header);
			header = header->next_zone;
		}
		*index += 1;
	}
	return (NULL);
}

t_chunk		*find_chunk(t_head *head, void *ptr)
{
	t_chunk	*chunk;
	
	chunk = head->meta_start;
	while (chunk != NULL)
	{
		if (chunk->chunk_start == ptr && (chunk->used == 1))
			return (chunk);
		chunk = chunk->next_chunk;
	}
	return (NULL);
}

void		deallocate_chunk(void *ptr)
{
	t_chunk *chunk;

	chunk = ptr;
	chunk->used = 0;
	//printf("chunk_dealocated: %d\t", chunk->used);
}

void	ft_free(void *ptr)
{
	int		index;
	t_chunk	*chunk;
	t_head	*head;

	index = 0;
	if (ptr == NULL)
		return ;
	head = find_zone(ptr, &index);
	if (head == NULL)
		return ;
	chunk = find_chunk(head, ptr);
	if (chunk == NULL)
		return ;
//printf("\tINDEX: %d\tptr: %p\t",index, &ptr);
	deallocate_chunk(ptr);
	if (empty_zone(head))
		deallocate_zone(index, head);
}
