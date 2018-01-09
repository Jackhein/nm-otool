/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 12:43:42 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/09 13:28:08 by ademenet         ###   ########.fr       */
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
# include <mach-o/ranlib.h>
# include "../../libft/libft.h"
# include "../../libft/ft_printf/include/fpf_printf.h"

typedef struct		s_env
{
	char			*file;
	int				endianness;
	void			*buff_addr;
	int				buff_size;
}					t_env;

t_env				g_env;

typedef struct		s_sym
{
	int				text;
	int				data;
	int				bss;
}					t_sym;

/*
** DISPLAY
*/

int				display_64(struct symtab_command *sym, char *stringtable,
				struct nlist_64 *array, t_sym *symtab);
int				display_32(struct symtab_command *sym, char *stringtable,
				struct nlist *array, t_sym *symtab);

/*
** FT_NM
*/

void			nm(char *ptr);

/*
** GET_TYPE
*/

char			get_type(uint8_t n_type, uint8_t n_sect, int n_value, 
				t_sym *symbol);

/*
** HANDLE_32
*/

int				print_output_32(struct symtab_command *sym,
				t_sym *symtab, char *ptr);
int				handle_32(char *ptr);

/*
** HANDLE_64
*/

int				print_output_64(struct symtab_command *sym,
				t_sym *symtab, char *ptr);
int				handle_64(char *ptr);

/*
** HANDLE_FAT
*/

void			handle_fat(char *ptr);

/*
** HANDLE_LIB
*/

int				handle_lib(char *ptr);

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

int				check(void *ptr);
int				error_display(char *error);
void		    usage(void);
int				is_swap(uint32_t magic);

#endif