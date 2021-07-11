// File: genetic.cpp
//
// Description: This file contains the C++ class
//              definition for class 'genetic'.
//
// from my book "C++ Power Paradigms"
//
// Copyright 1995, Mark Watson
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

#define random(x) (rand() % (x))

#include "genetic.h"

genetic::genetic(const int chrom_size, const int num_chrom,
                 fitness_function ff)
{
   chromosome_size = chrom_size;
   num_chromosomes = num_chrom;
   if (num_chromosomes > MAX_CHROMOSOMES) {
      std::cerr << "Chromosome size is too large.\n";
      exit(1);
   }
   fitness_func = ff;
   // Initialize the population:
   for (int i=0; i<num_chromosomes; i++) {
      population[i] = new unsigned char[chromosome_size];
      for (int j=0; j<chromosome_size; j++) {
         if (random(10) < 7)
            population[i][j] = 0;
         else
            population[i][j] = 1;
      }
   }
}

genetic::~genetic()
{
   for (int i=0; i<num_chromosomes; i++)
      delete population[i];
}

void genetic::do_mutations()
{

    // Copy the best chromosomes:
    for (int m=0; m<2; m++) {
         for (int g=0; g<chromosome_size; g++) {
             population[p_chrom[num_chromosomes -1 -m]][g] =
               population[p_chrom[m]][g];
         }
    }
    int nskip = 2 + num_chromosomes / 10;
    int threshold = 995 - ((1000 / chromosome_size) / num_chromosomes);
    for (int i=nskip; i<num_chromosomes; i++) { // skip 'nskip' best chromosomes
        for (int j=0; j<chromosome_size; j++) {
             if (random(1000) > threshold)
                 population[p_chrom[i]][j] =
                        1 - population[p_chrom[i]][j];
        }
    }
}

void genetic::do_crossovers()
{
    // Note: sort_by_fitness() should be called
    //       before this function.
    for (int m=0; m<(num_chromosomes / (num_chromosomes / 2)); m++) {
        // choose one chromosome to change from
        // the "worse" half of the population:
        int c1 = random(num_chromosomes / 2);
        c1 = p_chrom[num_chromosomes - c1 - 1];
        // choose two chromosomes to copy genetic
        // material from fit members of the population
        int s1 = random(num_chromosomes / 4) - 2;
        int s2 = random(num_chromosomes / 4) - 2;
        if (random(10) < 5) {
           s1 /= 2;
           s2 /= 2;
        }
        if (s1 < 0) s1 = 0;  // bias for best chromosome
        if (s2 < 0) s2 = 0;  // bias for best chromosome
        // choose a random allele (gene index)
        // for the crossover operation:
        int cross = 1 + random(chromosome_size - 2);
        for (int i=0; i<cross; i++)
            population[c1][i] = population[s1][i];
        for (int i=cross; i<chromosome_size; i++)
            population[c1][i] = population[s2][i];

    }
}

void genetic::sort_by_fitness()
{
        // Start by calling the fitness function for each
        // chromosome in the population:
        for (int i=0; i<num_chromosomes; i++) {
           fitness_values[i] =
             (*fitness_func)(i, chromosome_size, &(population[i][0]));
        }

        for (int i=0; i<num_chromosomes; i++) p_chrom[i] = i;
        // do a "bubble", or exchange sort:
        for (int i=0; i<num_chromosomes; i++) {
           for (int j=(num_chromosomes-2); j>=i; j--) {
              if (fitness_values[j] < fitness_values[j+1]) {
                 int k = p_chrom[j];
                 float f = fitness_values[j];
                 p_chrom[j] = p_chrom[j+1];
                 fitness_values[j] = fitness_values[j+1];
                 p_chrom[j+1] = k;
                 fitness_values[j+1] = f;
              }
           }
        }
}


void genetic::set_chromosome(int index, gene *chrom)
{
   if (index < 0)  index = 0;
   if (index > (num_chromosomes - 1)) index = num_chromosomes - 1;
   for (int i=0; i<chromosome_size; i++)
      population[index][i] = chrom[i];
}

void genetic::get_chromosome(int index, gene *chrom)
{
   if (index < 0)  index = 0;
   if (index > (num_chromosomes - 1)) index = num_chromosomes - 1;
   // You must call sort_by_fitness() before
   // calling this function.
   for (int i=0; i<chromosome_size; i++)
      chrom[i] = population[p_chrom[index]][i];
}

