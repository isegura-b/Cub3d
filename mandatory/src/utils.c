/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:27:18 by isegura-          #+#    #+#             */
/*   Updated: 2025/08/17 15:27:20 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	ft_error(char *error_str)
{
	if (error_str)
		printf("Error : %s\n", error_str);
	exit(EXIT_FAILURE);
}

void	my_pixel_put(int x, int y, int color, t_data *img)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->info + offset) = color;
}

int	handle_exit(void *param)
{
	cleanup_data((t_data *)param);
	exit(0);
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;
	size_t	i;

	len = 0;
	while (s[len])
		len++;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		copy[i] = s[i];
		i++;
	}
	return (copy);
}

char	*ft_strdup_path(const char *s)
{
	size_t	len;
	char	*copy;
	size_t	i;

	len = 0;
	while (s[len] && s[len] != ' ' && s[len] != '\n' && s[len] != '\r')
		len++;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}
