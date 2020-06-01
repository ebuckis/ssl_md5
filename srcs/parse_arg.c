
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

int ft_parse(int ac, char **av)
{
	int i;
	int j;

	i = 2;
	j = 0;
	while (i < ac)
	{
		if (av[j] == '-')
		{
			j++;
			while (av[j] != '\0')
			{
				if (av[j] == 'p')
				{

				}
				else if (av[j] == 'q')
				{
					
				}
				else if (av[j] == 'r')
				{
					
				}
				else if (av[j] == 's')
				{
					//read juste after
					//read next arg
				}
				else
				{
					//parse error
					return (-1);
				}
				j++;
			}
		}
		
		/* code */
		j++;
	}
	


	return (0);
}