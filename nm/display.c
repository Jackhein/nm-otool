/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:42:01 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/29 15:14:33 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

void				print_output_64(int nsyms, int symoff, int stroff, 
					char *ptr)
{
	int						i;
    char                    type;
	char					*stringtable;
	struct nlist_64			*array;

	i = -1;
	stringtable = (void *)ptr + stroff;
    array = (void *)ptr + symoff;
	array = sort_64(stringtable, array, nsyms);
	sort_value_64(stringtable, array, nsyms);
	// for (i = 0; i < nsyms; ++i)
    while (++i < nsyms)
	{
		// const char			*n_type;
		// n_type = NULL;
		// uint8_t 			mask;
		// mask = array[i].n_type & N_TYPE;
		// if (mask == N_UNDF)
		// 	n_type = "N_UNDF";
		// else if (mask == N_ABS)
		// 	n_type = "N_ABS";
		// else if (mask == N_SECT)
		// 	n_type = "N_SECT";
		// else if (mask == N_PBUD)
		// 	n_type = "N_PBUD";
		// else if (mask == N_INDR)
		// 	n_type = "N_INDR";
		// else
		// 	return ;
		if (array[i].n_value == 0)
			ft_printf("%15llx ", ' ');
		else
			ft_printf("%015llx ", array[i].n_value);
        type = get_type_64(array[i].n_sect); // va chercher la lettre qu'il faut
		ft_printf("%c ", type);
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}
