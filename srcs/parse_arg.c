
#include "ft_ssl.h"
#include "parse_arg.h"

e_hash_type	get_hash_type(int ac, char **av)
{
	int			ret;
	e_hash_type	i;
	char		*hash_type[nbr_hash_type];

	hash_type[md5_type] = "md5";
	hash_type[sha256_type] = "sha256";
	if (ac < 2)
		return (-2);
	i = md5_type;
	while (i < nbr_hash_type)
	{
		if (strcmp(hash_type[i]))
			return (i);
		i++;
	}
	return (-1);
}

