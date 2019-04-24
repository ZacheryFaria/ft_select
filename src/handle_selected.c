/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_selected.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 20:13:24 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/24 12:30:06 by zfaria           ###   ########.fr       */
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

void	move_left(t_list *list)
{
	int			start;
	t_list		*orig;
	t_select	*sel;

	orig = list;
	start = get_active_index(list);
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
	start = get_active_index(list);
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

void	remove_selected(t_list **head, t_list *list, t_list *last)
{
	t_select	*sel;

	while (list)
	{
		sel = list->content;
		if (sel->status & ACTIVE)
		{
			ft_memdel((void **)&sel);
			if (last)
				last->next = list->next;
			else
				*head = list->next;
			if (list->next->next)
				sel = list->next->content;
			else if (last)
				sel = (last)->content;
			if (!sel)
				finish(1);
			free(list);
			sel->status |= ACTIVE;
			break ;
		}
		last = list;
		list = list->next;
	}
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
