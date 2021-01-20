/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 12:51:50 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/20 14:26:05 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "error.h"

static char	*expand_find(t_vector *env, char *pos, int *len)
{
	char	*key;
	char	*value;
	int		key_len;
	int		index;
	t_env	*item;

	key_len = 0;
	while (ft_isalnum(pos[key_len]) || pos[key_len] == '_')
		key_len++;
	key = (char *)e_malloc(sizeof(char) * key_len + 1);
	key = ft_memcpy(key, pos, sizeof(char) * key_len);
	*len = key_len;
	index = vector_search(env, compare_key, key);
	free(key);
	item = vector_get(env, index);
	if (item == NULL)
		value = ft_strdup("");
	else
		value = ft_strdup(item->value);
	return (value);
}

static void		expand_env_variable(t_vector *env, char **str, size_t *i)
{
	char	*replace;
	char	*final;
	int		len;

	final = NULL;
	replace = expand_find(env, (*str) + *i + 1, &len);
	if (replace == NULL)
		error_exit_errno();
	final = ft_strsplice((*str), *i, len + 1, replace);
	if (!final)
		error_exit_errno();
	free(*str);
	free(replace);
	(*str) = final;
	*i = *i + len - 1;
}

static void		replace_arg(t_vector *env, char **str, size_t *i, t_quotes q)
{
	char	*final;
	char	*ret;

	final = NULL;
	if ((*str)[*i + 1] == '?')
	{
		ret = ft_itoa(g_ret_val);
		final = ft_strsplice((*str), *i, 2, ret);
		free(ret);
		if (!final)
			error_exit_errno();
		free(*str);
		(*str) = final;
		i += 2;
	}
	else if (((*str)[*i + 1] == '"' && q.dquote % 2 == 0) ||
			((*str)[*i + 1] == '\'' && q.quote % 2 == 0) ||
			(*str)[*i + 1] == '_' || (*str)[*i + 1] == '*' ||
			ft_isalnum((*str)[*i + 1]))
	{
		expand_env_variable(env, str, i);
	}
	else
		(*i)++;
}

static void		quotes(char c, int *quote, int *dquote)
{
	if (c == '"')
	{
		if ((*quote) % 2 == 0)
			((*dquote))++;
		else
			((*dquote))--;
	}
	else if (c == '\'')
	{
		if ((*dquote) % 2 == 0)
			(*quote)++;
		else
			(*quote)--;
	}
}

void			expand_env(t_vector *env, char **str)
{
	size_t		i;
	t_quotes	q;
	int			esc;

	i = 0;
	q.quote = 0;
	q.dquote = 0;
	esc = 0;
	while ((*str)[i] != '\0')
	{
		quotes((*str)[i], &q.quote, &q.dquote);
		if ((*str)[i] == '$' && q.quote % 2 == 0 && esc % 2 == 0)
			replace_arg(env, str, &i, q);
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
