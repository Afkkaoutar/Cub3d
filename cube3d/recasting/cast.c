/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-11 23:13:52 by kaafkhar          #+#    #+#             */
/*   Updated: 2025-01-11 23:13:52 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	finalize_ray(t_rays *ray, float ray_angle, float player_angle)
{
	ray->ray_angle = ray_angle;
	ray->distance *= cos(player_angle - ray_angle);
}

float	normal_angle(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	initialize_and_find_hits(t_mlx *mlx, t_rays *ray, float ray_angle, float *hits)
{
	int	found_horz;
	int	found_vert;

	initialize_ray(ray, ray_angle);
	hits[0] = 0;
	hits[1] = 0;
	hits[2] = 0;
	hits[3] = 0;
	found_horz = 0;
	found_vert = 0;
	find_horizontal_hit(mlx, ray, ray_angle, &hits[0], &hits[1], &found_horz);
	find_vertical_hit(mlx, ray, ray_angle, &hits[2], &hits[3], &found_vert);
	hits[4] = found_horz;
	hits[5] = found_vert;
}

void	process_ray(t_mlx *mlx, int strip_id, float ray_angle)
{
	t_rays	*ray;
	t_hit	horz;
	t_hit	vert;
	t_point	player;
	float	hits[6];

	ray = &mlx->rays[strip_id];
	initialize_and_find_hits(mlx, ray, ray_angle, hits);
	player.x = mlx->player_x;
	player.y = mlx->player_y;
	horz.point.x = hits[0];
	horz.point.y = hits[1];
	horz.found = (int)hits[4];
	vert.point.x = hits[2];
	vert.point.y = hits[3];
	vert.found = (int)hits[5];
	choose_closest_hit(ray, player, horz, vert);
	finalize_ray(ray, ray_angle, mlx->player_angle);
}

void	cast_rays(t_mlx *mlx)
{
	float	ray_angle;
	int		strip_id;

	strip_id = 0;
	ray_angle = mlx->player_angle - (FOV_ANGLE / 2);
	while (strip_id < NUM_RAYS)
	{
		ray_angle = normal_angle(ray_angle);
		process_ray(mlx, strip_id, ray_angle);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		strip_id++;
	}
}
