/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmahdi <kmahdi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:43:34 by aaitouna          #+#    #+#             */
/*   Updated: 2023/04/08 06:11:19 by kmahdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct node
{
	int		input_file;
	char	*command;
	char	**arguments;
	int		output_file;
	int		shelvl;
}			m_node;

enum				EXIT_STATUS
{
	M_SIG_INT = 78
};

enum				file_input
{
	NONE = -3,
	NO_FILE = -1,
	ERROR = -2,
};

typedef struct s_tree
{
	int				op;
	char			*content;

	struct s_tree	*left;
	struct s_tree	*right;
	struct node		*node;
}					t_tree;


typedef struct proccess
{
	int	length;
	int	*proccess;
}	t_proccess;

#endif