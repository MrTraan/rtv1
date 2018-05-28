/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:25:27 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/24 15:16:58 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

int			str_is_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\n')
		return (1);
	return (0);
}

char		*parser_put_error(char *message)
{
	ft_putstr_fd("RTv1 scene file error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

char		*parser_put_invalid_instr(char *data)
{
	char	*eol;

	eol = ft_strchr(data, '\n');
	ft_putstr_fd("RTv1 scene file error: Invalid instruction: \n", 2);
	if (eol)
		write(2, data, eol - data);
	else
		write(2, data, ft_strlen(data));
	ft_putstr_fd("\n", 2);
	exit(1);
	return (NULL);
}

char		*read_error(char *error, char err, char *contents)
{
	if (contents)
		free(contents);
	*error = err;
	return (NULL);
}
