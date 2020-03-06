/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcabus <kcabus@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:16:15 by kcabus            #+#    #+#             */
/*   Updated: 2020/03/06 14:54:05 by kcabus           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
}t_letters;

uint32_t k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

/*int 	r[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};*/

uint32_t	h0 = 0x6a09e667;
uint32_t	h1 = 0xbb67ae85;
uint32_t	h2 = 0x3c6ef372;
uint32_t	h3 = 0xa54ff53a;
uint32_t	h4 = 0x510e527f;
uint32_t	h5 = 0x9b05688c;
uint32_t	h6 = 0x1f83d9ab;
uint32_t	h7 = 0x5be0cd19;

uint32_t	right_rotate(uint32_t val, int n)
{
	uint32_t ret;

	n = n % 32;
	if (n == 0)
		return (val);
	ret = (val >> n) | (val << (32 - n));
	return (ret);
}

uint32_t	bit_reverse32(uint32_t val)
{
	uint32_t	tmp;

	tmp = val >> 24;
	tmp |= (val & 0x00FF0000) >> 8;
	tmp |= (val & 0x0000FF00) << 8;
	tmp |= (val & 0xFF) << 24;
	return (tmp);
}

void	ft_algo_sha256(uint32_t *w, t_letters *let)
{
	uint32_t s0, s1, tmp1, tmp2, ch;

	for (int i = 0; i < 64; i++)
	{
		w[i] = bit_reverse32(w[i]);
	}


	for (int i = 16; i < 64; i++)
	{
		s0 = (right_rotate(w[i - 15], 7) ^ right_rotate(w[i - 15], 18) ^ (w[i - 15] >> 3));
		s1 = (right_rotate(w[i - 2], 17) ^ right_rotate(w[i - 2], 19) ^ (w[i - 2] >> 10));
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}


	for (int i = 0; i < 64; i++)
	{
		if (i % 8 == 0)
			printf("\n");
		printf("0x%.8x ", w[i]);
	}

	printf("\n");
	for (int i = 0; i < 64; i++)
	{
		s1 = right_rotate(let->e, 6) ^ right_rotate(let->e, 11) ^ right_rotate(let->e, 25);
		ch = (let->e & let->f) ^ ((~let->e) & let->g);
		tmp1 = let->h + s1 + ch + k[i] + w[i];
		s0 = right_rotate(let->a, 2) ^ right_rotate(let->a, 13) ^ right_rotate(let->a, 22);
		tmp2 = s0 + ((let->a & let->b) ^ (let->a & let->c) ^ (let->b & let->c));

		let->h = let->g;
        let->g = let->f;
        let->f = let->e;
        let->e = let->d + tmp1;
        let->d = let->c;
        let->c = let->b;
        let->b = let->a;
        let->a = tmp1 + tmp2;
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
		s1[max_len - (i + 1)] = (len >> (i * 8));
		i++;
	}

	return (s1);
}

char *sha256_hash(const char *str)
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
	
	for (int j = 0; j < len  / 8; j++)
		printf("msg[%d] : 0x%.2x\n", j , msg[j]);

	t_letters let;

	i = 0;
	while (i < len)
	{
		let.a = h0;
		let.b = h1;
		let.c = h2;
		let.d = h3;
		let.e = h4;
		let.f = h5;
		let.g = h6;
		let.h = h7;
		ft_algo_sha256((uint32_t *)(msg + (i / 8)), &let);
		h0 += let.a;
		h1 += let.b;
		h2 += let.c;
		h3 += let.d;
		h4 += let.e;
		h5 += let.f;
		h6 += let.g;
		h7 += let.h;
		i += 512;
	}

	uint32_t f_table[8];

	f_table[0] = h0;
	f_table[1] = h1;
	f_table[2] = h2;
	f_table[3] = h3;
	f_table[4] = h4;
	f_table[5] = h5;
	f_table[6] = h6;
	f_table[7] = h7;

	for (i = 0; i < 8; i++)
		printf("%.8x ", f_table[i]);
	printf("\n");
	return ((char *)msg);
}
