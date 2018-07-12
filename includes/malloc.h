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


#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/mman.h>
# include "../libft/libft.h"

# define PROT_ALL (PROT_READ | PROT_WRITE | PROT_EXEC)
# define FT_MAP_ANON (MAP_ANONYMOUS | MAP_PRIVATE | MAP_NOCACHE)
# define TINY_INDEX 0
# define SMALL_INDEX 1
# define LARGE_INDEX 2
# define MAX_ALLOCATIONS 200
# define SPACING 1			//this will be used for memory protection i.e. to cause seg faults.
# define TINY_ZONE	8
# define SMALL_ZONE 128

typedef struct	__attribute__((packed))	s_table
{
	size_t		len;
	char		used;
	void		*chunk_start;
	void		*next_meta;
	void		*next_zone;
}										t_table;

typedef struct __attribute((packed))	s_zone
{
	size_t	zone_size;
	void	*meta_start;
}										t_zone;

void		*g_slabs[3];

//void	free(void *ptr);
void	*malloc(size_t size);
//void	*realloc(void *ptr, size_t size);
//void	show_alloc_mem();

#endif
