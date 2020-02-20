
typedef enum	s_hash_type
{
	md5_hash = 0,
	sha256_hash
}	t_hash_type;

typedef	enum	s_errors
{
	illegal_option = -1,
	not_a_file = -2,
	invalid_command = -3,
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
	t_option	op;
	char		*target;
	char		*result;
	int			(*parse)(struct s_ssl *ssl, int ac, char **av);
	int			(*hash)(struct s_ssl *ssl);
	unsigned	std_in_read;

}				t_ssl;


int		parse_arg_pqrs(t_ssl *ssl, int ac, char **av);