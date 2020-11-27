


#ifndef		FT_HASH_H
#define		FT_HASH_H

#include	"parser/ft_options.h"
#include	"ft_hash_type.h"

typedef struct	s_hash
{
	void	*private_str;
	char	*(* hash)(struct s_hash *obj, char *msg);
	int		(* newone)(struct s_hash *obj, char *msg);
//	void	(* display)(struct s_hash *obj, t_options opt);
	void	(* free)(struct s_hash *obj);
	/* data */
}t_hash;

int		hash_create(t_hash *obj, t_hash_type type);

#endif