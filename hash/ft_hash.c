

#include "ft_hash.h"

/* Privates members */

static void hash_free(t_hash *obj)
{

}


/** Public members */

static int	hash_newone(t_hash *obj, char *msg)
{
	
}

static void	hash_display(t_hash *obj, t_options opt)
{

	//free all 
}

int		hash_create(t_hash *obj, t_hash_type type)
{
	//assign good method
	int	(* hash_type_init[nbr_hash_type])(/*arg*/);

	hash_type_init[e_md5] = md5_init;
	hash_type_init[e_sha256] = sha256_init;

	return (0);
}