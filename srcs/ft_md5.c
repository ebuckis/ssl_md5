int	get_part_str(char *str, int *i, unsigned **w)
{
	int		is_end = 0;
	int		j = 0;
	int		k;
	unsigned	res;
	int len;

	len = strlen(str);

	while (j && j < 16)
	{
		k = 0;
		res = 0;
		while (k < 4)
		{
			if (len < ((*i) * 64) + (j * 4) + k)
				res |= str[((*i) * 64) + (j * 4) + k] << k;
			else
				is_end = 1;
			k++;
		}
		(*w)[j] = res;
		j += 4;
	}
	return (is_end);
}

char *md5_hash(const char *str)
{
	unsigned	w[16] = {0};
	int i;
	unsigned	a, b, c, d;
	unsigned	h0 = 0x67452301;
	unsigned	h1 = 0xEFCDAB89;
	unsigned	h2 = 0x98BADCFE;
	unsigned	h3 = 0x10325476;

	i = 0;

	a = h0;
	b = h1;
	c = h2;
	d = h3;

	while (get_part_str(str, &i, &w))
	{

	}
}