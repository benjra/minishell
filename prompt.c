/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:46 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/06 11:27:38 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// char *gethost()
char	*prompt(void)
{
	char	*ptr;

	ptr = ft_strdup(BGreen);
	get_prompt(&ptr, ">>>");
	get_prompt(&ptr, BWhite);
	return (ptr);
}
