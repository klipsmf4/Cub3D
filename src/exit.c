/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klever <klever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:57:57 by klever            #+#    #+#             */
/*   Updated: 2020/11/16 02:14:46 by klever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	err_handler(t_game *game, char *str)
{
	if (write(2, "Error\n", 6) < 0)
		err_handler(game, "Write failed\n");
	if (str)
	{
		if (write(2, str, ft_strlen(str)) < 0)
			err_handler(game, "Write failed\n");
	}
	//exiter(game, -1);
}