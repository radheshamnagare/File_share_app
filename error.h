#include<stdio.h>
#include<string.h>
#include<errno.h>

#define EBBSN  132 // bad byte send
#define EBBRV  133 // bad byte receive
unsigned int error = 0;
char buff[512];
extern int errno;

void _resetIntrupt(){
	error = 0;
}
char * error_str(unsigned int error){

	switch(error)
  {
     
        case EBBSN : strcpy(buff,"BAD BYTE SEND\0"); 
                      break;
        case EBBRV : strcpy(buff,"BAD BYTE RECEIVE\0");
                      break;                                                                
         default :   strcpy(buff,strerror(error));
                      break;                         
	}
	_resetIntrupt();
  return buff;	
}
int isIntrupt(){
  if(error>0)
	return -1;
return 0;
}
void setIntrupt(unsigned int err){
  error = err;
}
char * getIntrupt(){
	return (error_str(error));
}

int generateFile(int err){
  FILE *fp;
  char c[512];
  fp = fopen("error.txt","w");
  if(fp == NULL)
    setIntrupt(errno);
  else
  {
      strcpy(c,error_str(err));
      for(int i=0;c[i]!='\0';i++)
        fputc(c[i],fp);
  }

  return isIntrupt();
}
