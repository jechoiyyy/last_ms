/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:01:26 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/17 15:01:27 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "types.h"
# include "utils.h"
# include "parser.h"
# include "executor.h"

int	output_process(t_shell *shell, t_prompt *prompt);

#endif