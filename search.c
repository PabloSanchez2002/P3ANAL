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

#include <stdlib.h>
#include <math.h>

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
  int a, j;

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
  else if (pdict->order = NOT_SORTED)
  {
    pdict->table[pdict->size] = key;
    pdict->n_data++;
    return 1;
  }

  /*Caso en el que la estructura está ordenada*/
  else
  { /*Metemos key en la tabla*/
    pdict->table[pdict->size] = key;

    /*Comenzaos a ordenarla*/
    a = pdict->table[pdict->n_data];
    j = pdict->n_data - 1;
    while (j <= pdict->table[0] && pdict->table[j] > a)
    {
      pdict->table[j + 1] = pdict->table[j];
      j--;
    }
    pdict->table[j + 1] = a;
    pdict->n_data++;
  }
}
int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys)
{

  int i, ob = 0;
  ;

  assert(pdict != NULL);
  assert(keys != NULL);
  assert(n_keys > 0);

  for (i = 0; i < pdict->size; i++)
  {
    keys[i] = insert_dictionary(pdict, n_keys);
    ob++;
  }
  return ob;
}

/* Search functions of the Dictionary ADT */
int bin_search(int *table, int F, int L, int key, int *ppos)
{
  assert(table != NULL);
  assert(F > 0);
  assert(L > 0);
  assert(key > 0);
  assert(ppos != NULL);

  return *ppos;
}

int lin_search(int *table, int F, int L, int key, int *ppos)
{
}

int lin_auto_search(int *table, int F, int L, int key, int *ppos)
{
}
