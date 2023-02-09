#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>

char *param[5];
char *func;

void getCommand(){
	char input[256];
	char cwd[1000];
	getcwd(cwd, 1000);
	strcat(cwd,": ");
	printf("%s", cwd);
	scanf(" %[^\n]s", input);
	char *token = strtok(input, " ");
	
	
	int i = 0;
	func = token;
	while(token){
    		token = strtok(NULL, " ");
    		param[i++] = token;
	}
	
	
	
}

int main(int argc, char *argv[]){
	getCommand();
	while(strcmp(func, "quit") != 0){
	
		if(strcmp(func, "cd") == 0){
			chdir(param[0]);
			
		}
	getCommand();
	}
	
}	
