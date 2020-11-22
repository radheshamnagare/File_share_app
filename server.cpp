using namespace std;
#include<iostream>
#include<cerrno>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include"error.h"

extern int errno;
class Server
{
     private :
       struct sockaddr_in addr;
       unsigned char *buffer[80];
     public :  
       int serv_fd,sock;
       size_t sz = 80;

     public :  
       Server()
       {
       	 errno = 0;
       }

       int connect(string port,string host)
       {
             
          if((serv_fd = socket(AF_INET,SOCK_STREAM,0))==-1)
            setIntrupt(errno);	     
          else
          {
          	 perror("[+] CONNECTING.. :");
          	 addr.sin_family = AF_INET;
          	 addr.sin_addr.s_addr = htonl(INADDR_ANY);
             addr.sin_port = htons(atoi(port.c_str()));
             if(bind(serv_fd,(struct sockaddr *)&addr,sizeof(addr)) == -1)
              setIntrupt(errno);	
             else
             {
              perror("[+] BINDING SUCCESSFULY:");	
              if(listen(serv_fd,1) == -1)
               setIntrupt(errno);
              else
              {
                perror("[+] LISTENING SUCCESSFULY:");	
                socklen_t len = sizeof(addr);
                
                if((sock = accept(serv_fd,(struct sockaddr *)&addr,&len)) == -1)
                 setIntrupt(errno);
                else
                 perror("[+] CONNECTION ACCEPTED:");   	
              }
             } 	
           } 
           
           if(isIntrupt() == 0)
            return sock;   

         return -1;    
       }

       int sendFile(int sock)
       {
       	 string filename;
         int fd ;
         size_t f_sz=0;
         ssize_t byte,b;
         
         cout<<"\nEnter the filepath :";
         cin>>filename;
         if(filename.length() <=0)
         	setIntrupt(errno);
         else if((fd = open(filename.c_str(),O_RDONLY)) == -1)
          setIntrupt(errno);
         else
         {
            do
            {
               memset(buffer,0,80);
               if((byte = read(fd,buffer,sz)) == -1)
               	{
               	  setIntrupt(errno);
                  break;
               	}
               else if((b=send(sock,buffer,byte,0)) ==-1)
               {
               	 setIntrupt(errno);
               	 break;
               }
               else if(byte!=b)
               {
               	 setIntrupt(EBBSN);
               	 break;
               }
               	
            }while(byte>0);
         }

         return isIntrupt();
       }

       int recvFile(int sock)
       {
         int fd;
         ssize_t byte,b;
         string file;
         cout<<"\nEnter the filename";
         cin>>file;
         if((fd = open(file.c_str(),O_WRONLY|O_CREAT,S_IRWXU)) == -1)
         	setIntrupt(errno);
         else 
         {
         	
         	do
         	{
         	  memset(buffer,0,80);
              if((byte = recv(sock,buffer,sz,0))== -1)
              {
              	setIntrupt(errno);
              	break;
              }
              else if(byte == 0)
                 break;
              else if((b=write(fd,buffer,byte)) == -1)
              {
              	setIntrupt(errno);
              	break;
              }
              else if(byte!=b)
              {
              	setIntrupt(EBBRV);
              	break;
              }
               
         	}while(byte >0);
         } 

       	 return isIntrupt();
       }
};

int main(int argc, char const *argv[])
{

 Server s; 	
 int conn,choise;
 int file;

 if(argc!=3)
  cout<<"use %s <port> <host>"<<argv[0]<<endl;
 else
 {
   conn = s.connect(argv[1],argv[2]);
   if(conn ==-1)
   	cout<<"ERROR :"<<getIntrupt();
   else
   {
      cout<<"Enter the choise :"<<endl;
      cout<<"\n1 - send file \n2- receving file\n3-exit"<<endl;
      cout<<"Enter the choise :";
      cin>>choise;

      switch(choise)
      {

      	case 1: file = s.sendFile(conn);
      	        if(file == -1)
      	        	cout<<"[-] ERROR :"<<getIntrupt()<<endl;
      	        else
      	        {
      	        	cout<<"[+] FILE SEND SUCCESSFULY"<<endl;
      	        	close(s.sock);
      	        }
      	        break;

        case 2: file = s.recvFile(conn);
                if(file == -1)
                 cout<<"[-] ERROR :"<<getIntrupt()<<endl;
                else
                {
                 cout<<"[+] FILE RECEVING SUCCESSFULY"<<endl;
                 close(s.sock);
                }
                break; 
        case 3: exit(0);        

        default :cout<<"Wrong choise entered "<<endl;         	        
      }
   }
 }

 
 return 0;
}