#include "minishell.h"

char*	add_dquote(char *str)
{
	int i;
	int k;
	char *new;

	k = 0;
	i = 0;
	new = malloc(sizeof(char ) * ft_strlen(str) + 3);
	if (!new)
		return (NULL);
	new[k++] = 34;
	while (str[i] != '\0')
	{
		new[k++] = str[i++];
	}
	new[k++] = 34;
	new[k] = '\0';
	free(str);
	return (new);
}

int dollars_in_quote(char *str, int index)
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
                return (-1);
        }
        i++;
    }
    return (1);
}

char	*strcpyn(char *dest, char *src, int index, int size)
{
	int i;

	i = 0;
	while (size > 1  && src[index] != '\0')
	{
		dest[i] = src[index];
		index++;
		i++;
		size--;
	}
	dest[i] = '\0';
	return (dest);
}

int	get_index(char *str)
{
	int i;

	i = 0;
	while (str[i] != '$' && dollars_in_quote(str,i) == 1)
	{
		i++;
	}
	return (i);
	
}
char *change_value(char *env, char *str)
{
	int size;
	char *new;
	int i;
	int index;

	i = 0;
	index = get_index(str);
	size = index + 1;
	while (str[size] != '\0' && str[size] != 32 && str[size] != '$' && str[size] != 39)
		size++;
	new = malloc(sizeof(char *) * (ft_strlen(str) - (size - index)) + ft_strlen(env) + 1);
	if (!new)
		return (NULL);
	new = ft_strncpy(new,str,index);
	while (env[i] != '\0')
		new[index++] = env[i++];
	while (str[size] != '\0')
	{
		new[index] = str[size];
		size++;
		index++;
	}
	new[index] = '\0';
	free(env);
	return (new);
}