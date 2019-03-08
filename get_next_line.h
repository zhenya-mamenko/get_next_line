/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 11:18:24 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/07 19:56:14 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1000

typedef struct	s_fpt
{
	int			fd;
	char		*buf;
}				t_fpt;

int				get_next_line(const int fd, char **line);

#endif
