#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void cleanup();

#define MAX_BUF  64

FILE *logFile;
int myListenSocket, clientSocket;


int main()
{
  FILE *configFile;
  char logName[MAX_BUF];
  char ip[MAX_BUF];
  int  port;
  char str[MAX_BUF];
  struct sockaddr_in myAddr, clientAddr;
  int i, addrSize, bytesRcv;
  char buffer[MAX_BUF];


//installs a signal handler to listen for an inturupt signal
  signal(SIGINT, cleanup);

/* get IP address and port number from config file */
  if (!(configFile=fopen(".config","r"))) {
    printf("cannot read config file...\n");
    exit(1);
  }
  fscanf(configFile, "%s", ip);
  fscanf(configFile, "%d", &port);
  fclose(configFile);

/* create name of log file;  format is
    username followed by timestamp
    usernameYYYYMMDDHHMM.log */
  strcpy(logName, getenv("USER"));
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(str, "%4d%02d%02d%02d%02d",
          tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
          tm.tm_hour, tm.tm_min);
  strcat(logName, str);
  strcat(logName, ".log");

/* open log file for writing */
  if (!(logFile=fopen(logName,"w"))) {
    printf("cannot write to file...\n");
    exit(1);
  }


/* set up connection, receive commands typed
   into cuShell process, and log them to the
   logFile */

//creates the socket
  myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  if(myListenSocket < 0){
    printf("Could not open socket!\n");
    exit(-1);
  }

 // sets up the server address
  memset(&myAddr, 0, sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myAddr.sin_port = htons((unsigned short) port);

 //binds to the listen socket
  i = bind(myListenSocket, (struct sockaddr *) &myAddr, sizeof(myAddr));

  if (i < 0){
    printf("Couldn't bind socket\n");
    exit(-1);
  }

//listens on the socket
  i = listen(myListenSocket, 0);
  if (i < 0){
    printf("Couldn't listen!\n");
    exit(-1);
  }


//the server waits until a client connects to the server
  addrSize = sizeof(clientAddr);

  clientSocket = accept(myListenSocket,
			(struct sockaddr *) &clientAddr,
			&addrSize);

  if (clientSocket < 0){
    printf("Couldn't accept the connection!\n");
    exit(-1);
  }

//reads the message sent by the client then outputs it to the logfile
  while(1){
    bytesRcv = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesRcv] = 0;
    //fetches the current time
    t = time(NULL);
    tm = *localtime(&t);
    //prints the current time and command entered into the logfile
    fprintf(logFile, "%4d-%02d-%02d-%02d:%02d:%02d: %s\n",
          tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
	    tm.tm_hour, tm.tm_min, tm.tm_sec, buffer);
    if(strcmp(buffer, "exit") == 0){
      cleanup();
    }
  }
  return 0;
}

/*
  Function:  cleanup
   Purpose:  To close the sockets and logfile and exit the logger
*/

void cleanup(){

  close(clientSocket);
  close(myListenSocket);
  fclose(logFile);
  exit(1);

}
