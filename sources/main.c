/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 13:05:06 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/10 13:05:07 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include "../libft/libft.h"
#include "../includes/ft_malloc.h"

/*
*	#include <sys/mman.h>
*	int munmap(void *addr, size_t len);
*	http://pubs.opengroup.org/onlinepubs/009696799/functions/munmap.html
*
*	include <sys/mman.h>
*	void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset):
*	http://man7.org/linux/man-pages/man2/mmap.2.html
*
*	#include <unistd.h>
*	int getpagesize(void);
*	http://man7.org/linux/man-pages/man2/getpagesize.2.html
*
*	#include <sys/time.h> <sys/resource.h>
*	int getrlimit(int resource, struct rlimit *rlim);
*	http://man7.org/linux/man-pages/man2/getrlimit.2.html
*/

int		main(int argc, char **argv)
{
	int count;
	(void)argc;
//	void	*shit;
	int		i;
	int		random;
	time_t	t;
	int		number[5];
	void	*ptr[5];

	i = 0;
	count = ft_atoi(argv[1]);
	srand((unsigned) time(&t));
	while (i < 5)
	{
		number[i] = (rand() % 5);
		printf("%d, ", number[i]);
		ptr[i] = malloc(number[i]);
//		printf("MALOC\tADDR: %p\tsize: %d\n", ptr[i], i);
		i++;
	}
//	show_alloc_mem(DETAIL);
	i = 0;
	while (i < 5)
	{
		free(ptr[i]);
//		printf("FREE\t\tADDR:%p\n", ptr[i]);
		i++;
	}
	show_alloc_mem(DETAIL);
	return (0);
}
