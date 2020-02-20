
#include "ft_ssl.h"

int		get_target_string(t_ssl *ssl, int fd)
{
	//open
	//read
	//close
	ssl->std_in_read = 1;
	return (1);
}

int		parse_arg_pqrs(t_ssl *ssl, int ac, char **av)
{
	static int	i = 2;
	int			ret;

	ret = 0;
	if (i == ac && ssl->std_in_read == 0)
	{//pas d'arg on lit sur stdin
		ret = get_target_string(ssl, 0);
		i++;
	}
	else if (i >= ac)
	{
		return (0);
	}
	else
	{
		while (i < ac && parse_opt(av[i], ssl))
		{
			i++;
		}
	}
	return (1);
}