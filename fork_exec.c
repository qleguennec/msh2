/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:06:25 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/03 12:33:02 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENOPERM "minishell: %s: can't execute: permission denied"

static int
	child_exec
	(t_dict *env
	, char *path
	, t_lst *args)
{
	char	**argv;
	char	**envp;
	int		i;

	MALLOC_N(argv, (1 + lst_len(args)));
	assert(lst_len(args) >= 1);
	i = 0;
	while (args)
	{
		argv[i++] = args->data;
		args = args->next;
	}
	argv[i] = NULL;
	envp = dict_str_export(env, "=");
	if (execve(path, argv, envp) == -1)
		return (ERR("execve error", -1, 0));
	free(argv);
	return (0);
}

int
	fork_exec
	(t_dict *env
	, char *path
	, t_lst *args)
{
	int	ret;
	int	pid;

	if (access(path, X_OK))
		return (ERR(ENOPERM, 0, path));
	pid = fork();
	if (pid == -1)
		return (ERR("fork error", -1, 0));
	if (pid == 0)
		exit(child_exec(env, path, args));
	wait(&ret);
	return (ret);
}
