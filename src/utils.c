#include "minishell.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	//printf("%s | ", str );
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	//printf("voila  %s %d\n",str,  i);
	return (i);
}

int	strlen_no_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (str[i - 1] == ' ')
		i--;
	return (i);
}

int	have_digit(char *str, int i)
{
	while (str[i] != '\0' || str[i] == '|')
	{
		if (str[i] != ' ' && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A'
				|| str[i] > 'Z') && (str[i] < '0' || str[i] > '9'))
			return (-1);
		i++;
	}
	return (1);
}

int	check_start_end(char *str)
{
	int	size;
	int	i;

	size = strlen_no_space(str);
	i = 0;
	if (str[i] == '|' || str[size - 1] == '|')
		return (-1);
	i++;
	return (0);
}

int	only_special(char *str)
{
	int	i;
	int	c;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != ' ' && str[i] != 39 && str[i] != 34)
			return (0);
		i++;
	}
	return (-1);
}

char	*malloc_cpy(char *dest, char *src)
{
	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	dest = strcpy(dest, src);
	dest[ft_strlen(src)] = '\0';
	return (dest);


}

int	no_authorize(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != ' ' && str[i] != '$' && str[i] != '|' && str[i] != '>' && str[i] != 39 && str[i] != 34 && str[i] != '-' && str[i] != '<')
			&& (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9'))
			return (-1);
		i++;
	}
	return (0);
}

