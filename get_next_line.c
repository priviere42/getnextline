/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 12:43:11 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/25 11:02:31 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int			check_newline(char **rest, char **line)
{
	char	*tmp;

	if (!(tmp = ft_strchr(*rest, '\n')))
		return (0);
	*tmp = '\0';
	*line = ft_strdup(*rest, rest);
	*rest = ft_strdup(&tmp[0] + 1, rest);
	return (1);
}

int			ft_read_fd(int fd, char *buf, char **rest, char **line)
{
	int		ret;
	char	*tmp;

	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (*rest)
		{
			tmp = *rest;
			*rest = ft_strjoin(tmp, buf);
		}
		else
			*rest = ft_strdup(buf, rest);
		free(tmp);
		tmp = NULL;
		if (check_newline(&*rest, line))
		{
			free(buf);
			return (1);
		}
	}
	free(buf);
	return (0);
}

int ft_call_reading(int ret, char **rest, char **line)
{
	if (*rest && (ret > 0 || **rest == '\0' || *rest == NULL))
	{
		if (!ret && *line)
		{
			*line = ft_strdup("", rest);
			return (0);
		}
		return (1);
	}
	if (!*rest)
	{
		*line = ft_strdup("", rest);
		return (0);
	}
	*line = *rest;
	*rest = NULL;
	return (0);
}


int			get_next_line(int fd, char **line)
{
	static char		*rest = NULL;
	char			*buf;
	int				ret;
	int 			value;

	if (!line || fd < 0 || read(fd, rest, 0) < 0)
	{
		*line = ft_strdup("", &rest);
		return (-1);
	}
	if (!rest)
	{
		rest = ft_strdup("", &rest);
		*line = ft_strdup("", &rest);
		free(*line);
	}
	if (rest)
        if (check_newline(&rest, line))
			return (1);
    if (!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
        return (-1);
	value = 0;
	while (value < BUFFER_SIZE)
		buf[value++] = '\0';
	ret = ft_read_fd(fd, buf, &rest, line);
	value = ft_call_reading(ret, &rest, line);
	return (value);
}

#include <sys/stat.h>
#include <fcntl.h>

void		ft_putendl(char const *s)
{
	if (s != NULL)
	{
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
	}
}
	
int			main()
{
    int fd;	
	int get = 1;
	int i = 4;
    char *dest = NULL;

    fd = open("file", O_RDONLY);
	while (i > 0)
	{
		get = get_next_line(fd, &dest);
		printf("Retour de fonction : %d\n", get);
	    ft_putendl(dest);
		free(dest);
		i--;
	}
	close(fd);
}
