
/*
** header
*/
/*
func_ptr_parse
func_ptr_hash

*/
#include "ft_ssl.h"

int		hash_type(int ac, char **av, t_ssl *ssl)
{
	if (ac < 2)
		return (1);
	if (ft_strcmp(av[1], "md5") == 0)
	{
		ssl->parse = parse_arg_pqrs;
		ssl->hash = md5_hash;
	}
	else if (ft_strcmp(av[1], "sha256") == 0)
	{
		ssl->parse = parse_arg_pqrs;
		ssl->hash = sha256_hash;
	}
	else
	{
		printf("md5 or sha256\n");
		return (0);
	}
	return (1);	
		
}

void 	ssl_init(t_ssl *ssl)
{
	ssl->op.p = 0;
	ssl->op.q = 0;
	ssl->op.r = 0;
	ssl->op.s = 0;
	ssl->target = NULL;
	ssl->result = NULL;
	ssl->std_in_read = 0;
} 

int		main(int ac, char **av)
{
	int		ret;
	char	*target;
	t_ssl	ssl;

	ssl_init(&ssl);
	if (hash_type(ac, av, &ssl) == 0)//get type md5 || sha256
		return (1);//invalid command

	while (ssl.parse(&ssl, ac, av) != 0)//1 if ok, 0 if end, negative if error
	{
		ret = ssl.hash(&ssl);//use target + option (negative return  if an error occures)
		if (ret < 0)
			manage_errors(ret, target);
	}
	return (0);
}