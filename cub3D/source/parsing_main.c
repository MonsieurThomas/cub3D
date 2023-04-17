/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romainthomas <romainthomas@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:42:21 by romainthoma       #+#    #+#             */
/*   Updated: 2023/04/17 22:51:35 by romainthoma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	check_openning_texture(t_data *data)
{
	data->texture[0].img = mlx_xpm_file_to_image \
	(data->mlx, data->no, &data->imgsiz, &data->imgsiz);
	data->texture[1].img = mlx_xpm_file_to_image \
	(data->mlx, data->so, &data->imgsiz, &data->imgsiz);
	data->texture[2].img = mlx_xpm_file_to_image \
	(data->mlx, data->we, &data->imgsiz, &data->imgsiz);
	data->texture[3].img = mlx_xpm_file_to_image \
	(data->mlx, data->ea, &data->imgsiz, &data->imgsiz);
	if (data->texture[0].img == NULL || data->texture[1].img == NULL \
	|| data->texture[2].img == NULL || data->texture[3].img == NULL)
		return (ft_print_error("Error\nProbleme de textures", NULL));
	return (0);
}

int	parsing_main_loop(t_data *data)
{
	if (!ft_strncmp(data->map[data->i], "NO ", 3) || \
	!ft_strncmp(data->map[data->i], "SO ", 3) || \
	!ft_strncmp(data->map[data->i], "WE ", 3) || \
	!ft_strncmp(data->map[data->i], "EA ", 3))
		data->error += put_wall_in_struct(data, data->i);
	else if (!ft_strncmp(data->map[data->i], "F ", 2) || \
	!ft_strncmp(data->map[data->i], "C ", 2))
		data->error += get_color(data, data->i);
	else if (data->wall == 4 && data->color_c && data->color_f)
	{
		if (is_beginning_of_map(data, data->i))
		{
			if (create_new_map(data, data->i))
				return (1);
			data->parsing_main_loop += 1 ;
		}
	}
	if (data->error)
		return (1);
	return (0);
}

int	parsing_main(t_data *data)
{
	data->i = 0;
	while (data->map[data->i])
	{
		if (parsing_main_loop(data))
			return (1);
		if (data->parsing_main_loop)
			break ;
		(data->i)++;
	}
	if (!data->is_map)
		return (ft_print_error("Error\nProbleme de carteee", NULL));
	if (data->wall != 4 || !data->color_c || !data->color_f)
		return (ft_print_error("Error\nProbleme de textures", NULL));
	if (check_openning_texture(data))
		return (1);
	return (0);
}
