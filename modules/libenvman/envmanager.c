#include <stdlib.h>
#include "libft.h"
#include "envmanager_internal.h"

// init: set envp
// clear: set none
// getval: set (char **)buf, name
// setval: set name, val
// unsetval: set name
// getenvp: set (char ***)buf
int	envmanager(char **envp, void *buf, char *name, char *val)
{
	static t_list	*envlist;

	if (envp && !buf && !name && !val)
		return (envmanager_init(&envlist, envp));
	else if (!envp && !buf && !name && !val)
		return (envmanager_clear(&envlist));
	else if (!envp && buf && name && !val)
		return (envmanager_getval(envlist, buf, name));
	else if (!envp && !buf && name && val)
		return (envmanager_setval(&envlist, name, val));
	else if (!envp && !buf && name && !val)
		return (envmanager_unsetval(&envlist, name));
	else if (!envp && buf && !name && !val)
		return (envmanager_getenvp(envlist, buf));
	return (CODE_ERROR_DATA);
}
