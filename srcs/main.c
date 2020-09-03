
/*
** header
*/
/*
func_ptr_parse
func_ptr_hash

*/
#include	"errors/ft_errrors.h"
#include	"hash/ft_hash.h"
#include	"parser/ft_parser.h"

int		main(int ac, char **av)
{
	int			ret;
	char		msg;
	t_parser	parser;
	t_hash		hash;

	ret = parser_create(&parser, ac, av);
	if (ret != ret_ok)
		return (display_errror(ret));
	hash_create(&hash, parser.get_type(&parser));//maybe get the return
	while ((ret = parser.get_message(&parser, &msg)) != ret_eof)
	{
		hash.new(&hash, msg);
		hash.display(&hash);
	}
	return (0);
}
