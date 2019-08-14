/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:10:57 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/13 20:11:04 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fractol.h"

int	main(int ac, char *av[])
{
	t_data	all;

	init_data(&all);
	get_fractal_types(&all, ac, av);
	if (!(all.mlx_data.p_mlx = mlx_init()))
		error("Error: Failed to init mlx.");
	draw(&all);
	mlx_loop(all.mlx_data.p_mlx);
	return (0);
}
