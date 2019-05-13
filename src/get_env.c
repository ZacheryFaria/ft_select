/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:44:26 by zfaria            #+#    #+#             */
/*   Updated: 2019/05/13 14:32:30 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_select.h>

char	*get_env(char *key)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(key);
	while (g_env[++i])
		if (ft_strncmp(g_env[i], key, len) == 0 && g_env[i][len] == '=')
			return (g_env[i] + len + 1);
	return (0);
}
