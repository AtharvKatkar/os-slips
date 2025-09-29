/*
 * 	Slip 2-2
 * 	Write a program to implement the shell. It should display the command
 	prompt “myshell$”. Tokenize the command line and execute the given
	command by creating the child process. Additionally it should interpret the
	following ‘list’ commands as
	myshell$ list f dirname :- To print names of all the files in current
 	directory.
 	myshell$ list n dirname :- To print the number of all entries in the current
 	directory
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

void list(char dirname[10], char op){
	DIR *dp = opendir(dirname);
	struct dirent *entry;

	if(dp == NULL){
		printf("Invalid directory name %s does not exist \n", dirname);
		exit(0);
	}

	if(op == 'f'){
		printf("List all files in directory \n");
		while(entry = readdir(dp)){
			if(entry -> d_type == DT_REG)
				printf("o %s\n", entry -> d_name);
		}
	}

	if(op == 'n'){
		printf("Number of all entries in dir \n");
		int fcount=0, dcount=0;

		while(entry = readdir(dp)){
			if(entry -> d_type == DT_REG)
				fcount++;
			if(entry -> d_type == DT_DIR)
				dcount++;
		}

		printf("Total files found in directory: %d\nTotal folders in directory: %d\n", fcount, dcount);
	}
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
		fgets(cmd, 100, stdin);
		sscanf(cmd, "%s%s%s", t1, t2, t3);
		printf("Provided command %s %s %s \n", t1, t2, t3);

		if(strcmp("list", t1) == 0){
			list(t3, t2[0]);
		} else {
			pid = fork();
			if(pid > 0)
				wait(NULL);
		}
	}
}
