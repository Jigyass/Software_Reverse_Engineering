/* Template program to test assembly knowledge */


/*
You are given the "objdump" output for some binary and
and a template C program. Your assignment is to interpret
the objdump output to allow you to complete this template
program. Then, compile and run this completed program and
give the output generated for each question in your HW.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int gval;

int main(int argc, char *argv[])
{
  int val, ret;

  if(argc < 2){
    printf("Program takes one argument.\n");
    exit(0);
  }
  val = atoi(argv[1]);

  if(val > 1000){

    printf("A: %d\n", ret);
  }
  else if(val > 500){
    printf("B: %d\n", val);
    printf("B: @@@\n"); 
  }
  else if(val > 200){
    int arr[500];
    printf("C: %d\n", arr[100]);
  }
  else if(val > 100){
    printf("D: %d\n", gval);
  }
  else if(val > 10){
    printf("E: FLAG Reached\n");
  }
  else{
    printf("F: %d\n", ret);
  }

  return 0;
}
