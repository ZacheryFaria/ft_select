/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:55:09 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/14 10:58:26 by zfaria           ###   ########.fr       */
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

int		get_longest(t_list *args)
{
	t_select	*data;
	int			maxlen;

	maxlen = 0;
	while (args)
	{
		data = args->content;
		if (data)
		{
			if (ft_strlen(data->str) > maxlen)
				maxlen = ft_strlen(data->str);
		}
		args = args->next;
	}
	return (maxlen);
}

int		amount_per_row(int longest, t_shell shell)
{
	return (shell.screen_cols / longest);
}

int		can_fit(int longest, t_list *list, t_shell shell)
{
	int	row;
	int len;

	row = amount_per_row(longest, shell) - 1;
	len = ft_lstlen(list);
	if (row <= 0 || len / row > shell.screen_rows)
		return (0);
	return (1);
}

void	write_element(t_select *node, int len, int rowc, int i)
{
	char	*tgb;
	char	*str;

	tgb = get_shell()->tgb;
	if (node)
	{
		str = ft_strnew(ft_strlen(node->str) + ft_strlen(UE) + ft_strlen(ME));
		ft_strvcat(str, node->str, UE, ME, 0);
		ft_fprintf(2, get_color(node->str));
		if (node->status & ACTIVE)
			ft_fprintf(2, "%s", US);
		if (node->status & SELECTED)
			ft_fprintf(2, "%s", MR);
		ft_fprintf(2, "%-*s ", len + ft_strlen(UE) + ft_strlen(ME), str);
		ft_fprintf(2, WHITE);
		if (i % rowc == 0)
		{
			ft_fprintf(2, "\n");
			i = -1;
			while (++i < get_shell()->screen_cols)
				ft_fprintf(2, tgetstr("le", &tgb));
		}
		free(str);
	}
}
