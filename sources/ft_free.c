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
			return (chunk);
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

t_head	*empty_zone(t_head *head)
{
	t_chunk	*chunk;

	while (head != NULL)
	{
		chunk = head->meta_start;
		while (chunk != NULL)
		{
			if (chunk->used == 1)
				break ;
			if (chunk->next_chunk == NULL)
				break ;
			chunk = chunk->next_chunk;
		}
		if (chunk != NULL && chunk->next_chunk != NULL && chunk->used == 0)
			return (head);
		head = head->next_zone;
	}
	return (NULL);
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
		next = head->next_zone;
		prev->next_zone = next;
	}
	else
		g_slabs[index] = NULL;
	munmap(head, head->bytes_per_zone);
}

/*
*	change below so.....
*	first the zone is found and address returned
	then, the chunk pointer is found and returned
	set chunk->used to 0
	then check the zone if empty
		if empty, munmap the zone
*/


void	ft_free(void *ptr)
{
	int		index;
	t_chunk	*result;
	int		before;
	t_head	*head;

	index = 0;
	if (ptr == NULL)
		return ;
	result = find_ptr(ptr, &index);
	before = result->used;
	result->used = 0;
	if (result != NULL && (head = empty_zone()) != NULL)
		deallocate_zone(index, head);
	//printf("\t\t\t\tINDEX: %d\tresult: %p\tbefore: %d\tafter: %d\n", index, &result, before, result->used);
}
