#include <stddef.h>
#include "libft_def.h"
#include "t_token.h"
#include "t_node.h"
#include "parser_internal.h"

t_node	*_parse_addchild_and_return(t_parser *p, t_node *root, t_node *child)
{
	if (_node_addchild(root, child))
		return (_parse_abort(p, root, child));
	return (root);
}

int	_parse_terminal_and_addchild(t_parser *p, int n_t, t_node *root)
{
	int		stat;
	t_node	*child;

	child = _parse_terminal(p, n_t);
	if (!child)
	{
		_parse_abort(p, root, NULL);
		return (CODE_ERROR_GENERIC);
	}
	stat = _node_addchild(root, child);
	if (stat)
	{
		_parse_abort(p, root, child);
		return (stat);
	}
	return (CODE_OK);
}

t_node	*_parse_abort(t_parser *p, t_node *root, t_node *child)
{
	int	rewind_counter;

	rewind_counter = 0;
	if (root)
	{
		rewind_counter += node_getntokens(root);
		_node_destroy(root);
	}
	if (child)
	{
		rewind_counter += node_getntokens(child);
		_node_destroy(child);
	}
	p->tok_curr -= rewind_counter;
	return (NULL);
}
