#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_strcpy(char *dst, char *src);
char	*ft_strchr(char *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t len);

#endif
