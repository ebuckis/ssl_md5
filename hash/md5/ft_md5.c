
#include "hash/ft_hash.h"
#include "ft_md5.h"

#include <math.h>



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

uint32_t	left_rotate32(uint32_t val, int n)
{
	uint32_t ret;

	n = n % 32;
	if (n == 0)
		return (val);
	ret = (val << n) | (val >> (32 - n));
	return (ret);
}

uint32_t	md5_bitwise(t_buffer buf, char opt)
{
	if (opt == 'algo.f')
		return ((buf.b & buf.c) | ((~buf.b) & buf.d));
	else if (opt == 'g')
		return ((buf.b & buf.d) | (buf.c & (~buf.d)));
	else if (opt == 'h')
		return (buf.b ^ buf.c ^ buf.d);
	else if (opt == 'i')
		return (buf.c ^ (buf.b | (~buf.d)));
}

void	ft_algo_md5(t_buffer *buf, uint32_t *w)
{
	uint32_t	tmp;
	int16_t		i;
	t_md5algo	algo;

	i = 0;
	while (i < 64)//512bits -> 64bytes
	{
		if (i < 16) {
			algo.f = md5_bitwise(*buf, 'algo.f');
			algo.g = i;
		}
		else if (i < 32) {
			algo.f = md5_bitwise(*buf, 'g');
			algo.g = (5 * i + 1) % 16;
		}
		else if (i < 48) {
			algo.f = md5_bitwise(*buf, 'h');
			algo.g = (3 * i + 5) % 16;
		}
		else if (i < 64) {
			algo.f = md5_bitwise(*buf, 'i');
			algo.g = (7 * i) % 16;
		}
		tmp = buf->d;
		buf->d = buf->c;
		buf->c = buf->b;
		buf->b = left_rotate32(buf->a + algo.f + algo.k[i] + w[algo.g], algo.r[i]) + buf->b;
		buf->a = tmp;
		i++;
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
	len *= 8;//in bits
/*	uint64_t *tmp_s1;
	tmp_s1 = (uint64_t *)s1;
	tmp_s1[(max_len / 8) - 1] = len;*/
	//TODO: voir si ça fonctionne
	while (i < 8)
	{
		s1[(max_len - 8) + i] = (len >> (i * 8));//msb first
		i++;
	}

	return (s1);
}

char *md5_hash(t_hash this, char *str)
{
	int			i;
	t_md5		md5;

	/* Find Size */
	md5.len = (strlen(str) + 1 + 8) * 8;//len + 0x1 (8bits) + len (64bits)
	md5.n_block = (md5.len % 512 == 0) ? (md5.len / 512) : (md5.len / 512 + 1);
	md5.len = md5.n_block * 512;

	md5.msg = (uint8_t *)malloc(md5.len / 8);
	bzero((void *)md5.msg, md5.len / 8);
	/* */

	md5.msg = ft_padding(md5.msg, (uint8_t *)str, md5.len / 8);

	t_buffer buf_tmp;

	i = 0;
	while (i < md5.len)
	{
		/* copy struct */
		buf_tmp = md5.buf;
		ft_algo_md5((uint32_t *)(md5.msg + (i / 8)), &buf_tmp);
		md5.buf.a += buf_tmp.a;
		md5.buf.b += buf_tmp.b;
		md5.buf.c += buf_tmp.c;
		md5.buf.d += buf_tmp.d;
		i += 512;//continue in the padding
	}
	free(md5.msg);


	/************remove this [debug]*****************/
	uint32_t f_table[4];

	f_table[0] = md5.buf.a;
	f_table[1] = md5.buf.b;
	f_table[2] = md5.buf.c;
	f_table[3] = md5.buf.d;

	for (i = 0; i < 16; i++)
		printf("%.2x", ((uint8_t *)f_table)[i]);
	printf("\n");
	/************remove this [debug]*****************/
	return ((char *)md5.msg);
}

static void	md5_free(t_hash *this)
{
	//free every thing
}

static int	md5_newone(t_hash *this, char *msg)
{

}

int		md5_init(t_hash *this)
{
	this->newone = md5_newone;//prepare
	this->hash = md5_hash;//hash
	this->free = md5_free;//free memory
	this->md5.buf.a = 0x67452301;
	this->md5.buf.b = 0xEFCDAB89;
	this->md5.buf.c = 0x98BADCFE;
	this->md5.buf.d = 0x10325476;
	this->md5.algo.k = k;//mem copy
	this->md5.algo.r = r;//mem copy

	//pointeur de fonction
	//init variable
}

