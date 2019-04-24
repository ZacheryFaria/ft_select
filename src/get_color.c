/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:22:50 by zfaria            #+#    #+#             */
/*   Updated: 2019/04/24 12:28:38 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>
#include <sys/stat.h>

char	*get_color(char *str)
{
	struct stat	st;

	if (lstat(str, &st) == -1)
		return (WHITE);
	if (S_ISDIR(st.st_mode))
		return (BLUE);
	if (S_ISLNK(st.st_mode))
		return (MAGENTA);
	if (st.st_mode & S_IXUSR)
		return (RED);
	return (WHITE);
}
