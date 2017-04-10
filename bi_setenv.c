/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 11:14:58 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/27 15:10:55 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENOARG "minishell: setenv: %s: invalid argument"

int
	bi_setenv
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	if (inp == NULL)
		return (0);
	if (dict_str_import(env, inp->data, "="
		, DICT_IMPORT_SET | DICT_IMPORT_STR) == 0)
		return (FMTERR(ENOARG, -1, inp->data));
	*ret = 1;
	return (bi_setenv(env, inp->next, ret));
}
