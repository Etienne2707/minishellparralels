#include "minishell.h"

char    *ft_remove_quote(char *str, int q)
{
    int k;
    int i;
    int c;
    char *dest;

    k = 0;
    c = 0;
    while(str[k] != '\0')
    {
        if (str[k] == 34 || str[k] == 39)
        {
            c++;
        }
        k++;
    }
    if (c == 0)
        return (str);
    printf("%d/n", ft_strlen(str) - c + (c % 2) + 1);
    dest  = malloc(sizeof(char) * ft_strlen(str) - c + (c % 2) + 1);
    if (!dest)
        return (NULL);
    k = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 39)
        {
            i++;
            while (str[i] != 39 && str[i] != '\0')
            {
                
                dest[k++] = str[i++];
               
            }
        }
        else if (str[i] == 34)
        {
            i++;
            while (str[i] != 34 && str[i] != '\0')
            {
                dest[k++] = str[i++];
            }
        }
        i++;
    }
    dest[k] = '\0';
    printf("%s\n", dest);
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
    int k;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 34)
        {
            k = i;
            while (str[i] != 34 && str[i] != '\0')
                i++;
            if (str[i] == '\0')
                return (-1);
            if (index > k && index < i)
                return (1);
        } 
       if (str[i] == 39)
        {

            k = i;
            while (str[++i] != 39 && str[i] != '\0')
            if (str[i] == '\0')
                return (-1);
            if (index > k && index < i)
                return (0);
        }
        i++;
    }
    return (1);
}

int check_quote(char *str, char *find)
{
    int i;
    int k;

    i = 0;
    find = ft_strjoin("$", find);

    k = ft_strstr2(str, find);
    if (check_in_quote(str, k) != 1)
        return (0);

    return (1);
}


