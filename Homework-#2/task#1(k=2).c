#include <stdio.h>
#include <stdlib.h>
#include <wait.h> 
#include <unistd.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv) {
    int number_of_terms, n;
    float pi = 0.0, terms = 0.0;
    double time_taken = 0.0;

    // pipefd[0] refers to the read end of the pipe.  
    // pipefd[1] refers to the write end of the pipe.
    int pipefd[2];
    pid_t pid;

    clock_t start = clock();

    printf("Calculating value of Pi (k = Number of Processes = 2)\n");

    if (argc < 2) {
        printf("Help: ./task#1 number_of_terms\n");
        return -1;
    }

    number_of_terms = atoi(argv[1]);
    
    if (pipe(pipefd) < 0) {
        printf("[X] Error: Calling `pipe` function\n");
        return -1;
    }

    pid = fork();
    
    if (pid < 0) {
        printf("[X] Error: Calling `fork` function\n");
        return -1;

    }

    /* parent proces */ 
    else if (pid > 0) {
        close(pipefd[0]);
        write(pipefd[1], &number_of_terms, 100);

        for (int i = 1; i < number_of_terms/2; i++) {
            pi += (pow(-1, i+1) * 4) / (2*i - 1);
        }

        wait(NULL);

        close(pipefd[1]);
        n = read(pipefd[0], &terms, 100);

        pi += terms;

        printf("\nValue of Pi (with number_of_terms = %i): %4.2f\n", number_of_terms, pi);

        clock_t end = clock();

        time_taken = ((double)end-start)/(double)CLOCKS_PER_SEC;
        printf("\nTime: %f\n", time_taken);   
        
    } 
    /* child process */
    else { 
        close(pipefd[1]);
        n = read(pipefd[0], &n, 100);

        for (int i = n/2; i <= n; i++) {
            terms += (pow(-1, i+1) * 4) / (2*i - 1);
        }

        close(pipefd[0]);
        write(pipefd[1], &terms, 100);     
    }
    
    return 0;
}