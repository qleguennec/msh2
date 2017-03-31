/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 11:31:32 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/31 11:41:11 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	bi_echo
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	int		nl;

	(void)ret;
	(void)env;
	if (!(nl = inp == NULL || ft_strcmp(inp->data, "-n") != 0))
		inp = inp->next;
	while (inp)
	{
		write(1, inp->data, ft_strlen(inp->data));
		if ((inp = inp->next))
			write(1, " ", 1);
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
