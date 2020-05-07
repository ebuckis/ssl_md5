
#include <stdint.h>

#ifndef	FT_SHA256_H
#define	FT_SHA256_H

typedef struct	s_var
{
	uint32_t	h0;
	uint32_t	h1;
	uint32_t	h2;
	uint32_t	h3;
	uint32_t	h4;
	uint32_t	h5;
	uint32_t	h6;
	uint32_t	h7;
	/* data */
}				t_var;

typedef struct	s_sha256
{
	t_var		tmp;
	t_var		result;
	uint32_t	len;
	uint32_t	n_block;
	uint8_t		*msg;

	char	*(* run)(struct s_sha256 *this, const char *str);
	/* data */
}				t_sha256;



#endif