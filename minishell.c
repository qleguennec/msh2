/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:33:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/10 15:03:33 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SPLIT(v) vll_split(v, " ", 1, VLL_SPLIT_STR)

static int
	loop
	(t_dict *env
	, t_vect *buf)
{ 
	t_vll	*spl;

	buf->used = 0;
	vect_req(buf, 64);
	while (read(0, buf->data, 1) == 1)
	{
		buf->used++;
		vect_req(buf, 1);
	}
	if (buf->used == 0)
		return (0);
	spl = SPLIT(buf);
	printf("%lu\n", spl->size);
	vll_print(0, spl, 0);
	return (loop(env, buf));
}

int
	main
	(int argc
	, char **argv
	, char **env_def)
{
	t_dict	env;
	t_vect	buf;

	(void)argc;
	(void)argv;
	dict_str_init(&env, 10);
	while (*env_def)
		dict_str_import(&env, *env_def++, "="
			, DICT_IMPORT_ADD | DICT_IMPORT_STR);
	vect_init(&buf);
	return (loop(&env, &buf));
}
