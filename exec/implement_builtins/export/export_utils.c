/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 05:00:34 by kmahdi            #+#    #+#             */
/*   Updated: 2023/04/05 10:50:47 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec.h"

int	is_value(char *argument)
{
	int	i;
	
	i = 0;
	while (argument && argument[i])
	{
		if (argument[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	get_start(char *argument)
{
	int	start;

	start = 0;
	while (argument && argument[start] && argument[start] != '=')
		start++;
	if (argument[start] == '=')
		start++;
	return (start);
}

char	**get_name(char **argument)
{
	char	**name;
	int		start;
	int		index;

	index = 0;
	name = NULL;
	if (argument[index])
	{
		name = malloc(size(argument) * sizeof(char *));
		while (argument[index])
		{
			start = 0;
			while (argument[index][start] != '=' && argument[index][start])
				start++;
			if (argument[index][start] == '=')
				start++;
			name[index] = ft_substr(argument[index], 0, start);
			index++;
		}
		name[index] = NULL;
	}
	return (name);
}

int is_equal_plus(char *argument)
{
	int	len;
	int	index;
	int is_valid;

	len = 0;
	index = 1;
	is_valid = 0;
	while (argument && argument[len] && argument[len] != '=')
		len++;
	if (argument && argument[len] && argument[len] == '=')
		is_valid = 1;
	while (index < len)
	{
		if (argument[index] == '+')
		{
			if (is_valid == 1)
				return (1);
			return (0);
		}
		index++;
	}
	return (1);
}

int ft_isalpha_nbr(char c)
{
	return ((c >= '0' && c <= '9' ) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int is_forbidden_char(char *argument)
{
	int len;
	int index;

	len = 0;
	index = 1;
	while(argument && argument[len] && argument[len] != '=')
		len++;
	while(index < len)
	{
		if(!ft_isalpha_nbr(argument[index]))
			return(1);
		index++;
	}
	return (0);
}