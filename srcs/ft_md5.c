#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_letters
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}t_letters;


uint32_t 	k[64] = {0};

int 	r[64] = {	 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
					 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
					 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
					 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};

void	init_k(void)
{
	double tmp;

	for (int i = 0; i < 64; i++)
	{
		k[i] = (fabs(sin(i + 1)) * 0x100000000);
		printf("%x\n", k[i]);
	}
}

void	ft_algo_md5(uint8_t *msg, t_letters *l)
{
	uint8_t i;
	uint32_t temp;
	uint32_t f;
	uint32_t g;
	uint32_t w[16] = {0};

	for (int j = 0; j < 16; j++)
	{
		w[j] |= msg[j * 4];
		w[j] |= msg[j * 4 + 1] << 8;
		w[j] |= msg[j * 4 + 2] << 16;
		w[j] |= msg[j * 4 + 3] << 24;
		printf("0x%.8x\n", w[j]);
	}
	i = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			f = (l->b & l->c) | ((~l->b) & l->d);
			g = i;
		}
		else if (i < 32)
		{
			f = (l->d & l->b) | ((~l->d) & l->c);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			f = l->b ^ l->c ^ l->d;
			g = (3 * i + 5) % 16;
		}
		else if (i < 64)
		{
			f = l->c ^ (l->b | (~l->d));
			g = (7 * i) % 16;
		}
		temp = l->d;
		l->d = l->c;
		l->c = l->b;
		l->b = ((uint64_t)(l->a + f + k[i] + w[g]) << r[i]) + l->b;
		l->a = temp;
		i++;
	}
}

char	*ft_padding(char *s1, const char *s2, uint32_t max_len)
{
	uint32_t	i;
	uint64_t	len;

	init_k();
	i = 0;
	len = strlen(s2);
	while (i < len)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = 0x80;
	i = 0;
	len *= 8;
	while (i < 8)
	{
		printf("%d et %d\n", max_len - (i + 1), (len >> (i * 8)));
		s1[max_len - (i + 1)] = (len >> (i * 8));
		i++;
	}
	return (s1);
}

char	*md5_hash(const char *str)
{
	unsigned	w[16] = {0};
	int i;
	unsigned	h0 = 0x67452301;
	unsigned	h1 = 0xEFCDAB89;
	unsigned	h2 = 0x98BADCFE;
	unsigned	h3 = 0x10325476;

	unsigned	len;
	unsigned	n_block;

	char	*msg;

	/* Find Size */
	len = (strlen(str) + 1 + 8) * 8;
	n_block = (len % 512 == 0) ? len / 512 : len / 512 + 1;
	len = n_block * 512;
	msg = (char *)malloc(len / 8);
	bzero((void *)msg, len / 8);
	/* */
	msg = ft_padding((char *)msg, str, len / 8);
	
	t_letters  let;



	i = 0;
	while (i < len)
	{
		let.a = h0;
		let.b = h1;
		let.c = h2;
		let.d = h3;
		ft_algo_md5(msg + (i / 8), &let);
		h0 += let.a;
		h1 += let.b;
		h2 += let.c;
		h3 += let.d;
		i += 512;
	}


	i = 0;

	while (i < len / 8)
	{
		if (i % 8 == 0)
			printf("\n");
		printf("0x%.2X ", (unsigned char)msg[i]);
			i++;
	}
	printf("\n%.2X | %.2X | %.2X | %.2X\n", h0, h1, h2, h3);
	return (msg);
}
