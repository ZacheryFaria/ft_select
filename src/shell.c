/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:07:42 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/22 17:37:54 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>
#include <unistd.h>
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

void	die(char *str)
{
	ft_printf("%s", str);
	disable_raw_mode();
	exit(1);
}

void	shell_init(void)
{

	g_state.curs_x = 0;
	g_state.curs_y = 0;
	g_state.hist = 0;
}

void	disable_raw_mode(void)
{
	tcsetattr(2, TCSAFLUSH, &g_state.orig_termios);
	tputs(tgetstr("te", NULL), 1, ft_printnbr);
	tputs(tgetstr("ve", NULL), 1, ft_printnbr);
}

int		ft_printnbr(int num)
{
	ft_putchar(num);
	return (0);
}

void	enable_raw_mode(void)
{
	struct termios	raw;
	char			*tgb;

	tgb = ft_memalloc(2048);
	if (tcgetattr(2, &g_state.orig_termios) == -1)
		die("tcgetattr");
	raw = g_state.orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	tcsetattr(2, TCSAFLUSH, &raw);
	tgetent(NULL, get_env("TERM"));
	setsignal();
	ft_putstr(tgetstr("ti", &tgb));
	ft_putstr(tgetstr("vi", &tgb));
}
