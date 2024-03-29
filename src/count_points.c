/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:22:29 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 23:22:30 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int		is_in_mandelbrot_set(double x, double y)
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

void	count_points(t_data *data, t_set *set)
{
	double temp;

	set->iter = 0;
	set_complex(&(set->z_sqrt),
		set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
	while (set->iter < data->params->max_iter)
	{
		if (data->type == burning_ship)
			set_complex(&(set->old_z), fabs(set->new_z.re),
										fabs(set->new_z.im) * -1.0);
		else
			set_complex(&(set->old_z), set->new_z.re, set->new_z.im);
		temp = set->z_sqrt.re - set->z_sqrt.im;
		set->new_z.re = temp + set->c.re;
		temp = set->old_z.re + set->old_z.re;
		temp = (data->type == tricorn) ? -temp : temp;
		set->new_z.im = temp * set->old_z.im + set->c.im;
		set_complex(&(set->z_sqrt),
			set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
		temp = set->z_sqrt.re + set->z_sqrt.im;
		set->iter++;
		if (temp > 4)
			break ;
	}
}

void	count_menu_points(t_data *data, t_set *set, int i)
{
	double temp;

	set->iter = 0;
	set_complex(&(set->z_sqrt),
		set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
	while (set->iter < SP_MAX_ITER)
	{
		if (data->img[i].type == burning_ship)
			set_complex(&(set->old_z), fabs(set->new_z.re),
										fabs(set->new_z.im) * -1.0);
		else
			set_complex(&(set->old_z), set->new_z.re, set->new_z.im);
		temp = set->z_sqrt.re - set->z_sqrt.im;
		set->new_z.re = temp + set->c.re;
		temp = set->old_z.re + set->old_z.re;
		temp = (data->img[i].type == tricorn) ? -temp : temp;
		set->new_z.im = temp * set->old_z.im + set->c.im;
		set_complex(&(set->z_sqrt),
			set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
		temp = set->z_sqrt.re + set->z_sqrt.im;
		set->iter++;
		if (temp > 4)
			break ;
	}
}
