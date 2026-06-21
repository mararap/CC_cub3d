/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 20:31:01 by marapovi          #+#    #+#             */
/*   Updated: 2026/06/21 17:14:36 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	// validate input
	// init structs
	// setup map
	// 
	(void)ac;
	(void)av;
	char *str;
	int	i;
	i = 0;
	str = "Hello World!";
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
	return (0);
}