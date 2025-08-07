#include "../inc/cub.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*spc;

	i = 0;
	spc = malloc(nmemb * size);
	if (!spc)
		return (NULL);
	while (i < nmemb * size)
	{
		spc[i] = 0;
		i++;
	}
	return (spc);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		s1_len;
	size_t		s2_len;
	char		*mem;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	mem = malloc(s1_len + s2_len + 1);
	if (!mem)
		return (NULL);
	while (i < s1_len)
	{
		mem[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		mem[i] = s2[i - s1_len];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	cc;

	i = 0;
	cc = (char)c;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}
