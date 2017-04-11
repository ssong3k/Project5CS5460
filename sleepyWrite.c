/**
* @file   testebbchar.c
* @author Derek Molloy
* @date   7 April 2015
* @version 0.1
* @brief  A Linux user space program that communicates with the ebbchar.c LKM. It passes a
* string to the LKM and reads the response from the LKM. For this example to work the device
* must be called /dev/ebbchar.
* @see http://www.derekmolloy.ie/ for a full description and follow-up descriptions.
*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
 
#define BUFFER_LENGTH 256               ///< The buffer length (crude but fine)
static char receive[BUFFER_LENGTH];     ///< The receive buffer from the LKM
static char bytes[4];

char* changeToChar(int a) {
  bytes[3] = (a >> 24) & 0xFF;
  bytes[2] = (a >> 16) & 0xFF;
  bytes[1] = (a >> 8) & 0xFF;
  bytes[0] = a & 0xFF;
  printf("%d\n", a);
  return bytes;
}

int main(){
   int ret, fd;
   char stringToSend[BUFFER_LENGTH];
   printf("Starting device test code example...\n");
   fd = open("/dev/sleepy0", O_RDWR);             // Open the device with read/write access
   if (fd < 0){
      perror("Failed to open the device...");
      return errno;
   }
   printf("Type in a short string to send to the kernel module:\n");
   scanf("%[^\n]%*c", stringToSend);                // Read in a string (with spaces)
   printf("Writing message to the device [%s].\n", stringToSend);
   int number = atoi(stringToSend);
   changeToChar(number);
   printf("%d, %d, %d, %d\n", bytes[0], bytes[1], bytes[2], bytes[3]);
   ret = write(fd, bytes, sizeof(int)); // Send the string to the LKM
   if (ret < 0){
      perror("Failed to write the message to the device.");
      return errno;
   }
 
   /*printf("Press ENTER to read back from the device...\n");
   getchar();
 
   printf("Reading from the device...\n");
   ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM
   if (ret < 0){
      perror("Failed to read the message from the device.");
      return errno;
   }
   printf("The received message is: [%s]\n", receive);*/
   printf("End of the program\n");
   return 0;
}


