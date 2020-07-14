/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:04:15 by mriley            #+#    #+#             */
/*   Updated: 2020/07/14 20:01:57 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/virtual.h"
#include <stdio.h>

char			g_arena[MEM_SIZE];
extern t_op		g_op_tab[17];

t_car	*init_champions(t_car *player, int j, t_core *champ)
{
	player->num = champ->champions[j].num;
	player->pc = change_arena(champ->champions[j], player->num, champ->num_ch);
	player->time = -1;
	player->cycle_live = -1;
	player->carry = 0;
	player = init_reg(player);
	player = to_reg_from_int(player, 1, -player->num);
	player->next = malloc(sizeof(t_car));
	return (player);
}

t_car	*help_arena_set(t_car *player, t_core *champ, int j)
{
	player = init_champions(player, j, champ);
	player = player->next;
	player->num = -1;
	return (player);
}

void	free_start(t_car *champ, t_car *start)
{
	champ = NULL;
	champ = start;
	while (start)
	{
		if (start->next && start->next->num == -1)
		{
			free(start->next);
			start->next = NULL;
		}
		start = start->next;
	}
}

void	arena_set(t_core *champ)
{
	int		j;
	int		i;
	int		car;
	t_car	*start;

	i = champ->num_ch;
	j = champ->num_ch - 1;
	car = 0;
	champ->player = malloc(sizeof(t_car));
	start = champ->player;
	while (i > 0)
	{
		while (j > -1)
			if (i == champ->champions[j--].num)
				champ->player = help_arena_set(champ->player, champ, j + 1);
		j = champ->num_ch - 1;
		i--;
	}
	free_start(champ->player, start);
	champ->player = NULL;
	champ->player = start;
}

void	print_addres(int i)
{
	ft_printf("\n");
	if (i < 0x10)
		ft_printf("0x000%x : ", i);
	else
	{
		if (i < 0x100)
			ft_printf("0x00%x : ", i);
		else
			(i < 0x1000) ? ft_printf("0x0%x : ", i) : ft_printf("0x%x : ", i);
	}
}

void	print_arena(int num)
{
	int				i;
	unsigned int	buf;

	i = 0;
	buf = 0;
	ft_printf("0x000%x : ", i);
	while (i < MEM_SIZE)
	{
		buf = g_arena[i++];
		buf = buf & 0x000000ff;
		if (buf != 0)
			(buf < 16) ? ft_printf("0%x ", buf) : ft_printf("%x ", buf);
		else
			ft_printf("00 ");
		if (i % num == 0 && (i - 1) != 0 && i != MEM_SIZE)
			print_addres(i);
	}
	ft_printf("\n");
}
