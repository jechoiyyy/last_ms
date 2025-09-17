/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:02:17 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/17 15:11:30 by jechoi           ###   ########.fr       */
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

//파싱부에서 실행부쪽으로 안넘어가는 상황은 token_lst를 NULL로 세팅합니다.
int	main(int ac, char **av, char **envp)
{
	t_prompt	prompt;
	t_shell		shell;

	if (ac != 1 || !av || ready_minishell(&prompt, &shell, envp) == 0)
		return (-1);
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
		clear_list(&prompt);
	}
	cleanup_shell(&shell);
	free(prompt.input);
	clear_list(&prompt);
	clear_envp_list(&prompt.envp_lst);
	return (g_exit_status);
}
