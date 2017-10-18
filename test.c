#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_wait(void* arg) {
	int* arg_int = (int*) arg;

	pthread_t tid = pthread_self();

	sleep(*arg_int);

	printf("Thread with the ID: %d finished waiting for %i seconds!\n", tid, *arg_int);

	pthread_exit(tid);
}

int main(int argc, char *argv[]) {
	int x = 5;
	int y = 10;

	printf("Welcome to the QNX Momentics IDE\n");

	pthread_t p1, p2;

	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	int thread_return_code;

	thread_return_code = pthread_create(&p1,&attr,&thread_wait,&x);
	if(thread_return_code != 0) {
		printf("pthread_create: %s\n", strerror(thread_return_code));
		exit(-1);
	}

	thread_return_code = pthread_create(&p2,&attr,&thread_wait,&y);
	if(thread_return_code != 0) {
		printf("pthread_create: %s\n", strerror(thread_return_code));
		exit(-1);
	}


	pthread_t pid1, pid2;

	pthread_join(p1,&pid1);
	pthread_join(p2,&pid2);


	if(p1 != pid1) {
		printf("PIDs for thread 1 are not equal!\n");
	} else {
		printf("PIDs for thread 1 (ID: %d) are equal.\n", pid1);
	}

	if(p2 != pid2) {
			printf("PIDs for thread 2 are not equal!\n");
		} else {
			printf("PIDs for thread 2 (ID: %d) are equal.\n", pid2);
		}

	return EXIT_SUCCESS;
}

