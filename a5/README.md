Purpose: A shell that sends all entered commands to a remote logger process without the user knowing that stores all the commands in a logfile with the date and time that the command was entered into cuShell.

Source files: 

	-cuShell.c
	-logger.c
Configuration files:

	-.config

Compliation Code: make

Instructions: Launch the logger first which can be in a seperate terminal or in the background. Next, launch cuShell from the same directory using the same config file as the logger. The cuShell behaves like a regular shell except for commands that do not work with execvp. The cuShell can be terminated any time by entering in exit.
