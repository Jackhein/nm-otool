/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:24:32 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/09 17:04:21 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

static void			display_lib(char *ptr, int *ar_array, int array_size)
{
	int				i;
	int				ar_offset;
	char			*name;
	struct ar_hdr	*ar;

	i = -1;
	while (++i < array_size)
	{
		ar = (void *)ptr + ar_array[i];
		name = ft_strstr(ar->ar_name, ARFMAG) + ft_strlen(ARFMAG);
		ar_offset = ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
		ft_printf("\n%s(%s):\n", g_env.file, name);
		nm((void *)ar + sizeof(struct ar_hdr) + ar_offset);
	}
}

static int			is_not_inside(int *ar_array, int ran_off, int size)
{
	int				i;

	i = -1;
	while (++i < size)
	{
		if (ar_array[i] == ran_off)
			return (0);
	}
	return (1);
}

static int			get_lib_ar(struct ranlib *ran, int size, char *ptr)
{
	int				i;
	int				j;
	int				ar_array[size];

	i = -1;
	j = 0;
	while (++i < size)
	{
		if (is_not_inside(ar_array, ran[i].ran_off, size))
		{
			ar_array[j] = ran[i].ran_off;
			j++;
		}
	}
	display_lib(ptr, ar_array, j);
	return (0);
}

int					handle_lib(char *ptr)
{
	int				offset;
	int				size;
	void			*offset_tab;
	struct ranlib	*ran;

	offset = ft_atoi(ft_strchr((void *)(ptr + SARMAG), '/') + 1);
	offset_tab = ptr + sizeof(struct ar_hdr) + SARMAG + offset;
	ran = (struct ranlib *)(offset_tab + sizeof(uint32_t));
	size = (*((int *)offset_tab)) / sizeof(struct ranlib);
	if (check(ran) || check(offset_tab))
		return (error_display("File truncated or someway invalid."));
	get_lib_ar(ran, size, ptr);
	return (0);
}
