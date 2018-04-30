/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libdodo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 11:46:00 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:15:22 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBDODO_H
# define LIBDODO_H

# include <stdlib.h>
# include <unistd.h>

typedef struct			s_list2
{
	void				*content;
	size_t				content_size;
	struct s_list2		*next;
}						t_list2;

typedef unsigned int	t_int;

void					ft_putstr2(const char *s);
long					ft_atol2(const char *str);
double					ft_atod2(const char *str);
char					*ft_strncpy2(char *dst, const char *src, size_t n);
int						ft_strcmp2(const char *s1, const char *s2);
void					ft_putendl2(char const *s);
void					ft_putendl_fd2(char const *s, int fd);
void					ft_lstaddend2(t_list2 **alst, t_list2 *new);

#endif
