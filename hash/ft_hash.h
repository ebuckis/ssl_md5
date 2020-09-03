


#ifndef		FT_HASH_H
#define		FT_HASH_H

#include	"parser/ft_options.h"
#include	"hash/ft_hash_type.h"

typedef struct	s_hash
{
	int		(* newone)(struct s_hash *obj, char *msg);
	void	(* display)(struct s_hash *obj, t_options opt);
	/* data */
}t_hash;

int		hash_create(t_hash *obj, t_hash_type type);

#endif