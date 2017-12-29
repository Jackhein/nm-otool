/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:49:57 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/29 15:14:19 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

// TODO :
// 1 - lire quel type de fichier > appel la bonne fonction
// 2 - iterer sur les symbols et recuperer les infos

/*
** 
*/

static void		nm(char *ptr)
{
	// Nous regardons les 4 premiers octets du fichier afin de déterminer
	// sur quel type d'architecture nous nous trouvons : 64 bits, fat
	// binaries, etc.
	// `hexdump -C -n 4 a.out`
	int			magic_number;

	magic_number = *(int *)ptr;
	// g_endianness = is_swap(magic_number);
	if (!ft_strncmp(ptr, ARMAG, SARMAG))
		handle_lib(ptr);
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64(ptr);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle_32(ptr);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr);
	else
		error_display("No such magic number.");
}

static int		iterate_over_files(void)
{
	int			fd;
	char		*ptr;
	struct stat	buf;
	
	if ((fd = open(g_filename, O_RDONLY)) < 0)
		return (error_display("No such file or directory."));
	if (fstat(fd, &buf) < 0)
		return(error_display("An error occured with fstat."));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (error_display("An error occured with mmap."));
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return(error_display("An error occured with munmap."));
	return (EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	int			i;

	if (ac == 1)
	{
		g_filename = "a.out";		
		iterate_over_files();
	}
	else
	{
		i = 0;
		while (++i < ac)
		{
			g_filename = av[i];
			if (ac > 2)
				ft_printf("\n%s:\n", g_filename);
			iterate_over_files();
		}
	}
	return (EXIT_SUCCESS);
}
