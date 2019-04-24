/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:35:37 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/23 20:20:46 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termios.h>
# include <libft.h>


typedef struct		s_hellstate
{
	int				screen_rows;
	int				screen_cols;
	int				curs_x;
	int				curs_y;
	int				hist;
	struct termios	orig_termios;
	t_list			*list;
	char			*tgb;
}					t_shell;

typedef struct		s_select
{
	char			*str;
	int				status;
}					t_select;

#define				HIDDEN (1 << 3)
#define				SELECTED (1 << 1)
#define				ACTIVE (1 << 2)

char				**g_env;

void				die(char *str);
void				shell_init(void);
t_shell				*get_shell(void);
void				shell_exit(void);
void				finish(int sig);
void				disable_raw_mode(void);
void				enable_raw_mode(void);
long				read_keypress(void);
void				process_keypress(long c, t_list **list);
void				shell_read(t_list **list);
char				*get_env(char *key);
int					ft_printnbr(int nbr);
void				print_selected(t_list *list);
void				setsignal(void);
void				write_options(t_list *list, char *tgb);
void				move_left(t_list *list);
void				move_right(t_list *list);
int					get_active_index(t_list *list);
void				set_selected(t_list *list);
void				remove_selected(t_list **head, t_list *list, t_list *last);

#endif

