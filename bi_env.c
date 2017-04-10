/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 13:34:37 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/03 13:25:42 by qle-guen         ###   ########.fr       */
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
		{
			dict_del(env, s);
			return (0);
		}
		else if ((*inp = (*inp)->next) == NULL)
			return (FMTERR(ENOARG, -1, 0));
		dict_del(env, (*inp)->data);
	}
	return (*s ? env_process_arg(env, inp, s) : 0);
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
			return (FMTERR(EINVARG, -1, inp->data));
		inp = inp->next;
	}
	inp ? inp_query(env, inp) : dict_print(env, "=", "\n");
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
		return (FMTERR("fork error\n", -1, 0));
	if (pid == 0)
		exit(exec_env(env, inp));
	wait(ret);
	return (0);
}
