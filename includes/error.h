/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 10:06:02 by jsaariko      #+#    #+#                 */
/*   Updated: 2020/12/18 15:52:26 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdlib.h>

# define C_INVALID_FILE 132
# define E_INVALID_FILE "Invalid fd"
# define C_GNL_FAIL 133
# define E_GNL_FAIL "GNL returned an invalid exit code"

void	error_exit_errno(void);
void	error_exit_msg(const unsigned int e_code, const char *e_msg);
void	*e_malloc(size_t size);
void	e_write(int fd, const char *buf, size_t size);
void	e_close(int fd);
char	*e_strjoin(const char *s1, const char *s2);

#endif
