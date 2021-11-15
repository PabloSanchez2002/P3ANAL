/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "permutations.h"

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{
  int **perms = generate_permutations(n_perms, N);
  clock_t t_ini, t_fin;
  int i, OB, min, max;
  double count = 0;

  if (perms == NULL)
    return ERR;

  min = INT_MAX;
  max = 0;
  t_ini = clock();

  for (i = 0; i < n_perms; i++)
  {
    OB = metodo(perms[i], 0, N - 1);

    if (OB < min)
      min = OB;
    if (OB > max)
      max = OB;
    count += OB;
  }

  t_fin = clock();
  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = ((double)(t_fin - t_ini) / n_perms) / CLOCKS_PER_SEC;
  ptime->average_ob = count / n_perms;
  ptime->min_ob = min;
  ptime->max_ob = max;

  for (i = 0; i < n_perms; i++)
  {
    free(perms[i]);
  }

  free(perms);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file, int num_min, int num_max, int incr, int n_perms)
{
  TIME_AA *times = NULL;
  int i = 0, tamano = 0;

  tamano = (num_max - num_min) / incr + 1;

  times = (TIME_AA *)malloc(tamano * sizeof(TIME_AA));
  if (!times)
  {
    for (i = 0; i < tamano; i++)
    {
      free(&times[i]);
    }
    free(times);
    return ERR;
  }

  for (i = 0; i < tamano; i++)
  {
    average_sorting_time(method, n_perms, i * incr + num_min, &times[i]);
  }

  save_time_table(file, times, tamano);
  free(times);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char *file, PTIME_AA ptime, int n_times)
{
  int i;
  FILE *pf = NULL;

  if (file == NULL)
    return ERR;

  pf = fopen(file, "w");

  if (pf == NULL)
  {
    fclose(pf);
    return ERR;
  }

  for (i = 0; i < n_times; i++)
  {
    fprintf(pf, "%d %f %f %d %d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
  }

  fclose(pf);

  return OK;
}
