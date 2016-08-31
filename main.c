/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnessaiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 13:44:21 by dnessaiv          #+#    #+#             */
/*   Updated: 2016/08/30 13:44:21 by dnessaiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>

int ft_puterror(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i++], 1);
	}
	return (0);
}

int	line_size(fd)
{	
	char	buffer;
	int		j;

	j = 1;
	buffer = 0;
	while (buffer != '\n')
	{
		read(fd, &buffer, 1);
		j++;
	}
	lseek(fd, -j, SEEK_END);
	return (j);
}

int		create_2D_array(int fd, int length, char **map)
{
	char	buffer;
	int		ret;
	int		i;
	int		j;
	
	ret = 1;
	j = 0;
	i = 0;

	printf("Start creation:\n");

	while (i < length && ret)										// While row count within parameters.	
	{
		printf("start buffer : %c\n", buffer);

		while ((ret = read(fd, &buffer, 1)))							// While we're not at the end of file.
		{
			j = 0;															// First column.

			printf("fd : %d\n", fd);
			printf("ret : %d\n", ret);
			printf("current buffer: %c\n", buffer);

			map[i] = (char *)malloc(sizeof(char) * line_size(fd));

			printf("Successfully allocated.\n");

			while (buffer != '\n' && ret)									// While we're not at end of line.
			{
				map[i][j] = buffer;												// Assign current buffer value to second dimension array.
				j++;

				printf("j = %d\n", j);
				printf("Current Buffer : %c\n", buffer);
				printf("Current Address Value: %c\n", map[i][j]);

				ret = read(fd, &buffer, 1);										// Read next char from file.

				printf("Buffer2 : %c\n\n", buffer);
			}

			printf("++++++++++++++++++++++BREAK LOOP 3+++++++++++++++++++\n\n");

			map[i][j] = buffer;												// Assign /n character to end of array.
			i++;															// Go to next row.

			printf("Current i : %d\n", i);
			printf("Current ret : %d\n\n", ret);
		}

		printf("++++++++++++++++++++++BREAK LOOP 2+++++++++++++++++++\n\n");

	}
	
	printf("++++++++++++++++++++++BREAK LOOP 1+++++++++++++++++++\n\n");

	printf("%d\n", length);
	printf("%d\n", i);

	return (0);
	if (length != i || map[i - 1][j - 1] != '\n')					// Check if listed length of file is dif from actual length
		return (0);													// or if final char is not a newline.
	return (1);
}

int	main(int argc, char **argv)
{
	char 	**map;
	char	instructions[5];
	char	empty;
	char	obstacle;
	char	full;
	int		length;
	int		fd;

	printf("Number of arg : %d\n", argc);
	printf("Beginning of function\n");

	argv	= 0;
	fd		= 0;
	if (argc > 1)
		fd = open("file", O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);	//	Open up file with all permissions in APPEND mode.
	if (read(fd, &instructions, 5) != 5 || instructions[4] != '\n')	//	Check if the instruction line is a valid line.
		return (ft_puterror("map error"));
	//length		= instructions[0];
	length		= 3;												// replace with atoi
	empty		= instructions[1];
	obstacle	= instructions[2];
	full		= instructions[3];

	printf("Length : %d\n", length);	

	if (!(map = (char **)malloc(length * sizeof(char *)) + 1))		// Allocate first dimension of 2D array.
		return (ft_puterror("map error"));

	printf("Length : %d\n", length);

	if (!(create_2D_array(fd, length, map)))						// Create 2d array.
		return (ft_puterror("map error"));

	return (0);
}






























