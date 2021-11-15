/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Wilson Simbaña y Pablo Sanchez
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */

#include "permutations.h"
#include "times.h"

#include <stdlib.h>
#include <assert.h>

/***************************************************/
/* Function: random_num Date: 27/9/2021            */
/* Authors: Wilson Simbaña y Pablo Sanchez         */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  assert(inf <= sup);
  return rand() % (sup - inf + 1) + inf;
}

/***************************************************/
/* Function: generate_perm Date: 4/10/2021         */
/* Authors: Wilson Simbaña y Pablo Sanchez         */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/

/**
 * @brief swaps index of int table with random index
 * 
 * @param tabla 
 * @param i 
 * @param rand 
 */
void swap(int *a, int *b);

void swap(int *a, int *b)
{
  int aux = 0;
  assert(a != NULL);
  assert(b != NULL);

  aux = *a;
  *a = *b;
  *b = aux;
  return;
}

int *generate_perm(int N)
{
  int i = 0, *perm = NULL;
  assert(N > 0);
  perm = (int *)malloc(N * sizeof(perm[0]));
  if (!perm)
  {
    free(perm);
    return NULL;
  }

  for (i = 0; i < N; i++)
  {
    perm[i] = i + 1;
  }

  for (i = 0; i < N; i++)
  {
    swap(&perm[i], &perm[random_num(i, N - 1)]);
  }

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int **generate_permutations(int n_perms, int N)
{
  int i = 0, **array = NULL;
  assert(n_perms > 0);
  assert(N > 0);

  array = (int **)malloc(n_perms * sizeof(int *));
  if (!array)
  {
    free(array);
    return NULL;
  }

  for (i = 0; i < n_perms; i++)
  {
    array[i] = generate_perm(N);
  }
  return array;
}