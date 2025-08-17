/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:59:54 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/17 15:59:57 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

static char	*alloc_copy_row(const char *src, int width, int row)
{
	char	*dst;
	int		j;

	dst = malloc(width + 1);
	if (!dst)
		return (NULL);
	j = 0;
	while (j < width && src[j])
	{
		if (is_invalid_char(src[j]))
		{
			printf("Invalid char '%c' at row %d col %d\n", src[j], row, j);
			free(dst);
			return (NULL);
		}
		dst[j] = src[j];
		j++;
	}
	while (j < width)
		dst[j++] = ' ';
	dst[j] = '\0';
	return (dst);
}

char	**copy_map(char **map, int height, int width)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = alloc_copy_row(map[i], width, i);
		if (!copy[i])
		{
			free_map(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}
