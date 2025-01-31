/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 00:25:37 by kaafkhar          #+#    #+#             */
/*   Updated: 2025-01-31 00:25:37 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calculate_wall_params(t_mlx *mlx, int strip_id, int *top, int *bottom, float *height)
{
	float	perp_dist;

	perp_dist = mlx->rays[strip_id].distance;
	if (perp_dist < 1)
		perp_dist = 1;
	*height = (mlx->range_ve_size * HEIGHT) / perp_dist;
	if (*height > HEIGHT * 3)
		*height = HEIGHT * 3;
	*top = (HEIGHT / 2) - (*height / 2);
	if (*top < 0)
		*top = 0;
	*bottom = (HEIGHT / 2) + (*height / 2);
	if (*bottom > HEIGHT)
		*bottom = HEIGHT;
}

void	draw_wall_strip(t_mlx *mlx, int strip_id, int top, int bottom, float height)
{
	int	y;
    (void)height;

	y = 0;
	while (y < top)
		my_mlx_pixel_put(mlx, strip_id, y++, 0xff00000);
	y = top;
	while (y < bottom)
		my_mlx_pixel_put(mlx, strip_id, y++, mlx->addr[1]);
	y = bottom;
	while (y < HEIGHT)
		my_mlx_pixel_put(mlx, strip_id, y++, 0x654321);
}

void	draw_walls(t_mlx *mlx)
{
	int		strip_id;
	int		wall_top;
	int		wall_bottom;
	float	wall_height;

	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		calculate_wall_params(mlx, strip_id, &wall_top, &wall_bottom, &wall_height);
		draw_wall_strip(mlx, strip_id, wall_top, wall_bottom, wall_height);
		strip_id++;
	}
}
