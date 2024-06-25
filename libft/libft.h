/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:58:11 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/23 13:00:30 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int			ft_isalpha(int a);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_strlen(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *str, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(char *str, int c);
void		*ft_memchr(void *str, int c, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strrchr(const char *str, int c);
void		*ft_memmove(void *dst, void *src, size_t len);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);
int			ft_atoi(const char *str);
char		*ft_strdup(char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin2(char *s1, char *s2, int n);

// part two
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

//get_next_line
char		*get_next_line(int fd);

//utils.c
int			double_dollor(const char **str, int *count);
int			dollor_len(const char	**str);
int			ft_sep2(char c);
int			ft_skip(const char **str);

#endif
