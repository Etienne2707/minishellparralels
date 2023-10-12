#include "minishell.h"

t_pars	*get_info(char *str, int c)
{
	t_pars	*new;

	new = (t_pars *)malloc(sizeof(t_pars));
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_add_back(t_pars **pars, t_pars *new)
{
	t_pars	*tmp;

	tmp = *pars;
	if (*pars == NULL)
	{
		*pars = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	tmp->prev = tmp;
}

void	print_list(t_pars **pars)
{
	t_pars	*current;

	current = *pars;
	printf("Liste chaînée : \n");
	while (current != NULL)
	{
		current = current->next;
	}
}

void	list_am(t_token *token, t_pars **pars)
{
	t_pars	*tmp;

	tmp = get_info("test", 5);
	if (!tmp)
		return ;
	lst_add_back(pars, tmp);
	print_list(pars);

}

char	**put_arg(char **lexer, t_token *token)
{
	int		i;
    int     c;

	i = 0;
	c = 0;
    printf("les argumes devrais pas seg %s", token->arg[0]);
	while (token->arg[i] != 0)
	{
		if (strcmp(token->arg[i], "<") == 0 || strcmp(token->arg[i], ">") == 0
			|| strcmp(token->arg[i], ">>") == 0 || strcmp(token->arg[i], "<<") == 0)
                c++;
        i++;
	}    
    printf("le malloc serait de %d\n", i - (c * 2) + 1);

    lexer = malloc(sizeof(char *) * i - (c * 2) + 1);
    if (!lexer)
        return (NULL);
}

int	get_list(char **cmd, t_token *token)
{
	int i;
	char **lexer;

    i = 0;
    
	while (cmd[i] != 0)
	{
		put_arg(lexer, token[i].arg);
        i++;
	}
}