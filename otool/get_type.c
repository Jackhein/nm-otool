/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:43:59 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/12 17:54:00 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_otool.h"

static char		get_sect_type(uint8_t n_sect, t_sym *symtab)
{
	if (n_sect == symtab->text)
		return ('T');
	else if (n_sect == symtab->data)
		return ('D');
	else if (n_sect == symtab->bss)
		return ('B');
	else
		return ('S');
}

char			get_type(uint8_t n_type, uint8_t n_sect, int n_value,
				t_sym *symtab)
{
	char		type;
	uint8_t		masked;

	masked = n_type & N_TYPE;
	if (n_type & N_STAB)
		type = '-';
	else if ((masked == N_UNDF && n_value == 0) || masked == N_PBUD)
		type = 'U';
	else if (masked == N_UNDF && n_value != 0)
		type = 'C';
	else if (masked == N_ABS)
		type = 'A';
	else if (masked == N_SECT)
		type = get_sect_type(n_sect, symtab);
	else
		type = (masked == N_INDR ? 'I' : '?');
	if (!(n_type & N_EXT))
		type = ft_tolower(type);
	return (type);
}
