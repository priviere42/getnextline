/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 12:54:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/29 17:20:18 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strdupn(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		get_next_line(int fd, char **line);

#endif
