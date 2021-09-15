#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <assert.h>
#include <thread>
#include <chrono>
#include <sstream>

char mess[100];
char func[100];
char thredz[100];
int linez;
int des_size = 0;


using namespace std;

//char mess[100];



void sleepThread()
{
    this_thread::sleep_for(chrono::seconds(1));
}


string tp[50];
char L[10];

void Level(char level[50], char msg[100])
{
    
    strcpy(mess, msg);   
   

    if(strcmp(level,"error") == 0)
    {
        
        Logger::Error(msg);
    }
    else if(strcmp(level,"debug") == 0)
    {
        Logger::Debug(msg);
    }
    else if(strcmp(level,"info") == 0)
    {
        Logger::Info(msg);
    }

}

void Log_Here(char* functioname, thread::id id, int lin)
{
    
    

    cout<<"Enter Particular Log Level"<<endl;
    char ll[100];
    cin>> ll;   

    int flag;
    char message[100];

    cout<<"Enter the Message to be printed:"<<endl;
    cin>> message;

    if(strcmp(L,"error") == 0)
    {
        flag = 1;

        if(strcmp(ll, "error") != 0)
        {
            
        }

        else
        {
            Level(ll, message);
        }

        
    } 

    if(strcmp(L,"info") == 0)
    {

        Level(ll, message);
    } 

    if(strcmp(L,"debug") == 0)
    {
        flag = 2;

          if(strcmp(ll, "info") == 0)
        {
            
        }

        else
        {
            Level(ll, message);
        }
    } 

   cout<<id;
  // id.join();
   cout<<" : "<<functioname;
   cout<<" : "<<lin;
   cout<<" \""<<mess<<"\"";
}

int check_log_file_size()
{
    ifstream IN_file("log.txt", ios::binary);
    IN_file.seekg(0,ios::end);
    int file_size = IN_file.tellg();
    //cout<<"\n";
    //cout<<"SIZE: "<<file_size<<" Bytes";
    return file_size;
}

void rollover()
{
   
   int curr_size = check_log_file_size();
   if (curr_size >= des_size)
   {
       Logger::CloseFileOutput();
       cout<<" MAX SIZE REACHED -> NO OUTPUT IN LOGFILE";
   }
}

void trial()
{
    thread thread1(sleepThread); 
    thread::id t1_id = thread1.get_id();  
    strcpy(func, __func__);
    thread1.join();
    linez = __LINE__;
    Log_Here(func, t1_id, linez);
    rollover();
    
}



int main()
{

   Logger::EnableFileOutput();
   fstream newfile;
   char log_level[50]; 
   
   



   newfile.open("config.txt",ios::in); //open a file to perform read operation using file object
   if (newfile.is_open())
   { //checking whether the file is open
      
      for(int i=0;i<50;i++)
      {
          newfile >> tp[i];
      }
      newfile.close(); //close the file object.
   }

   for(int i=0;i<50;i++)
   {
       if(tp[i] == "Logging_level:")
       {
           cout<<tp[i]<<" "<<tp[i+1]<<endl;

           strcpy(L, tp[i+1].c_str());

                 
       }

       if(tp[i] == "Log_File_Count:")
       {
           cout<<tp[i]<<" "<<tp[i+1]<<endl;
       }

       if(tp[i] == "File_Size_(mb):")
       {
           cout<<tp[i]<<" "<<tp[i+1]<<endl;
           stringstream file_size(tp[i+1]);
           int des_size_mb = 0;
           file_size>>des_size_mb; 
           des_size = des_size_mb*1000000;
       }

    }

    
    
    trial();

   // check_log_file_size();
    

   // Level(L,message);

    
}