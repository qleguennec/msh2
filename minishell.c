/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:33:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/15 13:33:22 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int bi_env (t_dict *env) {dict_print(env, "=", "\n"); return (0);}

static int
	query_bi
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	static char	names[][10] = {"env"};
	static int	(*f[]) (t_dict *) =  {&bi_env};
	size_t		i;	

	i = 0;
	while (i < sizeof(names) / sizeof(*names))
	{
		if (ft_strcmp(names[i], inp->data) == 0)
		{
			*ret = f[i](env);
			return (1);
		}
		i++;
	}
	return (0);
}

static int
	loop
	(t_dict *env
	, t_vect *buf)
{ 
	t_lst	*inp;
	int		ret;

	buf->used = 0;
	vect_req(buf, 64);
	while (read(0, buf->data + buf->used, 1) == 1)
	{
		if (((char *)buf->data)[buf->used] == '\n')
			break ;
		vect_req(buf, 1);
		buf->used++;
	}
	if (buf->used == 0)
		return (0);
	inp = lst_split(buf->data, buf->used, " \t", 2);
	query_bi(env, inp, &ret);
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
