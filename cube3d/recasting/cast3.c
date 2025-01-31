/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-31 00:19:52 by kaafkhar          #+#    #+#             */
/*   Updated: 2025-01-31 00:19:52 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	calculate_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

float	get_distance(t_point player, t_point hit)
{
	return (calculate_distance(player.x, player.y, hit.x, hit.y));
}

float	choose_distance(t_point player, t_hit hit)
{
	if (hit.found)
		return (get_distance(player, hit.point));
	return (FLT_MAX);
}

void	set_ray_hit(t_rays *ray, float distance, t_point hit, int hit_ver)
{
	ray->distance = distance;
	ray->wallhitx = hit.x;
	ray->wallhity = hit.y;
	ray->hit_ver = hit_ver;
}

void	choose_closest_hit(t_rays *ray, t_point player, t_hit horz, t_hit vert)
{
	float	horz_distance;
	float	vert_distance;

	horz_distance = choose_distance(player, horz);
	vert_distance = choose_distance(player, vert);
	if (horz_distance < vert_distance)
		set_ray_hit(ray, horz_distance, horz.point, 0);
	else
		set_ray_hit(ray, vert_distance, vert.point, 1);
}
