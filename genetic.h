// File: genetic.h
//
// Description: This file contains the C++ class interface
//              for class 'genetic'.
//
// Copyright 1995, Mark Watson
//

#ifndef genetic_h
#define genetic_h

#define random(x) (rand() % (x))

typedef unsigned char gene;

typedef float (*fitness_function)(const int chrom_index,
                                  const int chrom_size,
                                  unsigned char *chrom);


class genetic {
 public:
    genetic(const int chrom_size, const int num_chrom,
            fitness_function ff);
   ~genetic();
    void do_mutations();
    void do_crossovers();
    void sort_by_fitness();
    void set_chromosome(int index, gene *chrom);
    void get_chromosome(int index, gene *chrom);
 protected:
    int chromosome_size;   // # of genes per chromosome
    int num_chromosomes;
    fitness_function fitness_func;
    enum {MAX_CHROMOSOMES=100};
    gene * population[MAX_CHROMOSOMES];
    float fitness_values[MAX_CHROMOSOMES];
    int p_chrom[MAX_CHROMOSOMES];
};

#endif
