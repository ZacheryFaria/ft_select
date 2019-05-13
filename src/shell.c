/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:07:42 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/13 11:16:30 by zfaria           ###   ########.fr       */
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

t_shell	*get_shell(void)
{
	static t_shell	shell;
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	shell.screen_rows = ws.ws_row;
	shell.screen_cols = ws.ws_col;
	return (&shell);
}

void	disable_raw_mode(void)
{
	t_shell	*shell;

	shell = get_shell();
	tcsetattr(2, TCSAFLUSH, &shell->orig_termios);
	tputs(tgetstr("te", NULL), 1, ft_printnbr);
	tputs(tgetstr("ve", NULL), 1, ft_printnbr);
}

int		ft_printnbr(int num)
{
	ft_putchar_fd(num, 2);
	return (0);
}

void	enable_raw_mode(void)
{
	struct termios	raw;
	char			*tgb;
	char			*ptr;
	t_shell			*shell;

	tgb = ft_memalloc(2048);
	ptr = tgb;
	shell = get_shell();
	if (tcgetattr(2, &shell->orig_termios) == -1)
		die("tcgetattr");
	raw = shell->orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	tcsetattr(2, TCSAFLUSH, &raw);
	if (tgetent(NULL, get_env("TERM")) == -1)
		die("bad env configuration");
	setsignal();
	ft_putstr_fd(tgetstr("ti", &tgb), 2);
	ft_putstr_fd(tgetstr("vi", &tgb), 2);
	free(ptr);
}
