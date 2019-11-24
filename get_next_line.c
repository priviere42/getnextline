/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 12:43:11 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 16:24:12 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

//  Vérifier s'il y a un \n dans le buffer.
// si pas de \n dans le buff, on arrête la fonction et on return 0
// si on trouve un newline, stock en tampon le contenu à partir du \n.
// on fait une copie de tout le buffer dans line
// on remet dans le buffer le "reste" qui a été lu

int			check_newline(char **rest, char **line)
{
	char	*tmp = NULL;

    if (!(tmp = ft_strchr(*rest, '\n')))
        return (0);
    *tmp = '\0';
	*line = ft_strdup(*rest, rest);
	*rest = ft_strdup(&tmp[0] + 1, rest);
	return (1);
}

/*
Lire tout ce qu'il y a à lire avec le buffer. (comme avec ft_linenumber)
Checker s'il y a du reste (après le \n). 
Si oui, strjoin de ça avec ce qu'il y avait avant le \n.
Si pas de reste, on copie l'integralite du buffer dans "reste" pour pouvoir parser le fd.
On vérifie si il y a une newline dans notre buffer, si oui on sort de la boucle pour pouvoir rappeler gnl.
Si ret était > 0, c'est qu'on peut encore lire et on renvoie 1. Sinon, on return 0 pour indiquer qu'on n'a plus rien a lire.
*/
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
		{
			free(*rest);
			*rest = ft_strdup(buf, rest);
		}
		free(tmp);
		tmp = NULL;
		if (check_newline(&*rest, line))
		{
			free(buf);
            if (ret > 0)
                return (1);
            else
                return (0);
        }
	}
	free(buf);
    return (0);
}

/*
Checker s'il y a qqchose dans le reste (variable statique ?).
Si oui on vérifie qu'il y ait bien une newline. (avec check_newline au dessus)
sinon, on alloue la mémoire pour le buffer, et on lit le fichier.
Quand on a fini de lire le fichier, on check la valeur de ret.
 Si on a 1 ou -1, il faut return ça.
 Si ret est différent de 1 ou de -1, (donc = 0), c'est qu'on est à la fin du fd, donc on return 1.
 des appels successifs doivent lire tout le texte sur le fd (un appel = une ligne)
 */
int			get_next_line(int fd, char **line)
{
	static char		*rest;
	char			*buf;
	int				ret;

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
	if (fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	ret = ft_read_fd(fd, buf, &rest, line);
	if (rest && (ret > 0 || *rest == '\0' || rest == NULL))
	{
		if (!ret && *line)
		{
			*line = ft_strdup("", &rest);
	//		free(rest);
			return (0);
		}
		return (1);
	}
	// on rentre dans ce cas si le fichier est vide
	if (!rest)
	{
		rest = NULL;
		*line = ft_strdup("", &rest);
		return (0);
	}
	*line = rest;
	rest = NULL;
	return (0);
}

#include <sys/stat.h>
#include <fcntl.h>

void	ft_putendl(char const *s)
{
	if (s != NULL)
	{
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
	}
}
	
int main()
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