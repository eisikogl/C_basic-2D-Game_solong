/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:39:13 by eisikogl          #+#    #+#             */
/*   Updated: 2022/07/29 03:52:27 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	map_validate(t_gamedata *gamedata, int row_size, int column_size)
{
	int	i;
	int	j;

	i = 0;
	while (gamedata->map[i])
	{
		j = 0;
		while (gamedata->map[i][j])
		{
			if (i == 0 || i == column_size || j == 0 || j == row_size)
				if (gamedata->map[i][j] != '1')
					exit_game(gamedata, 3);
			if (gamedata->map[i][j] != '0' && gamedata->map[i][j] != '1' && \
				gamedata->map[i][j] != 'P' && gamedata->map[i][j] != 'E' && \
				gamedata->map[i][j] != 'C')
				exit_game(gamedata, 7);
			j++;
		}
		if (row_size != j - 1)
			exit_game(gamedata, 8);
		i++;
	}
	if (column_size != i - 1)
		exit_game(gamedata, 9);
}

void	validate(t_gamedata *gamedata)
{
	if (gamedata->player_spawn_point_count != 1)
		exit_game(gamedata, 4);
	if (gamedata->collectible_size < 1)
		exit_game(gamedata, 5);
	if (gamedata->exit_count < 1)
		exit_game(gamedata, 6);
}
