/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:19:53 by amabchou          #+#    #+#             */
/*   Updated: 2024/07/11 12:05:02 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

int ft_pwd()
{
    char    cwd[4096];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_putstr_fd(cwd, 1);
    else
        return (1);
    return (0);
}
