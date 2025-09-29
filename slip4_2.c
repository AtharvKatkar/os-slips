/*
 *	Write a program to implement the shell. It should display the command
 	prompt “myshell$”. Tokenize the command line and execute the given
 	command by creating the child process. Additionally it should interpret the
 	following commands.
 		- myshell$ search a filename pattern :- To search all the occurrence of pattern in the file.
 		- myshell$ search c filename pattern :- To count the number of occurrence of pattern in the f
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void searchFn(char fn[10], char op, char pat[10]){
	FILE *fp = fopen(fn, "r");
	char word[20];
	int linec = 0, oc=0;

	while(fgets(word, sizeof(word), fp) != NULL){
		if(strcmp(word, "\n") == 0)
			linec++;
		if(strstr(pat, word)){
			oc++;
			if(op == 'a')
				printf("%s occured on line %d \n", pat, linec);
		}
	}
	
	if(op == 'c')
		printf("%s occured in file %d times \n", pat, oc);
}

void main(){
	char cmd[100], t1[10], t2[10], t3[10], t4[10];
	int pid;

	while(1){
		printf("myshell$ ");
		strcpy(t1, "");
		strcpy(t2, "");
		strcpy(t3, "");
		strcpy(t4, "");
		fflush(stdin);
		fgets(cmd, 100, stdin);
		sscanf(cmd, "%s%s%s%s", t1, t2, t3, t4);
		if(strcmp(t1, "search") == 0)
			searchFn(t3, t2[0], t4);
		else {
			pid = fork();
			if(pid > 0)
				wait(NULL);
		}
	}
}
