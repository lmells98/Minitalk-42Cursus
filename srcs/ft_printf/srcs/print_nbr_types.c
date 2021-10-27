#include "../includes/ft_printf.h"

static int	print_number(unsigned long int nbr)
{
	int	ret;
	char *values;

	ret = 0;
	values = 0;
	if (nbr != 0)
	{
		values = ft_itoa(nbr);
		if (!values)
			return (ret);
		ret += print_str(values);
		free(values);
	}
	else
		ret += print_char('0');
	return (ret);
}

int	print_nbr_types(char *type, va_list *arg_p)
{
	int	ret;

	ret = 0;
	if (ft_strchr("di", *type))
		ret += print_number(va_arg(*arg_p, int));
	else if (*type == 'u')
		ret += print_number(va_arg(*arg_p, unsigned int));
	return (ret);
}
