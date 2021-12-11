/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"
#include "permutations.h"

#include <stdlib.h>
#include <math.h>
#include <assert.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be
 *				 allocated externally to the function.
 */

/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for (i = 0; i < n_keys; i++)
    keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for (i = 0; i < n_keys; i++)
  {
    keys[i] = .5 + max / (1 + max * ((double)rand() / (RAND_MAX)));
  }

  return;
}

PDICT init_dictionary(int size, char order)
{
  DICT *new_dict = NULL;
  assert(size >= 0);

  new_dict = (DICT *)malloc(sizeof(DICT));
  if (new_dict == NULL)
  {
    return NULL;
  }
  new_dict->size = size;
  new_dict->order = order;
  new_dict->n_data = 0;
  new_dict->table = (int *)malloc(size * sizeof(int));

  if (new_dict->table == NULL)
  {
    return NULL;
  }

  return new_dict;
}

void free_dictionary(PDICT pdict)
{
  free(pdict->table);
  free(pdict);
}

int insert_dictionary(PDICT pdict, int key)
{
  int a, j, ob = 0;

  assert(pdict != NULL);
  assert(key > 0);

  /*Caso en el que la tabla está vacía, independientemente del orden*/
  if (pdict->n_data == 0)
  {
    pdict->table[0] = key;
    pdict->n_data++;
    return 1;
  }

  /*Caso en el que la estructurano no está ordenadad*/
  else if (pdict->order == NOT_SORTED)
  {
    pdict->table[pdict->n_data] = key;
    pdict->n_data++;
    return 1;
  }

  /*Caso en el que la estructura está ordenada*/
  else
  { /*Metemos key en la tabla*/
    pdict->table[pdict->n_data] = key;

    /*Comenzamos a insertar ordenadamente*/
    a = pdict->table[pdict->n_data];
    j = pdict->n_data - 1;
    while (j >= 0 && pdict->table[j] > a)
    {
      ob++;
      pdict->table[j + 1] = pdict->table[j];
      j--;
    }
    pdict->table[j + 1] = a;
    pdict->n_data++;
  }
  return ob;
}
int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys)
{

  int i, ob = 0, funcion = 0;

  assert(pdict != NULL);
  assert(keys != NULL);
  assert(n_keys > 0);

  for (i = 0; i < n_keys; i++)
  {
    funcion = insert_dictionary(pdict, keys[i]);
    if (funcion == ERR)
    {
      return ERR;
    }
    ob += funcion;
  }
  return ob;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  int ob = 0;
  assert(pdict != NULL);
  assert(key > 0);
  assert(ppos != NULL);
  assert(method != NULL);

  ob = method(pdict->table, 0, pdict->n_data - 1, key, ppos);

  return ob;
}

/* Search functions of the Dictionary ADT */
int bin_search(int *table, int F, int L, int key, int *ppos)
{
  int mid;
  assert(table != NULL);
  assert(L >= 0);
  assert(key > 0);

  /* Base case 1, n not found :*/
  if (F > L)
  {
    *ppos = NOT_FOUND;
    return ERR;
  }
  /*Base case 2, n found:*/
  mid = (F + L) / 2;
  if (table[mid] == key)
  {
    *ppos = mid;
    return 1;
  }
  /*Recursion on left part:*/
  if (table[mid] > key)
    return 1 + bin_search(table, F, mid - 1, key, ppos);
  /* Recursion on right part:*/
  else
    return 1 + bin_search(table, mid + 1, L, key, ppos);
}

int lin_search(int *table, int F, int L, int key, int *ppos)
{
  int i, ob = 0;

  for (i = F; i <= L; i++)
  {
    ob++;
    if (table[i] == key)
    {
      *ppos = i;
      return ob;
    }
  }
  *ppos = NOT_FOUND;

  return ob;
}

int lin_auto_search(int *table, int F, int L, int key, int *ppos)
{
  int i, ob = 0;
  for (i = F; i <= L; i++)
  {
    ob++;
    if (table[i] == key)
    {
      if (i == F)
      {
        *ppos = i;
      }

      else
      {
        swap(&table[i], &table[i - 1]);
        *ppos = i - 1;
      }

      return ob;
    }
  }
  *ppos = NOT_FOUND;

  return ob;
}
