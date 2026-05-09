#define MIN_TIME 2000000
#define VAR_TIME 1000000
#define STEP_TIME 10000
#define PROB_FAIL_PER_SEC 50000
#define PROB_RETIRE_PER_SEC 50000
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>

void player( void);
