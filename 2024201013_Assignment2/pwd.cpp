#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>       //for getcwd
#include <linux/limits.h> //for path max
#include <errno.h>
#include "header.hpp"

using namespace std;
char pwd[PATH_MAX];
void pwd_print(char *home)
{
    // int len_home_path =
    string home_str = home; // path till our project
    int len_home_path = home_str.size();
    if (getcwd(pwd, sizeof(pwd)) == NULL)
    {
        // cout << "nothing found";
        // strerror(errno); // will this give the output?
        perror("No such directory exists"); // ask someone how to handle with perror, what to do in perror.h?
    }
    else
    {
        {
            //  printf("Path of pwd is: %s", pwd);
            char *cwd = pwd;
            string cwd_str = cwd;
            // string home_str
            // cout << "home is" << home << endl;
            // cout << "cwd is" << cwd << endl;
            if (home_str == cwd)
            {
                //  cout << "within equal" << endl;
                printf("Path of pwd is: %s", cwd);
            }
            else // relative path //NOTE: once check after cd function
            {
                const char *cstr = cwd_str.substr(len_home_path).c_str();
                char *cwd_substr = (char *)cstr;
                // cout << "within else, cwd is " << cwd_substr << endl;
                // cout << "within pwd.cpp, else, else " << cwd_str.substr(len_home_path) << endl; // correct
                // cout << "Home is " << home << endl;
                // cout << "home size" << len_home_path << endl;
                // printf("Path of pwd is: %s", cwd_str.substr(len_home_path));
                cout << "Path of pwd is: ~" << cwd_str.substr(len_home_path);
                //  printf("Path of pwd is: ~%s", cwd_str.substr(len_home_path)); // if mistake check for path size
                //  printf("paht will be later");
            }
            cout << endl;
        }
    }
    //  cout << "pwd is" << pwd << endl;
    // return pwd;
}