/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:05:16 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/10 13:05:17 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include "../libft/libft.h"

# define PROT_ALL (PROT_READ | PROT_WRITE | PROT_EXEC)
# define FT_MAP_ANON (MAP_ANONYMOUS | MAP_PRIVATE | MAP_NOCACHE)
# define TINY_INDEX		0
# define SMALL_INDEX	1
# define LARGE_INDEX	2
# define MAX_ALLOCATIONS	300
# define TINY_ZONE		8
# define SMALL_ZONE		128
# define SAFEZONE		1
# define INDEX_COUNT	3
# define DUMP			1
# define DETAIL			2

typedef struct	__attribute__((packed))	s_chunk
{
	size_t		size;
	uint8_t		used;
	void		*chunk_start;
	void		*next_chunk;
}										t_chunk;

typedef struct __attribute__((packed))	s_head
{
	size_t		page_size;
	size_t		bytes_per_zone;
	void		*meta_start;
	void		*next_zone;
}										t_head;

extern void		*g_slabs[INDEX_COUNT];

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
int			main(int argc, char **argv);
t_head		*find_zone(void *ptr, int *index);
t_chunk		*find_chunk(t_head *head, void *ptr);
void		show_alloc_mem(int call);




#endif
