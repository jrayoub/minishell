/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:11 by aaitouna          #+#    #+#             */
/*   Updated: 2023/02/19 19:10:12 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_name(char *s, int *len)
{
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	while (s[i] && ft_isalnum(s[i]))
	{
		if (s[i] != '\n' && s[i] != '\\')
			name = ft_str_append(name, s[i]);
		i++;
	}
	*len = i;
	return (name);
}

void	toggle_quteflag_n_increment(char c, int *qute_flag, int *index)
{
	if (c == '"' && *qute_flag == 0)
	{
		*qute_flag = 2;
		(*index)++;
	}
	else if (c == '\'' && *qute_flag == 0)
	{
		*qute_flag = 1;
		(*index)++;
	}
	else if ((c == '\'' && *qute_flag == 1) || (c == '"' && *qute_flag == 2))
	{
		*qute_flag = 0;
		(*index)++;
	}
}

char	*copy_variable_value(char *dst, char *src, int *index)
{
	char	*value;
	char	*name;
	int		j;
	int		name_len;

	name_len = 0;
	j = 0;
	(*index)++;
	name = get_env_name(&src[*index], &name_len);
	(*index) += name_len - 1;
	if (name == NULL)
		return (dst);
	value = getenv(name);
	if (value == NULL)
		return (dst);
	while (value[j])
		dst = ft_str_append(dst, value[j++]);
	return (dst);
}

void	toggle_quteflag(char c, int *qute_flag)
{
	if (c == '"' && *qute_flag == 0)
		*qute_flag = 2;
	else if (c == '\'' && *qute_flag == 0)
		*qute_flag = 1;
	else if ((c == '\'' && *qute_flag == 1) || (c == '"' && *qute_flag == 2))
		*qute_flag = 0;
}
