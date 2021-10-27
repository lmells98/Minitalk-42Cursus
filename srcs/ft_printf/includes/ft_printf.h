#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# include "../srcs/libft/libft.h"

int		ft_printf(const char *format, ...);
int		convert_type(const char **format, char *type, va_list *arg_p);
int		print_nbr_types(char *type, va_list *arg_p);
int		print_char_types(char *type, va_list *arg_p);
int		print_hex_types(char *type, va_list *arg_p);
int		print_sign(char *type);
int		print_str(char *str);
int		print_char(char c);
int		print_percent(char *type);
char	*verify_type(const char **format);

#endif
