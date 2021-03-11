
what i want to do ?
 now , we shares files different number of ways like as 
 - using pysical drives : we copy the file on drives and paste in destination machine.
 
 - if it is possible we can share file using GMAIL also (here i'm not considering any domain specific)
 
 - we can stores files in could and we simply share the links of the files to unother user. 
 
 or other some ways we can share files like bluetooth.
 so i want to shares file using simplest way without westing any extra memory space .
 -------------------------------------------------------------------------------------------------------------------------------------------------------
what is problem we face ?
 
 *pysical drives sharing : 
  
  if we want copy some files one source machine to unother machine then we do copy files from source machine and then after we pysicaly connects the drives to 
  destination machine and paste the files it but we can understand here there is wastage of time to copy files from source and again paste operation we required 
  another time for destination machine. 
  
  another point is we required space/memory in drives for perticular file copy or paste operation that's a disadvantages of it.if we want to copy arbitory large
  file so that's we required that much drives/memory .
  
  *GMAIL sharing :
     we also shares files using from specific domain that file actualy stores in server then destination user can access these files. here we can see this process 
     is costly and some sort of file is supporting that domain and also restrict to shares long size files.
     
 *Cloud sharing :
     we can stores files on cloud and then other user can access that files. here we can understand the copies of that file exists on server that's we needs some 
     space on cloud also that is costly .that is good if we use as your hard drive and other can also access files easily .
     but , if we want to shares local hard drives file then all of ways costly and have some restictions.
     
     so what can we do?
       one of way we know is using peer to peer bluetooth but bluetooth restrict some area range .
       so unother best way that i did : we can shares file using sockets .
       
------------------------------------------------------------------------------------------------------------------------------------------------------------ 
       
 what i did ?
 
  i just connect to machine using socket c so we need just ip address and port number to connect two machine .also i used TCP/ip protocol to share file, reasone
  is TCP is rellable and that's guarantee to shares file.
  also just use minimum buffer 256 bytes to perform opetation receving file or sending file ,the resone is i want run the application very less memory constraint
  but there is not restriction how much long file or what file type so we can shares files with different size and types.
  also i handle the error also during if any error occer we can easily find it.that's all abouts.
  
  
  support : linux operating system because i strictly used linux system calls
   
     
     
  
  
  
  
