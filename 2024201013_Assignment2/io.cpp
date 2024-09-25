#include <string.h>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include "header.hpp"

void io_exev(char *input_file, char *output_file, char *first_argument, vector<string> arguments, bool append)
{
    char *argument_carr[arguments.size()];
    for (int i = 0; i < arguments.size(); i++)
    {
        argument_carr[i] = (char *)arguments[i].c_str();
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        cout << "Unable to fork" << endl;
        return;
    }
    if (pid == 0)
    {
        if (input_file != NULL)
        {
            int fd_input = open(input_file, O_RDONLY);
            cout << "input file" << input_file << endl;
            if (fd_input < 0)
            {
                cout << "Error Input file does not exists" << endl;
                return;
            }
            dup2(fd_input, STDIN_FILENO);
            close(fd_input);
        }
        if (output_file != NULL)
        {
            int fd_output;
            if (append)
            {
                fd_output = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            }
            else
            {
                fd_output = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (fd_output < 0)
            {
                cout << "Failed to open output file" << endl;
                return;
            }
            dup2(fd_output, STDOUT_FILENO);
            close(fd_output);
        }
        // execvp(first_argument, argument_carr);
        if (execvp(first_argument, argument_carr) == -1)
        {
            perror(strerror(errno));
        }
    }
    else
    {
        int *status;
        waitpid(pid, status, 0);
    }
}
void ioredirect(string command_io)
{
    bool append = false;
    char *input_file;
    char *output_file;
    char *first_cmd = NULL;
    vector<string> arguments;
    char *command_io_cptr = (char *)command_io.c_str();
    char *token = strtok(command_io_cptr, " \t");
    while (token != NULL)
    {
        cout << "within io " << endl;
        cout << "token: " << token << endl;
        if (token == ">>")
        {
            append = true;
        }
        if (token == "<")
        {
            cout << "within <" << endl;
            token = strtok(NULL, " \t");
            input_file = token;
            cout << "input file " << input_file << endl;
        }

        else if (token == ">")
        {
            token = strtok(NULL, " \t");
            output_file = token;
        }
        else
        {
            if (first_cmd == NULL)
            {
                first_cmd = token;
            }
            arguments.push_back(token);
        }
        token = strtok(NULL, " \t");
    }
    if (first_cmd != NULL)
    {
        cout << first_cmd << endl;
        // for (int i = 0; i)
        io_exev(input_file, output_file, first_cmd, arguments, append);
    }
}