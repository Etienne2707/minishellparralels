#include "minishell.h"

char	*change_value(char *value, char *str, char *swap, int c)
{
	char	*new;
	int i;
	int k;

	i = 0;
	k = 0;
	if (!swap)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(swap) + (ft_strlen(str) - ft_strlen(value) + 1));
	if (!new)
		return (NULL);
	new = ft_strlcpy(new,str,c);
	new = ft_strjoin(new,swap);
	new = ft_strnjoin(new, str, c + ft_strlen(value));
	return (new);
}


char	*get_value(char *env, char *str, char *cmd)
{
	int i;
	int c;
	char	*value;

	i = ft_strlen(str) + 1;
	c = 0;
	if(ft_compare(str, env, ft_strlen(str)) != 0)
		return (NULL);
	value = malloc(sizeof(char) * ft_strlen(env) - ft_strlen(str));
	while (env[i] != '\0')
	{
		value[c] = env[i];
		i++;
		c++;
	}

	value[c] = '\0';
    if (check_quote(cmd,str) == 0)
		return (NULL);
	return (value);
}
	char	*swap_value(char *value, char **envp, char *str)
	{
		int i;
		char *temp;

		i = 0;
		while (envp[i] != NULL)
		{
			if ((temp = get_value(envp[i], value,str)) != NULL)
				return (temp);
			
			i++;
		}
		return (NULL);
	}


char*	get_dollars(char *str, int pos, char **envp)
{
	int i;
	int c;
	char *value;
	char *new;

	i = pos + 1;
	while (str[pos] != ' ' && str[pos] != 39 && str[pos] != 34 && str[pos] != '}' && str[pos] != '_' && (str[pos] < '0' || str[pos] > '9') && str[pos] != '\0')
		pos++;
	value = malloc(sizeof(char) * pos - i + 1);
	if (!value)
		return (NULL);
	c = 0;
	while (i < pos)
	{
		value[c] = str[i];
		i++;
		c++;
	}
	value[c] = '\0';
	c = i - c;
	return (change_value(value, str, swap_value(value, envp, str), c));
}

char*	checkdollars(char *str, char **envp)
{
	int i;
	char *lea;

	i = 0;
	
	while(str[i] != '\0')
	{
        lea = str;
		if (str[i] == '$')
		{
			str = get_dollars(str, i, envp);
            
            if (!str)
	        	str = lea;
		}
        
		i++;
	}
	return (str);
	
}