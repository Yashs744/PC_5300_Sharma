// Task Number #1 - Process (P)
// P1 -> P2 -> P3
//        |--> P4

#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid_P2, pid_P3, pid_P4;

	printf("Parallel Computing Homework #1 - Task #1\n\n");

	printf("Parent Process P1 ID: %i\n", getpid());
	printf("\nForking Child Process P2 from Parent Process P1\n\n");

	pid_P2 = fork();

	if (pid_P2 < 0){
		printf("Error\n");
		return 1;
	}
	else if (pid_P2 == 0) {
		printf("Child Process (P2) Executed\n");

		printf("Parent P1 ID: %i\n", getppid());
		printf("Child P2 ID: %i\n", getpid());

		printf("\nForking Child Process P3 and P4 from Parent Process P2\n\n");

		pid_P3 = fork();
		pid_P4 = fork();

		if (pid_P3 > 0 && pid_P4 > 0) {
			printf("Child Process (P3) & (P4) Created\n\n");

			printf("Parent Process P2 ID: %i\n", getpid());

			printf("Waiting for Child Processes\n\n");
			wait(NULL);
			printf("Completed\n");		
		}

		else if (pid_P3 == 0 && pid_P4 > 0) {
			printf("Child Process (P3) Executed\n");

			printf("Parent P2 ID: %i\n", getppid());
			printf("Child P3 ID: %i\n\n", getpid());
		}
		else if (pid_P3 > 0 && pid_P4 == 0) {
			printf("Child Process (P4) Executed\n");

			printf("Parent P2 ID: %i\n", getppid());
			printf("Child P4 ID: %i\n\n", getpid());
		}
		else {
			return 1;
		}
	}
	else if (pid_P2 > 0) {
		printf("Child Process (P2) Created\n");
		printf("Parent Process P1 ID: %i\n", getpid());

		printf("\nWaiting for Child Process (P2)\n\n");
		wait(NULL);
		printf("Completed\n");

	}

	return 0;
}