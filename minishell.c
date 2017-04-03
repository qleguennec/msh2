/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:33:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/03 13:18:34 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EPWD "minishell: error: can't determine current directory"

static int
	process_input
	(t_dict *env
	, t_lst **split)
{
	t_lst	*inp;
	t_lst	*tmp;
	int		ret;

	inp = lst_split((*split)->data, ft_strlen((*split)->data), " \t", 2);
	expand_input(env, inp);
	ret = inp_query(env, inp);
	lst_free(inp);
	tmp = (*split)->next;
	free((*split)->data);
	free(*split);
	*split = tmp;
	return (ret);
}

static int
	prompt
	(t_dict *env)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		dict_set(env, "PWD", pwd, 1 + ft_strlen(pwd));
		write(1, pwd, ft_strlen(pwd));
		write(1, " $> ", 4);
	}
	else
	{
		write(1, "$> ", 3);
		return (ERR(EPWD, -1, 0));
	}
	return (0);
}

static int
	loop
	(t_dict *env
	, t_vect *buf)
{
	char	c;
	ssize_t	ret;
	t_lst	*split;

	prompt(env);
	buf->used = 0;
	while ((ret = read(0, &c, 1)) == 1 && c != '\n')
		vect_mset_end(buf, c, 1);
	if (ret == -1)
		return (ERR("read error", -1, 0));
	if (ret == 0)
		return (ECHO("", 0, 0));
	split = lst_split(buf->data, buf->used, ";", 1);
	while (split != NULL)
		process_input(env, &split);
	return (loop(env, buf));
}

int
	main
	(int argc
	, char **argv
	, char **env_def)
{
	int		ret;
	t_dict	env;
	t_vect	buf;

	(void)argc;
	(void)argv;
	dict_str_init(&env, 10);
	while (*env_def)
		dict_str_import(&env, *env_def++, "="
			, DICT_IMPORT_ADD | DICT_IMPORT_STR);
	vect_init(&buf);
	ret = loop(&env, &buf);
	dict_free(&env);
	free(buf.data);
	return (ret);
}
