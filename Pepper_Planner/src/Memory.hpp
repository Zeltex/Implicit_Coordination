#pragma once

#ifdef __linux__

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void report_memory_usage() {

        pid_t pid = getpid();

        char buffer[256];

        sprintf(buffer, "pmap %d | tail -n 1 | grep -oh '\\w*K\\w*' | tee memory_usage.txt", pid);

	printf("Memory usage: ");
	fflush(stdout);
	system(buffer);
}

#else 
void report_memory_usage() {
}
#endif
