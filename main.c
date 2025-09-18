/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:34:51 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/17 17:47:40 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "setup.h"
#include "input.h"
#include "list.h"
#include "utils.h"
#include "output.h"
#include "global.h"
#include "sigft.h"

int	g_exit_status = 0;

static void	cleanup_resource(t_shell *shell, t_prompt *prompt)
{
	cleanup_shell(shell);
	if (prompt->input)
	{
		free(prompt->input);
		prompt->input = NULL;
	}
	clear_token_list(&prompt->token_lst);
	clear_envp_list(&prompt->envp_lst);
	clear_hd_list(&prompt->hd_lst);
}

//파싱부에서 실행부쪽으로 안넘어가는 상황은 token_lst를 NULL로 세팅합니다.
int	main(int ac, char **av, char **envp)
{
	t_prompt	prompt;
	t_shell		shell;

	if (ac != 1 || !av || ready_minishell(&prompt, &shell, envp) == 0)
		return (1);
	while (!shell.exit_flag)
	{
		if (input_process(&prompt) == 0)
			break ;
		if (prompt.token_lst)
		{
			setup_signals_noninteractive();
			g_exit_status = output_process(&shell, &prompt);
			check_child_signal_status();
			setup_signals_interactive();
		}
		free(prompt.input);
		prompt.input = NULL;
		clear_token_list(&prompt.token_lst);
		clear_hd_list(&prompt.hd_lst);
	}
	cleanup_resource(&shell, &prompt);
	return (g_exit_status);
}
