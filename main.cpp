#include <iostream>
#include <unistd.h> //for chdir
#include <string.h>
#include <string>
#include <vector>
#include <sys/wait.h>     //for foreground
#include <linux/limits.h> //for path max
#define _OPEN_SYS         // for foreground
#include <errno.h>        //ask

// declaring our header file
#include "header.hpp"
using namespace std;

int main()
{
    // storing the home path for pwd case 1
    char pwd[PATH_MAX];
    char home_const[PATH_MAX];
    bool is_background = false;
    if (getcwd(home_const, sizeof(pwd)) == NULL)
    {
        perror("No such directory exists"); // ask someone how to handle with perror, what to do in perror.h?
    }
    char *home = home_const;
    string home_str = home; // path till our project
    int len_home_path = home_str.size();

    while (true)
    {
        int HOST_NAME_MAX = 100;
        char hostname[HOST_NAME_MAX];
        char name[NAME_MAX];
        string user_input;
        vector<vector<string>> multiple_command;

        int host_no = gethostname(hostname, sizeof(hostname));
        int name_no = getlogin_r(name, sizeof(name));
        if (name_no == -1)
        {
            printf("Not able to fetch the name");
            return 0;
        }
        if (host_no == -1)
        {
            // perror(errno);
            printf("Not able to fetch hostname"); // is this line fine?
            return 0;                             // have to change?
        }
        else
        {
            cout << name << "@" << hostname << ":~";

            getcwd(pwd, sizeof(pwd));
            char *cwd = pwd;
            string cwd_str = cwd;

            if (home != cwd)
            {
                const char *cstr = cwd_str.substr(len_home_path).c_str();
                char *cwd_substr = (char *)cstr;

                cout << cwd_str.substr(len_home_path);
            }

            cout << ">";
        }

        string command;

        getline(cin, user_input);
        char *demo = (char *)user_input.c_str();

        // tokenization process
        vector<string> semi_vec; // entire vector to store string
        vector<string> semi_vec_io;
        char *semi = strtok(demo, ";");
        for (; semi != NULL; semi = strtok(NULL, ";")) // some problem in ; don't delete it
        {
            semi_vec.push_back(semi);
            semi_vec_io.push_back(semi);
        }

        for (int i = 0; i < semi_vec.size(); i++)
        {
            vector<string> v;
            char *p = strtok((char *)semi_vec[i].c_str(), " \t");
            for (; p != NULL; p = strtok(NULL, " \t")) // not working with double tab
            {
                v.push_back(p);
                if (v[0] == "echo")
                {
                    print(demo + 5);
                    break;
                }
            }
            if (v[0] == "pwd")
            {
                // case 1 when in home
                pwd_print(home);
            }
            else if (v[0] == "cd")
            {
                if (v.size() == 1)
                {
                    continue;
                }
                cd_print(v[1], home);
            }
            else if (v[0] == "ls")
            {
                // cout << "v size" << v.size();
                if (v.size() > 2)
                {
                    ls_print(v[1], v[2], home);
                }
                else if (v.size() > 1)
                    ls_print(v[1], "", home);
                else
                    ls_print("", "", home);
            }
            else if (user_input == "exit") // or EXIT or both?
            {
                return 0;
            }
            else if (v[0] == "pinfo") // just pinfo in input?
            {
                process_info(v, is_background);
            }
            else if (v[0] == "search")
            {
                if (v.size() < 2)
                {
                    cout << "Lesser number of arguments passed" << endl;
                    continue;
                }
                bool search_result = search(".", v[1]);
                if (search_result == 1)
                {
                    cout << "True" << endl;
                }
                else
                {
                    cout << "False" << endl;
                }
            }
            else if (v[0] == "history")
            {
            }
            else
            {
                // cout << "within else" << endl;
                bool io_red = false;

                int len_charptr = v.size();
                // to check for i/o redirection
                for (int i = 0; i < len_charptr; i++)
                {
                    if (v[i] == ">" || v[i] == "<")
                    {
                        // perform i/o redirection
                        // cout << "perform i/p" << endl;
                        io_red = true;
                        break;
                    }
                }
                if (io_red)
                {
                    // io redirection
                    cout << semi_vec_io[i];
                    ioredirect(semi_vec_io[i]);
                }
                else
                {
                    char *exvp_para[len_charptr];
                    char *exvp_para_back[len_charptr - 1];
                    if (v[len_charptr - 1] == "&")
                    {
                        is_background = true;
                    }
                    if (!is_background)
                    {
                        //   cout << "len is " << len_charptr << endl;

                        for (int i = 0; i < len_charptr; i++)
                        {
                            exvp_para[i] = (char *)v[i].c_str();
                        }
                        exvp_para[len_charptr] = NULL;
                    }
                    else
                    {

                        for (int i = 0; i < len_charptr - 1; i++)
                        {
                            exvp_para_back[i] = (char *)v[i].c_str();
                        }
                        exvp_para_back[len_charptr - 1] = NULL;
                    }
                    const char *foreground_process = v[0].c_str();
                    //   cout << "foreg " << foreground_process << endl;
                    pid_t process_id = fork();
                    if (process_id < 0)
                    {
                        cout << "Failure to create a new process";
                    }
                    else if (process_id == 0)
                    {
                        setpgid(0, 0);
                        if (!is_background)
                        {
                            if (execvp(foreground_process, exvp_para) == -1)
                            {
                                perror(strerror(errno));
                                cout << "foreground process not created" << endl;
                            }
                        }
                        else
                        {
                            if (execvp(foreground_process, exvp_para_back) == -1)
                            {
                                perror(strerror(errno));
                                cout << "background process not created" << endl;
                            }
                        }
                    }
                    else
                    {
                        // cout << "I'm parent process " << (int)getpid() << " parent pid " << (int)getppid() << endl;
                        int *status; //  pointer to the location where status information for the terminating process is to be stored.
                        if (is_background)
                        {
                            // cout << "within background" << endl;
                            cout << "Process id is: " << (int)getpid() << endl;
                        }
                        else if (waitpid(process_id, status, 0) == -1) // for foreground process
                        {
                            cout << "error in waitpid in parent";
                        }
                    }
                }
            }
        }
    }
    return 0;
}