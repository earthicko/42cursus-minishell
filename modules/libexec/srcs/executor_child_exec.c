#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "envmanager.h"
#include "executor_internal.h"
#include "libft.h"
#include "libft_def.h"
#include "strutils.h"


//int	signal_set_state_default(void);

static int	set_fd_stream(t_info *info)
{
	const t_exec_unit	cur_unit = info->units->arr[info->cur_idx];

	if (info->units->n_unit == 1)
		return (process_redir(cur_unit.redir_arr, cur_unit.n_redir));
	if (info->cur_idx == 0)
	{
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	}
	else if (info->cur_idx == info->n_unit - 1)
	{
		if (dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0)
			return (CODE_ERROR_IO);
	}
	else
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (process_redir(cur_unit.redir_arr, cur_unit.n_redir));
}

// 참고만: stat, lstat 심볼릭 링크파일인 경우 동작이 다르대..
// TODO: 빌트인 커맨드 실패에 대한 exit status 세분화
// TODO: 놈 맞추기, 함수 쪼개기
 void	child_exec_cmd(t_info *info)
{
	struct stat	s_statbuf;
	char	**argv;
	int		status;
	char	**envp_paths;
	int		builtin_stat;

	if (set_fd_stream(info) < 0)
		exit(EXIT_FAILURE);
	argv = info->units->arr[info->cur_idx].argv;
	status = envman_getenvp(&envp_paths);
	if (status)
	{
		// 에러메시지를 여기서 체크해도 무방할듯
		ft_printf("%s: error while getenvp, stat %d\n", __func__, status);
		exit(EXIT_FAILURE);
	}
	status = find_exec(&argv[0]);
	if (status > 0)
	{
		builtin_stat = exec_builtin_cmd(info->units->arr + info->cur_idx, SUBSHELL);
		if (builtin_stat != CODE_OK)
			exit(EXIT_FAILURE);
		exit(CODE_OK);
	}
	// 아래 두 경우에 대한 에러메시지는 서브루틴에서 처리
	if (status == CODE_ERROR_MALLOC)
		exit(EXIT_FAILURE);
	if (status == CODE_ERROR_GENERIC)
		exit(127);
	if (stat(argv[0], &s_statbuf) != 0)
	{
		perror("stat function failed\n");
		exit(EXIT_FAILURE);
	}
	if (S_ISDIR(s_statbuf.st_mode))
	{
		dprintf(2, "shell: %s: is a directory\n", argv[0]);
		exit(126);
	}
	if (access(argv[0], X_OK) == 0)
		execve(argv[0], argv, envp_paths);
	else 
	{
		dprintf(2, "shell: %s: Permission denied\n", argv[0]);
		exit(126);
	}
	//As the convention, call _exit(127) in such case
	exit(127);
}
