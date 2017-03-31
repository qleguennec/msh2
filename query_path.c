/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 11:35:38 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/31 14:13:19 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	path_match
	(DIR *dir
	, char *file)
{
	struct dirent	*ent;

	while ((ent = readdir(dir)) != NULL)
	{
		if (ft_strcmp(file, ent->d_name) == 0)
			return (1);
	}
	return (0);
}

char
	*query_path
	(char *path
	, char *file)
{
	DIR			*dir;
	char		*ret;
	t_lst		*lst;
	t_lst		*next;

	lst = lst_split(path, ft_strlen(path), ":", 1);
	while (lst)
	{
		if ((dir = opendir(lst->data)) != NULL)
		{
			if (path_match(dir, file))
			{
				ret = ft_strdup(lst->data);
				lst_free(lst);
				closedir(dir);
				return (ret);
			}
			closedir(dir);
		}
		free(lst->data);
		next = lst->next;
		free(lst);
		lst = next;
	}
	return (NULL);
}

char
	*query_path_env
	(t_dict *env
	, char *file)
{
	t_dict_ent	*path;

	if ((path = dict_lookup(env, "PATH")) == NULL)
		return (NULL);
	return (query_path(path->val.data, file));
}
