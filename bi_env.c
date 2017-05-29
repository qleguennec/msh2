/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 13:34:37 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/29 04:44:05 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENOARG "minishell: env: option requires an argument: -- u"
#define EINVARG "minishell: env: %s: invalid argument"

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
				return (err(-1, ENOARG));
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
		if (dict_str_import(env, inp->data, "="
			, DICT_IMPORT_SET | DICT_IMPORT_STR) == 0)
			return (err(-1, EINVARG, inp->data));
		inp = inp->next;
	}
	if (inp)
		inp_query(env, inp);
	else
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
		return (err(-1, "fork error\n"));
	if (pid == 0)
		exit(exec_env(env, inp));
	wait(ret);
	return (0);
}
