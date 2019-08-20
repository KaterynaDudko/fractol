/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 19:40:53 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/20 19:40:55 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/fractol.h"

// static int	get_light(int start, int end, double percentage)
// {
// 	return ((int)((1 - percentage) * start * percentage * end));
// }

static int	get_color_value(int iter, int max)
{
	t_color	color;
	double	percent;

	if (iter == max)
		return (BLACK);
	percent = (double)iter / (double)max;
	color.r = (int)(9 * (1 - percent) * pow(percent, 3) * 255);
	color.g = (int)(15 * pow((1 - percent), 2) * pow(percent, 2) * 255);
	color.b = (int)(8.5 * pow((1 - percent), 3) * percent * 255);
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void		set_color_to_point(t_data *data, int x, int y)
{
	int	i;
	int	color;

	color = get_color_value(data->iter, data->max_iter);
	x = (x > 0) ? x : -x;
	y = (y > 0) ? y : -y;
	if (x < WIDTH && y < HEIGHT)
	{
		i = (x * data->bpp / 8) + (y * data->size_line);
		data->img_buffer[i] = color;
		data->img_buffer[++i] = color >> 8;
		data->img_buffer[++i] = color >> 16;
		data->img_buffer[++i] = 0;
	}
}