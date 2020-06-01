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

#include "ft_sha256.h"

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

void	ft_algo_sha256(uint32_t *w, t_var *let)
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
		s1 = right_rotate(let->h4, 6) ^ right_rotate(let->h4, 11) ^ right_rotate(let->h4, 25);
		ch = (let->h4 & let->h5) ^ ((~let->h4) & let->h6);
		tmp1 = let->h7 + s1 + ch + k[i] + w[i];
		s0 = right_rotate(let->h0, 2) ^ right_rotate(let->h0, 13) ^ right_rotate(let->h0, 22);
		tmp2 = s0 + ((let->h0 & let->h1) ^ (let->h0 & let->h2) ^ (let->h1 & let->h3));

		let->h7 = let->h6;
        let->h6 = let->h5;
        let->h5 = let->h4;
        let->h4 = let->h3 + tmp1;
        let->h3 = let->h2;
        let->h2 = let->h1;
        let->h1 = let->h0;
        let->h0 = tmp1 + tmp2;
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

void	sha265_find_size(t_sha256 *this, char *str)
{
	this->len = (strlen(str) + 1 + 8) * 8;
	if (this->len % 512 == 0)
	{
		this->n_block = this->len / 512;
	}
	else
	{
		this->n_block = this->len / 512 + 1;
	}
	this->len = this->n_block * 512;
	this->msg = (uint8_t *)malloc(this->len / 8);
	bzero((void *)this->msg, this->len / 8);
}
void	sha265_sum_struct(t_sha256 *this)
{
	this->result.h0 += this->tmp.h0;
	this->result.h1 += this->tmp.h1;
	this->result.h2 += this->tmp.h2;
	this->result.h3 += this->tmp.h3;
	this->result.h4 += this->tmp.h4;
	this->result.h5 += this->tmp.h5;
	this->result.h6 += this->tmp.h6;
	this->result.h7 += this->tmp.h7;
}

char *sha256_run(t_sha256 *this, const char *str)
{
	int			i;

	sha256_find_size(this, str);
	this->msg = ft_padding(this->msg, (uint8_t *)str, this->len / 8);
	
	//for (int j = 0; j < this->len  / 8; j++)
	//	printf("msg[%d] : 0x%.2x\n", j , this->msg[j]);

	i = 0;
	while (i < this->len)
	{
		//copy struct
		this->tmp = this->result;
		ft_algo_sha256((uint32_t *)(this->msg + (i / 8)), &(this.tmp));
		//sum struct
		sha256_sum_struct(this);
		i += 512;
	}

/*	uint32_t f_table[8];
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
	printf("\n");*/

	return ((char *)this->msg);
}

void	sha256_init(t_sha256 *this)
{
	if (this->msg != NULL)
	{
		free(this->msg);
	}
	this->msg = NULL;
	this->result.h0 = 0x6a09e667;
	this->result.h1 = 0xbb67ae85;
	this->result.h2 = 0x3c6ef372;
	this->result.h3 = 0xa54ff53a;
	this->result.h4 = 0x510e527f;
	this->result.h5 = 0x9b05688c;
	this->result.h6 = 0x1f83d9ab;
	this->result.h7 = 0x5be0cd19;

}

int	sha256_create(t_sha256 *this)
{
	this->run = sha256_run;
	this->msg = NULL;

}