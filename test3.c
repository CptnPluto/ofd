#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"
int checkif(char c, char obstacles)
{
	if (obstacles == c ||c == '\n' || c =='\0')//this makes it behave strangely
	{
			return 1;//was 0
	}
	return 0;
}

int innerchecker(char **origin, t_iterators offset, int size, char obstacle)
	//will be used to check once largest square has been found no sense in checking borders 
	//if internal aren't valid
{
	char **o = origin;
	int i = 0;
	int j = 0;
	if (size == 0)
	{
		return 0;
	}
//	printf("CHECK\n");
	while (i<size)
	{
		while(j<size)
		{
			if (!checkif(o[(offset.x)+i][(offset.y)+j],obstacle))
			{
				return 0;
			}
			j++;
		}
		i++;
	}
	return 1;
}

int borderchecker(char **origin, t_iterators offset, int size, char obstacle)
{
	char **o = origin;
	int test=0;
	int i = offset.x;
	int j = offset.y;
	if (size == 1 || size == 0) //looking for a square of size 1
	{
		return checkif(o[i][j],obstacle);//check if the element o points to is an obstacle
		//it will return 1 if it is not an obstacle and 0 if it is.
	}
	else if (size == 2) //looking for a square of size 2
	{	//assume that 1 is already a square 0,0
//		printf("THIS ISNT BEGIN CALLED FOR ALL SIZES\n");
	
		while (i<size-1)//accounts for indices being offset by 1 and loops from 0 to 1(accounts for 0,1 )
		{
			test = checkif(o[i++][size-1],obstacle);
			if (!test)//why not test??
			{
				return 0;
			}
		}
		while (j<size)
		{		
			test = checkif (o[size-1][j++],obstacle);//accounts for 1,0 1,1
			if (!test)//why not test?
			{
				return 0;
			}
		}
		if (test)//if test is 1 return the size because it has passed test and is a 2 square
		{		
			return size;
		}
		return 0;//else return 0 not a 2square
	}
	else if (size > 2 )//looking for a square of size >2
	{	
		while (i < size-1)
		{		
			test = checkif(o[i++][size-1],obstacle);//gets horizontal border elements
			if (!test)//why not test??
			{
				return 0;
			}
		}
		while (j < size-2)
		{		
			test = checkif (o[size-1][j++],obstacle);//gets vertical border elements
			if (!test)//why not test??
			{
				return 0;
			}
		}
		if (test)
		{
			return size;
		}
		return 0;
	}
	else
	{
		return 0;
	}
}
int gsq(char **origin, t_iterators offset, int size, char obstacle)
{
	int temp = 0;
	if ((temp = innerchecker(origin,offset,size,obstacle)))//if innerchecker doesn't return 0
	{
		while ((temp = borderchecker(origin,offset,size++,obstacle)))//while borderchecker !=0
		{
			size = temp;
		}//size is being allocated to null when it returns from borderchecker then size is 0 and doesn't count;
	}	
	return size;
	
}
