
/*
** header
*/
/*
func_ptr_parse
func_ptr_hash

*/
#include "ft_ssl.h"

int		print_usage(void)
{
	ft_putstr("usage\n");
	return (1);
}

int		main(int ac, char **av)
{
	int		ret;
	char	*target;
	t_ssl	ssl;

	if (hash_type(ac, av, ssl) == 0)//get type md5 || sha256
		return (1);

	target = NULL;
	while (parse_arg(ac, av) != 0)//1 if ok, 0 if end, negative if error
	{
		ret = run(ssl);//use target + option (negative return  if an error occures)
		if (ret < 0)
			manage_errors(ret, target);
	}
	
	
	return (0);
}