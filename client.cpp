/*requied header files*/
using namespace std;
#include <iostream>
#include<cerrno>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include"error.h"
#include<netdb.h>


extern int errno;
unsigned char *buffer[80];
size_t sz = 80;
ssize_t byte,b;

int rcvFile(int sock,string filename)
{
  int fd;
   
   if((fd = open(filename.c_str(),O_WRONLY | O_CREAT,S_IRWXU)) ==-1)
      setIntrupt(errno);
   else
   {
      do
      {
           memset(buffer,0,sz); 
           if((byte = recv(sock,buffer,sz,0)) == -1)
           {
            setIntrupt(errno);
            break;
           }
           else if(byte == 0)
            break;
           else if((b = write(fd,buffer,byte)) ==-1)
           {
             setIntrupt(errno);
             break;
           }
           else if(byte!=b)
           {
             setIntrupt(EBBRV);
             break;
           }
      }while(byte>0);
   }
}
int sendFile(int sock,string filename)
{
  int fd;

  if((fd = open(filename.c_str(),O_RDONLY)) == -1)
      setIntrupt(errno);
  else
  {
      do
      {
         memset(buffer,0,80);   
         if((byte = read(fd,buffer,sz))== -1)
         {
            setIntrupt(errno);
         }
         else if((b = send(sock,buffer,byte,0)) ==-1)
         {
            setIntrupt(errno);
         }
         else if(b!=byte)
         {
            setIntrupt(EBBSN);
            break;
         }

      }while(byte > 0);
  }

 return isIntrupt(); 
}
int main(int argc, char const **argv)
{
	/*declaration of variabel*/
	struct sockaddr_in addr;
	struct hostent *host;
	int sock,choise,file;
      string filename;
      
	system("clear");

       
       if(argc!=3)//checking command line argument
       {
       	printf("use %s <port> <host>",argv[0]);
       	exit(0);
       }
      
       /*creating socket*/
      if((sock = socket(AF_INET,SOCK_STREAM,0))==-1)
            perror("[-] ERROR :");
      else
      {
       perror("[+] CONNECTING:");
       addr.sin_family = AF_INET;
       addr.sin_port = htons(atoi(argv[1]));//port no
       host = gethostbyname(argv[2]);//hostname in string formate
      /*checking host is valid or not*/
       if(host == NULL)
            perror("[-]ERROR");
       else
       {
            if(connect(sock,(struct sockaddr *)&addr,sizeof(addr))==-1)
             perror("[-]ERROR:");
            else
            {
                 perror("[+]CONNECTION ACCEPT:");
                 
                
                         cout<<"\n1-send file\n2-receive file\n3 exit"<<endl;
                         cout<<"Enter the choise :";
                         cin>>choise;

                         switch(choise)
                         {
                             case 1: cout<<"\nEnter the file :";
                                     cin>>filename;   
                                     file = sendFile(sock,filename);
                                     if(file == -1)
                                          cout<<"[-] ERROR:"<<getIntrupt();
                                     else
                                     {
                                         cout<<"[+]FILE SEND SUCCESSFULY"<<endl; 
                                         close(sock);
                                     }
                                     break;

                              case 2: cout<<"\nEnter the file :";
                                      cin>>filename;
                                      file = rcvFile(sock,filename);
                                      if(file == -1)
                                       cout<<"[-] ERROR :"<<getIntrupt();
                                      else
                                      {
                                          cout<<"[+]FILE RECEIVE SUCCESSFULY"<<endl;
                                          close(sock);
                                      }      
                                      break;   
                               case 3: cout<<"[+]EXITED"<<endl;
                                      break;
                               default : cout<<"[-] WRONG CHOISE ENTERED"<<endl;        
                         }
                    
            }  
      
       }     
      }

return 0;
}