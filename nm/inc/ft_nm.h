/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:43:42 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/03 18:23:14 by ademenet         ###   ########.fr       */
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
	int				text;
	int				data;
	int				bss;
}					t_sym;

/*
** DISPLAY
*/


/*
** FT_NM
*/

/*
** GET_TYPE
*/

char			get_type(uint8_t n_type, uint8_t n_sect, int n_value, 
				t_sym *symbol);

/*
** HANDLE_32
*/

void			print_output_32(struct symtab_command *sym,
				t_sym *symtab, char *ptr);
void			handle_32(char *ptr);

/*
** HANDLE_64
*/

int				check_addr_error(struct load_command *lc);
void			print_output_64(struct symtab_command *sym,
				t_sym *symtab, char *ptr);
void			handle_64(char *ptr);

/*
** HANDLE_FAT
*/

void			handle_fat(char *ptr);

/*
** HANDLE_LIB
*/

void			handle_lib(char *ptr);

/*
** SORT_32
*/

void			sort_value_32(char *stringtable, struct nlist *sort,
				int nsyms);
struct nlist	*sort_32(char *stringtable, struct nlist *array,
				int nsyms);

/*
** SORT_64
*/

void			sort_value_64(char *stringtable, struct nlist_64 *sort,
				int nsyms);
struct nlist_64	*sort_64(char *stringtable, struct nlist_64 *array, 
				int nsyms);

/*
** UTILS
*/

int				error_display(char *error);
void		    usage(void);
int				is_32(uint32_t magic);
int				is_64(uint32_t magic);
int				is_swap(uint32_t magic);

#endif