/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:58:32 by asebrani          #+#    #+#             */
/*   Updated: 2025/03/24 16:09:11 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int	get_texture_color(t_texture *texture, int x, int y)
{
	int				position;
	unsigned char	*ptr;

	position = (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	ptr = (unsigned char *)texture->addr;
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	return ((unsigned int)ptr[position + 3] << 24
		| (unsigned int)ptr[position + 2] << 16
		| (unsigned int)ptr[position + 1] << 8
		| (unsigned int)ptr[position] << 0);
}

int	init_texture(void *mlx, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (0);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(mlx, texture->img);
		return (0);
	}
	return (1);
}

void	set_textures(t_map *map, t_mlx *mlx)
{
	init_texture(mlx, &mlx->texs.north, map->no_texts);
	init_texture(mlx, &mlx->texs.east, map->ea_texts);
	init_texture(mlx, &mlx->texs.south, map->so_texts);
	init_texture(mlx, &mlx->texs.west, map->we_texts);
	init_texture(mlx, &mlx->weapon.frames[0], "texture/001.xpm");
	init_texture(mlx, &mlx->weapon.frames[1], "texture/002.xpm");
	init_texture(mlx, &mlx->weapon.frames[2], "texture/003.xpm");
	init_texture(mlx, &mlx->weapon.frames[3], "texture/004.xpm");
}
