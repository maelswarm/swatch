//
//  main.c
//  swatch
//
//  Created by fairy-slipper on 5/9/16.
//  Copyright © 2016 fairy-slipper. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>

pid_t  pid;
int status;
struct timeval begin, end;
double timediff;

int main(int argc, const char * argv[]) {
    // insert code here...
    gettimeofday(&begin , NULL);
    
    pid = fork();
    if (pid == 0) {
        char *execArgs[argc];
        for (int i=0; i<argc-1; i++) {
            execArgs[i] = malloc(sizeof(char)*strlen(argv[i+1]));
            strcpy(execArgs[i], argv[i+1]);
        }
        execArgs[argc-1] = NULL;
        int prxspawn = execvp(execArgs[0], execArgs);
    } else {
        waitpid(-1, &status, 0);
        gettimeofday(&end , NULL);
        timediff = (end.tv_sec - begin.tv_sec) + 1e-6 * (end.tv_usec - begin.tv_usec);
        printf("Time elapsed: %lf\n", timediff);
    }
    
    return 0;
}
