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
#include <vector>



using namespace std; 
using std::filesystem::current_path;
namespace fs = std::filesystem;

// #define DIR_PATH = "/home/zornic/projects/grep_cpp"



 
std::vector<int>  grep_func( fs::path path_to_search , std::string search_str)
{ 
    std::vector<int> res; 
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
                if (pos != string::npos)
                    {
                        files_w_pattern++; 
                        txt_file << entry.path(); 
                        txt_file << ":" << line_no << ":" << line << endl; 
                    }
                
                /*
                if(line_no > 200)
                    return res; 
                */
             }
           //  log_file << entry.path() << std::endl;

            searched_files++; 
       
        }
        txt_file.close(); 

    res.push_back(searched_files); 
    res.push_back(files_w_pattern); 
    res.push_back(patterns_number); 

return res; 

}




void display_help()
{
        cout << "Grepx help: Please insert with the following format\n";
        cout << "Usage: " << "./grepex " << " [search_string] [-d][directory] [-l][log file] " 
                                        " [r][result file] [-t][threads]\n"; 
}



void display_results(int s, int f, int p)
{
    std::cout << "Searched files: " << s << std::endl; 
    std::cout << "Files with pattern: " << f << std::endl; 
    std::cout << "Patterns_number: " << p << std::endl; 
    
}







int main(int argc, char* argv[])
{
    int searched_files; 
    int files_w_pattern; 
    int patterns_number; 

    std::vector<int> results; 

    // setting up the flags 
    std::string flag1;
    std::string flag2;
    std::string flag3;
    std::string flag4;
    std::string d_flag = "-d"; 
    std::string l_flag = "-l";
    std::string r_flag = "-r";
    std::string t_flag = "-t"; 


    

    string given_exec = argv[0]; 
    string file_exec = "./grepex"; 

     
    
    

    if(argc % 2 == 1) // if ./grepex executed once, the following instructions will be prompted 
    {   
        display_help(); 
        return 1; 
    }
    
    

    string search; 

    if (argc == 2)
    {   search = argv[1]; 
        fs::path cwd = fs::current_path();   
        results = grep_func(cwd, search); 
        searched_files = results[0]; 
        files_w_pattern = results[1]; 
        patterns_number = results[2]; 
        display_results(searched_files, files_w_pattern, patterns_number); 
    }
    else if (argc == 4 && given_exec == file_exec)
    {
        flag1 = argv[2]; 

        if(flag1 == d_flag)
            string directory = argv[3]; 
        else if(flag1 == l_flag)
            {

            }
        else if(flag1 == r_rflag)
            {

            }
        else if(flag1 == t_flag)
            {

            }
        else
        {
            display_help();
            return 1; 

        }



        results = grep_func(directory, argv[1]); 
        searched_files = results[0]; 
        files_w_pattern = results[1]; 
        patterns_number = results[2]; 
        display_results(searched_files, files_w_pattern, patterns_number); 
    }
  
    
   
   //grep_func("/home/zornic/projects/grep_cpp","karaalioglu"); 

     if (argc == 6)
     {
        flag1 = argv[2];
        flag2 = argv[4]; 
        if(flag1 == d_flag && flag2 == l_flag)
        {

        }
        else if(flag1 == l_flag && flag2 == r_flag)
        {


        }
        else if(flag1 == r_flag && flag2 == t_flag)
        {

        }
        
    }
    if(argc == 8)
    {   
        flag1 = argv[2];
        flag2 = argv[4];
        flag3 = argv[6];
        
        if(flag1 == d_flag && flag2 == l_flag && flag3 == r_flag)
        {

        }
        else if(flag1 == l_flag && flag2 == r_flag && flag3 == t_flag)
        {
            

        }
        else if(flag1 == d_flag && flag2 == r_flag && flag3 == t_flag)     
        {


        }
        else
        {
            display_help();
            return 1; 
        }

    }
    
    if (argc == 10)
    {
        flag1 = argv[2];
        flag2 = argv[4];
        flag3 = argv[6];
        flag4 = argv[8];
        
        if(flag1 == d_flag && flag2 == l_flag && flag3 == r_flag && t_flag)
        {




        }
        else 
        {
            display_help();
            return 1; 
        }














    }


  

     
    
    // if (argc == 8 && argv[2] == "-d" && argv[4] == "-l" && argv[6] == "-r" )
    //     { 
 

    //     }
   
 // tfs::path curent_p = fs::current_path(); 
 //grep_func("/home/zornic/Desktop/test", "seyit"); 
//grep_func("/home/zornic/projects/grep_cpp", "karaalioglu"); 


//grep_func("/home/zornic/projects/grep_cpp", "seyit"); 




//grep_func(argv[3], argv[1]); 




}

// "/home/zornic/Desktop/test" // test directory 
 // "/home/zornic/projects/grep_cpp" // grep_directory 