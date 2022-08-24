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
#include <chrono>       
#include <future>




using namespace std; 
using std::filesystem::current_path;
using namespace std::chrono;
namespace fs = std::filesystem;

// #define DIR_PATH = "/home/zornic/projects/grep_cpp"


 
std::vector<int>  grep_func(fs::path path_to_search, std::string search_str, std::string logfname, std::string txtfname)
{ 
    std::vector<int> res; 
    string search = search_str; 

    fs::path p = path_to_search; 

    int searched_files = 0, files_w_pattern = 0, patterns_number = 0; 

    // default file names 
    std::string def_log_filename = "grepex.log"; 
    std::string def_txt_filename = "grepex.txt"; 

      std::ofstream txt_file; 
      std::ofstream log_file;

    std::string log_file_name; 
    std::string text_file_name; 

    if(logfname == def_log_filename)
        {
            log_file_name = logfname;
            log_file.open(def_log_filename);     
        }
    else
        {
            log_file_name = logfname + ".log";
            log_file.open(log_file_name); 
        }

    if(txtfname == def_txt_filename)
        {
            text_file_name == txtfname;
            txt_file.open(def_txt_filename);
        }
    else
        {
        text_file_name = txtfname + ".txt";
        txt_file.open(text_file_name); 
        }

      //std::string log_file_name = logfname;
      //std::string txt_file_name = txtfname;

     
      //log_file.open(log_file_name); 
      //txt_file.open(txtfname); 
        
    
  
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


/*
std::packaged_task<std::vector<int>> task_thread()
{
    //std::packaged_task<std::vector(fs::path, std::string, std::string, std::string) task(grep_func); 
    //std::future<std::vector<int>> result = task.get_future(); 

    // std::thread task_td(std::move(task), )

}
*/ 


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
    auto start = high_resolution_clock::now();

    int searched_files; 
    int files_w_pattern; 
    int patterns_number; 
    int num_of_threads = 4; // default value for the number of threads 



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


    // word to search for 
    std::string search; 
    

    string given_exec = argv[0]; 
    string file_exec = "./grepex"; 

    // default file names 
    std::string def_log_name = "grepex.log"; 
    std::string def_txt_name = "grepex.txt"; 


    // user defined file names 
    std::string log_file_name;
    std::string text_file_name; 



     // current working directory
     fs::path cwd = fs::current_path();

     std::string directory_value; 

     

    
    

    if(argc % 2 == 1) // if ./grepex executed once, the following instructions will be prompted 
    {   
        display_help(); 
        return 1; 
    }

    if(argc > 1)
    {
        search = argv[1]; 
    }

    if (argc == 2)
    {    
        results = grep_func(cwd.string(), search, def_log_name, def_txt_name); 
        searched_files = results[0]; 
        files_w_pattern = results[1]; 
        patterns_number = results[2]; 
        display_results(searched_files, files_w_pattern, patterns_number); 
    }
    else if (argc == 4 && given_exec == file_exec)
    {   
        // ctpl::thread_pool p(num_of_threads); 
        
         
        flag1 = argv[2]; 

        if(flag1 == d_flag)
        {
            directory_value = argv[3];
            results = grep_func(directory_value, search, def_log_name, def_txt_name);
            searched_files = results[0]; 
            files_w_pattern = results[1]; 
            patterns_number = results[2]; 
            display_results(searched_files, files_w_pattern, patterns_number);
        }
        else if(flag1 == l_flag)
            {
                log_file_name = argv[3];
                results = grep_func(cwd.string(),search, log_file_name, def_txt_name); 
                searched_files = results[0]; 
                files_w_pattern = results[1]; 
                patterns_number = results[2]; 
                display_results(searched_files, files_w_pattern, patterns_number);

            }
        else if(flag1 == r_flag)
            {
                text_file_name = argv[3];
                results = grep_func(cwd.string(),search, def_log_name, text_file_name); 
                searched_files = results[0]; 
                files_w_pattern = results[1]; 
                patterns_number = results[2]; 
                display_results(searched_files, files_w_pattern, patterns_number);


            }
        else if(flag1 == t_flag) // I DON'T KNOW THIS YET 
            {



            }
        else
        {
            display_help();
            return 1; 

        }
        /*
        results = grep_func(directory_value, search, log_file_name); 
        searched_files = results[0]; 
        files_w_pattern = results[1]; 
        patterns_number = results[2]; 
        display_results(searched_files, files_w_pattern, patterns_number); 
        */ 
    }
  
    
   
   //grep_func("/home/zornic/projects/grep_cpp","karaalioglu"); 

     if (argc == 6)
     {
        flag1 = argv[2];
        flag2 = argv[4]; 
        if(flag1 == d_flag && flag2 == l_flag)
        {
            directory_value = argv[3];
            log_file_name = argv[5];
            results = grep_func(directory_value,search, log_file_name, def_txt_name);
            searched_files = results[0]; 
            files_w_pattern = results[1]; 
            patterns_number = results[2]; 
            display_results(searched_files, files_w_pattern, patterns_number);

        }
        else if(flag1 == l_flag && flag2 == r_flag)
        {
            log_file_name = argv[3]; 
            text_file_name = argv[5]; 
            results = grep_func(cwd.string(),search, log_file_name, text_file_name);
            searched_files = results[0]; 
            files_w_pattern = results[1]; 
            patterns_number = results[2]; 
            display_results(searched_files, files_w_pattern, patterns_number);

        }
        else if(flag1 == r_flag && flag2 == t_flag) // t flag not known yet 
        {
            text_file_name = argv[3]; 



        }
        
    }
    if(argc == 8)
    {   
        flag1 = argv[2];
        flag2 = argv[4];
        flag3 = argv[6];
        
        if(flag1 == d_flag && flag2 == l_flag && flag3 == r_flag)
        {
            directory_value = argv[3]; 
            log_file_name = argv[5];
            text_file_name = argv[7];
            results = grep_func(directory_value, search, log_file_name, text_file_name);
            searched_files = results[0]; 
            files_w_pattern = results[1]; 
            patterns_number = results[2]; 
            display_results(searched_files, files_w_pattern, patterns_number);

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
        
        if(flag1 == d_flag && flag2 == l_flag && flag3 == r_flag && flag4 == t_flag)
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

std::cout << "Result file: " << text_file_name << ".txt" << std::endl;
std::cout << "Log file: " <<  log_file_name << ".log" << std::endl; 
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);
std::cout << "Elapsed time: " << duration.count() << "[ms]" << endl;


}

// "/home/zornic/Desktop/test" // test directory 
 // "/home/zornic/projects/grep_cpp" // grep_directory 