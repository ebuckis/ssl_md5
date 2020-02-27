#include "math.h"
#include <stdio.h>
#include <stdlib.h>


char	*md5_hash(const char *str);

int main(int ac, char **av)
{
	int i = 1;

//	while (i < ac)
//	{
		md5_hash(av[1]);
		//printf("%s\n", hash_md5(av[i]);
//		i++;
//	}

	return (0);
}