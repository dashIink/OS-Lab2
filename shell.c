#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/wait.h>

char *param[5];
char *func;
char allParam[256];
int status;

extern char **environ;//extern allows the shell to grab the environment variables from the OS

void getCommand(){
	//Input can be up to 256 characters long
	char input[256];
	char cwd[1000];
	getcwd(cwd, 1000);// grabs the current working directory and concatinates it with ": "
	strcat(cwd,": ");
	printf("%s", cwd);//Prints out the CWD before every line
	scanf(" %[^\n]s", input); //Scan for user input, including spaces
	strcpy(allParam, input);
	char *token = strtok(input, " ");
	//Tokenize inputs in order to get each function of the command
	
	int i = 0;
	func = token;
	while(token){
    		token = strtok(NULL, " ");
    		param[i++] = token;
	}
	//Set each token as a potential parameter
	
	
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

// Removes the beginning letters of a string, namely used in the echo function to echo back a string
void removeChar(char temp[], int start, int fin){
	char new[256];
	for (int i = start; i < fin; i++){
		new[i-start]=temp[i];
	}
	printf("\n%s\n", new);
}
//prints out the conents of the current or specified directory
int listDir(){
	DIR *folder;
	struct dirent *entry;
	int files=0;
	// if no parameter is entered, assume the CWD
	if(param[0]==NULL){
		folder=opendir(".");
	}
	else{
		folder = opendir(param[0]);
	}
	if(folder==NULL){
		//If we are unable to find a file, inform the user
		puts("Unable to read directory!");
		return(1);
	}
	while((entry=readdir(folder))){
		//For every file in the directory, print out the name
		files++;
		printf("File %3d: %s\n", files, entry->d_name);
	}
	return(0);

}
//Returns a boolean based on if a file exists in the CWD or not
bool searchForFile(char nof[]){
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (strcmp(dir->d_name, nof) == 0){
				//If a file by the same name is found, return true as a signal that the file can be opened
				return true;
			}
	    	}
	    	closedir(d);
	}
	//If nothing is found, return false
	return false;
}
//Until the user presses enter, run a continous loop of clearing the input space.
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
	// On a main file opening, call getCommand, which reads for user input and parses it
	char enter = 0;
	getCommand();
	//So long as the user has not entered quit, keep the loop running
	while(strcmp(func, "quit") != 0){
	//If the user calls the CD function, call the change directory function
		if(strcmp(func, "cd") == 0){
			chdir(param[0]);
			
		}
		//If the user calls dir, call the listDir function
		if(strcmp(func, "dir")==0){
			listDir(param[0]);
		}
		//If the user calls clear, call the system clear funtion to clear the screen
		if(strcmp(func,"clr")==0){
			system("clear");
		}
		//If the user calls pause, clear the input and pause the shell
		if(strcmp(func,"pause")==0){
			fflush(stdin);
			pauseShell();
		}
		//If the User calls echo, remove the function call and only print the second part of the input
		if(strcmp(func, "echo")==0){
			removeChar(allParam, 5, strlen(allParam));
			
		}
		if(strcmp(func, "environ") == 0){
            		// loop over the environ variable and print each environment variable
            		for (char **env = environ; *env != NULL; env++)
            		{
                		printf("%s\n", *env);
            		}
        	}
		if (strcmp(func, "help") == 0) {
			pid_t pid = fork();//Create a fork
			if(pid == 0){//If child process
				char *args[] = {"more", "readme.md", NULL};
            			execvp(args[0], args);	
			}
			else{
				waitpid(pid, &status, 0);// wait for child
			}
		}
		else{//if the input is not recognized, search for a file by the name
			if (searchForFile(func)){
			char executeFile[] = "./";
			if(param[0] != NULL){//The user has entered a second parameter
				if (*param[0] == '&'){//The user wants to call a file using a fork without having the parent wait
					pid_t pid = fork();//Create a fork
					if(pid == 0){//If child process
						strcat(executeFile, func);
						char *args[]={executeFile,NULL};//Create arguments for the file
						execvp(args[0],args);//change from current code to new file
					}	
				}
				else{
					pid_t pid = fork();//create a fork
					if(pid == 0){//if child
						strcat(executeFile, func);
						char *args[]={executeFile,NULL};
						execvp(args[0],args);// run the file in the child process
					}
					else{
						waitpid(pid, &status, 0);// wait for child process to finish
					}
				}
			}
			else{// no second parameter, run with wait
				pid_t pid = fork();
				if(pid == 0){
					strcat(executeFile, func);
					char *args[]={executeFile,NULL};
					execvp(args[0],args);
				}
				else{
					waitpid(pid, &status, 0);
				}
			}
			}
			else{
				printf("Unable to find file!\n");// if no file was found on initial search, inform the user
			}
		}
	getCommand();//run input after finishing function.
	}
	
}	
