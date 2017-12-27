/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:43:59 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/27 16:13:58 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

static char		get_sect_type(uint8_t n_sect, t_sym *symbol)
{
	if (n_sect == symbol->text)
		return ('T');
	else if (n_sect == symbol->data)
		return ('D');
	else if (n_sect == symbol->bss)
		return ('B');
	else
		return ('S');
}

char			get_type(uint8_t n_type, uint8_t n_sect, int n_value, 
				t_sym *symbol)
{
	char		type;
	uint8_t		masked;

	masked = n_type & N_TYPE;
	if (n_type & N_STAB)
		type = '-';
	else if (masked == N_UNDF)
		type = 'U';
	else if (masked == N_ABS)
		type = 'A';
	else if (masked == N_SECT)
		type = get_sect_type(n_sect);
	else if (masked == N_PBUD)
		type = 'P'; // Pas sur de la lettre
	else if (masked == N_INDR)
		type = 'I';
	else
		type = '\0';
	return (type);
}
