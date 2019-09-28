/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn_fractal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:19:35 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 23:19:36 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_tricorn_fractal(t_data *data, int x, int y, int i)
{
	t_set set;

	set.f.re = (data->max.re - data->min.re) / (IMG_W - 1.0);
	set.f.im = (data->max.im - data->min.im) / (IMG_H - 1.0);
	set.c.re = data->min.re + x * set.f.re;
	set.c.im = data->max.im - y * set.f.im;
	set_complex(&(set.new_z), set.c.re, set.c.im);
	count_points(data, &set);
	data->iter[i] = set.iter;
	color_point(data, x, y, i);
}

void	draw_menu_tricorn_fractal(t_data *data, int i)
{
	int		y;
	int		x;
	t_set	set;

	y = -1;
	while (++y < data->small_img[i].h)
	{
		x = -1;
		while (++x < data->small_img[i].w)
		{
			set.f.re = (data->small_img[i].m_max.re -
				data->small_img[i].m_min.re) / (data->small_img[i].w - 1.0);
			set.f.im = (data->small_img[i].m_max.im -
				data->small_img[i].m_min.im) / (data->small_img[i].h - 1.0);
			set.c.re = data->small_img[i].m_min.re + x * set.f.re;
			set.c.im = data->small_img[i].m_max.im - y * set.f.im;
			set_complex(&(set.new_z), set.c.re, set.c.im);
			count_menu_points(data, &set, i);
			data->small_img[i].iter = set.iter_double;
			color_menu_point(data, x, y, i);
		}
	}
}
