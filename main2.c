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

	j = 0;
	buffer = '0';
	while (buffer != '\n')
	{
		read(fd, &buffer, 1);
		j++;
	}

	return (j);
}

int		create_2D_array(int fd, int length, char **map)
{
	char	buffer;
	int		ret;
	int		i;
	int		j;
	int		size;
	
	ret = 1;
	j = 0;
	i = 0;
	size = line_size(fd);
	lseek(fd, -size, SEEK_CUR);
	
	printf("Line Size : %d\n", size);
	printf("\n++++++++++++++++++++++++++++++Start creation++++++++++++++++++++++++++++++\n");

	while (i < length && ret)										// While row count within parameters.	
	{

	printf("++++++++++++++++++++++LOOP 1+++++++++++++++++++\n\n");
	printf("start buffer : %c\n", buffer);

		while ((ret = read(fd, &buffer, 1)))							// While we're not at the end of file.
		{

			printf("++++++++++++++++++++++LOOP 2+++++++++++++++++++\n\n");

			j = 0;															// First column.

			printf("##LINE NUMBER : %d##\n", i);
			printf("Buffer: %c\n\n", buffer);

			map[i] = (char *)malloc(8 * size);

			printf("Sizeof char * : %zu\n", sizeof(char *));
			printf("Line Size : %d\n", size);
			printf("Size that should be allocated to map[i]: %zu\n", (sizeof(char *) * size));
			printf("Size Allocated to map[i] : %zu\n", sizeof(map[i]));
			printf("Successfully allocated.\n\n");

			while (buffer != '\n' && ret)									// While we're not at end of line.
			{
				printf("++++++++++++++++++++++LOOP 3+++++++++++++++++++\n\n");
				printf("Current Buffer : %c\n", buffer);

				map[i][j] = buffer;												// Assign current buffer value to second dimension array.

				printf("Current Address Value: %c\n", map[i][j]);
				
				j++;

				printf("j = %d\n", j);
				ret = read(fd, &buffer, 1);										// Read next char from file.

				printf("ret : %d\n", ret);
				printf("Buffer2 : %c\n\n", buffer);

				if (j > size)
					return (0);
			}

				printf("---------------------------BREAK LOOP 3---------------------------\n\n");

			map[i][j] = buffer;												// Assign /n character to end of array.
			i++;															// Go to next row.
			printf("Current buffer : %c\n", buffer);
			printf("Current Line : %d\n", i);
		}

		printf("---------------------------BREAK LOOP 2---------------------------\n\n");

	}
	
	printf("---------------------------BREAK LOOP 1---------------------------\n\n");

	printf("Length			: %d\n", length);
	printf("Number of actual lines	: %d\n", i + 1);
	printf("Final map value: %c\n", map[i-1][j]);

	return (0);
	if ((length != i + 1) || (map[i-1][j] != '\n'))					// Check if listed length of file is dif from actual length
		return (0);											// or if final char is not a newline.
	printf("Did we make it?");
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
	
	printf("Instructions: %s\n", instructions);

	//length		= instructions[0];								// replace with atoi
	length		= 5;												
	empty		= instructions[1];
	obstacle	= instructions[2];
	full		= instructions[3];

	if (!(map = (char **)malloc(length * sizeof(char *)) + 1))		// Allocate first dimension of 2D array.
		return (ft_puterror("map error"));

	printf("Length : %d\n", length);

	if (!(create_2D_array(fd, length, map)))						// Create 2d array.
		return (ft_puterror("map error"));

	return (0);
}






























