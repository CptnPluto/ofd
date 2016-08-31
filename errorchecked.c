/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnessaiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 00:08:50 by dnessaiv          #+#    #+#             */
/*   Updated: 2016/08/31 04:35:04 by whickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdlib.h>
#include <unistd.h>
#include "ft_list.h"
#include "test3.c"

#define MAX_READ 4096													// Copy pasted to read input.

/*
** Keep CPY_TYPE as char to trigger autovectorization (-O3)
*/

#define CPY_TYPE char
#define	CPY_WSIZE sizeof(CPY_TYPE)
#define CPY_WMASK (CPY_WSIZE - 1)

void	ft_memcpy_aligned(void *dst, void *src, size_t length)				
{
	size_t	t;

//	printf("HERE?3\n");
	if (!src)
	{
//		printf("NOPE!\n");

		return ;
	}
//		printf("HERE?4\n");
	src += length;
	dst += length;
	t = length / CPY_WSIZE;
//	printf("HERE?5\n");
	while (t > 0)
	{	
		src -= CPY_WSIZE;
		dst -= CPY_WSIZE;
		*(CPY_TYPE*)dst = *(CPY_TYPE*)src;
		t--;
	}
}

char	*ft_realloc(char *buf, ssize_t *buf_cap)						// Copy pasted to read input.  Doubles memory allocation
{																		// if we've run out of space in our buffer.
	ssize_t	old_cap;
	char	*newbuf;
//	printf("DOES IT GET HERE 2?\n");
	old_cap = *buf_cap;
	*buf_cap = old_cap * 2;
	newbuf = malloc(*buf_cap);
	ft_memcpy_aligned(newbuf, buf, old_cap);
	free(buf);
//	printf("HERE 6\n");
	return (newbuf);
}

char	*ft_read_input(int fd)											// Reads from input.
{
	ssize_t	read_size;
	char	*buf;
	ssize_t buf_cap;
	ssize_t buf_offset;
//	printf("DOES IT GET HERE?\n");
	buf_cap = MAX_READ / 2;
	buf = ft_realloc(NULL, &buf_cap);
	buf_offset = 0;
//	printf("HERE7\n");
	while ((read_size = read(fd, buf + buf_offset, MAX_READ)) > 0)
	{
//		printf("HERE8\n");
		buf_offset = buf_offset + read_size;
		if (buf_cap - buf_offset < MAX_READ + 1)
			buf = ft_realloc(buf, &buf_cap);
//			printf("HERE9\n");
	}
//	printf("HERE10\n");
	buf[buf_offset] = 0;
	return (buf);
}																		// End copy-paste.
/*
int		test_errors(char *buff)
{
	int i;
	int size;

	size = 0;
	i = 4;
	if (buff[i] != '\n')
		return (0);
	i++;
	while (buff[i])
	{
		while (buff[i] != '\n')
		{
			i++;
			size++;
		}
		while ()
		{

			return (0);
		}
	}
}

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

int	check_errors(char *buffer)
{
	//check true instances
	//otherwise 
	return (1);
}
*/
char 	**build_2d(char *buffer, int width, int height)											//Builds 2D array out of content of buffer.
{
	char **our_array;
	int index;
	int i;
	int j;

	i = 0;
	j = 0;
	index = 5;
//	printf("HERE THEN?\n");
	printf("#1 Current buffer: %c  -  i = %d  -  j = %d\n", buffer[index], i, j);
	our_array = (char **)malloc (sizeof(char *) * width);//doesn't seem to be the issue
	while (i < height)
	{
		our_array[i] = malloc(sizeof(char *) * width);
		i++;
	}
	//space is allocated
//		printf("I WAS STUCK IN A LOOP \n");
		i = 0;
/*
 *
 *
 *	Below i want the function to copy from the start of index to the first instance of '\n'
 *	then I want to move to the next line by iterating i and restart at j=0;
 *	this process should continue until end of line
 *
 *	
 */
		while (i < height && buffer[index])
		{
			while (j <= width && buffer[index])
			{
				//This is an error. Should already be checked in check_errors.
				if (buffer[index] == '\n')
				{
					//index++;
					i++;
					j++;
					printf("#2 Current buffer: %c  -  i = %d  -  j = %d\n", buffer[index], i, j);
				}
				else
					our_array[i][j] = buffer[index];
					index++;
					j++;
					printf("#3 Current buffer: %c  -  i = %d  -  j = %d\n", buffer[index], i, j);

			}
			j=0;
		// i++;//suspicious of this.. in what case will the character after width not be a \n ?
		}
	
	return our_array;
}

