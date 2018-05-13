/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:09:44 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 11:58:52 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_strcmp2(const char *s1, const char *s2)
{
	return ((*s1 == *s2 && *s1) ? ft_strcmp2(s1 + 1, s2 + 1) : *s1 - *s2);
}
