/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:44:47 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/28 13:23:18 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

int				error_display(char *error)
{
	ft_printf("ft_nm: %s: %s\n", g_filename, error);
	return (-1);
}

void			usage(void)
{
	ft_printf("Usage: %s [file ...]\n", g_filename);
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
