/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:49:57 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/10 18:48:51 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

int					nm(char *ptr)
{
	unsigned int	magic_number;

	if (check(ptr))
		return (set_type_error("1 File truncated or someway invalid."));
	magic_number = *(int *)ptr;
	g_env.endianness = is_swap(magic_number);
	if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_lib(ptr);
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64(ptr);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle_32(ptr);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr);
	return (EXIT_SUCCESS);
}

static int			iterate_over_files(void)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(g_env.file, O_RDONLY)) < 0)
		return (error_display("No such file or directory."));
	if (fstat(fd, &buf) < 0)
		return (error_display("An error occured with fstat."));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (error_display("An error occured with mmap."));
	g_env.buff_addr = ptr;
	g_env.buff_size = buf.st_size;
	if (nm(ptr))
		return (error_display(NULL));
	if (munmap(ptr, buf.st_size) < 0)
		return (error_display("An error occured with munmap."));
	return (EXIT_SUCCESS);
}

int					main(int ac, char **av)
{
	int				i;

	if (ac == 1)
	{
		g_env.file = "a.out";
		if (iterate_over_files())
			return (EXIT_FAILURE);
	}
	else
	{
		i = 0;
		while (++i < ac)
		{
			g_env.file = av[i];
			if (ac > 2)
				ft_printf("\n%s:\n", g_env.file);
			if (iterate_over_files())
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
