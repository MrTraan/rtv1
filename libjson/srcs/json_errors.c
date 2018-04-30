/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:13:53 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 17:13:55 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjson.h"

void	malloc_error(void)
{
	write(2, "Could not allocate enough memory.\n", 34);
	exit(1);
}

void	wrong_format(void)
{
	write(2, "File format is invalid.\n", 24);
	exit(0);
}

void	no_colon(void)
{
	write(2, "No colon found beetween key and value.\n", 39);
	exit(0);
}
