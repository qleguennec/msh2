/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:01:00 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/29 04:51:43 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	expand_input
	(t_dict *env
	, t_lst *inp)
{
	t_vect	buf;

	if (inp == NULL || inp->next == NULL)
		return ;
	inp = inp->next;
	vect_init(&buf);
	buf.malloc_err_f = &malloc_err;
	if (*(char *)inp->data == '~')
	{
		env_cpy_val(env, "HOME", &buf);
		if (*(char *)(inp->data + 1) != '\0')
			vfmt(0, &buf, "%s", inp->data + 1);
	}
	if (buf.data)
	{
		vfmt(0, &buf, "\0", 0);
		free(inp->data);
		inp->data = buf.data;
	}
	expand_input(env, inp->next);
}
