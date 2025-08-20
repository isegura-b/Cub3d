#include "../inc/cub.h"

static char	*ft_free(char *buffer, char *tmp)
{
	char	*save;

	save = ft_strjoin(buffer, tmp);
	if (!save)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (save);
}

static char	*ft_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_read(int fd, char *buffer)
{
	char		*tmp;
	ssize_t	r;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	r = 1;
	while (r > 0 && !ft_strchr(buffer, '\n'))
	{
		r = read(fd, tmp, BUFFER_SIZE);
		if (r == -1)
		{
			free(tmp);
			free(buffer);
			return (NULL);
		}
		tmp[r] = '\0';
		buffer = ft_free(buffer, tmp);
		if (r == 0)
			break ;
	}
	free(tmp);
	return (buffer);
}

static char	*res_buffer(char *buffer)
{
	char		*res;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	if (buffer[i] == '\n')
		i++;
	res = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!res)
		return (NULL);
	j = 0;
	while (buffer[i])
	{
		res[j++] = buffer[i++];
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483648)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = res_buffer(buffer);
	if (!line || *line == '\0')
	{
		free(line);
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (line);
}