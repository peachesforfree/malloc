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



void	*find_ptr(void *ptr)
{
	int		i;

	while (i < INDEX_COUNT)
}

void	ft_free(void *ptr)
{
	void	*result;

	if (error_handle(ptr))
		return (NULL);
	result = find_ptr(ptr);
}
