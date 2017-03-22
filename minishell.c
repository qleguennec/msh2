/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:33:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/22 15:28:35 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CWD_ERROR "minishell: error: can't determine current directory"
#define NOT_FOUND_ERROR "minishell: %s: not found"

static int
	query_bi
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	static char	names[][10] = {"env", "exit", "cd", "setenv", "unsetenv"};
	static int	(*f[]) (t_dict *, t_lst *, int *) = {&bi_env
		, &bi_exit, &bi_cd, &bi_setenv, &bi_unsetenv};
	size_t		i;

	i = 0;
	while (i < sizeof(names) / sizeof(*names))
	{
		if (ft_strcmp(names[i], inp->data) == 0)
		{
			*ret = f[i](env, inp->next, ret);
			return (1);
		}
		i++;
	}
	return (0);
}

static int
	query
	(t_dict *env
	, t_lst *inp)
{
	char		*s;
	int			ret;
	struct stat	st;
	t_vect		path;

	if (inp == NULL)
		return (0);
	if ((*(char *)inp->data == '/' || ft_strstr(inp->data, "./") == inp->data)
		&& stat(inp->data, &st) != -1)
		return (fork_exec(env, inp->data, inp));
	else if (query_bi(env, inp, &ret))
		return (ret);
	else if ((s = query_path_env(env, inp->data)))
	{
		vect_init(&path);
		VFMT(&path, "%s/%s\0", s, inp->data);
		ret = fork_exec(env, path.data, inp);
		free(path.data);
		return (ret);
	}
	return (ERR(NOT_FOUND_ERROR, 0, inp->data));
}

static int
	pre_loop
	(t_dict *env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ERR(CWD_ERROR, -1, 0));
	dict_set(env, "PWD", cwd, 1 + ft_strlen(cwd));
	return (0);
}

static int
	loop
	(t_dict *env
	, t_vect *buf)
{
	t_lst	*inp;
	char	c;

	pre_loop(env);
	write(1, "$> ", 3);
	buf->used = 0;
	while (read(0, &c, 1) == 1 && c != '\n')
		vect_mset_end(buf, c, 1);
	if (buf->used == 0)
		return (c == '\n' ? loop(env, buf) : 0);
	inp = lst_split(buf->data, buf->used, " \t", 2);
	expand_input(env, inp);
	query(env, inp);
	lst_free(inp);
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
