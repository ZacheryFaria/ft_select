/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:07:42 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/23 11:09:44 by zfaria           ###   ########.fr       */
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

void	init_shell(void)
{
	t_shell *shell;

	shell = get_shell();
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
	t_shell			*shell;

	tgb = ft_memalloc(2048);
	shell = get_shell();
	if (tcgetattr(2, &shell->orig_termios) == -1)
		die("tcgetattr");
	raw = shell->orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	tcsetattr(2, TCSAFLUSH, &raw);
	tgetent(NULL, get_env("TERM"));
	setsignal();
	ft_putstr_fd(tgetstr("ti", &tgb), 2);
	ft_putstr_fd(tgetstr("vi", &tgb), 2);
}
