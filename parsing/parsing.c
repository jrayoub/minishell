#include "../minishell.h"

int qoute(int i, int mode)
{
	static int qoute_flag;

	if (mode == 0)
		qoute_flag = i;
	return (qoute_flag);
}

int	here_doc(char *limiter)
{
	char	*line;
	int		fd;

	fd = open(".temp_file", O_CREAT | O_RDWR, 0664);
	while (1)
	{
		ft_printf("here_doc> ");
		line = strip_nl(get_next_line(0));
		if (ft_strlen(limiter) == ft_strlen(line) && !ft_strncmp(line, limiter,
				ft_strlen(line)))
			break ;
		write(fd, line, ft_strlen(line));
	}
	close(fd);
	return (open(".temp_file", O_RDONLY));
}

int	open_input_file(char *line, int *i)
{
	int	input_file;

	if (line[(*i) + 1] == '<')
		return (here_doc(get_str(&line[(*i) += 2], i)));
	else if ((input_file = open(get_str(&line[++(*i)], i), O_RDONLY)) == -1)
	{
		// input file doesn't open
	}
	return (input_file);
}

int	open_output_file(char *line, int *i)
{
	int	opne_flag;
	int	output_file;

	opne_flag = 0;
	if (line[(*i) + 1] == '>')
	{
		opne_flag = O_CREAT | O_RDWR | O_APPEND;
		(*i)++;
	}
	else
		opne_flag = O_CREAT | O_RDWR | O_TRUNC;
	if ((output_file = open(get_str(&line[++(*i)], i), opne_flag, 0664)) ==
		-1)
	{
		// input file doesn't open
	}
	return (output_file);
}

char	**parse_arguments(char *line, char *cmd, int *i)
{
	char	*arguments;

	arguments = cmd;
	while (line[*i] && ((line[*i] != '|' && line[*i] != '<'
				&& line[*i] != '>')))
	{
		arguments = ft_strjoin(arguments, ft_strjoin(" ", get_str(&line[*i],
						i)));
	}
	return (ft_split(arguments, ' '));
}

void	parse_cur_commend(char *line, t_list **list)
{
	int		i;
	m_node	*node;

	i = 0;
	node = new_m_node();
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '<')
			node->input_file = open_input_file(line, &i);
		else if (line[i] == '>')
			node->output_file = open_output_file(line, &i);
		else
		{
			if (!node->commend)
				node->commend = get_str(&line[i], &i);
			node->arguments = parse_arguments(line, node->commend, &i);
			
		}
	}
	ft_lstadd_back(list, ft_lstnew(node));
	if (line[i] && line[i] == '|')
		parse_cur_commend(&line[++i], list);
}

void	parse(char *line, t_list **list)
{
	parse_cur_commend(line, list);

}

size_t string_list_len(char **list)
{
	int i;
	
	i = 0;
	while (list[i])
		i++;
	return (i);
}

void single_qoute(m_node *node, char *line)
{
	int len = string_list_len(node->arguments) - 1;
	node->arguments[len] = ft_strjoin(node->arguments[len], line);
	if (ft_strchr(line, '\''))
		qoute(0, 0);
}

void	tty(void)
{
	char	*line;
	char	cur_dir[64];
	t_list	*list;
	
	list = NULL;
	while (1)
	{
		getcwd(cur_dir, 64);
		
		if(qoute(0, -1) == 1)
			ft_printf("qoute>");
		else if(qoute(0, -1) == 2)
			ft_printf("dqoute>");
		else
			ft_printf("minishell:\e[1;34m%s\e[0m>", cur_dir);
		line = get_next_line(0);
		if(qoute(0, -1) == 1)
			single_qoute((m_node *)(ft_lstlast(list)->content), line);
		else 
			parse(strip_nl(line), &list);
		if(qoute(0, -1) != 1)
		{
			printf_list(list);
			ft_lstclear(&list, free);
		}
		if (line == NULL)
			break ;
	}	
}
