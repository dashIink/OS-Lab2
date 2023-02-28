Manual:
This project consists of a command line interface that allows interaction between the user and the operating system, also known as a simple unix shell. 
This shell provides basic commands for navigation, running programs, and file manipulation. 
The shell can be utilized by entering a command as well as any necessary parameters. 
This will tell the shell to execute the command and display the output.


Commands: 
cd <directory> : Change from current directory to argument passed
clr:  Will clear the screen
dir <directory> : Lists the contents of directory in argument 
environ: Displays all environment strings
echo <comment> : Displays the passed argument on the screen
help: Displays the user manual on the screen
pause: Pause shell until interrupt key is pressed 
quit: Exits the shell


Environment: 
The shells environment consists of the variables that programs can utilize when the shell is being run. 
These variables define the environment and are either set by the system, the user, or the shell. 
Environment variables are commonly used to manipulate the behaviour of the shell or to store information from programs within the shell and can be displayed or updated using the command “environ”. 
The list of environment variables is long and varied but the major concepts and variables set by the shell can be considered below.

Home: This variable speicifies the current users home directory.
Term: Stores the type and name of the terminal that the user is currently utilizing.
Path: Tells the system which directories to search for programs when a user enters a command into the interface.
Using these, as well as other variables, allows the user to easily manipulate their directories and store information on their current working directory or shell.


I/O Redirection:
In a standard shell command, input usually comes from a keyboard or other input device, and output tends to be sent to either a display or other output device. 
I/O redirection allows us to manipulate the output and input sources and change how programs are run in shell. 
The two main types of I/O redirection are input and output redirection. 
The first type, input redirection, allows us to change the source of a commands input. 
This means rather than using a keyboard for input, you can use a file as a souce instead. 
Placeing a “<” can be used to accomplish this redirection and an example is provided below. 
Output redirection works similarly, however, rather than changing the source of the input, you are now controlling the destination of the output. 
This means rather than the output being displayed to the screen, you can use a “>” to instead redirect the output to either another file or command.

Input Redirection: “program” < input.txt
Output Redirection: “program” > output.txt
In the first example, the “program” application will be accepting the data inside the input.txt file as its input rather than from the user. Furthemore, in the second example, rather than display the output to the screen, the “program” will send its output to the output.txt file after executing. Other utilizations of I/O redirection include using both at the same time, aswell as appending outputs to a file rather than overwriting them. In the first example, input will be taken from the input.txt file and used in the “program”, then output of the “program” will then be sent to the output.txt file. In the second example, if the output.txt file has already been created, rather than deleting it and storing the new output (which would be done if only one “>” was used), it will instead append the new output to whatever data already existed within the file.
Input and Output Redirection: “program” < input.txt > output.txt
Appending Output:  “program” >> output.txt


Background Execution
During usual command execution, the user enters a command, the shell waits for the command to finish, and then the shell returns control back to the user. 
Background execution is a workaround to this which allows us to run a command in the background instead of the foreground, thus allowing us to maintain access to the shell prompt. 
This is accomplished by adding an “&” to the end of of your command line which tells the shell to run this command in the background. 
Once the user hits enter the program will be run in the background and they will immediately be shown the command line prompt again so they can continue to execute other programs. 
This strategy of background execution is especially useful for long running programs or commands that do not require much input from the user.
