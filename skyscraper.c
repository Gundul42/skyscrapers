/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   skyscraper.c                                         .|||||||||.         */
/*                                                       |||||||||||||        */
/*   By: graja <gundul@mailbox.org>                     /. `|||||||||||       */
/*                                                     o__,_||||||||||'       */
/*   Created: 2021/05/08 16:22:44 by graja                                    */
/*   Updated: 2021/05/10 19:01:39 by graja                Gundul.net          */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>

int	ft_permut(int *arr, unsigned current, unsigned max, unsigned n, int used[], int idx)
{
	unsigned i;

	if (n == 0)
  	{
		idx++;
		/*printf("%d  - %d\n", current, idx);*/
		arr[idx - 1] = current;
	}
	else
	{
		i = 0;
		while (i < max)
		{
			i++;
      			if (!used[i])
			{
				used[i] = 1;
				idx = ft_permut(arr, current*10 + i, max, n - 1, used, idx);
				used[i] = 0;
			}
		}
	}
  return(idx);
}

int	ft_fact(int n)
{
	int	i;
	int	res;

	res = 1;
	i = 1;
	while (i <= n)
	{
		res *= i;
		i++;
	}
	return (res);
}

int **ft_getmem2d(int n)
{
  int  i;
  int  **matrix;

  matrix = calloc(n, sizeof(int *));
  i = 0;
  while (i < n)
  {
    matrix[i] = calloc(n, sizeof(int));
    i++;
  }
  return (matrix);
}

int  ft_zerocheck(int  **field, int n)
{
  int  x;
  int  y;
  
  x = 0;
  while (x < n)
  {
    y = 0;
    while (y < n)
    {
	if (field[x][y] == 0)
		return (1);
      y++;
    }
    x++;
  }
  return (0);
}

void  ft_printfield(int  **field,int  n)
{
  int  row;
  int  col;
  
  row = 0;
  while (row < n)
  {
    col = 0;
    while (col < n)
    {
      printf("%d ", field[row][col]);
      col++;
    }
    printf("\n");
    row++;
  }
  printf("\n\n");
}

int  ft_countrow(int  **field,int  row,int  n, int dir)
{
  int  i;
  int  sum;
  int  max;
 
  sum = 0;
  max = 0;
  if (dir == 0)
  {
    i = 0;
    while (i < n)
    {
      if ((field[row][0] <= field[row][i]) && (field[row][i] > max))
      {
        max = field[row][i];
        sum++;
      }
      i++;
    }
    return (sum);
   }
  else
  {
    i = n -1;
    max = 0;
    while (i >= 0)
    {
      if ((field[row][n - 1] <= field[row][i]) && (field[row][i] > max))
      {
        max = field[row][i];
        sum++;
      }
      i--;
    }
    return (sum);
  }
}

int  ft_countcol(int  **field,int  col,int  n, int dir)
{
  int  i;
  int  sum;
  int  max;
 
  sum = 0;
  max = 0;
  if (dir == 0)
  {
    i = 0;
    while (i < n)
    {
      if ((field[0][col] <= field[i][col]) && (field[i][col] > max))
      {
        max = field[i][col];
        sum++;
      }
      i++;
    }
    return (sum);
   }
  else
  {
    i = n - 1;
    max = 0;
    while (i >= 0)
    {
      if ((field[n - 1][col] <= field[i][col]) && (field[i][col] > max))
      {
        max = field[i][col];
        sum++;
      }
      i--;
    }
    return (sum);
  }
}

int  ft_checkall(int  **field, int  *clues, int  n)
{
  int  i;
  int  *tmp;
  
  tmp = calloc((n * 4), sizeof(int));
  i = 0;
  while(i < (n * 4))
  {
    if (i < n)
      tmp[i] = ft_countcol(field, i, n, 0);
    if ((i > (n - 1)) && (i < (2 * n)))
      tmp[i] = ft_countrow(field, i - n, n, 1);
    if ((i > (2 * n - 1)) && (i < (3 * n)))
      tmp[i] = ft_countcol(field, 3 * n - i - 1, n, 1);
    if ((i > (3 * n - 1)) && ( i < 4 * n))
      tmp[i] =  ft_countrow(field, 4 * n - i - 1, n, 0);
    i++;
    }
  i = 0;
  if (ft_zerocheck(field, n) == 1)
  {
	  free(tmp);
	  return (1);
  }
  while (i < (n * 4))
    {
      if (clues[i] != 0)
      {
        if (clues[i] != tmp[i])
	{
		free(tmp);
		return(1);
	}
      }
    i++;
  }
  free(tmp);
  return(0);
}

int  ft_isvalid(int  **field, int row, int col, int num, int n)
{
  int i;
  
  i = 0;
  while (i < n)
  {
    if ((field[row][i] == num) || (field[i][col] == num))
      return (1);
    i++;
  }
  return (0);
}

int	ft_delrow(int **field, int row, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		field[row][i] = 0;
		i++;
	}
}

int	ft_fillrow(int **field, int row, int num, int n)
{
	int	i;
	int	chk;

	i = 0;
	while (i < n)
	{
		chk = num % 10;
		num /= 10;
		if ((ft_isvalid(field, row, n - i - 1, chk, n) == 1) && (row != 0))
		{
			ft_delrow(field, row, n);
			return (1);
		}
		field[row][n - i - 1] = chk;
		i++;
	}
	return (0);
}

int  ft_solve(int  **field, int *clues, int *mutasi, int  row, int  max, int  n)
{
	int	i;
	int	j;
	int	val;
	int	bck;
  
	bck = 1;
	j = 0;
	while ((j < max) && (bck == 1))
	{
		val = ft_fillrow(field, row, mutasi[j], n);
		if ((row < n - 1) && (val == 0))
		{
			bck = ft_solve(field, clues, mutasi, row + 1, max, n);
			if (bck == 1)
				ft_delrow(field, row + 1, n);
		}
		if ((row == n - 1) && (val == 0))
		{
			if (ft_checkall(field, clues, n) != 0)
			{
				ft_delrow(field, row, n);
			}
			else
				return(0);
		}
		/*ft_printfield(field, n);*/
		j++;
	}
	return (ft_checkall(field, clues, n));
}

int** SolvePuzzle (int *clues)
{
  int	n;
  int	**field;
  int	*mutasi;
  int	idx;
  int	used[10] = { 0 };

  idx = 0;
  n = 4;   /* make it flexible for later projects */
  mutasi = malloc(sizeof(int) * ft_fact(n));
  field = ft_getmem2d(n);
  idx = ft_permut(mutasi, 0, n, n, used, idx);
  ft_solve(field, clues, mutasi, 0, idx, n);
  ft_printfield(field, n);
  free(mutasi);
  return (field);
}

int	main(void)
{
	int	**matrix;
	int	*clues;
	int	clue[16] = {0,3,0,0,0,3,3,0,0,0,0,2,0,0,0,0};

	clues = &clue[0];
	matrix = SolvePuzzle(clues);
	return(0);
}
