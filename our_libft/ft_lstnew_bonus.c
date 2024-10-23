/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:26:40 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/26 18:53:25 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*linked_lst;

	linked_lst = malloc(sizeof(t_list));
	if (!linked_lst)
		return (NULL);
	linked_lst->content = content;
	linked_lst->next = NULL;
	return (linked_lst);
}
