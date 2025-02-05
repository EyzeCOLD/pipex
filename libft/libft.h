/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:19:34 by juaho             #+#    #+#             */
/*   Updated: 2025/02/05 22:31:05 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

//////////////////////////////////////////////////////////////// char checks //
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
///////////////////////////////////////////////////////////////////// memory //
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
/////////////////////////////////////////////////////////////// string utils //
int		ft_atoi(const char *nptr);
int		ft_atoi2(const char *a, int *i);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinm(size_t	n, ...);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//////////////////////////////////////////////////////////////////////// bsd //
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
///////////////////////////////////////////////////////////////////// prints //
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
//////////////////////////////////////////////////////////////// linked list //
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *lnew);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *lnew);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/////////////////////////////////////////////////////////////////////// math //
int		ft_abs(int n);
int		ft_min(int n1, int n2);
int		ft_max(int n1, int n2);
int		ft_pow(int n, unsigned int p);
/////////////////////////////////////////////////////////////////////// misc //
char	**ft_split(char const *s, char c);
int		ft_toupper(int c);
int		ft_tolower(int c);
////////////////////////////////////////////////////////////////// ft_printf //
int		ft_printf(const char *format, ...);
int		print_int(int i, const char *base);
int		print_uint(uintptr_t i, const char *base);
int		print_ptr(uintptr_t ptr);
////////////////////////////////////////////////////////////// get_next_line //
char	*get_next_line(int fd);

#endif
