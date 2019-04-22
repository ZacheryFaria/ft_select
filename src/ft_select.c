/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:24:39 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/22 16:48:16 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_select.h>

int	main(int argc, char **argv, char **env)
{
	int			i;
	t_select	*sel;
	t_list		*list;

	if (argc == 1)
		die ("Usage: ./ft_select (files)");
	i = argc - 1;
	list = ft_lstnew(0, 0);
	while (i > 0)
	{
		sel = ft_memalloc(sizeof(t_select));
		sel->str = argv[i];
		ft_lstadd(&list, sel, sizeof(t_select));
		free(sel);
		i--;
	}
	sel = list->content;
	sel->status |= ACTIVE;
	g_env = arrdup(env);
	shell_init();
	shell_read(list);
	disable_raw_mode();
	print_selected(list);
}
