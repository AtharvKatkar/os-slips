/*
 * Slip soln 1.2 typeline 1) first +n lines 2) -a print all lines
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void fileCMD(char fname[10], char op[10]){
	FILE *fp = fopen(fname, "r");
	char ch;

	if(fp == NULL){
		printf("Invalid %s file does not exist \n", fname);
		exit(0);
	}

	if(strcmp(op, "-a") == 0){
		printf("Printing all the contents of the file:\n\n");
		while((ch = fgetc(fp)) != EOF){
			printf("%c", ch);
		}
	}

	if(atoi(op) > 0){
		int i = 0;
		printf("Printing first %d no of lines\n\n", atoi(op));

		while((ch = fgetc(fp)) != EOF && i < atoi(op)){
			printf("%c", ch);
			if(ch == '\n' || ch == '\0')
				i++;
		}
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
		// printf("Provided command %s %s %s", t1, t2, t3);
		
		if(strcmp(t1, "typeline") == 0){
			fileCMD(t3, t2);
		} else {
			pid = fork();
			if(pid > 0)
				wait(NULL);
		}
	}
}
