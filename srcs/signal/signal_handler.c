#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"
#include "msgdef.h"

void	_sighandler_int_interactive(int signo)
{
	(void)signo;
	ft_printf("\r%s%s  \n", MSG_SHELL_PROMPT, rl_line_buffer);
	rl_replace_line("", TRUE);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	_sighandler_int_heredoc(int signo)
{
	(void)signo;
	exit(0);
	return ;
}