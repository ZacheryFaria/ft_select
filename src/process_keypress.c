/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keypress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:31:10 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/22 17:42:02 by zfaria           ###   ########.fr       */
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

char	read_keypress(void)
{
	char c;

	if (read(STDIN_FILENO, &c, 1) == -1)
		die("read");
	return (c);
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
		list = list->next;
		start++;
	}
	if (start == 0)
		start = ft_lstlen(orig) - 2;
	else
		start--;
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
	if (start == ft_lstlen(orig) - 2)
		start = 0;
	else
		start++;
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
		die ("");
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

int		process_keypress(char c, char *tgb, t_list *list)
{
	char	seq[3];

	if (c == 'q')
		die("");
	if (c == ' ')
		set_selected(list);
	if (c == 127)
		remove_selected(list);
	if (c == '\x1b')
	{
		read(1, &seq[0], 1);
		read(1, &seq[1], 1);
		if (seq[0] != '[')
			return (0);
		if (seq[1] == 'D')
			move_left(list);
		if (seq[1] == 'C')
			move_right(list);
	}
	(void)tgb;
	(void)list;
	return (0);
}

void	write_options(t_list *list, char *tgb)
{
	t_select	*node;

	ft_putstr(tgetstr("cl", &tgb));
	while (list)
	{
		node = list->content;
		if (node)
		{
			if (node->status & ACTIVE)
				ft_printf("%s", US);
			if (node->status & SELECTED)
				ft_printf("%s", MR);
			if (!(node->status & HIDDEN))
				ft_printf("%s", node->str);
			ft_printf("%s%s", UE, ME);
			if (!(node->status & HIDDEN))
				ft_printf(" ");
		}
		list = list->next;
	}
}

void	shell_read(t_list *list)
{
	char	*tgb;
	char	c;
	int		ret;

	enable_raw_mode();
	tgetent(NULL, get_env("TERM"));
	tgb = ft_memalloc(2048);
	ret = 0;
	while (1)
	{
		write_options(list, tgb);
		c = read_keypress();
		if (c == '\n')
			break ;
		if ((ret = process_keypress(c, tgb, list)))
			break ;
	}
	ft_printf(tgetstr("cl", &tgb));
}
