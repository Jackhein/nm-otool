/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/22 18:24:39 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

int					check_addr_error(struct load_command *lc)
{
	// To be implemented
	return (0);
}

struct nlist_64		*init_sort_64(struct nlist_64 *sort, struct nlist_64 *array,
					int nsyms)
{
	int				i;
	struct nlist_64	*sort;
	
	i = -1;
	sort = (struct nlist_64 *)malloc(nsyms * sizeof(struct nlist_64));
	while (++i < nsyms)
		sort[i] = array[i];
	return (sort);
}

struct nlist_64		*sort_64(char *stringtable, struct nlist_64 *array, 
					int nsyms)
{
	int				i;
	int				j;
	struct nlist_64	temp;
	struct nlist_64	*sort;

	i = -1;
	sort = init_sort_64(sort, array, nsyms);
	while (++i < nsyms)
	{
		j = -1;
		while (++j < nsyms)
		{
			if (ft_strcmp(stringtable + sort[i].n_un.n_strx, 
			stringtable + sort[j].n_un.n_strx) < 0)
			{
				temp = array[i];
				sort[i] = sort[j];
				sort[j] = temp;
			}
		}
	}
	return (sort);
}

void				print_output_64(int nsyms, int symoff, int stroff, 
					char *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;

	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	// TODO checker les ranges
	// TODO sort
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
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}

void				handle_64(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_64(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		if (check_addr_error(lc))
		{
			error_display(ADDR_ERR)
			return ;
		}
	}
}
