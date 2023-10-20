#include "minishell.h"

t_pars	*ft_lstlast_(t_pars *lst)
{
	while (lst->next != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

char **put_arg_list(char **dest, char **str)
{
    int i;
    int c;

    i = 0;
    c = 0;
    
    while (str[i] != 0)
    {
        if (strcmp(">>", str[i]) == 0 || strcmp("<<", str[i]) == 0 || strcmp(">", str[i]) == 0 || strcmp("<", str[i]) == 0)
            i = i + 2;
        if (str[i] != 0)
        {
            i++;
            c++;
        }
    }

    dest = malloc(sizeof(char *) * (c + 1));

    if (!dest)
        return (NULL);

    i = 0;
    c = 0;

    while (str[i] != 0)
    {
        if (strcmp(">>", str[i]) == 0 || strcmp("<<", str[i]) == 0 || strcmp(">", str[i]) == 0 || strcmp("<", str[i]) == 0)
            i = i + 2;

        if (str[i] != 0)
        {
            dest[c] = malloc_cpy(dest[c], str[i]);
            i++;
            c++;
        }
    }

    dest[c] = 0;
    i = 0;

    while (dest[i] != 0)
    {
        printf("voici : %s\n", dest[i]);
        i++;
    }

    return dest;
}

t_pars	*get_info(t_token *token)
{
	t_pars	*new;
    char **send;

	new = (t_pars *)malloc(sizeof(t_pars));
	if (!new)
		return NULL;
	new->cmd = put_arg_list(new->cmd,token->arg);
	new->delimiter = token->delimiter;
	new->outfile = token->outfile;
	new->infile = token->infile;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void lst_add_back(t_pars **pars, t_pars *new)
{
    t_pars *tmp;

    tmp = *pars;
    if (*pars == NULL)
    {
        *pars = new;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp; // Correction ici
}

void print_list(t_pars **pars)
{
    t_pars *current;
    int i;

    current = *pars;

    while (current != NULL)
    {
        i = 0;
        while (current->cmd[i] != NULL)
        {
            printf("cmdlist = %s   ", current->cmd[i]);
            i++;
        }
		printf("\noutfile = %d \n", current->outfile);
		printf("infile = %d\n", current->infile);
        if (current->delimiter != NULL)
        {
            i = 0;
            while (current->delimiter[i] != NULL)
            {
                printf("heredoc = %s\n", current->delimiter[i]);
                i++;
            }
        }
        current = current->next;
    }
}

void	get_list(t_token *token, t_pars **pars)
{
	t_pars	*tmp;

	tmp = get_info(token);
	if (!tmp)
		return ;
	lst_add_back(pars, tmp);	
	
}