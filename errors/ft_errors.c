
#include "ft_errrors.h"



static void	error_diplayFile(t_error *this)
{

}

static void	error_diplayOption(t_error *this)
{

}

static void	error_run(t_error *this)
{
	if (this->error_type != 0)
	{
		//manage error
	}
}

int			error_create(t_error *this)
{
	this->run = error_run;
}