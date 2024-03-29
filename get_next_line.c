/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 12:43:11 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 18:04:21 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

int			free_all(char **rest, char *tmp, char *buf)
{
	if (*rest)
		free(*rest);
	if (tmp)
		free(tmp);
	if (buf)
		free(buf);
	return (-1);
}

int			check_newline(char **rest, char **line, char *buf)
{
	char	*tmp;

	if (!(ft_strchr(*rest, '\n')))
		return (0);
	if (!(tmp = ft_strdup(ft_strchr(*rest, '\n'))))
		return (free_all(rest, tmp, buf));
	if (!(*line = ft_strdupn(*rest)))
		return (free_all(rest, tmp, buf));
	free(*rest);
	if (!(*rest = ft_strdup(&tmp[1])))
		return (free_all(rest, tmp, buf));
	free(tmp);
	free(buf);
	return (1);
}

int			ft_read_fd(int fd, char *buf, char **rest, char **line)
{
	int		ret;
	char	*tmp;

	if (!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (free_all(rest, NULL, buf));
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (*rest)
		{
			if (!(tmp = ft_strdup(*rest)))
				return (free_all(rest, tmp, buf));
			free(*rest);
			if (!(*rest = ft_strjoin(tmp, buf)))
				return (free_all(rest, tmp, buf));
			free(tmp);
		}
		else if (!(*rest = ft_strdup(buf)))
			return (free_all(rest, tmp, buf));
		if ((ret = check_newline(rest, line, buf)))
			return ((ret == -1) ? ret : 1);
	}
	free(buf);
	return (0);
}

int			ft_call_reading(int ret, char **rest, char **line)
{
	if (*rest && (ret > 0 || **rest == '\0'))
	{
		if (!ret)
		{
			if (!(*line = ft_strdup("")))
				return (free_all(rest, NULL, NULL));
			free(*rest);
			*rest = NULL;
			return (0);
		}
		return (1);
	}
	if (!*rest)
	{
		if (!(*line = ft_strdup("")))
			return (free_all(rest, NULL, NULL));
		free(*rest);
		*rest = NULL;
		return (0);
	}
	if (!(*line = ft_strdup(*rest)))
		return (free_all(rest, NULL, NULL));
	free(*rest);
	*rest = NULL;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char		*rest = NULL;
	char			*buf;
	int				ret;
	int				value;

	buf = NULL;
	if (!line || fd < 0 || read(fd, rest, 0) < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!rest)
		if (!(rest = ft_strdup("")))
			return (free_all(&rest, NULL, NULL));
	if ((ret = check_newline(&rest, line, buf)))
		return ((ret == -1) ? ret : 1);
	ret = ft_read_fd(fd, buf, &rest, line);
	value = ft_call_reading(ret, &rest, line);
	return (value);
}
