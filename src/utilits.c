/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:45:18 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/14 20:45:20 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	init_extremums(t_data *data)
{
	if (data->type == julia)
	{
		set_complex(&(data->min), -3.00, -3.00);
		set_complex(&(data->max), 3.00, 3.00);
	}
	else
	{
		set_complex(&(data->min), -2.5, -1.0);
		set_complex(&(data->max), 1.0, 1.0);
	}
}

void	set_complex(t_cnum *n, double real, double imaginary)
{
	n->re = real;
	n->im = imaginary;
}

void	init_mlx_window(t_data *data, char *name)
{
	pthread_t id;

	if ((data->mlx->p_mlx = mlx_init()) == NULL)
		error(strerror(errno));
	data->mlx->win = mlx_new_window(data->mlx->p_mlx, IMG_W + MENU_W,
													MENU_H, name);
	if (!(data->mlx->win))
		error(strerror(errno));
	if ((pthread_create(&id, NULL, &draw_app_menu, (void *)data)))
		error("pthread failed to create new thread");
	pthread_join(id, NULL);
	mlx_expose_hook(data->mlx->win, expose_hook, data);
	mlx_hook(data->mlx->win, 2, 0, key_press, data);
	mlx_hook(data->mlx->win, 6, 0, julia_motion, data);
	mlx_hook(data->mlx->win, 17, 0, close, data);
	mlx_mouse_hook(data->mlx->win, mouse_hook, data);
	mlx_do_key_autorepeaton(data->mlx->p_mlx);
	mlx_loop(data->mlx->p_mlx);
}

void	init_programm_architecture(t_data *data)
{
	if ((data->menu = (t_menu *)malloc(sizeof(t_menu))) == NULL)
		error(strerror(errno));
	data->menu-> start_x = IMG_W + 1;
	data->menu-> start_y = MENU_H - IMG_H;
	data->menu-> finish_x = IMG_W + MENU_W;
	data->menu-> finish_y = MENU_H;
	if ((data->mlx = (t_mlx *)malloc(sizeof(t_mlx))) == NULL)
		error(strerror(errno));
	data->mlx->bpp = 0;
	data->mlx->size = 0;
	data->mlx->end = 0;
	if ((data->params = (t_params *)malloc(sizeof(t_params))) == NULL)
		error(strerror(errno));
	data->params->max_iter = MAX_ITER;
	data->params->zoom = 1.1;
	data->params->zoom_factor = 0;
	set_complex(&(data->params->julia_k), 1.8, 0.6);
	data->julia_mouse_lock = 0;
}
