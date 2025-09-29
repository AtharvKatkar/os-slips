/*
 *	Write a programto implement the toy shell. It should display the command
	prompt “myshell$”. Tokenize the command line and execute the given
 	command by creating the child process. Additionally it should interpret the
 	following commands.
		- count c filename :- To print number of characters in the file.
 		- count w filename :- To print number of words in the file.
 		- count l filename :- To print number of lines in the file.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void countFn(char fname[10], char op){
	FILE *fp = fopen(fname, "r");
	int charc = 0, wordc = 0, linec = 0;
	char ch;

	if(fp == NULL){
		printf("Could not open file (%s)", fname);
		exit(0);
	}

	while((ch = fgetc(fp)) != EOF){
		if(ch == '\n' || ch == '\0')
			linec++;
		if(ch == '\n' || ch == '\t' || ch == '\0' || ch == ' ')
			wordc++;
		charc++;
	}

	if(op == 'c')
		printf("Total characters in file: %d", charc);
	if(op == 'w')
		printf("Total words in file: %d", wordc);
	if(op == 'l')
		printf("Total lines in file %d", linec);
}

void main(){
	char cmd[100], t1[10], t2[10], t3[10];
	int pid;

	while(1){
		printf("myshell$ ");
		strcpy(t1, "");
		strcpy(t2, "");
		strcpy(t3, "");
		fflush(stdin);
		fgets(cmd, sizeof(cmd), stdin);
		sscanf(cmd, "%s%s%s", t1, t2, t3);
		if(strcmp("count", t1) == 0){
			countFn(t3, t2[0]);
		} else {
			pid = fork();
			if(pid > 0){
				wait(NULL);
			}
		}
	}
}

