/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:44:47 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/08 13:41:41 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"


int				check_range_addr(void *ptr)
{
	if (ptr <= (g_env.buff_addr + g_env.buff_size))
		return (0);
	return (1);
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

int				is_32(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM);
}

int				is_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

int				is_swap(uint32_t magic)
{
	return (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM);
}
