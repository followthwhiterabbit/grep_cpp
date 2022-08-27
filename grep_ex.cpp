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
#include <map>
#include <iterator>
#include <algorithm>
#include <thread> 



using namespace std; 
using std::filesystem::current_path;
using namespace std::chrono;
namespace fs = std::filesystem;

// #define DIR_PATH = "/home/zornic/projects/grep_cpp"

bool compare_dir(std::pair<std::string, int>&a,
                 std::pair<std::string, int>&b)
{
    return a.second > b.second; 
}

std::vector<std::pair<std::string, int>> sort_func(std::map<std::string, int>& M)
{
    
    std::vector<pair<string, int>> temp;


    for(auto &it : M)
        temp.push_back(it); 


    sort(temp.begin(), temp.end(), compare_dir); 


    return temp; 

}
 
void 
grep_func(fs::path path_to_search, std::string search_str, std::string logfname, std::string txtfname, std::vector<int> &results)
{ 
    std::vector<std::pair<std::string, int>> sorted; 
    std::vector<std::pair<std::string, int>>::iterator sortitr; 
    std::map<int, int>::iterator itr;
    std::vector<int> res; 
    std::string search = search_str; 

    fs::path p = path_to_search; 

    size_t searched_files = 0, files_w_pattern = 0, patterns_number = 0; 

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
        
    std::map<string, int> m;
    
    //static int word_count = 0; 
    
    for (const auto  & entry : fs::recursive_directory_iterator(p))
        {   

            size_t line_no = 0; 
            size_t word_count = 0; 
             string line; 
             ifstream infile(entry.path()); 
             std::string curpath = entry.path(); 
              //m[curpath]++;
             //std::map<string, int> m; 
             
            //int path_counter = 0; 
             while(getline(infile, line))
             {

                ++line_no; 
                auto pos = line.find(search); 
                if (pos != string::npos)        // here we can now print the directories by returning the sorted map 
                    {                           // but i dont have time for that 
                        //word_count++; 
                        files_w_pattern++; 
                        txt_file << entry.path(); 
                        txt_file << ":" << line_no << ":" << line << std::endl; 
                        log_file << std::this_thread::get_id() << ": " << entry.path() << std::endl; 
                          m[curpath]++; 
                    }
                   // std::cout << word_count; 
                
                /*
                if(line_no > 200)
                    return res; 
                */
                
                 //m[curpath]++; 
                 
             }
           //  log_file << entry.path() << std::endl;

            searched_files++; 
            sorted = sort_func(m);
            //txt_file << entry.path(); 

        }

        //sorted = sort_func(m); 

        // txt_file << el.first << std::endl; 


        /*
        
          for(auto sortitr = sorted.begin(); sortitr != sorted.end(); sortitr++)
            {
                std::cout << sortitr->first << " " << sortitr->second << endl; 
                txt_file << sortitr->first << std::endl;             

            }
         
         */ 

        txt_file.close(); 
   
        
         for(auto itr = m.begin(); itr != m.end(); ++itr)
            {
                patterns_number += itr->second; 
            }
          

        files_w_pattern = m.size();

    results.push_back(searched_files); 
    results.push_back(files_w_pattern); 
    results.push_back(patterns_number); 

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
        std::cout << "Grepx help: Please insert with the following format\n";
        std::cout << "Usage: " << "./grepex " << " [search_string] [-d][directory] [-l][log file] " 
                                        " [r][result file] [-t][threads]\n"; 
}


