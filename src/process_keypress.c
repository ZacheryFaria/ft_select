/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keypress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:31:10 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/23 11:46:28 by zfaria           ###   ########.fr       */
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

#define US tgetstr("us", &tgb)
#define UE tgetstr("ue", &tgb)
#define MR tgetstr("mr", &tgb)
#define ME tgetstr("me", &tgb)

t_shell	*get_shell(void)
{
	static t_shell shell;

	return (&shell);
}

long	read_keypress(void)
{
	long l;

	if (read(0, &l, 8) == -1)
		die("read");
	return (l);
}

void	move_left(t_list *list)
{
	int			start;
	t_list		*orig;
	t_select	*sel;

	start = 0;
	orig = list;
	while (list)
	{
		sel = list->content;
		if (sel->status & ACTIVE)
		{
			sel->status &= ~ACTIVE;
			break ;
		}
		if (!(sel->status & HIDDEN))
			start++;
		list = list->next;
	}
	start = !start ? ft_lstlen(orig) - 2 : start - 1;
	list = orig;
	while (start-- > 0)
		list = list->next;
	sel = list->content;
	sel->status |= ACTIVE;
}

void	move_right(t_list *list)
{
	t_list		*orig;
	t_select	*sel;
	int			start;

	orig = list;
	start = 0;
	while (list)
	{
		sel = list->content;
		if (sel->status & ACTIVE)
		{
			sel->status &= ~ACTIVE;
			break ;
		}
		list = list->next;
		start++;
	}
	start = start == ft_lstlen(orig) - 2 ? 0 : start + 1;
	list = orig;
	while (start-- > 0)
		list = list->next;
	sel = list->content;
	sel->status |= ACTIVE;
}

void	set_selected(t_list *list)
{
	t_list		*orig;
	t_select	*sel;

	orig = list;
	while (list)
	{
		sel = list->content;
		if (sel->status & ACTIVE && !(sel->status & SELECTED))
		{
			sel->status |= SELECTED;
			break ;
		}
		else if (sel->status & ACTIVE && sel->status & SELECTED)
		{
			sel->status &= ~SELECTED;
			break ;
		}
		list = list->next;
	}
	move_right(orig);
}

void	check_list(t_list *list)
{
	t_select	*sel;
	int			ok;

	ok = 0;
	while (list)
	{
		sel = list->content;
		if (sel && !(sel->status & HIDDEN))
			ok = 1;
		list = list->next;
	}
	if (!ok)
		die("");
}

void	remove_selected(t_list *list)
{
	t_list		*orig;
	t_select	*sel;

	orig = list;
	while (list)
	{
		sel = list->content;
		if (sel->status & ACTIVE)
		{
			sel->status |= HIDDEN;
			break ;
		}
		list = list->next;
	}
	check_list(orig);
	move_right(orig);
}

void	print_selected(t_list *list)
{
	t_select	*sel;

	while (list)
	{
		sel = list->content;
		if (sel && (sel->status & SELECTED))
			ft_printf("%s ", sel->str);
		list = list->next;
	}
}

int		process_keypress(long c, t_list *list)
{
	if (c == 'q')
		finish(1);
	else if (c == ' ')
		set_selected(list);
	else if (c == 127)
		remove_selected(list);
	else if (c == 0x445B1B || c == 0x415B1B)
		move_left(list);
	else if (c == 0x435B1B || c == 0x425B1B)
		move_right(list);
	else if (c == 27)
		finish(1);
	else if (c == 0x7E335B1B)
		remove_selected(list);
	else
		return (1);
	return (0);
}

void	write_options(t_list *list, char *tgb)
{
	t_select	*node;

	ft_putstr_fd(tgetstr("cl", &tgb), 2);
	while (list)
	{
		node = list->content;
		if (node)
		{
			if (node->status & ACTIVE)
				ft_fprintf(2, "%s", US);
			if (node->status & SELECTED)
				ft_fprintf(2, "%s", MR);
			if (!(node->status & HIDDEN))
				ft_fprintf(2, "%s", node->str);
			ft_fprintf(2, "%s%s", UE, ME);
			if (!(node->status & HIDDEN))
				ft_fprintf(2, " ");
		}
		list = list->next;
	}
}

void	shell_read(t_list *list)
{
	char	*tgb;
	long	c;
	t_shell	*shell;

	shell = get_shell();
	enable_raw_mode();
	tgetent(NULL, get_env("TERM"));
	tgb = ft_memalloc(2048);
	shell->list = list;
	shell->tgb = tgb;
	while (1)
	{
		write_options(list, tgb);
		c = read_keypress();
		if (c == '\n')
			break ;
		process_keypress(c, list);
	}
	ft_fprintf(2, tgetstr("cl", &tgb));
}
