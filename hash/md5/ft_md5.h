#include <stdint.h>

typedef struct	s_buffer
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_buffer;

typedef	struct	s_md5algo
{
	uint32_t	f;
	uint32_t	g;
	uint32_t	k[64];
	int			r[64];
}				t_md5algo;

typedef struct	s_md5
{
	t_buffer	buf;
	t_md5algo	algo;
	uint32_t	len;
	uint32_t	n_block;
	uint8_t		*msg;

}				t_md5;
