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

#include "../includes/ft_malloc.h"
#include <time.h>

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
//	int		random;
	time_t	t;
	int		number[12] = {1, 5, 7, 7, 1, 8, 7, 6, 5, 6, 6, 2};
	void	*ptr[12];

	i = 0;
	count = ft_atoi(argv[1]);
	srand((unsigned) time(&t));
	while (i < 12)
	{
//		random = (rand() % 150);
//		printf("%d, ", random);
		ptr[i] = ft_malloc(number[i]);
		//printf("ADDR: %p\tsize: %d\n", shit, random);
		i++;
	}
	i = 0;
	while (i < 12)
	{
		free(ptr[i]);
		i++;
	}
	return (0);
}
