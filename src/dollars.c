
#include "minishell.h"
char*	add_dquote(char *str)
{
	int i;
	int k;
	char *new;

	k = 0;
	i = 0;
	printf("%d\n", ft_strlen(str));
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
	new = strncpy(new,str,index);
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

char	*get_env(char *env, char *str)
{
	int i;
	int c;
	char	*value;

	i = ft_strlen(str) + 1;
	c = 0;
	if(ft_compare(str, env, ft_strlen(str)) != 0)
		return (NULL);
	value = malloc(sizeof(char) * ft_strlen(env) - ft_strlen(str) + 1);
	if (!value)
		return (NULL);
	while (env[i] != '\0')
	{
		value[c] = env[i];
		i++;
		c++;
	}
	
	value[c] = '\0';
	value = add_dquote(value);
	free(str);
	return (value);
}

char	*remove_dol(char *str, char *value)
{
	int i;
	char *new;
	int c;

	i = 0;
	c = 0;
	printf("%s et %d\n", str, ft_strlen(str));
	new = malloc(sizeof(char ) * ft_strlen(str) - ft_strlen(value) + 1);
	if (!new)
		return (NULL);
	while (str[i] != '$' && dollars_in_quote(str, i) == 1 && str[i] != '\0')
	{
		new[c++] = str[i++];
	}
	i = i + ft_strlen(value) + 1;
	while (str[i] != '\0')
	{
		new[c++] = str[i++];
	}
	new[c] = '\0';
	free(value);
	printf("%s voici new \n",new);
	return (new);
}

char	*swap_value(char *value, char **envp, char *str)
	{
		int i;
		char *temp;

		i = 0;
		while (envp[i] != NULL)
		{
			temp = get_env(envp[i],value);
			if (temp != NULL)
				return (temp);
			i++;
		}
		free(temp);
		return (NULL);
	}

char	*get_value(char *str, int index)
{
	int i;
	char *value;

	i = index + 1;
	while (str[i] != '\0' && str[i] != 32 && str[i] != '$' && str[i] != 39)
		i++;
	value = malloc(sizeof(char) * (i - index) + 1);
	if (!value)
		return (NULL);
	value = strcpyn(value,str, index + 1, i - index);	
	return (value);

}

char*	ft_dollars(char *str, char **envp, char *dest)
{
	int i;
	char *temp;
	char *tmp;

	i = 0;
	dest = str;
	while (str[i] != 0)
	{
		if (str[i] == '$' && dollars_in_quote(str,i) == 1)
		{
			temp = swap_value(get_value(str, i),envp,dest);
			if (temp != NULL)
			{
				dest = change_value(temp,dest);
			}
			else 
				dest = remove_dol(dest,get_value(str,i));
		}
		i++;
	}
	return (dest);
}