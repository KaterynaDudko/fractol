/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:19:10 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 23:19:12 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static int	is_in_mandelbrot_set(double x, double y)
{
	double sqrt_x;
	double sqrt_y;
	double z;
	double q;
	double temp;

	temp = (x - 1.0 / 4.0);
	sqrt_x = temp * temp;
	sqrt_y = y * y;
	q = sqrt_x + sqrt_y;
	z = q * (q + temp);
	temp = sqrt_y / 4.0;
	if (z <= temp)
		return (1);
	return (0);
}

void		draw_mandelbrot_set(t_data *data, int x, int y, int i)
{
	t_set set;

	set.f.re = (data->max.re - data->min.re) / (IMG_W - 1.0);
	set.f.im = (data->max.im - data->min.im) / (IMG_H - 1.0);
	set.c.re = data->min.re + x * set.f.re;
	set.c.im = data->max.im - y * set.f.im;
	set_complex(&(set.new_z), 0.0, 0.0);
	if (is_in_mandelbrot_set(set.c.re, set.c.im))
		set.iter = data->params->max_iter;
	else
		count_points(data, &set);
	data->iter[i] = set.iter_double;
	color_point(data, x, y, i);
}

void		draw_menu_mandelbrot_set(t_data *data, int i)
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
			set_complex(&(set.new_z), 0, 0);
			if (is_in_mandelbrot_set(set.c.re, set.c.im))
				set.iter = data->params->max_iter;
			else
				count_menu_points(data, &set, i);
			data->small_img[i].iter = set.iter_double;
			color_menu_point(data, x, y, i);
		}
	}
}
