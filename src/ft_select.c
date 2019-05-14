/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:24:39 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/14 10:54:45 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_select.h>

int	main(int argc, char **argv, char **env)
{
	int			i;
	t_select	*sel;
	t_list		*list;

	g_env = arrdup(env);
	enable_raw_mode();
	if (argc == 1)
		die("Usage: ./ft_select (args)\n");
	i = argc - 1;
	list = ft_lstnew(0, 0);
	while (i-- > 0)
	{
		if (argv[i + 1][0] == 0)
			continue;
		sel = ft_memalloc(sizeof(t_select));
		sel->str = argv[i + 1];
		ft_lstadd(&list, sel, sizeof(t_select));
		free(sel);
	}
	if (ft_lstlen(list) == 1)
		die("No valid arguments");
	((t_select *)list->content)->status |= ACTIVE;
	shell_read(&list);
	disable_raw_mode();
	print_selected(list);
}
