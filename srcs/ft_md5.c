#include <stdio.h>
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

uint32_t k[64] = {
	3614090360, 3905402710,  606105819, 3250441966, 4118548399, 1200080426, 2821735955, 4249261313,
	1770035416, 2336552879, 4294925233, 2304563134, 1804603682, 4254626195, 2792965006, 1236535329,
	4129170786, 3225465664,  643717713, 3921069994, 3593408605,   38016083, 3634488961, 3889429448,
	 568446438, 3275163606, 4107603335, 1163531501, 2850285829, 4243563512, 1735328473, 2368359562,
	4294588738, 2272392833, 1839030562, 4259657740, 2763975236, 1272893353, 4139469664, 3200236656,
	 681279174, 3936430074, 3572445317,   76029189, 3654602809, 3873151461,  530742520, 3299628645,
	4096336452, 1126891415, 2878612391, 4237533241, 1700485571, 2399980690, 4293915773, 2240044497,
	1873313359, 4264355552, 2734768916, 1309151649, 4149444226, 3174756917,  718787259, 3951481745
};

int 	r[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

uint32_t	h0 = 0x67452301;
uint32_t	h1 = 0xEFCDAB89;
uint32_t	h2 = 0x98BADCFE;
uint32_t	h3 = 0x10325476;

uint32_t	left_rotate(uint32_t val, int n)
{
	uint32_t ret;

	n = n % 32;
	if (n == 0)
		return (val);
	ret = (val << n) | (val >> (32 - n));
	return (ret);
}

uint32_t	f_function(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | ((~x) & z));
}

uint32_t	g_function(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | (y & (~z)));
}

uint32_t	h_function(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t	i_function(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (x | (~z)));
}

void	ft_algo_md5(uint32_t *w, t_letters *let)
{
	uint32_t f, g, tmp;

	for (int i = 0; i < 64; i++)
	{
		if (i < 16) {
			f = f_function(let->b, let->c, let->d);
			g = i;
		}
		else if (i < 32) {
			f = g_function(let->b, let->c, let->d);
			g = (5 * i + 1) % 16;
		}
		else if (i < 48) {
			f = h_function(let->b, let->c, let->d);
			g = (3 * i + 5) % 16;
		}
		else if (i < 64) {
			f = i_function(let->b, let->c, let->d);
			g = (7 * i) % 16;
		}
		tmp = let->d;
		let->d = let->c;
		let->c = let->b;
		let->b = left_rotate(let->a + f + k[i] + w[g], r[i]) + let->b;
		let->a = tmp;
	}
}

uint8_t *ft_padding(uint8_t *s1, const uint8_t *s2, uint32_t max_len)
{
	uint32_t i;
	uint64_t len;

	i = 0;
	len = strlen((char *)s2);
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
		s1[max_len - (8 - i)] = (len >> (i * 8));
		i++;
	}

	return (s1);
}

char *md5_hash(const char *str)
{
	int			i;
	uint32_t	len;
	uint32_t	n_block;
	uint8_t		*msg;

	/* Find Size */
	len = (strlen(str) + 1 + 8) * 8;
	n_block = (len % 512 == 0) ? len / 512 : len / 512 + 1;
	len = n_block * 512;
	msg = (uint8_t *)malloc(len / 8);
	bzero((void *)msg, len / 8);
	/* */
	msg = ft_padding(msg, (uint8_t *)str, len / 8);

	t_letters let;

	i = 0;
	while (i < len)
	{
		let.a = h0;
		let.b = h1;
		let.c = h2;
		let.d = h3;
		ft_algo_md5((uint32_t *)(msg + (i / 8)), &let);
		h0 += let.a;
		h1 += let.b;
		h2 += let.c;
		h3 += let.d;
		i += 512;
	}

	uint32_t f_table[4];

	f_table[0] = h0;
	f_table[1] = h1;
	f_table[2] = h2;
	f_table[3] = h3;

	for (i = 0; i < 16; i++)
		printf("%.2x", ((uint8_t *)f_table)[i]);
	printf("\n");
	return ((char *)msg);
}
