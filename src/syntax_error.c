#include "minishell.h"

void	wserror(void)
{
	write(2, "Syntax Error", 12);
}


int check_red_arg(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '<' || str[i] == '>')
        {
            while(str[i] == '>' || str[i] == '<' && str[i] != '\0')
                i++;
            while (str[i] == 32 && str[i] != '\0')
                i++;
            if (str[i] == '>' || str[i] == '<' || str[i] == '\0')
                return (-1);
        }
        i++;
    }
        
    return (1);
}

int check_in_out(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '>' && str[i + 1] == '<' && str[i + 1] != '\0')
            return (-1);
        else if (str[i] == '<' && str[i + 1] == '>' && str[i + 1]  != '\0')
            return (-1);
        i++;
    }
    return (1);
}

int syntax_red(char *str)
{
    int i;
    char c;
    int k;

    i = 0;
    while (str[i] != '\0')
    {
        k = 0;
        if (str[i] == '>' && check_in_quote(str, i) == -1 || str[i] == '<' && check_in_quote(str,i) == -1)
        {
            c = str[i];
            while (c == str[i] && str[i] != '\0')
            {
                i++;
                k++;
            }
            if (k > 2)
                return (-1);
        }
        i++;
    }
    if (check_in_out(str) == -1 || check_red_arg(str) == -1)
        return (-1);
    
    return (1);
}

int	syntax_charac(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != ' ' && str[i] != '$' && str[i] != '|' && str[i] != '>' && str[i] != 39 && str[i] != 34 && str[i] != '-' && str[i] != '<')
			&& (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9') && check_in_quote(str,i) != 1)
            {
			    return (-1);
            }
		i++;
	}
	return (0);
}

int	syntax_quote(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && check_in_quote(str, i) == -1)
			c++;
		i++;
	}
	if ((c % 2) != 0)
		return (0);
	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39 && check_in_quote(str, i) == -1)
			c++;
		i++;
	}
	if ((c % 2) != 0)
		return (0);
	return (1);
}

int	syntax_check(char *str)
{
	int i;

	i = 0;
	if (syntax_quote(str) == 0)
		return (0);
	if (syntax_charac(str) == -1)
		return (0);
    if (syntax_red(str) == -1)
        return (0);
    return (1);
}