int main(int argc, char* argv[])
{
    auto start = high_resolution_clock::now();

    size_t searched_files; 
    size_t files_w_pattern; 
    size_t patterns_number; 
    size_t num_of_threads = 4; // default value for the number of threads 



    std::vector<int> results; 
    std::vector<std::thread> threads; 

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
    

    std::string given_exec = argv[0]; 
    std::string file_exec = "./grepex"; 

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
        for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, cwd.string(), std::ref(search), std::ref(def_log_name),std::ref(text_file_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
    }
    else if (argc == 4 && given_exec == file_exec)
    {   
        // ctpl::thread_pool p(num_of_threads); 
        
         
        flag1 = argv[2]; 

        if(flag1 == d_flag)
        {
            directory_value = argv[3];
            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, directory_value, std::ref(search), std::ref(def_log_name),std::ref(def_txt_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

            
        }
        else if(flag1 == l_flag)
            {
                log_file_name = argv[3];
               for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, cwd.string(), std::ref(search), std::ref(log_file_name),std::ref(def_txt_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }


            }
        else if(flag1 == r_flag)
            {
                text_file_name = argv[3];
                for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, cwd.string(), std::ref(search), std::ref(def_log_name),std::ref(text_file_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
            


            }
        else if(flag1 == t_flag) // I DON'T KNOW THIS YET 
            {
  
                num_of_threads = atoi(argv[3]); 
                for( size_t i = 0; i < num_of_threads; i++) // cwd.string() is an r-value already,
                    {                                       // but we need to send the others as std::ref 
                        threads.emplace_back(grep_func, cwd.string(), std::ref(search), std::ref(def_log_name),std::ref(def_txt_name), std::ref(results)); 
                    }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
    
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
            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, directory_value, std::ref(search), std::ref(log_file_name),std::ref(def_txt_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
            

        }
        else if(flag1 == l_flag && flag2 == r_flag)
        {
            log_file_name = argv[3]; 
            text_file_name = argv[5]; 
            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, cwd.string(), std::ref(search), std::ref(log_file_name),std::ref(text_file_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

        }
        else if(flag1 == r_flag && flag2 == t_flag) // t flag not known yet 
        {
            text_file_name = argv[3]; 
            num_of_threads = atoi(argv[5]); 

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, cwd.string(), std::ref(search), std::ref(def_log_name),std::ref(text_file_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
        }
        else if(flag1 == d_flag && flag2 == r_flag)
        {
            directory_value = argv[3]; 
            text_file_name = argv[5];
            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, directory_value, std::ref(search), std::ref(def_log_name),std::ref(text_file_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

            

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
            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, directory_value, std::ref(search), std::ref(log_file_name),std::ref(text_file_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

        }
        else if(flag1 == l_flag && flag2 == r_flag && flag3 == t_flag)
        {
            log_file_name = argv[3]; 
            text_file_name = argv[5];
            num_of_threads = atoi(argv[7]);

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, cwd.string(), std::ref(search), std::ref(log_file_name),std::ref(text_file_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
            
        }
        else if(flag1 == d_flag && flag2 == r_flag && flag3 == t_flag)     
        {
            directory_value = argv[3];
            text_file_name = argv[5];
            num_of_threads = atoi(argv[7]); 

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, directory_value, std::ref(search), std::ref(def_log_name),std::ref(text_file_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }
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
            directory_value = argv[3];
            log_file_name = argv[5];
            text_file_name = argv[7]; 
            num_of_threads = atoi(argv[9]);

            for( size_t i = 0; i < num_of_threads; i++)
                {                                       
                    threads.emplace_back(grep_func, directory_value, std::ref(search), std::ref(log_file_name),std::ref(text_file_name), std::ref(results)); 
                }

                for(auto & thread : threads)
                    {
                        thread.join(); 
                    }

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
std::cout << "Searched files: " << results.at(0) << std::endl; 
std::cout << "Files with pattern: " << results.at(1) << std::endl; 
std::cout << "Patterns_number: " << results.at(2) << std::endl; 
std::cout << "Result file: " << text_file_name << ".txt" << std::endl;
std::cout << "Log file: " <<  log_file_name << ".log" << std::endl; 
std::cout << "Used threads: " << num_of_threads << std::endl; 
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);
std::cout << "Elapsed time: " << duration.count() << "[ms]" << std::endl;

}

// "/home/zornic/Desktop/test" // test directory 
 // "/home/zornic/projects/grep_cpp" // grep_directory 