/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:43:39 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/16 20:28:24 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_args(char **args)
{
	int	count;

	if (!args)
		return (0);
	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	add_argument(t_cmd *cmd, char *arg)
{
	char	**new_args;
	int		count;
	int		i;

	if (!cmd || !arg)
		return ;
	count = count_args(cmd->args);
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = -1;
	while (++i < count)
		new_args[i] = cmd->args[i];
	new_args[count] = malloc(ft_strlen(arg) + 1);
	if (!new_args[count])
	{
		free(new_args);
		return ;
	}
	ft_strcpy(new_args[count], arg);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

t_cmd	*parse_simple_command(t_token **current, t_prompt *prompt)
{
	t_cmd	*cmd;

	if (!current || !*current)
		return (NULL);
	cmd = create_command(prompt->hd_lst);
	if (!cmd)
		return (NULL);
	while (*current && (*current)->type != T_PIPE)
	{
		if (is_redirect_token((*current)->type))
		{
			if (parse_redirections(current, cmd, prompt) == FAILURE)
				return (free_commands(cmd), NULL);
		}
		else if ((*current)->type == T_WORD)
		{
			add_argument(cmd, (*current)->value);
			*current = (*current)->next;
		}
		else
			break ;
	}
	return (cmd);
}

int	parse_redirections(t_token **current, t_cmd *cmd, t_prompt *prompt)
{
	t_token_type	redir_type;

	if (!current || !*current || !cmd)
		return (FAILURE);
	redir_type = (*current)->type;
	*current = (*current)->next;
	if (!*current || ((*current)->type != T_WORD && (*current)->type != T_CORRECT_FILNAME && (*current)->type != T_WRONG_FILNAME))
	{
		return (FAILURE);
	}
	if (redir_type == T_REDIR_IN || redir_type == T_HEREDOC)
		set_input_file(cmd, *current, prompt, redir_type);
	else if (redir_type == T_REDIR_OUT)
		set_output_file(cmd, *current, 0, redir_type);
	else if (redir_type == T_APPEND)
		set_output_file(cmd, *current, 1, redir_type);
	*current = (*current)->next;
	return (SUCCESS);
}
