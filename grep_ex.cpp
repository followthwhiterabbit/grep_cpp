#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sstream>
#include <dirent.h>
#include <unordered_map>



using namespace std; 
using std::filesystem::current_path;
namespace fs = std::filesystem;

// #define DIR_PATH = "/home/zornic/projects/grep_cpp"



 
void  text_file_set( fs::path path_to_search , std::string search_str)
{ 
    
    string search = search_str; 

    fs::path p = path_to_search; 

    int searched_files = 0, files_w_pattern = 0, patterns_number = 0; 


     std::ofstream txt_file; 
      txt_file.open("grep_ex.txt"); 
  
  
    for (const auto  & entry : fs::recursive_directory_iterator(p))
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
                        files_w_pattern++; 
                        txt_file << entry.path(); 
                        txt_file << ":" << line_no << ":" << line << endl; 
                    }
                if(line_no > 100)
                    return; 

             }
           //  log_file << entry.path() << std::endl;

            searched_files++; 
       
        }
          txt_file << searched_files << " " << files_w_pattern;
        txt_file.close(); 


}







int main(int argc, char* argv[])
{
    
    


    // if(argc % 2 == 1) // if ./grepex executed once, the following instructions will be prompted 
    // {   
    //     cout << "Grepx help: Please insert with the following format\n";
    //     cout << "Usage: " << argv[0] << " [search_string] [-d][directory] [-l][log file] " 
    //                                     " [r][result file] [-t][threads]\n"; 
    //     return 1; 
    // }
    

     

    // if(argc == 2)
    // {
    //    text_file_set(fs::current_path(), argv[1]); 
    // } 
    


    //   if (argc == 4 && argv[2] == "-d")
    //  {
    //     string directory = argv[3]; 

     
  
    //       text_file_set(directory, argv[1]); 
    //  }


    // if(argc == 6 && argv[2] == "-d" && argv[4] == "-l")
    // {
  

    // }
    
    // if (argc == 8 && argv[2] == "-d" && argv[4] == "-l" && argv[6] == "-r" )
    //     { 
 

    //     }
   
 // tfs::path curent_p = fs::current_path(); 
 //text_file_set("/home/zornic/Desktop/test", "seyit"); 
//text_file_set("/home/zornic/projects/grep_cpp", "karaalioglu"); 


//text_file_set("/home/zornic/projects/grep_cpp", "seyit"); 


//char *cwd = get_current_dir_name();




}

// "/home/zornic/Desktop/test" // test directory 
 // "/home/zornic/projects/grep_cpp" // grep_directory 