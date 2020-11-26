/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 12:51:50 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/26 14:55:26 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

/*
** //TODO: Make work with multiple args
*/

static t_env	*expand_find(t_vector *env, char *pos)
{
	int		len;
	char	*key;
	int		index;
	t_env	*item;

	len = ft_strchrset(pos, " \"\'-");//TODO: add whatever other chars that will be parsed out eventually
	if (len > 0)//TODO: Maybe change back to (len > 0)
	{
		key = (char *)e_malloc(sizeof(char) * len + 1);
		key = ft_memcpy(key, pos, sizeof(char) * len);
	}
	else
		key = ft_strdup(pos);
	index = vector_search(env, compare_key, key);
	item = vector_get(env, index);
	if (item == NULL)
	{
		item = (t_env *)e_malloc(sizeof(t_env));
		item->key = key;
		item->value = ft_strdup("");
	}
	else
		free(key);
	return (item);
}

static void		replace_arg(t_vector *env, char **str, size_t *i)
{
	char	*final;
	t_env	*replace;

	final = NULL;
	// ft_dprintf(STDOUT_FILENO, "here? [%s] [%d]\n", *str, *i);
	if (!ft_isprint((*str)[*i + 1]) ||
			(*str)[*i + 1] == '\"' ||
			(*str)[*i + 1] == '\'' ||
			(*str)[*i + 1] == ' ' ||
			(*str)[*i + 1] == '/') //TODO: wtf is / //TODO: I assume this is correct
	{
		//TODO: also ignore if next char is a quote of some form
		//TODO: Test [echo /$"123$USER"]
		(*i)++;
		return ;
	}
	else if ((*str)[*i + 1] == '?')
	{
		final = ft_strsplice((*str), *i, 2, ft_itoa(g_ret_val));
		free(*str);
		(*str) = final;
		i += 2;
	}
	else
	{
		// ft_dprintf(STDOUT_FILENO, "replacing\n");
		replace = expand_find(env, (*str) + *i + 1);
		final = ft_strsplice((*str), *i,
					ft_strlen(replace->key) + 1,
					replace->value);
		free(*str);
		(*str) = final;
		*i = *i - (ft_strlen(replace->key) + 1) + ft_strlen(replace->value);
	}
}

void expand_env_arg(t_vector *env, t_icomp *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->cmd[i] != '\0')
	{
		if (cmd->cmd[i] == '$')
			replace_arg(env, &(cmd->cmd), &i);
		else
			i++;
	}
	i = 0;
	while (cmd->arg[i] != '\0')
	{
		if (cmd->arg[i] == '$')
			replace_arg(env, &(cmd->arg), &i);
		else
			i++;
	}
}

// TODO: if between single quotes, do not expand
// TODO: this should work?? echo '$USER'$USER\$USER/"$USER"
void	expand_env(t_vector *env, char **str)
{
	size_t	i;

	i = 0;
	int quote = 0;
	int dquote = 0;
	while ((*str)[i] != '\0')
	{
		ft_dprintf(STDOUT_FILENO, "cur char: [%c] i: %d\n", (*str)[i], i);
		if ((*str)[i] == '"')
		{
			if (quote % 2 == 0)
				(dquote)++;
			else
				(dquote)--;
		}
		else if ((*str)[i] == '\'')	
		{
			if (dquote % 2 == 0)
				(quote)++;
			else
				(quote)--;
		}
		//TODO: This might be horrendeously wrong
		if ((*str)[i] == '$' && quote % 2 == 0) //TODO: make sure this doesnt crash
		{
			if (i - 1 >= 0 && (*str)[i - 1] != '\\')
				replace_arg(env, str, &i);
			else if (i - 1 < 0)
				replace_arg(env, str, &i);
			else
				i++;
		}
		else
			i++;
	}
}
