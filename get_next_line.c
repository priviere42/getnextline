/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 12:43:11 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/29 17:08:01 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int			check_newline(char **rest, char **line)
{
	char	*tmp;

	if (!(ft_strchr(*rest, '\n')))
		return (0);
	tmp = ft_strdup(ft_strchr(*rest, '\n'));
	*line = ft_strdupn(*rest);
	free(*rest);
	*rest = ft_strdup(&tmp[1]);
	free(tmp);
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
			tmp = ft_strdup(*rest);
			free(*rest);
			*rest = ft_strjoin(tmp, buf);
			free(tmp);
		}
		else
			*rest = ft_strdup(buf);
		if (check_newline(&*rest, line))
			return (1);
	}
	return (0);
}

int ft_call_reading(int ret, char **rest, char **line)
{
	if (*rest && (ret > 0 || **rest == '\0' || *rest == NULL))
	{
		if (!ret && *line)
		{
			*line = ft_strdup("");
			free(*rest);
			*rest = NULL;
			return (0);
		}
		return (1);
	}
	if (!*rest)
	{
		*line = ft_strdup("");
		free(*rest);
		*rest = NULL;
		return (0);
	}
	*line = *rest;
	free(*rest);
	*rest = NULL;
	return (0);
}


int			get_next_line(int fd, char **line)
{
	static char		*rest = NULL;
	char			*buf;
	int				ret;
	int 			value;

	if (!line || fd < 0 || read(fd, rest, 0) < 0 || BUFFER_SIZE < 1)
	{
		*line = ft_strdup("");
		return (-1);
	}
	if (!rest)
	{
		rest = ft_strdup("");
		*line = ft_strdup("");
		free(*line);
	}
    if (check_newline(&rest, line))
		return (1);
    if (!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1)))
        return (-1);
	value = 0;
	ret = ft_read_fd(fd, buf, &rest, line);
	free(buf);
	value = ft_call_reading(ret, &rest, line);
	return (value);
}

// #include <sys/stat.h>
// #include <fcntl.h>

// void		ft_putendl(char const *s)
// {
// 	if (s != NULL)
// 	{
// 		write(1, s, ft_strlen(s));
// 		write(1, "\n", 1);
// 	}
// }
	
// int			main()
// {
//     int fd;	
// 	int get = 1;
// 	int i = 8;
//     char *dest = NULL;

//     fd = open("file", O_RDONLY);
// 	while (i > 0)
// 	{
// 		get = get_next_line(fd, &dest);
// 		printf("Retour de fonction : %d\n", get);
// 	    ft_putendl(dest);
// 		free(dest);
// 		i--;
// 	}
// 	close(fd);
// }
