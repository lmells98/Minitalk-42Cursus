#include "../includes/ft_printf.h"

int	print_percent(char *type)
{
	int	ret;

	ret = 0;
	if (*type == '%')
		ret += print_char(*type);
	return (ret);
}

int	print_sign(char *type)
{
	int	ret;

	ret = 0;
	if (*type == 'p')
		ret += print_str("0x");
	return (ret);
}
