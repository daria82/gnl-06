/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:41:55 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/27 15:47:02 by mstroeva         ###   ########.fr       */
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
>>
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c 
get_next_line.h get_next_line_utils.c main.c

cc -D BUFFER_SIZE=42 get_next_line.c get_next_line.h get_next_line_utils.c main.c
printf("");

gcc -g -Og -std=gnu99 -Wall -Wextra -Werror -D 
BUFFER_SIZE=5 get_next_line.c get_next_line.h get_next_line_utils.c main.c

valgrind --leak-check=full ./a.out 
valgrind --leak-check=full --show-leak-kinds=all ./a.out 

*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test4.txt", O_RDONLY);
	if (fd < 0)
	{
 		printf("Error. Wrong file descriptor!");
		return(0);
	}
	printf("\tfd: (%d)", fd);
	//line = (char *)malloc(sizeof(char));
	printf("\033[1;36m >>>>>go to get next line function:\n\033[0m");

	int i = 1;

	while (1)
	{
		line = get_next_line(fd);
		//printf("\nmain line %d:\n\033[1;35m[%s]\033[0m", i, line);
		printf("\033[1;35m%s\033[0m", line);
		i++;
		if (line == NULL)
			break;
		free(line);
	}
		
	free(line);
	close(fd);
	return(0);
}
