/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:33:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/16 15:20:47 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	query_bi
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	static char	names[][10] = {"env"};
	static int	(*f[]) (t_dict *, t_lst *, int *) = {&bi_env};
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
	char	*s;
	int		ret;
	t_vect	path;

	if (query_bi(env, inp, &ret))
		return (ret);
	if ((s = query_path_env(env, inp->data)))
	{
		path.data = s;
		path.used = ft_strlen(s);
		path.total = path.used + 1;
		vect_mset_end(&path, '/', 1);
		vect_add(&path, inp->data, ft_strlen(inp->data));
		vect_mset_end(&path, '\0', 1);
		ret = fork_exec(env, path.data, inp);
		free(path.data);
	}	
	return (0);
}

static int
	loop
	(t_dict *env
	, t_vect *buf)
{
	t_lst	*inp;
	char	c;

	write(1, "> ", 2);
	buf->used = 0;
	vect_req(buf, 64);
	while (read(0, &c, 1) == 1)
	{
		vect_mset_end(buf, c, 1);
		if (((char *)buf->data)[buf->used - 1] == '\n')
		{
			printf("asd\n");
			break ;
		}	
	}
	if (buf->used == 0)
	{
		free(buf->data);
		return (0);
	}
	inp = lst_split(buf->data, buf->used, " \t", 2);
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
	return (ret);
}
