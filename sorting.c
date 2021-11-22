/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/

void swap2(int *xp, int *yp);
void copiar(int *tabla1, int *tabla2, int ip, int iu);

void swap2(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int BubbleSort(int *array, int ip, int iu)
{
  int i = ip, j = ip, cont = 0;
  assert(ip <= iu);
  if (!array)
    return ERR;

  for (i = ip; i < iu; i++)
    for (j = ip; j < iu; j++)
      if (array[j] > array[j + 1])
      {
        swap2(&array[j], &array[j + 1]);
        cont++;
      }

  return cont;
}

int BubbleSortFlag(int *array, int ip, int iu)
{
  int flag = 1, i, j, contador = 0;
  assert(ip <= iu);
  for (i = ip; i < iu && flag == 1; i++)
  {

    flag = 0;
    contador++;
    for (j = 0; j < iu; j++)
    {
      if (array[j] > array[j + 1])
      {
        swap2(&array[j], &array[j + 1]);
        flag = 1;
      }
    }
  }

  return contador;
}

int mergesort(int *tabla, int ip, int iu)
{
  int ob = 0, medio = 0, ob1 = 0, ob2 = 0;

  assert(ip >= ip);

  if (ip < iu)
  {
    medio = (iu + ip) / 2;

    ob1 = mergesort(tabla, ip, medio);
    if (ob1 == ERR)
    {
      return ERR;
    }

    ob2 = mergesort(tabla, medio + 1, iu);
    if (ob2 == ERR)
    {
      return ERR;
    }

    ob = ob + ob1 + ob2;

    return ob + merge(tabla, ip, iu, medio);
  }

  else
  {
    return 1;
  }
}

void copiar(int *tabla1, int *tabla2, int ip, int iu)
{
  int i = ip;
  tabla1 -= ip;
  while (i <= iu)
  {
    tabla2[i] = tabla1[i];
    i++;
  }
  return;
}

int merge(int *tabla, int ip, int iu, int imedio)
{

  int *aux = NULL, ob = 0, tam = 0, i = ip, j = imedio + 1, k = 0;
  assert(ip <= iu);
  assert(ip <= imedio);
  assert(iu >= imedio);

  tam = iu - ip + 1;
  aux = (int *)malloc((tam) * sizeof(int));
  if (aux == NULL)
  {
    free(aux);
    return ERR;
  }

  while (i <= imedio && j <= iu)
  {
    if (tabla[i] < tabla[j])
    {
      aux[k] = tabla[i];
      i++;
    }

    else
    {
      aux[k] = tabla[j];
      j++;
    }
    k++;
    ob++;
  }

  if (i > imedio)
  {
    while (j <= iu)
    {
      aux[k] = tabla[j];
      j++;
      k++;
    }
  }
  else if (j > iu)
  {
    while (i <= imedio)
    {
      aux[k] = tabla[i];
      i++;
      k++;
    }
  }

  copiar(aux, tabla, ip, iu);
  free(aux);

  return ob;
}

int quicksort(int *tabla, int ip, int iu)
{

  int m, ob = 0, pos;

  assert(ip <= iu);

  if (ip == iu)
  {
    return OK;
  }

  else
  {
    m = partition(tabla, ip, iu, &pos);

    if (m != ERR)
    {
      ob += m;
    }
    else
      return ERR;

    if (ip < (pos - 1))
    {
      m = quicksort(tabla, ip, pos - 1);

      if (m != ERR)
        ob += m;
      else
        return ERR;
    }

        if ((pos + 1) < iu)
    {
      m = quicksort(tabla, (pos + 1), iu);

      if (m != ERR)
        ob += m;
      else
        return ERR;
    }
  }

  return ob;
}

int quicksort_src(int *tabla, int ip, int iu)
{

  int m, ob = 0, pos, ret = 0;
  assert(tabla != NULL);
  assert(ip <= iu);

  while (ip != iu)
  {
    if (ip > iu)
      return ERR;
    m = partition(tabla, ip, iu, &pos);

    if (m != ERR)
    {
      ob += m;
    }
    else
      return ERR;

    if (ip < (pos - 1))
    {
      ret += quicksort_src(tabla, ip, pos - 1);

      if (ret == ERR)
        return ERR;
    }

    if (pos < iu)
    {
      ip = pos + 1;
    }
    else
      ip = iu;
  }
  return ob + ret;
}

int partition(int *tabla, int ip, int iu, int *pos)
{

  int k, i, err, OB = 0;

  err = median(tabla, ip, iu, pos);

  if (err != ERR)
    OB += err;
  else
    return ERR;

  k = tabla[*pos];
  swap2(&tabla[ip], &tabla[*pos]);

  (*pos) = ip;

  for (i = ip + 1; i <= iu; i++)

  {
    OB++;
    if (tabla[i] < k)
    {
      (*pos)++;
      swap2(&tabla[i], &tabla[*pos]);
    }
  }

  swap2(&tabla[ip], &tabla[*pos]);

  return OB;
}

int median(int *tabla, int ip, int iu, int *pos)
{
  assert(tabla != NULL);

  *pos = ip;

  return 0;
}
