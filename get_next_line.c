/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:52:35 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/27 15:43:15 by mstroeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function name 	get_next_line
Prototype		char *get_next_line(int fd);
Turn in files	get_next_line.c, get_next_line_utils.c, get_next_line.h
Parameters fd:	The file descriptor to read from
Return value	Read line:		correct behavior
				NULL: there is nothing else to read, or an error occurred
External functs.read, malloc, free
Description		Write a function that returns a line read from 
				a file descriptor

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line.h get_next_line_utils.c main.c

cc -D BUFFER_SIZE=42 get_next_line.c get_next_line.h get_next_line_utils.c main.c
printf("");

gcc -g -Og -std=gnu99 -Wall -Wextra -Werror -D 
BUFFER_SIZE=5 get_next_line.c get_next_line.h get_next_line_utils.c main.c

valgrind --leak-check=full ./a.out 

*/
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*box;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	box = ft_load_buf(box, fd);
	if (!box)
		return(NULL);

	line = ft_formline(box);
	box = ft_formbox(box);

	return (line);
}
