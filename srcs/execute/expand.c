/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 12:51:50 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/11/27 16:03:33 by jsaariko      ########   odam.nl         */
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

	len = 0;
	while (ft_isalnum(pos[len]) || pos[len] == '_')
		len++;
	if (len >= 0)
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
		replace = expand_find(env, (*str) + *i + 1);
		final = ft_strsplice((*str), *i,
					ft_strlen(replace->key) + 1,
					replace->value);
		free(*str);
		(*str) = final;
		*i = *i + ft_strlen(replace->value) - 1;
	}
	else
		(*i)++;
}

void	expand_env(t_vector *env, char **str)
{
	size_t	i;

	i = 0;
	int quote = 0;
	int dquote = 0;
	int esc = 0;
	while ((*str)[i] != '\0')
	{
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
		if ((*str)[i] == '$' && quote % 2 == 0 && esc % 2 == 0)
			replace_arg(env, str, &i, quote, dquote);
		else
			i++;
		if (i - 1 > 0)
		{
			if ((*str)[i - 1] == '\\')
				esc++;
			if ((*str)[i - 1] != '\\')
				esc = 0;
		}
	}
}

// NOTES: Not handling $* or $# as they're not mandatory

//what should i do with numbers.. And special chars like @ #...
