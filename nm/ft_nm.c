/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:49:57 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/22 10:19:29 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

// TODO :
// 1 - lire quel type de fichier > appel la bonne fonction
// 2 - iterer sur les symbols et recuperer les infos

static void		nm(char *ptr, char *file)
{
	// Nous regardons les 4 premiers octets du fichier afin de déterminer
	// sur quel type d'architecture nous nous trouvons : 64 bits, fat
	// binaries, etc.
	// `hexdump -C -n 4 a.out`
	int			magic_number;

	magic_number = *(int *)ptr;
	if (is_64(magic_number))
		handle_64(ptr);
	else if (is_32(magic_number))
		handle_32(ptr);
	else
		error_display(MAGIC_NUM);
}

// TODO :
// - verifier le magic number et appeler la bonne fonction
// - comment stocker les donnees pour les classer ensuite ?

static int		iterate_over_files(char *file)
{
	int			fd;
	char		*ptr;
	struct stat	buf;
	
	if ((fd = open(file, O_RDONLY)) < 0)
		return (error_display(OPEN));
	if (fstat(fd, &buf) < 0)
		return(error_display(FSTAT));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (error_display(MMAP));
	nm(ptr, file);
	if (munmap(ptr, buf.st_size) < 0)
		return(error_display(MUNMAP));
	return (EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	int			i;

	if (ac == 1)
		iterate_over_files("a.out");
	else
	{
		i = 0;
		while (++i < ac)
		{
			if (ac > 2)
				ft_printf("\n%s:\n", av[i]);
			iterate_over_files(av[i]);
		}
	}
	return (EXIT_SUCCESS);
}
