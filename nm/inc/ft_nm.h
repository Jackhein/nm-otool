/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:43:42 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/28 13:26:46 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <ar.h>
# include <mach-o/fat.h>
# include "../../libft/libft.h"
# include "../../libft/ft_printf/include/fpf_printf.h"

char				*g_filename;
// int					g_endianness = 0;

typedef struct		s_sym
{
	uint64_t		value;
	char			type;
	char*			name;
	struct s_sym	*next;
}					t_sym;

/*
** DISPLAY
*/

void			print_output_64(int nsyms, int symoff, int stroff, char *ptr);

/*
** FT_NM
*/

/*
** GET_TYPE
*/

// char			get_type(uint8_t n_type, uint8_t n_sect, int n_value, 
				// t_sym *symbol);

/*
** HANDLE_32
*/

void			handle_32(char *ptr);

/*
** HANDLE_64
*/

void			handle_64(char *ptr);
struct nlist_64	*sort_64(char *stringtable, struct nlist_64 *array, int nsyms);
void			sort_value_64(char *stringtable, struct nlist_64 *sort,
				int nsyms);


/*
** HANDLE_FAT
*/

void			handle_fat(char *ptr);

/*
** HANDLE_LIB
*/

void			handle_lib(char *ptr);

/*
** UTILS
*/

int				error_display(char *error);
void		    usage(void);
int				is_32(uint32_t magic);
int				is_64(uint32_t magic);
int				is_swap(uint32_t magic);

#endif