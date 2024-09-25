#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "header.hpp"
void process_info(vector<string> v, bool is_Background)
{
    string path;
    string read_file;
    string status;
    string memory;
    // if (v.size() > 1)
    {
        // cout << "within pinfo.cpp " << endl;
        if (v.size() > 1)
            path = "/proc/" + v[1] + "/status";
        else
            path = "/proc/" + to_string(getpid()) + "/status";
        //   cout << "path is: " << path << endl;
        ifstream status(path);
        if (!status)
        {
            // cout << "within !status" << endl;
            perror(strerror(errno));
            return;
        }
        while (getline(status, read_file))
        {
            if (read_file.find("State") == 0)
            {
                // cout << "Process Status--" << read_file << endl;
                cout << read_file;
                if (!is_Background)
                {
                    cout << "+";
                }
            }
            else if (read_file.find("VmSize:") == 0)
            {
                cout << endl;
                cout << read_file << endl;
            }
        }
        // string path_exe = "/proc/" + v[1] + "/exe";
        string path_exe;
        if (v.size() > 1)
            path_exe = "/proc/" + v[1] + "/exe";
        else
            path_exe = "/proc/" + to_string(getpid()) + "/exe";
        char buf[PATH_MAX];
        size_t len = readlink(path_exe.c_str(), buf, sizeof(buf));
        if (len == -1)
        {
            cout << "Unable to resolve executable path.";
        }
        else
        {
            cout << "Executable Path-- " << buf << endl;
        }
    }
    // else
    // {
    //     pid_t terminal_id = getpid();
    // }
}