/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:05:22 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/26 20:36:50 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	is_empty_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_num(const char *str, size_t *i)
{
	int	num;

	num = 0;
	if (!(str[*i] >= '0' && str[*i] <= '9'))
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		num = num * 10 + (str[*i] - '0');
		(*i)++;
	}
	if (num < 0 || num > 255)
		return (-1);
	return (num);
}

int	is_valid_rgb(const char *str)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		if (parse_num(str, &i) == -1)
			return (0);
		j++;
		if (j < 3 && str[i++] != ',')
			return (0);
	}
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r')
		i++;
	return (str[i] == '\0');
}

int	color_tests(char *line, int i, int f, int c)
{
	if (f > 1 || c > 1)
		return (ft_error("Duplicate floor color"), 1);
	if (line[i] == '\0')
		return (ft_error("Not color found"), 1);
	if (!is_valid_rgb(line + i))
		return (ft_error("Colors must be in R,G,B format (0-255)"), 1);
	return (0);
}

int	is_color(char *line)
{
	size_t		i;
	static int	f;
	static int	c;

	i = 1;
	while (line[i] == ' ')
		i++;
	if (line[0] == 'F')
	{
		f++;
		if (color_tests(line, i, f, c))
			return (-1);
		return (1);
	}
	else if (line[0] == 'C')
	{
		c++;
		if (color_tests(line, i, f, c))
			return (-1);
		return (1);
	}
	return (0);
}
