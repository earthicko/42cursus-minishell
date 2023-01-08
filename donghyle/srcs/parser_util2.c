#include "t_node.h"
#include "t_token.h"
#include "parser.h"
#include <stddef.h>

static int	can_parse_io_file(t_parser *parser)
{
	if (parser_is_last_token(parser))
		return (0);
	if (parser->tok_curr->type == TOKENTYPE_REDIR_IN)
		return (1);
	if (parser->tok_curr->type == TOKENTYPE_REDIR_OUT)
		return (1);
	if (parser->tok_curr->type == TOKENTYPE_REDIR_OUT_APPEND)
		return (1);
	return (0);
}

t_node	*parse_io_file(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	if (!can_parse_io_file(parser))
		return (NULL);
	root = create_node(NODETYPE_IO_FILE, parser->tok_curr->content, 1);
	if (!root)
		return (abort_parse(parser, NULL, NULL));
	parser_increment_token(parser, 1);
	child = parse_filename(parser);
	if (!child)
		return (abort_parse(parser, root, NULL));
	if (addchild_node(root, child))
		return (abort_parse(parser, root, child));
	return (root);
}

t_node	*parse_io_redirect(t_parser *parser)
{
	t_node	*root;
	t_node	*child;

	if (parser_is_last_token(parser))
		return (NULL);
	root = create_node(NODETYPE_IO_REDIRECT, "", 0);
	if (!root)
		return (NULL);
	child = parse_io_file(parser);
	if (child)
	{
		if (addchild_node(root, child))
			return (abort_parse(parser, root, child));
		return (root);
	}
	child = parse_io_here(parser);
	if (child)
	{
		if (addchild_node(root, child))
			return (abort_parse(parser, root, child));
		return (root);
	}
	return (abort_parse(parser, root, NULL));
}
