#include "math.h"
#include <stdio.h>
#include <stdlib.h>


int main(int ac, char **av)
{
	int i = 1;

	while (i < ac)
	{
		printf("%s\n", hash_md5(av[i]);
		i++;
	}

	return (0);
}