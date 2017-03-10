/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:33:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/10 13:20:58 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main
	(int argc
	, char **argv
	, char **env)
{
	t_dict	test;

	(void)argc;
	(void)argv;
	dict_str_init(&test, 10);
	while (*env)
		dict_str_import(&test, *env++, "=", DICT_IMPORT_ADD | DICT_IMPORT_STR);
	dict_print(&test, "=", "\n");
	dict_free(&test);
}
