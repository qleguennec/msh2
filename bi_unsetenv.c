/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 11:24:03 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/22 11:25:38 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	bi_unsetenv
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	if (inp == NULL)
		return (0);
	dict_del(env, inp->data);
	return (bi_unsetenv(env, inp->next, ret));
}
