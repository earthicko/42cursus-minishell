#include "builtin_commands.h"
#include "executor_internal.h"
#include "libft.h"
#include "libft_def.h"
#include "t_exec_unit.h"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


static int	map_cmd(char *cmd)
{

	const char	*builtin_cmds[8] = {
		"",
		"cd",
		"echo",
		"export",
		"pwd",
		"unset",
		"env",
		"exit"
	};
	const int	cmd_len = ft_strlen(cmd);
	int			i;

	i = -1;
	while (++i < 8)
		if (ft_strncmp(builtin_cmds[i], cmd, cmd_len + 1) == 0)
			return (i);
	return (CODE_ERROR_GENERIC);
}

int	exec_builtin_cmd(t_exec_unit *unit, int mode)
{
	const t_exec_builtin	exec_builtin[8] = {
		0, builtin_cd, builtin_echo,  builtin_export,
		builtin_pwd, builtin_unset, builtin_env, builtin_exit
	};
	const int				cmd_idx = map_cmd(unit->argv[0]);
	int						stat;

	if (mode == PARENTSHELL)
		io_manager(STDINOUT_BACKUP);
	stat = process_redir(unit->redir_arr, unit->n_redir);
	if (stat == CODE_ERROR_IO)
		return (1);
	if (cmd_idx == CODE_ERROR_GENERIC)
	{
		ft_dprintf(2, "Failed to map proper cmd index\n");
		return (-1);
	}
	stat = exec_builtin[cmd_idx](unit->argv);
	if (mode == PARENTSHELL)
		io_manager(STDINOUT_RESTORE);
	return (stat);
}
