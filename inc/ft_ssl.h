

typedef	enum	s_type
{
	md5 = 0,
	sha256,
}	t_type;	

typedef	enum	s_errors
{
	illegal_option = -1,
	not_a_file = -2,
}	t_errors;

typedef struct	s_option
{
	unsigned	p;
	unsigned	q;
	unsigned	r;
	unsigned	s;
}	t_option;

typedef struct	s_ssl
{
	t_type		type;
	t_option	op;
	char		*target;

}				t_ssl;
