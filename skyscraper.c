/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   skyscraper.c                                         .|||||||||.         */
/*                                                       |||||||||||||        */
/*   By: graja <gundul@mailbox.org>                     /. `|||||||||||       */
/*                                                     o__,_||||||||||'       */
/*   Created: 2021/05/08 16:22:44 by graja                                    */
/*   Updated: 2021/05/09 12:12:43 by graja                Gundul.net          */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  printf("\n");
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

int  ft_solve(int  **field, int *clues, int  row, int  col, int  n)
{
  int  i;
  
  i = 1;
  while (i <= n)
  {
    if (ft_isvalid(field, row, col, i, n) == 0)
    {
      field[row][col] = i;
      if ((col == n - 1) && (row < n - 1))
      {
        if (ft_solve(field, clues, row + 1, 0, n) == 1)
          field[row+1][0] = 0;
        else
          return(0);
      }
      if (col < n - 1)
      {
        if (ft_solve(field, clues, row, col + 1, n) == 1)
          field[row][col + 1] = 0;
        else
          return(0);
      }
    }
  i++;
  }
  return (ft_checkall(field, clues, n));
}

int** SolvePuzzle (int *clues)
{
  int  n;
  int  **field;
  /*n = 4;  */ /* make it flexible for later projects */
   n = 5; 
  /* n = 6; */
  field = ft_getmem2d(n);
  ft_solve(field, clues, 0, 0, n);
  ft_printfield(field, n);
    return (field);
}

int	main(void)
{
	int	**matrix;
	int	*clues;
	clock_t begin = clock();
	/* int	clue[16] = {2,2,1,3,2,2,3,1,1,2,2,3,3,2,1,3}; */
	 int		clue[20] = {4,0,3,2,0,0,0,0,2,0,0,4,0,0,0,1,0,2,3,3}; 
	/* int		clue[24] = {2,4,3,1,2,2,2,2,3,6,3,1,1,3,4,2,2,3,4,2,1,3,3,2}; */ 

	clues = &clue[0];
	matrix = SolvePuzzle(clues);
	clock_t end = clock();
	printf("calculated in %f s\n\n", (double)(end - begin) / CLOCKS_PER_SEC);
	return(0);
}
