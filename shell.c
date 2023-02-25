#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>

char *param[5];
char *func;
char allParam[256];

void getCommand(){
	char input[256];
	char cwd[1000];
	getcwd(cwd, 1000);
	strcat(cwd,": ");
	printf("%s", cwd);
	scanf(" %[^\n]s", input);
	strcpy(allParam, input);
	char *token = strtok(input, " ");
	
	
	int i = 0;
	func = token;
	while(token){
    		token = strtok(NULL, " ");
    		param[i++] = token;
	}
	
	
	
}

void clearStdin()
{
    // keep reading 1 more char as long as the end of the stream, indicated by the newline char has NOT been reached
    while (true)
    {
        int c = getc(stdin);
        if (c == EOF || c == '\n')
        {
            break;
        }
    }
}

void removeChar(char temp[], int start, int fin){
	char new[256];
	for (int i = start; i < fin; i++){
		new[i-start]=temp[i];
	}
	printf("\n%s\n", new);
}

int listDir(){
	DIR *folder;
	struct dirent *entry;
	int files=0;

	folder = opendir(param[0]);
	if(folder==NULL){
		puts("Unable to read directory!");
		return(1);
	}
	while((entry=readdir(folder))){
		files++;
		printf("File %3d: %s\n", files, entry->d_name);
	}
	closedir(folder);
	return(0);

}

int pauseShell(){
	printf("\nShell is paused until <Enter> is pressed!\n");
	while(1){
		clearStdin();
		int c = getc(stdin);
		if(c=='\n'){
			break;
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	char enter = 0;
	getCommand();
	while(strcmp(func, "quit") != 0){
	
		if(strcmp(func, "cd") == 0){
			chdir(param[0]);
			
		}
		if(strcmp(func, "dir")==0){
			listDir(param[0]);
		}
		if(strcmp(func,"clr")==0){
			system("clear");
		}
		if(strcmp(func,"pause")==0){
			fflush(stdin);
			pauseShell();
		}
		if(strcmp(func, "echo")==0){
			removeChar(allParam, 5, strlen(allParam));
			
		}
	getCommand();
	}
	
}	
