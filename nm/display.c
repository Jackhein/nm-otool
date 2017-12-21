/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:42:01 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/21 15:42:16 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

void			print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	char				*stringtable;
	struct  nlist_64	*array;

	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	for (i = 0; i < nsyms; ++i)
	{
		// Get type
		const char			*n_type;
		n_type = NULL;
		uint8_t 			mask;
		mask = array[i].n_type & N_TYPE;
		if (mask == N_UNDF)
			n_type = "N_UNDF";
		else if (mask == N_ABS)
			n_type = "N_ABS";
		else if (mask == N_SECT)
		{
			// TODO faire get_section qui recupere la section
			// cf. nlist.h l.146
			// n_sect est un ordinal pour trouver dans quelle section
			// nous nous trouvons >>> Trouver un moyen de determiner
			// dans quelle section je me trouve vraiment (T, d, S, etc.)
			n_type = "N_SECT";
			ft_printf("n_sect : %d\n", array[i].n_sect);
		}
		else if (mask == N_PBUD)
			n_type = "N_PBUD";
		else if (mask == N_INDR)
			n_type = "N_INDR";
		else
			return ;
		// End Get type

		ft_printf("%015llx ", array[i].n_value);
		ft_printf("%s ", n_type);
		// TODO faire un quicksort
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}
