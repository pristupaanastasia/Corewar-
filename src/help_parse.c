/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 20:05:37 by mriley            #+#    #+#             */
/*   Updated: 2020/07/18 16:45:36 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/virtual.h"
#include <stdio.h>

char		g_arena[MEM_SIZE];
extern t_op	g_op_tab[17];

t_core	*read_champ(char *s, t_core *core, int num)
{
	char	*line;
	int		fd;
	int		k;
	int		j;
	off_t	endfile;

	line = malloc(2);
	line[1] = '\0';
	j = 0;
	core->champions[num].buf = malloc(MEM_SIZE);
	if ((fd = open(s, O_RDONLY)) == -1 || !core->champions[num].buf)
		ft_error(EADDRNOTAVAIL, -3);
	endfile = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, 0);
	while (lseek(fd, 0, SEEK_CUR) != endfile)
	{
		if ((k = read(fd, line, 1)) == -1)
			exit(0);
		core->champions[num].buf[j] = line[0];
		j++;
	}
	core->champions[num].buf[j] = '\0';
	free(line);
	return (core);
}

void	print_mem(unsigned int n)
{
	int		i;

	i = 0;
	ft_printf("\n mem");
	while (i < 32)
	{
		if (n & 0x80000000)
			ft_printf("1");
		else
			ft_printf("0");
		i++;
		n = n << 1;
	}
	ft_printf("\n");
}

void	print_char(char k)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		if (k & 0x80)
			ft_printf("1");
		else
			ft_printf("0");
		i++;
		k = k << 1;
	}
}

void	print_hello(t_core *champ, int n)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < 4 && champ->champions[i].num != 0)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		champ->champions[i].num, champ->champions[i].mem.prog_size,
		champ->champions[i].mem.prog_name, champ->champions[i].mem.comment);
		i++;
	}
	if (n > 0)
		ft_printf("Contestant %d has won !\n", n);
}
