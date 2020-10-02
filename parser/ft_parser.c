#include "ft_parser.h"

t_hash_type	parser_gettype(t_parser *this)
{
	t_hash_type	i;
	int			ret;
	char		*hash_type[nbr_hash_type];

	hash_type[e_md5] = "md5";
	hash_type[e_sha256] = "sha256";

	i = e_md5;
	while (i < nbr_hash_type)
	{
		if (strcmp(hash_type[i], ) == 0)//TODO:
			return (i);
		i++;
	}
	return (-1);
}

int parser_create(t_parser *this, int ac, char **av)
{
	this->nb_of_arg = ac;
	this->av = av;
	this->current = 1;

	return (0);
}