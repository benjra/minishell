/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:52:07 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/13 10:56:19 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

char	*put_cmd_status(int status, char *cmd_path, char *cmd)
{
	if (status)
	{
		if (status == 1 && cmd && cmd[0] != '$')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		else if (cmd && cmd[0] != '$')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": permission denied\n", 2);
			exit(126);
		}
		return (NULL);
	}
	else
		return (cmd_path);
}

char	*get_cmd_path(char *cmd, char **exec_programs_dirs)
{
	char	*cmd_path;
	char	*temp;
	int		i;
	int		status;

	i = -1;
	status = 1;
	cmd_path = NULL;
	temp = NULL;
	while (exec_programs_dirs[++i] && cmd && cmd[0] && status)
	{
		temp = ft_strjoin(exec_programs_dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		if (access(cmd_path, F_OK))
			status = 1;
		else if (access(cmd_path, X_OK))
			status = 2;
		else
			status = 0;
	}
	return (put_cmd_status(status, cmd_path, cmd));
}

void	validate_cmd(t_lsttoken *token)
{
	if (ft_strchr(token->args[0], '/'))
		check_cmd_path(token);
	else
		check_command_name(token);
}

void	execs(t_lsttoken *token, int btn, t_name *env)
{
	if (btn != -1)
	{
		exec_builtin(btn, token, env);
		exit(0);
	}
	else if (token->cmd_path)
	{
		if (execve(token->cmd_path, token->args, g_var.envp) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(errno);
		}
	}
	else
		exit(0);
}
