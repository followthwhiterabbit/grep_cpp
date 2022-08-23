#include <iostream>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <dirent.h>


using namespace std; 
namespace fs = std::filesystem;

// #define DIR_PATH = "/home/zornic/projects/grep_cpp"



 
void text_file_set(std::string path, std::string search)
{ 
     std::ofstream txt_file; 
      txt_file.open("grep_ex.txt"); 
  
  
    for (const auto  & entry : fs::recursive_directory_iterator(path))
        {   

            int line_no = 0; 
             string line; 
             ifstream infile(entry.path()); 

             while(getline(infile, line))
             {

                ++line_no; 
                auto pos = line.find(search); 
                if(pos != string::npos)
                    {
                        txt_file << entry.path(); 
                        txt_file << ":" << line_no << ":" << line << endl; 
                    }

             }
           //  log_file << entry.path() << std::endl;

        }
        txt_file.close(); 

}





int main(int argc, char* argv[])
{
    /*

    if(argc % 2 == 1) // if ./grepex executed once, the following instructions will be prompted 
    {   
        cout << "Grepx help: Please insert with the following format\n";
        cout << "Usage: " << argv[0] << " [search_string] [-d][directory] [-l][log file] " 
                                        "[r][result file] [-t][threads]\n"; 
        return 1; 
    }
 
    string search;         
    if(argc == 2)
    {
         search = argv[1];
        ofstream log_file; 
        ofstream result_file; 

        string log_filename = argv[0];
        log_filename += ".log"; 

        string result_filename = argv[0]; 
        result_filename += ".txt"; 

        log_file.open(log_filename);
        result_file.open(result_filename); 
    }

    if(argc == 4 && argv[2] == "-d")
    {
         search = argv[1]; 
        string directory = argv[3]; 

        ofstream log_file; 
        ofstream result_file; 

        string log_filename = argv[0];
        log_filename += ".log"; 

        string result_filename = argv[0]; 
        result_filename += ".txt"; 

        log_file.open(log_filename);
        result_file.open(result_filename); 

    }

    if(argc == 6 && argv[2] == "-d" && argv[4] == "-l")
        {
         search = argv[1]; 
        string directory = argv[3]; 

        ofstream log_file; 
        ofstream result_file; 

        string log_filename = argv[5];
        log_filename += ".log"; 

        string result_filename = argv[0]; 
        result_filename += ".txt"; 

         log_file.open(log_filename);
        result_file.open(result_filename); 

        }
    
    if(argc == 8 && argv[2] == "-d" && argv[4] == "-l" && argv[6] == "-r" )
        {
         search = argv[1]; 
        string directory = argv[3]; 

        ofstream log_file; 
        ofstream result_file; 

        string log_filename = argv[5];
        log_filename += ".log"; 

        string result_filename = argv[7]; 
        result_filename += ".txt"; 

         log_file.open(log_filename);
        result_file.open(result_filename); 
        }
    

*/ 




 /*

    
    ifstream infile(argv[2]); 
    while(!infile)
    {
        cout << "Cannot open " << argv[2] << '\n';  
        return 1; 
    }

        ofstream log_file; 
        log_file.open("grep_ex.log"); 


    int lineno = 0;
    string line; 
    while(getline(infile, line))
    {
        ++lineno; 
        auto pos = line.find(argv[1]); 
        if (pos != string::npos)
            {
                log_file << lineno << ":" << line <<'\n'; 
            }
       
    }
    
         log_file.close();
            

   */   
   


/*
   
    std::ofstream log_file; 
    log_file.open("grep_ex.log"); 



   std::string path = "/home/zornic/projects/grep_cpp";
    for (const auto & entry : fs::recursive_directory_iterator(path))
        {    
            log_file << entry.path() << std::endl;

        }

        log_file.close(); 

*/ 



 text_file_set("/home/zornic/Desktop/test", "seyit"); 





}