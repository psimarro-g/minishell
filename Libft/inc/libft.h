/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:37:55 by psimarro          #+#    #+#             */
/*   Updated: 2023/05/30 20:51:24 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <limits.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# define BUFFER_SIZE 100
# define FSPECS		"%cdisxXpu"
# define STD_OUT	1
# define EX_BASE "0123456789abcdefghijklmnopqrstuvwxyz"
# define EX_BASE_UP "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_tprint
{
	char			*fid;
	int				zero;
	int				left;
	int				width;
	int				tlen;
	int				h_p;
	int				prcn;
	int				len;
	int				n_p;
	int				h_w;
	int				negative;
	int				plus;
	int				space;
	int				hash;
}	t_tprint;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *nptr);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strnew(size_t size);
char			**ft_split(char const *s, char c);
char			*ft_trimf(const char *str, char *set);
int				ft_nsep(char *str, char c);
char			*ft_itoa(long long int n);
long long int	ft_power(long long int base, long long int power);
long long int	ft_ndigit(long long int n,
					long long unsigned int base);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int nb, int fd);
char			*ft_strrchr(const char *s, int c);
int				ft_isalnum(int c);
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
char			*ft_itoa_base(long long unsigned int n, int base,
					char *elm_base);
char			*ft_strchrs(const char *str, char *set);
int				ft_printf(const char *format, ...);
void			precision(t_tprint *tab, va_list *args);
void			draw_width(t_tprint *tab);
void			print_prc_char(t_tprint *tab, va_list *args, char percent);
void			print_any_num(t_tprint *tab, va_list *args, char c);
void			flags(t_tprint *tab);
void			draw_precision(t_tprint *tab);
void			width(t_tprint *tab, va_list *args);
void			empty(t_tprint *tab);
void			print_string(t_tprint *tab, va_list *args);
int				star(t_tprint *tab, va_list *args);
int				is_negative(t_tprint *tab, char **nn);
char			*is_pnt_or_hex(t_tprint *tab, long long unsigned int n, char c);
void			hash(t_tprint *tab, char c, char *nn);
void			sign(t_tprint *tab, char **nn, char c);
void			sign_draw(t_tprint *tab, int k, char *nn, char c);
char			*get_next_line(int fd);
void			ft_strdel(char **as);

#endif
