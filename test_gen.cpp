// File: test_gen.cpp

#include <iostream>

#include "genetic.h"

float fitness_f(const int ch_size, const int chrom_size, unsigned char *chrom)
{
	float ret_val = 0.0;
	for (int i=0; i<ch_size; i++)
		ret_val += chrom[i];
	return ret_val;
}

const int NUM_GENES = 9;
const int NUM_CHROMOSOMES = 20;

int main()
{
	std::cerr << "Testing class 'genetic'\n";
	genetic g(NUM_GENES, NUM_CHROMOSOMES, fitness_f);
	for (int iter=0; iter<20; iter++) {
		g.sort_by_fitness();
		g.do_crossovers();
	 	g.do_mutations();
		gene ch[20];
		std::cerr << "best chromosomes: ";
		for (int l=0; l<4; l++) {  // 4 best chromosomes
				g.get_chromosome(l, ch);
				for (int j=0; j<NUM_GENES; j++)
					std::cerr << (int)ch[j];
				std::cerr << " ";
		}
		std::cerr << "\n";
	}
	return 0;
}

