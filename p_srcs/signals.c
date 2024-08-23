/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:28:22 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/23 21:24:52 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

// Function to determine the exit code
// void	determine_exit_code(int *exit_code)
// {
// 	if (g_signal == SIGINT)
// 		*exit_code = 130;
// 	else if (g_signal == SIGQUIT)
// 		*exit_code = 131;
// 	else
// 		*exit_code = 0;
// }
/*	Terminal ctrl setting disables echo messages of
	ctrl signals using flag ECHOCTRL
*/

void	_handle_child_signal(int signal)
{
	g_signal = signal;
	if (signal == SIGINT)
	{
		// write(1, "^C\n", 3);
	}
	if (signal == SIGQUIT)
	{
		// write(1, "^\\Quit: 3\n", 10);
	}
	return ;
}

// Signal handler for other signals
void	_handle_other_signals(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// Function to handle signals setup
void	_handle_signals(t_process stats, t_data *data)
{
	struct sigaction	sa;

	(void)data;
	if (stats == CHILD_PROCESS)
	{
		sa.sa_handler = &_handle_child_signal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			exit(-1);
		if (sigaction(SIGQUIT, &sa, NULL) < 0)
			exit(-1);
	}
	else
	{
		sa.sa_handler = &_handle_other_signals;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			return ;
		if (signal(SIGQUIT, SIG_IGN))
		// if (signal(SIGQUIT, SIG_IGN) < 0)
			return ;
	}
}

void	_init_terminal(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) != 0)
		_err_msg("Error!\n", EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &term) != 0)
		_err_msg("Error!\n", EXIT_FAILURE);
}
