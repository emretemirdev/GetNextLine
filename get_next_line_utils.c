#include "get_next_line.h"


int	ft_strcpy(char *dst, char *src)
{
	int	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}

char	*ft_strchr(char *s, char c)
{
	if (!s)
		return (0);
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (s);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	if (dst != src)
		while (len-- > 0)
			((char *)dst)[len] = ((char *)src)[len];
	return (dst);
}
