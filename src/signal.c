/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:59:48 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/22 17:31:56 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
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

void	finish(int s)
{
	(void)s;

	disable_raw_mode();
	exit(1);
}

void	suspend(int s)
{
	char	buf[2];

	(void)s;
	disable_raw_mode();
	buf[0] = g_state.orig_termios.c_cc[VSUSP];
	buf[1] = 0;
	tcsetattr(0, TCSADRAIN, &g_state.orig_termios);
	signal(SIGTSTP, SIG_DFL);
	ioctl(2, TIOCSTI, buf);
}

void	restart(int s)
{
	char	buf[2];
	(void)s;
	enable_raw_mode();
	buf[0] = -62;
	buf[1] = 0;
	ioctl(2, TIOCSTI, buf);
}

void	setsignal()
{
	//signal(SIGWINCH, size_changed);
	signal(SIGTSTP, suspend);
	signal(SIGCONT, restart);
	signal(SIGILL, finish);
	signal(SIGPIPE, finish);
	signal(SIGFPE, finish);
	signal(SIGSYS, finish);
	signal(SIGEMT, finish);
	signal(SIGTRAP, finish);
	signal(SIGHUP, finish);
	signal(SIGINT, finish);
	signal(SIGQUIT, finish);
	signal(SIGABRT, finish);
	signal(SIGKILL, finish);
	signal(SIGBUS, finish);
	signal(SIGSEGV, finish);
	signal(SIGALRM, finish);
	signal(SIGTERM, finish);
	signal(SIGUSR1, finish);
	signal(SIGUSR2, finish);
}