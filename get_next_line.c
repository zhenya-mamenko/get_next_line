/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 11:18:13 by emamenko          #+#    #+#             */
/*   Updated: 2019/02/18 22:30:30 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static int	prepare(const int fd, char **line, char **buf)
{
	if (fd < 3)
		return (-1);
	if (line == NULL)
		return (-1);
	*line = ft_strnew(0);
	if (*line == NULL)
		return (-1);
	*buf = ft_strnew(BUFF_SIZE);
	if (buf == NULL)
	{
		ft_strdel(line);
		return (-1);
	}
	return (0);
}

static int	init_fpt(t_list **fpt, const int fd)
{
	t_fpt	*d;

	d = (t_fpt *)malloc(sizeof(t_fpt));
	if (d == NULL)
		return (-1);
	d->fd = fd;
	d->buf = ft_strnew(BUFF_SIZE);
	if (d->buf == NULL)
		return (-1);
	*fpt = ft_lstnew(d, sizeof(t_fpt));
	if (*fpt == NULL)
	{
		free(d->buf);
		return (-1);
	}
	return (1);
}

static int	get_pd(t_list **cpd, t_list *beg, const int fd, char *buf)
{
	t_list	*el;
	t_fpt	*d;

	el = beg;
	while (1)
	{
		d = (t_fpt *)el->content;
		if (d->fd == fd)
		{
			if (d->buf == NULL)
				return (0);
			ft_strcpy(buf, d->buf);
			*cpd = el;
			return (1);
		}
		if (el->next != NULL)
			el = el->next;
		else
			break ;
	}
	if (init_fpt(cpd, fd) == 1)
		el->next = *cpd;
	else
		return (-1);
	return (1);
}

static int	finish_read(char **line, char *s, t_fpt *d)
{
	int		i;
	int		l;
	char	*sub;

	i = ft_strchri(s, '\n');
	if (i == -1)
		ft_strsetdel(line, ft_strjoin(*line, s));
	else
	{
		if (i != 0)
		{
			sub = ft_strsub(s, 0, i);
			ft_strsetdel(line, ft_strjoin(*line, sub));
			ft_strdel(&sub);
		}
		l = (int)ft_strlen(s);
		if ((i + 1) != l)
		{
			ft_strcpy(d->buf, s + i + 1);
			d->buf[l - i - 1] = '\0';
		}
	}
	s[0] = '\0';
	return (i == -1 ? 0 : 1);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*fpt = NULL;
	t_list			*d;
	char			*buf;
	ssize_t			c;
	ssize_t			i;

	if (prepare(fd, line, &buf) == -1)
		return (-1);
	if ((i = (fpt == NULL) ? init_fpt(&d, fd) : get_pd(&d, fpt, fd, buf)) < 1)
		return (i);
	fpt = (fpt == NULL) ? d : fpt;
	while (1)
	{
		i = ft_strlen(buf);
		if (ft_strchr(buf, '\n') == NULL)
		{
			c = read(fd, buf + i, BUFF_SIZE - i);
			if (c <= 0)
				return (c);
			buf[c + i] = (c + i < BUFF_SIZE) ? '\0' : buf[c + i];
		}
		if (finish_read(line, buf, (t_fpt *)(d->content)) == 1)
			return (1);
	}
}
