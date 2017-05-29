/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inp_query.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:41:03 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/29 04:51:31 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENOTFOUND "minishell: %s: not found"

static int
	query_bi
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	static char	names[][10] = {"env", "exit", "cd", "setenv", "unsetenv"
		, "echo"};
	static int	(*f[]) (t_dict *, t_lst *, int *) = {&bi_env, &bi_exit
		, &bi_cd, &bi_setenv, &bi_unsetenv, &bi_echo};
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

int
	inp_query
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
		path.malloc_err_f = &malloc_err;
		vfmt(0, &path, "%s/%s\0", s, inp->data);
		free(s);
		ret = fork_exec(env, path.data, inp);
		free(path.data);
		return (ret);
	}
	return (err(0, ENOTFOUND, inp->data));
}
