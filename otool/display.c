/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:42:01 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/17 12:09:22 by ademenet         ###   ########.fr       */
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
	ft_printf("Contents of (%s,", ft_strupr(name));
	ft_printf("%s) section\n", ft_strlwr(name));
	free(name);
	return (EXIT_SUCCESS);
}
