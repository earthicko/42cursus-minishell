#include <stdlib.h>
#include <unistd.h>
#include "strutils.h"
#include "libft.h"
#include "envmanager.h"
#include "heredoc_internal.h"

static char	*_extract_filename(int slot)
{
	char	*cursor;
	char	*fullname;

	fullname = ttyname(slot);
	if (!fullname)
		return (NULL);
	cursor = fullname;
	while (*cursor)
		cursor++;
	while (cursor != fullname)
	{
		if (*cursor == '/')
			break ;
		cursor--;
	}
	if (*cursor == '/')
		cursor++;
	return (ft_strdup(cursor));
}

int	_heredoc_init(
		int *n_heredoc, int *i_current, char **prefix_filename)
{
	char	*home_dir;
	char	*ttyfilename;
	char	*temp;
	int		stat;

	ttyfilename = _extract_filename(ttyslot());
	if (!ttyfilename)
		return (CODE_ERROR_GENERIC);
	stat = envman_getval("HOME", &home_dir);
	if (stat)
	{
		*prefix_filename = ttyfilename;
		// TODO: 경고 메시지
		return (CODE_OK);
	}
	temp = ft_strmerge(
			5, home_dir, "/", ttyfilename, PREFIX_HEREDOC_TEMPFILE, "_");
	free(home_dir);
	free(ttyfilename);
	*prefix_filename = temp;
	if (!temp)
		return (CODE_ERROR_MALLOC);
	_heredoc_clear(n_heredoc, i_current, *prefix_filename, -1);
	return (CODE_OK);
}