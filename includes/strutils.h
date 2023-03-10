/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:47:09 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:47:15 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUTILS_H
# define STRUTILS_H
# include "t_token.h"
# include "t_node.h"
# define PCHARARR_INITIAL_CAP 1

typedef struct s_pchararr
{
	int		len;
	int		cap;
	char	**data;
}	t_pchararr;

t_pchararr	*pchararr_create(void);
t_pchararr	*pchararr_destroy(t_pchararr *pchararr);
int			pchararr_expand(t_pchararr *pchararr);
int			pchararr_append(t_pchararr *pchararr, char *data);
char		*pchararr_merge(t_pchararr *strarr);
int			pchararr_to_strarr(t_pchararr *strarr, char ***buf);
void		pchararr_free_all_pchars(t_pchararr *strarr);

int			remove_quotes(char **buf);
int			remove_char(char **buf, char c);

int			is_valid_name(char *str);

int			find_exec(char **buf);

#endif
