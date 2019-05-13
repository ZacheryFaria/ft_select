/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keypress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:31:10 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/13 12:21:40 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <strings.h>
#include <ft_select.h>
#include <fcntl.h>

#define US tgetstr("us", &tgb)
#define UE tgetstr("ue", &tgb)
#define MR tgetstr("mr", &tgb)
#define ME tgetstr("me", &tgb)

int		get_active_index(t_list *list)
{
	int			index;
	t_select	*sel;

	index = 0;
	while (list)
	{
		sel = list->content;
		if (sel->status & ACTIVE)
		{
			sel->status &= ~ACTIVE;
			break ;
		}
		index++;
		list = list->next;
	}
	return (index);
}

void	process_keypress(long c, t_list **list)
{
	if (c == 'q')
		finish(1);
	else if (c == ' ')
		set_selected(*list);
	else if (c == 127)
		remove_selected(list, *list, 0);
	else if (c == 0x445B1B)
		move_left(*list);
	else if (c == 0x435B1B)
		move_right(*list);
	else if (c == 27)
		finish(1);
	else if (c == 0x7E335B1B)
		remove_selected(list, *list, 0);
}

void	write_options(t_list *list, char *tgb)
{
	int			i;
	int			rowc;
	int			len;

	ft_putstr_fd(tgetstr("cl", &tgb), 2);
	len = get_longest(list);
	rowc = amount_per_row(len, *get_shell()) - 1;
	if (!can_fit(len, list, *get_shell()))
	{
		ft_fprintf(2, "Can't fit");
		return ;
	}
	i = 0;
	while (list)
	{
		i++;
		write_element(list->content, len, rowc, i);
		list = list->next;
	}
}

void	shell_read(t_list **list)
{
	char	*tgb;
	long	l;
	t_shell	*shell;

	shell = get_shell();
	enable_raw_mode();
	tgetent(NULL, get_env("TERM"));
	tgb = ft_memalloc(1 << 16);
	shell->list = *list;
	shell->tgb = tgb;
	while (1)
	{
		write_options(*list, tgb);
		l = 0;
		read(0, &l, 8);
		if (l == '\n')
			break ;
		process_keypress(l, list);
	}
	ft_fprintf(2, tgetstr("cl", &tgb));
}
