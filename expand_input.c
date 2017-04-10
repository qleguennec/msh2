/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:01:00 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/10 13:56:50 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	expand_input
	(t_dict *env
	, t_lst *inp)
{
	t_vect	buf;

	if (inp == NULL)
		return ;
	vect_init(&buf);
	if (*(char *)inp->data == '~')
	{
		env_cpy_val(env, "HOME", &buf);
		if (*(char *)(inp->data + 1) != '\0')
			VFMT(&buf, "%s", inp->data + 1);
	}
	if (buf.data)
	{
		VFMT(&buf, "\0", 0);
		free(inp->data);
		inp->data = buf.data;
	}
	expand_input(env, inp->next);
}
