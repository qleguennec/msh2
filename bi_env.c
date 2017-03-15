/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 13:34:37 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/15 15:32:13 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	env_process_arg
	(t_dict *env
	, t_lst **inp
	, char *s)
{
	if (*s == 'i')
	{
		dict_clear(env);
		s++;
	}
	else if (*s == 'u')
	{
		s++;
		if (*s)
			dict_del(env, s);
		else
		{
			if ((*inp = (*inp)->next) == NULL)
				return
					(ERR("env: option requires an argument -- %c", -1, 'u'));
			dict_del(env, (*inp)->data);
		}
	}
	if (*s)
		return (env_process_arg(env, inp, s));
	else
		return (0);
}

static int
	exec_env
	(t_dict *env
	, t_lst *inp)
{
	char	*s;

	while (inp && *(s = inp->data) == '-')
	{
		env_process_arg(env, &inp, ++s);
		inp = inp->next;
	}
	while (inp && ft_strchr(inp->data, '=') != NULL)
	{
		dict_str_import(env, inp->data, "="
			, DICT_IMPORT_SET | DICT_IMPORT_STR);
		inp = inp->next;
	}
	dict_print(env, "=", "\n");
	return (0);
}

int
	bi_env
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ERR("fork error\n", -1, 0));
	if (pid == 0)
		exit(exec_env(env, inp));
	wait(ret);
	return (0);
}
