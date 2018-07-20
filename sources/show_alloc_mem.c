/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 17:10:12 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/19 17:10:13 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/ft_malloc.h"

/*
 * Goes thru each byte
 * if index modulo 16 is == 0, and if its == to 0, then print the ascii char
 * else we are done reading all 16 bytes for the line
 * Now the hex code for the specific characters
 * And store a printable ASCII character for later.
*/

void		hexdumpcont(int i, unsigned char *buff, unsigned char *pc)
{
	if ((i % 16) == 0)
	{
		if (i != 0)
			printf("  %s\n", buff);
		printf("  %04x ", i);
	}
	printf(" %02x", pc[i]);
	if ((pc[i] < 0x20) || (pc[i] > 0x7e))
		buff[i % 16] = '.';
	else
		buff[i % 16] = pc[i];
	buff[(i % 16) + 1] = '\0';
}

/*
 *desc is to be printed description
 *then loop thru each byte
 *Pad out last line if not exactly 16 characters.
 *And print the final ASCII bit.
*/

void		hexdump(char *desc, void *addr, int len)
{
	int				i;
	unsigned char	buff[17];
	unsigned char	*pc;

	i = 0;
	pc = (unsigned char*)addr;
	if (desc != NULL)
		printf("%s:\n", desc);
	while (i < len)
		hexdumpcont(i++, buff, pc);
	while ((i++ % 16) != 0)
		printf("   ");
	printf("  %s\n", buff);
}

void	dump(void)
{
	int		index;
	t_head	*head;

	index = 0;
	while (index <= INDEX_COUNT)
	{
		printf("g_slabs[%d]=%p\n", index, g_slabs[index]);
		head = g_slabs[index];
		while (head != NULL)
		{
			hexdump("\0", head, (int)head->bytes_per_zone);
			head = head->next_zone;
		}
		index++;
	}
}

void	print_head(t_head *head)
{
	printf("\tt_head:%p\n", &head);
	printf("\tpage_size:\t%zu\n", head->page_size);
	printf("\tbytes_per_zone\t%zu\n", head->bytes_per_zone);
	printf("\tmeta_start:\t%p\n", head->meta_start);
	printf("\tnext_zone:\t%p\n\n", head->next_zone);
}

void	print_chunk(t_chunk *chunk)
{
	printf("\t\tt_chunk:\t%p\n", chunk);
	printf("\t\tsize:\t%zu\n", chunk->size);
	printf("\t\tused:\t%d\n", chunk->used);
	printf("\t\tchunk_start:\t%p\n", chunk->chunk_start);
	printf("\t\tnext_chunk:\t%p\n\n", chunk->next_chunk);
}

void	detail_dump(void)
{
	int			index;
	t_head		*head;
	t_chunk		*chunk;

	index = 0;
	while (index < INDEX_COUNT)
	{
		printf("\ng_slabs[%d]:\n", index);
		head = g_slabs[index];
		while (head != NULL)
		{
			print_head(head);
			chunk = head->meta_start;
			while (chunk != NULL)
			{
				print_chunk(chunk);
				chunk = chunk->next_chunk;
			}
			head = head->next_zone;
		}
		index++;
	}
}

void	show_alloc_mem(int call)
{
	if (call == DUMP)
		dump();
	if (call == DETAIL)
		detail_dump();
}
