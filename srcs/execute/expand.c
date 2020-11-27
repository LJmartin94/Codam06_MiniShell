/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 12:51:50 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/27 14:24:35 by jsaariko      ########   odam.nl         */
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

	//charset !is_alnum
	// len = ft_strchrset(pos, " \"\'-");//TODO: add whatever other chars that will be parsed out eventually
	len = 0;
	while(ft_isalnum(pos[len]) || pos[len] == '_')
	{
		len++;
	}
	// ft_dprintf(STDOUT_FILENO, "%d\n", len);
	if (len >= 0)//TODO: Maybe change back to (len > 0)
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

static void		replace_arg(t_vector *env, char **str, size_t *i, int quote, int dquote)
{
	char	*final;
	t_env	*replace;

	final = NULL;
	// ft_dprintf(STDOUT_FILENO, "here? [%s] [%d]\n", *str, *i);
			// (*str)[*i + 1] == '\'' ||
			// (*str)[*i + 1] == '\"' ||
			// (*str)[*i + 1] == ' ' ||
			// (*str)[*i + 1] == '/') //TODO: wtf is / //TODO: I assume this is correct
			//TODO: Is alpha or is alnum??
	// if ((*str)[*i + 1] == '"')
	if ((*str)[*i + 1] == '?')
	{
		final = ft_strsplice((*str), *i, 2, ft_itoa(g_ret_val));
		free(*str);
		(*str) = final;
		i += 2;
	}
	else if (((*str)[*i + 1] == '"' && dquote % 2 == 0) ||
			((*str)[*i + 1] == '\'' && quote % 2 == 0) ||
			(*str)[*i + 1] == '_' ||
			(*str)[*i + 1] == '*' ||
			ft_isalnum((*str)[*i + 1]))
	{
		// ft_dprintf(STDOUT_FILENO, "replacing [%s]\n", (*str) + *i);
		replace = expand_find(env, (*str) + *i + 1);
		final = ft_strsplice((*str), *i,
					ft_strlen(replace->key) + 1,
					replace->value);
		free(*str);
		(*str) = final;
		// ft_dprintf(STDOUT_FILENO, "raplaced: [%s]\n\n", final);
		*i = *i - (ft_strlen(replace->key) + 1) + ft_strlen(replace->value);
	}
	else
	{
		//should not go here if next char is " '
		// ft_dprintf(STDOUT_FILENO, "hereee\n");
		//TODO: this should work..? echo "hallo$"
		//TODO: also ignore if next char is a quote of some form
		//TODO: Test [echo /$"123$USER"]
		(*i)++;
		return ;
	}
}

// void expand_env_arg(t_vector *env, t_icomp *cmd)
// {
// 	size_t	i;

// 	i = 0;
// 	while (cmd->cmd[i] != '\0')
// 	{
// 		if (cmd->cmd[i] == '$')
// 			replace_arg(env, &(cmd->cmd), &i);
// 		else
// 			i++;
// 	}
// 	i = 0;
// 	while (cmd->arg[i] != '\0')
// 	{
// 		if (cmd->arg[i] == '$')
// 			replace_arg(env, &(cmd->arg), &i);
// 		else
// 			i++;
// 	}
// }

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
		// ft_dprintf(STDOUT_FILENO, "cur char: [%c] i: %d\n", (*str)[i], i);
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
		if ((*str)[i] == '$' && quote % 2 == 0) //TODO: make sure this doesnt crash
		{
			if (i - 1 >= 0 && (*str)[i - 1] != '\\')
			{
				replace_arg(env, str, &i, quote, dquote);
			}
			else if (i - 1 < 0)
				replace_arg(env, str, &i, quote, dquote);
			else
				i++;
		}
		else
			i++;
	}
}

// NOTES: Not handling $* or $# as they're not mandatory


//echo "\\$USER" <- HOWW

// I still don't know whether to expand or not expand on @ and # ass next chars

//what should i do with numbers.. And special chars like @ #...
