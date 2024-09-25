#include <iostream>
#include <unistd.h>       //for getcwd
#include <linux/limits.h> //for path max
#include "header.hpp"
// Q. in cd do we also have to implement that we are within a directory and giving complete address of a directory outside it?
//  char pwd[PATH_MAX];
string prev_path_sl = "";
string prev_path_l = "";

void cd_print(string str, char *home)
{
    char pwd[PATH_MAX];
    string home_str = home;
    if (str[0] == '-')
    {
        // store cur path
        if (prev_path_l == "")
        {
            cout << "OLDPWD not set" << endl;
            return;
        }
        char *prev_path_cptr = (char *)prev_path_sl.c_str();

        chdir(prev_path_cptr);
    }
    else if (str[0] == '.' && str[1] == '.')
    {
        if (getcwd(pwd, sizeof(pwd)) == NULL)
        {
            // what to do think
        }
        else
        {
            // a/bc
            string pwd_str = pwd; // converted pwd to string now remove the last portion till /

            if (pwd_str == home_str)
            {
                pwd_print(home);
                return;
            }
            int ind_strt_to_rem = pwd_str.find_last_of('/') + 1;
            // cout << "last index is " << ind_strt_to_rem << endl;
            int len_to_take = pwd_str.size() - ind_strt_to_rem;
            // cout << "length to take " << len_to_take << endl;
            string parent_str = pwd_str.substr(0, ind_strt_to_rem);
            char *parent_carr = (char *)parent_str.c_str();
            // cout << "within cd.cpp else if else, parent path is" << parent_carr << endl;
            chdir(parent_carr);
            // cout << "within cd.cpp else if else" << endl;
            //   pwd_print(home);
        }
    }
    else if (str[0] == '.')
    {
        return;
    }
    else if (str[0] == '~')
    {
        chdir(home);
    }
    else
    {
        // string path_provided = str.substr(1);
        // const char *path = path_provided.c_str();
        // char *path_charptr = (char *)path;
        // printf("Paht is %s", path_charptr);
        // cout << endl;

        prev_path_sl = prev_path_l;
        prev_path_l = str;
        const char *path = str.c_str();
        char *path_charptr = (char *)path;
        if (chdir(path_charptr) == -1)
        {
            cout << "No such directory exists" << endl;
        }
        else
        {
            // pwd_print(home);
        }
    }
    // cout << "hi" << pwd_print(home) << endl;
}