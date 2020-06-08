#include <stdio.h>
#include <stdlib.h>
#include <wait.h> 
#include <unistd.h>
#include <time.h>
#include <math.h>

double pi_value(int start, int end) {
	double pi = 0;

	for (int i = start; i < end; i++) {
		pi += (pow(-1, i+1) * 4) / (2*i - 1);
	}
	return pi;
}

int main(int argc, char **argv) {
	int number_of_terms, number_of_processes, step_size, start, end;
    double pi = 0.0, terms = 0.0;
    double time_taken = 0.0;
    pid_t pid;

    // pipefd[0] refers to the read end of the pipe.  
    // pipefd[1] refers to the write end of the pipe.
    int pipefd[2];

    printf("Calculating value of Pi (Parallel)\n");

    if (argc < 3) {
        printf("Help: ./task#1 number_of_terms number_of_processes\n");
        return -1;
    }

    clock_t Cstart = clock();

    number_of_terms = atoi(argv[1]);
    number_of_processes = atoi(argv[2]);

    step_size = number_of_terms / number_of_processes;
    
    if (pipe(pipefd) < 0) {
        printf("[X] Error: Calling `pipe` function\n");
        return -1;
    }

    terms = 0.0;
    for (int i = 0; i < number_of_processes; i++) {
    	start = 0;

    	pid = fork();
        if (pid == 0) { 
            start = i * step_size;
            end = (i+1) * step_size;

            terms = pi_value(start, end);
            write(pipefd[1], &terms, sizeof(double));
            return 0;
        }
    }

    // Wait for the Child Processes to complete the execution
    for (int i = 0; i < number_of_processes; i++)
    	wait(NULL);

    terms = 0.0;
    for (int i = 0; i < number_of_processes; i++) {
    	read(pipefd[0], &terms, sizeof(double));

    	pi += terms;
    }

    close(pipefd[1]);

    printf("\nValue of Pi : %4.2f\n", pi);

    clock_t Cend = clock();

    time_taken = ((double)Cend-Cstart)/(double)CLOCKS_PER_SEC;
    printf("\nTime: %f\n", time_taken);  
}