
#ifndef		FT_ERRORS_H
#define		FT_ERRORS_H

typedef enum eError
{
	ret_ok = 0,
	ret_eof,
	ret_illegal_option,
	
}eError;

typedef struct	s_error
{
	char		*error_msg;
	eError		error_type;
}				t_error;

int		error_create(t_error *this);

#endif