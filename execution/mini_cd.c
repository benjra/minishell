/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:56:10 by amabchou          #+#    #+#             */
/*   Updated: 2024/07/20 11:11:42 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

int ft_cd(const char *pathname)
{
    
    if (chdir(pathname) != 0)
    {
        perror("chdir");
        return (1);
    }
    printf("Directory changed to %s\n", pathname);
    return (0);
}
