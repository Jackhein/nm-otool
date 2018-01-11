/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:44:47 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/11 12:59:54 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

int				check(void *ptr)
{
	if (ptr >= g_env.buff_addr && ptr <= (g_env.buff_addr + g_env.buff_size))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int				error_display(char *error)
{
	ft_printf("ft_nm: %s: %s\n", g_env.file, error);
	return (-1);
}

void			usage(void)
{
	ft_printf("Usage: %s [file ...]\n", g_env.file);
	return ;
}

int				is_swap(uint32_t magic)
{
	if (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM)
		return (1);
	return (0);
}
