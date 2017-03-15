/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:02:50 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/15 14:13:48 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libdict/libdict.h"
# include "liblst/liblst.h"
# include "libfmt/libfmt.h"

# include <unistd.h>
# include <sys/types.h>

// TODO remove debug includes
# include <stdio.h>
# include <assert.h>

int
	bi_env
	(t_dict *env
	, t_lst *inp
	, int *ret);

#endif
