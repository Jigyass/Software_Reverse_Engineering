#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAXSTR 1000
void insert(int, char *);
void increment(int);
void print_data();

int main(int argc, char *argv[])
{
  int addr, hash, t, child, signo, status;
  char str[MAXSTR], name[MAXSTR], t1[MAXSTR], ch;
  FILE *fp;
  struct user_regs_struct regs;

  if(argc < 2){
    fprintf(stderr, "Program to use ptrace to find the number of times each function is reached at run-time\n");
    fprintf(stderr, "Format: ./ptrace_fn <file with all fn names and start addresses> <Child program> <child program args>\n");
    exit(0);
  }

  if((fp = fopen(argv[1], "r")) == NULL){
    printf("File %s cannot be opened for reading\n", argv[1]);
    exit(0);
  }

  /* scan the list of function addresses obtained through an external
     program, like Ghidra or nm */
  fgets(str, MAXSTR, fp);
  while(!(feof(fp))){

    /* from 'nm' */
    if((t = sscanf(str, "%x %c %s", &addr, &ch, name)) == 3){
      if(ch=='t' || ch=='T'){
	/* insert function in database */
	insert(addr, name);
      }
    }
    fgets(str, MAXSTR, fp);
  }
  fclose(fp);

  if(argc < 3){
    printf("No executable specified to trace\n");
    exit(0);
  }
  
  /* fork a new process to run the child executable */
  child = fork();

  if(child == 0){
    /* we are in the child process. Enable tracing and launch the executable */
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execv(argv[2], &(argv[2]));
    printf("Should not reach here\n");
    exit(-1);
  }

  /* This is the code that will be executed by the tracer program */
  while(1){
    /* code will break here on any interrupts */
    wait(&status);
    if(WIFEXITED(status)){

      /* Returns True if the child exited normally */
      fprintf(stdout, "The tracee program has exited with exit status %d\n", WEXITSTATUS(status));
      break;
    }

    signo = WSTOPSIG(status); // Get the signal number

    if(signo == SIGTRAP) {
      /* likely stopped due to the PTRACE singlestepping, or continue.
	 Ignore. */
      signo = 0;
    }
    else if((signo == SIGHUP) || (signo == SIGINT)) {
      ptrace(PTRACE_CONT, child, 0, signo);
      fprintf(stdout, "Child got a SIGHUP or SIGINT. We are done\n");
      break;
    }
    else{
      // do nothing
    }

    ptrace(PTRACE_CONT, child, NULL, signo);
  }
  
  return 0;
}