int get_width(char *buffer)																		// Gets width of first line from buffer.
{
	int i;
	int width;

	width = 0;
	i = 5;
	if (buffer)
	{
		while (buffer[i] != '\n' && buffer[i])
		{
			++width;
			++i;
		}
	}
	return (width);
}

t_iterators solve_array(char **our_array, int height, int width, char obstacle)					// Returns coordinates of largest square origin.
{
	int i;
	int j;
	t_iterators	coordinates;

	coordinates.size = 0;
	i = 0;
	j = 0;
	while (i < height)
	{
		while (j < width)
		{
			coordinates.x = i;
			coordinates.y = j;
//			printf("THIS RUNS\n");
	
			if (coordinates.size < gsq(our_array, coordinates, obstacle, coordinates.size))		// Reset largest size everytime we get a larger one.
			{
				coordinates.prime_x = i;
				coordinates.prime_y = j;
				coordinates.size = gsq(our_array, coordinates, coordinates.size, obstacle);
				printf("Coordinates: (%d, %d)\n", coordinates.prime_x, coordinates.prime_y);
				printf("Size = %d\n", coordinates.size);
			}
			j++;
		}
		i++;
	}
	return (coordinates);
}

void	mod_array(char **our_array, t_iterators coordinates, char full)							// Should mod array to have 'full' characters in box.
{
	int i;
	int j;

	i=0;
	j=0;
	while (i<coordinates.size)
	{
		while (j<coordinates.size)
		{
			our_array[(coordinates.prime_x)+i][(coordinates.prime_y)+j] = full;
			j++;
		}
		i++;
	}
}

void	output_array(int width, int height, char **our_array)									// Prints modded array.
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < height)
	{
		while (j < width)
		{
		//	write(1, &our_array[i][j], 1);
			printf("%c",our_array[i][j]);
			j++;
		}
		printf("\n");
		j=0;
		i++;
	}
}


int main()
{
	int			fd;
	int			i;
	int			j;
	int			width;
	int			height;
	char		**our_array;
	t_iterators	coordinates;
	char		*buffer;
	char		empty;
	char		obstacle;
	char		full;//all of these could be used without creating variable names call the functions with them hard coded.

	i = 0;
	j = 0;
	fd = 0;
//	printf("STOPS HERE\n");
	buffer		= ft_read_input(fd);
//	printf("THIS SHOULD WORK!\n");
	while (buffer[i]!='\0')
	{
		printf("%c", buffer[i]);
		i++;
	}
	printf("\n");
	i=0;
	height		= atoi(&buffer[0]);//needs to be changed to ft_atoi with our own implementation
	printf("atoi says height is %d\n",height);
	empty		= buffer[1];
	obstacle	= buffer[2];
	full		= buffer[3];
//	printf("DOES THIS WORK?\n");
	width = get_width(buffer);
	printf("WIDTH : %d\n",width);
	//check_errors(buffer, width);
//	printf("SO THE ERROR IS BROUGHT TO THE SURFACE IN build_2d? \n");
	our_array = build_2d(buffer, width, height);
	printf("Current array:\n");
	output_array(width, height, our_array);															// Check if array was properly created.
	printf("\n");
//	printf("HOW ABOUT BUILD 2D?\n");
	//successfully build and print maps if they're valid.

	coordinates = solve_array(our_array, height, width, obstacle);
	printf("Expected coordinates: (0, 3)\n");
	printf("Actual coordinates:   (%d, %d)\n", coordinates.prime_x, coordinates.prime_y);
//	printf("HOW FAR WE HAVE COME\n");
	mod_array(our_array, coordinates, full);
//	printf("WHY NO ERRORS?\n");
	output_array(width, height, our_array);
//	printf("EXECUTES SUCCESSFULLY!\n");
	return (0);
}

