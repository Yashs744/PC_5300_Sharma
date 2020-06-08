#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv) {
	int number_of_terms;
	double pi = 0.0;

	clock_t start = clock();

	printf("Calculating value of Pi Sequentially\n");

	if (argc < 2) {
		printf("Help: ./CalcPi_Seq number_of_terms\n");
		return -1;
	}

	number_of_terms = atoi(argv[1]);

	// pi = 4/1 - 4/3 + 4/5 - 4/7 + 4/9 . . . (-1^(n+1) * 4) / (2*n + 1)
	for (int i = 1; i <= number_of_terms; i++) {
		pi += (pow(-1, i+1) * 4) / (2*i - 1);
	}

	printf("\nValue of Pi (with number_of_terms = %i): %4.2f\n", number_of_terms, pi);

	clock_t end = clock();

	printf("\nTime: %f\n", ((double)end-start)/(double)CLOCKS_PER_SEC);	

	return 0;
}