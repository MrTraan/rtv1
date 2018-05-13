/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:55:01 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:05:34 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	ft_putendl_fd2(char const *s, int fd)
{
	int		i;
	char	c;

	if (s != NULL && fd >= 0)
	{
		i = 0;
		while (s[i])
			i++;
		write(fd, s, i);
		c = '\n';
		write(fd, &c, 1);
	}
}
