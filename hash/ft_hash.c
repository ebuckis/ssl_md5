

#include "ft_hash.h"

/* Privates members */

static void hash_free(t_hash *this)
{

}


/** Public members */

static int	hash_newone(t_hash *this, char *msg)
{
	// hash type
}

static void	hash_display(t_hash *this, t_options opt)
{
	//useless ?

	//free all 
}

int		hash_create(t_hash *this, t_hash_type type)
{
	//assign good method
	int	(* hash_type_init[nbr_hash_type])(/*arg*/);

	hash_type_init[e_md5] = md5_init;
	hash_type_init[e_sha256] = sha256_init;

	return (0);
}