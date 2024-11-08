#include "philosopher.h"

void ft_check_args_quant(int ac)
{
    if (ac != 5 && ac != 6)
    {
        ft_printf("ERRO: NUMEROS DE ARGUMENTOS INVÁLIDOS");
        exit(1);
    }

}
int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_isdigit_str(char *str)
{
	while (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void check_valid_numbers(char **str)
{
    int i;

    i = 1;
    while (str[i] != NULL)
    {
        if (!ft_isdigit_str(str[i]))
        {
            ft_printf("ERRO: NUMEROS INVÁLIDOS");
            exit(1);
        }
        i++;
    }
}

void    check_philo_number(char **str)
{
    int number;
    int i;

    i = 1;
    number = 0;
    while (str[i] != NULL)
    {
        number = ft_atoi(str[i]);
        if ((number > 200 && i == 1) || (i == 1 && number < 1))
        {
            ft_printf("ERRO: NÃO DEVE HAVER MAIS DE 200 PHILOSOPHERS NEM MENOS DE 1");
            exit(1);
        }
        else if (i != 5 && number < 1)
        {
            ft_printf("ERRO: ARGUMENTOS ERRADOS");
            exit(1);
        }
        i++;
    }
}