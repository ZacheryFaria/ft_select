/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:35:37 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/22 17:27:12 by zfaria           ###   ########.fr       */
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
}					t_shell;

typedef struct		s_select
{
	char			*str;
	int				status;
}					t_select;

#define				HIDDEN (1 << 3)
#define				SELECTED (1 << 1)
#define				ACTIVE (1 << 2)

t_shell				g_state;
char				**g_env;

void				die(char *str);
void				shell_init(void);
void				shell_exit(void);
void				disable_raw_mode(void);
void				enable_raw_mode(void);
char				read_keypress(void);
int					process_keypress(char c, char *tgb, t_list *list);
void				shell_read(t_list *list);
char				*get_env(char *key);
int					ft_printnbr(int nbr);
void				print_selected(t_list *list);
void				setsignal();

#endif

