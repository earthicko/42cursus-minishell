#ifndef ENVMANAGER_H
# define ENVMANAGER_H

int		envman_split_envstr(char *str, char **ret_name, char **ret_val);
char	*envman_compose_envstr(char *name, char *val);

int		envmanager(char **envp, void *buf, char *name, char *val);

int		envmanager_expand(char **buf);

#endif
