/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnessaiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 00:08:50 by dnessaiv          #+#    #+#             */
/*   Updated: 2016/08/31 00:08:53 by dnessaiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdlib.h>
#include <unistd.h>
#include "ft_list.h"

#define MAX_READ 4096

/*
** Keep CPY_TYPE as char to trigger autovectorization (-O3)
*/

#define CPY_TYPE char
#define	CPY_WSIZE sizeof(CPY_TYPE)
#define CPY_WMASK (CPY_WSIZE - 1)

void	ft_memcpy_aligned(void *dst, void *src, size_t length)
{
	size_t	t;

	if (!src)
		return ;
	src += length;
	dst += length;
	t = length / CPY_WSIZE;
	while (t > 0)
	{
		src -= CPY_WSIZE;
		dst -= CPY_WSIZE;
		*(CPY_TYPE*)dst = *(CPY_TYPE*)src;
		t--;
	}
}

char	*ft_realloc(char *buf, ssize_t *buf_cap)
{
	ssize_t	old_cap;
	char	*newbuf;

	old_cap = *buf_cap;
	*buf_cap = old_cap * 2;
	newbuf = malloc(*buf_cap);
	ft_memcpy_aligned(newbuf, buf, old_cap);
	free(buf);
	return (newbuf);
}

char	*ft_read_input(int fd)
{
	ssize_t	read_size;
	char	*buf;
	ssize_t buf_cap;
	ssize_t buf_offset;

	buf_cap = MAX_READ / 2;
	buf = ft_realloc(NULL, &buf_cap);
	buf_offset = 0;
	while ((read_size = read(fd, buf + buf_offset, MAX_READ)) > 0)
	{
		buf_offset = buf_offset + read_size;
		if (buf_cap - buf_offset < MAX_READ + 1)
			buf = ft_realloc(buf, &buf_cap);
	}
	buf[buf_offset] = 0;
	return (buf);
}

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

void	check_errors(buffer)
{
	check true instances
	otherwise 
		return (0);
}

char 	**build_2d(buffer, width, height)
{
	char **our_array
	int index;
	int i;
	int j;

	i = 0;
	j = 0;
	index = 5;
	our_array = malloc (sizeof(char *) * width)
	while (buffer[index])
	{
		while (i < height)
		{
			our_array[i] = malloc(sizeof * width)
			i++;
		}
		i = 0;
		while (i < height && buffer[index])
		{
			if (buffer[index] = '\n')
			{
				index++;
				i++;
			}
			while (j < width && buffer[index])
			{
				our_array[i][j] = buffer[index];
				j++;
				index++;
			}
			i++;
		}
	}	
}

int get_width(buffer)
{
	int i;
	int width;

	width = 0;
	i = 6
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

t_iterators solve_array(our_array, height, width)
{
	int i;
	int j;
	t_iterators	coordinates;

	coordinates.size = 0
	i = 0;
	j = 0;
	while (i < heigth)
	{
		while (j < width)
		{
			coordinates.x = i;
			coordinates.y = j;
			if (size < gsq(our_array, coordinates, obstacle, coordinates.size))
			{
				coordinates.prime_x = i;
				coordinates.prime_y = j;
				coordinates.size = gsq(our_array, coordinates, obstacle, coordinates.size)
			}
			j++;
		}
		i++;
	}
	return (coordinates);
}

void	mod_array(char **our_array, t_iterator coordinates, full)
{
	int i;
	int j;
	while (i<size)
	{
		while (j<size)
		{
			our_array[(coordinates.prime_x)+i][(coordinates.prime_y)+j] = full
			j++;
		}
		i++;
	}
}

void	outputs_array(int width, int height, char **our_array)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < height)
	{
		while (j < width)
		{
			write(1, our_array[i][j], 1);
			j++;
		}
		i++;
	}
}


int main()
{
	int			i;
	int			j;
	int			width;
	int			height;
	char		instructions[5];
	char		**our_array;
	t_iterator	coordinates;

	i = 0;
	j = 0;
	buffer		= get_buffer;
	height		= ft_atoi(buffer[0]);
	empty		= buffer[1];
	obstacle	= buffer[2];
	full		= buffer[3];

	width = get_width(buffer);

	check_errors(buffer, width);

	our_array = build_2d(buffer, width, height);

	coordinates = solve_array(our_array, height, width, obstacle);

	mod_array(our_array, coordinates)

	greatest_square_size(our_array, i, j);
	return (0);
}

