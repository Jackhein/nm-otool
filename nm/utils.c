/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:44:47 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/22 12:27:01 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

int				error_display(t_err error)
{
	if (error == OPEN)
		write(2, "Error: open.\n", 13);
	else if (error == FSTAT)
		write(2, "Error: fstat.\n", 14);
	else if (error == MMAP)
		write(2, "Error: mmap.\n", 13);
	else if (error == MUNMAP)
		write(2, "Error: munmap.\n", 15);
	else if (error == MAGIC_NUM)
		write(2, "Error: no such magic number.\n", 29);
	else if (error == ADDR_ERR)
		write(2, "Error: the file is corrupted.\n", 30);
	return (EXIT_FAILURE);
}

void			usage(const char *file_name)
{
	ft_printf("Usage: %s [file ...]\n", file_name);
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
	return (magic == MH_CIGAM || magic == MH_CIGAM_64);
}
