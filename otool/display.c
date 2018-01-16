/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:42:01 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/16 15:00:11 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_otool.h"

int				display_bytes(uint8_t byte)
{
	ft_printf("%02x", byte);
	return (EXIT_SUCCESS);
}

int				display_sectname(char *sectname)
{
	char		*name;

	if (check(sectname))
		return (EXIT_FAILURE);
	name = ft_strdup(sectname);
	ft_printf("Contents of (%s,", ft_strupr(name)),
	ft_printf("%s) section\n", ft_strlwr(name));
	free(name);
	return (EXIT_SUCCESS);
}

int							display_32(struct symtab_command *sym,
							char *stringtable, struct nlist *array,
							t_sym *symtab)
{
	uint32_t				i;
	char					type;

	i = -1;
	while (++i < sym->nsyms)
	{
		type = get_type(array[i].n_type, array[i].n_sect, array[i].n_value,
			symtab);
		if (ft_strcmp("radr://5614542", stringtable + array[i].n_un.n_strx)
			!= 0 && type != '-')
		{
			if (array[i].n_value == 0 && (type == 'U' || type == 'u'))
				ft_printf("%8c %c %s\n", ' ', type,
					stringtable + array[i].n_un.n_strx);
			else
				ft_printf("%08llx %c %s\n", array[i].n_value, type,
					stringtable + array[i].n_un.n_strx);
		}
	}
	return (EXIT_SUCCESS);
}
