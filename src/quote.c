#include "minishell.h"

char    *string_woquotes(char *str, char *dest)
{
    int i;
    int k;

    i = 0;
    k = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 34 && check_in_quote(str, i) == -1)
            i++;
        else if (str[i] == 39 && check_in_quote(str, i) == -1)
            i++;
        else
            dest[k++] = str[i++];

    }
    dest[k] = '\0';
    return (dest);
}

char    *ft_remove_quote(char *str)
{
    int k;
    int i;
    int c;
    char *dest;

    k = 0;
    c = 0;
    
    while(str[k] != '\0')
    {
       // printf("element = %d = %d\n", str[k], check_in_quote(str, k));
        if ((str[k] == 34 || str[k] == 39) && check_in_quote(str, k) == -1)
            c++;
        k++;
    }
    if (c == 0 || c == 1)
        return (str);
    dest = malloc(sizeof(char) * ft_strlen(str) - c + 1);
    if (!dest)
        return (NULL);
    dest = string_woquotes(str,dest);
    return (dest);
}

int	ft_strstr2( char *str,  char *to_find)
{
	size_t	i;
	size_t	c;
	size_t	t;

	i = 0;
	c = 0;
	t = ft_strlen(to_find);
	if (to_find[0] == 0)
		return (0);
	if (str == to_find)
		return (0);
	while (str[i] != '\0')
	{
		c = 0;
		if (str[i] == to_find[c])
		{
			while (str[i + c] == to_find[c] && to_find[c] != '\0')
				c++;
			c--;
			if (str[i + c] != to_find[c])
				return (-1);
			if (to_find[c + 1] == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

int check_in_quote(char *str, int index)
{
    int i;
    int start;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 34)
        {
            i++;
            start = i;
            while ((str[i] != 34) && str[i] != '\0')
                i++;
            if (index >= start && index < i)
                return (1);
        }
        else if (str[i] == 39)
        {
            i++;
            start = i;
            while ((str[i] != 39) && str[i] != '\0')
                i++;
            if (index >= start && index < i)
                return (1);
        }
        i++;
    }
    return (-1);
}


  /*if(check_dquote(str, index) == 1 || check_squote(str, index) == 1)
        return (1);
    return (-1);*/  




int check_quote(char *str, char *find)
{
    int i;
    int k;

    i = 0;
    find = ft_strjoin("$", find);
    k = ft_strstr2(str, find);
    if (check_in_quote(str, k) == 1)
        return (0);
    free(find);
    return (1);
}


