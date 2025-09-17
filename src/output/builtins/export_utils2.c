/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:32:35 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/17 15:00:32 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ivi_utils(char c, int flag)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	if (flag && (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ivi_utils(name[0], 0))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ivi_utils(name[i], 1))
			return (0);
		i++;
	}
	return (1);
}

char	*extract_key2(char *arg)
{
	char	*equal_pos;
	char	*key;
	int		len;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		len = equal_pos - arg;
	else
		len = ft_strlen(arg);
	key = malloc(len + 1);
	if (!key)
		return (NULL);
	ft_strncpy(key, arg, len);
	key[len] = '\0';
	return (key);
}

char	*extract_value(char *arg)
{
	char	*equal_pos;
	char	*value;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (NULL);
	value = malloc(ft_strlen(equal_pos));
	if (!value)
		return (NULL);
	ft_strcpy(value, equal_pos + 1);
	return (value);
}

t_envp	*find_env_node(t_envp *envp_list, char *key)
{
	t_envp	*current;

	current = envp_list;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
