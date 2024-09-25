#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>       //for getcwd
#include <linux/limits.h> //for path max
#include <pwd.h>
#include <grp.h>
#include <iomanip>
#include "header.hpp"

void file_info(string full_path, struct stat file_stat, string dir_name)
{
    string permi;
    stat(full_path.c_str(), &file_stat);
    struct passwd *p;
    struct group *g;
    // string uid = &file_stat.st_uid;
    mode_t mode = file_stat.st_mode;
    mode_t permissions = mode & 0777;
    uid_t user_id = file_stat.st_uid;
    gid_t group_id = file_stat.st_gid;
    // cout << "premision is " << permissions << endl;
    permi += (S_ISDIR(permissions) ? 'd' : '-');

    permi += (permissions & 0400) ? 'r' : '-';
    permi += (permissions & 0200) ? 'w' : '-';
    permi += (permissions & 0100) ? 'x' : '-';

    permi += (permissions & 0040) ? 'r' : '-';
    permi += (permissions & 0020) ? 'w' : '-';
    permi += (permissions & 0010) ? 'x' : '-';

    permi += (permissions & 0004) ? 'r' : '-';
    permi += (permissions & 0002) ? 'w' : '-';
    permi += (permissions & 0001) ? 'x' : '-';

    cout << permi << " ";
    cout << file_stat.st_nlink << " ";
    if ((p = getpwuid(user_id)) == NULL)
    {
        cout << "unknown" << " ";
    }
    else
    {
        cout << p->pw_name << " ";
    }

    if ((g = getgrgid(group_id)) == NULL)
    {
        cout << "unknown" << " ";
    }
    else
    {
        cout << g->gr_name << " ";
    }
    cout << setw(8) << file_stat.st_size << " ";
    char time[20];
    strftime(time, sizeof(time), "%b %d %H:%M", localtime(&file_stat.st_mtime));
    // printf("%b %d %H:%M", localtime(&file_stat.st_mtime));
    cout << time << " ";
    cout << " " << dir_name << endl;
}
void ls_print(string path, string path2, char *home)
{
    string home_str = home;
    char pwd[PATH_MAX];
    DIR *dir;
    struct dirent *entry;
    char *path_cptr = (char *)path.c_str();
    struct stat file_stat;
    // cout << "path is " << path << endl;
    // cout << " check" << (path == "-al") << endl;
    if (path.size() == 0)
    {
        if (getcwd(pwd, sizeof(pwd)) == NULL)
        {
            // what to do think
        }
        else
        {
            char *pwd_cptr = pwd;
            if ((dir = opendir(pwd_cptr)) == NULL)
            {
                cout << "No such directory exits";
                return;
            }
            else
            {
                while ((entry = readdir(dir)) != NULL)
                {
                    if (entry->d_name[0] != '.')
                    {
                        cout << entry->d_name << endl;
                    }
                }
            }
            closedir(dir);
        }
    }
    else if (path2.size() > 0)
    {
        if (path == "-a" && path2 == "-l")
        {
            // cout << "within ls -a -l" << endl;
            if (getcwd(pwd, sizeof(pwd)) == NULL)
            {
                // what to do think
            }
            else
            {
                char *pwd_cptr = pwd;
                if ((dir = opendir(pwd_cptr)) == NULL)
                {
                    cout << "No such directory exits";
                    return;
                }
                else
                {
                    while ((entry = readdir(dir)) != NULL)
                    {

                        string pwd_str = pwd_cptr;
                        string dir_name = entry->d_name;
                        string full_path = pwd_str + "/" + dir_name;
                        char *full_path_cptr = (char *)full_path.c_str();

                        file_info(full_path, file_stat, dir_name);
                    }
                }
                closedir(dir);
            }
        }
    }
    else if (path == "-al" || path == "-la")
    {
        // cout << "within ls -al" << endl;
        // ls -al
        if (getcwd(pwd, sizeof(pwd)) == NULL)
        {
            // what to do think
        }
        else
        {
            char *pwd_cptr = pwd;
            if ((dir = opendir(pwd_cptr)) == NULL)
            {
                cout << "No such directory exits";
                return;
            }
            else
            {
                while ((entry = readdir(dir)) != NULL)
                {

                    string pwd_str = pwd_cptr;
                    string dir_name = entry->d_name;
                    string full_path = pwd_str + "/" + dir_name;
                    char *full_path_cptr = (char *)full_path.c_str();

                    file_info(full_path, file_stat, dir_name);
                    // cout << entry->d_name << endl;
                }
            }
            closedir(dir);
        }
    }
    else if (path[0] == '-' && path[1] == 'a')
    {
        if (getcwd(pwd, sizeof(pwd)) == NULL)
        {
            // what to do think
        }
        else
        {
            char *pwd_cptr = pwd;
            if ((dir = opendir(pwd_cptr)) == NULL)
            {
                cout << "No such directory exits";
                return;
            }
            else
            {
                while ((entry = readdir(dir)) != NULL)
                {
                    cout << entry->d_name << endl;
                }
            }
            closedir(dir);
        }
    }
    else if (path[0] == '-' && path[1] == 'l')
    {
        // ls -l
        if (getcwd(pwd, sizeof(pwd)) == NULL)
        {
            // what to do think
        }
        else
        {
            char *pwd_cptr = pwd;
            if ((dir = opendir(pwd_cptr)) == NULL)
            {
                cout << "No such directory exits";
                return;
            }
            else
            {
                while ((entry = readdir(dir)) != NULL)
                {
                    if (entry->d_name[0] != '.')
                    {
                        string pwd_str = pwd_cptr;
                        string dir_name = entry->d_name;
                        string full_path = pwd_str + "/" + dir_name;
                        char *full_path_cptr = (char *)full_path.c_str();
                        // char* full_path_cptr=(char)
                        // give file information
                        // cout << full_path << endl;
                        file_info(full_path, file_stat, dir_name);
                        // cout << entry->d_name << endl;
                    }
                }
            }
            closedir(dir);
        }
    }
    else if (path[0] == '.' && path[1] == '.')
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
                cout << "Parent folder doesn't exist" << endl;
                return;
            }
            int ind_strt_to_rem = pwd_str.find_last_of('/') + 1;
            // cout << "last index is " << ind_strt_to_rem << endl;
            int len_to_take = pwd_str.size() - ind_strt_to_rem;
            // cout << "length to take " << len_to_take << endl;
            string parent_str = pwd_str.substr(0, ind_strt_to_rem);
            char *parent_carr = (char *)parent_str.c_str();

            if ((dir = opendir(parent_carr)) == NULL)
            {
                cout << "No such directory exits";
                return;
            }
            else
            {
                while ((entry = readdir(dir)) != NULL)
                {
                    if (entry->d_name[0] != '.')
                    {
                        cout << entry->d_name << endl;
                    }
                }
            }
            closedir(dir);
        }
    }
    else if (path[0] == '.')
    {
        if (getcwd(pwd, sizeof(pwd)) == NULL)
        {
            // what to do think
        }
        else
        {
            char *pwd_cptr = pwd;
            if ((dir = opendir(pwd_cptr)) == NULL)
            {
                cout << "No such directory exits";
                return;
            }
            else
            {
                while ((entry = readdir(dir)) != NULL)
                {
                    if (entry->d_name[0] != '.')
                    {
                        cout << entry->d_name << endl;
                    }
                }
            }
            closedir(dir);
        }
    }
    else if (path[0] == '~')
    {
        if ((dir = opendir(home)) == NULL)
        {
            cout << "No such directory exits";
            return;
        }
        else
        {
            while ((entry = readdir(dir)) != NULL)
            {
                cout << entry->d_name << endl;
            }
        }
        closedir(dir);
    }

    else
    {
        if ((dir = opendir(path_cptr)) == NULL)
        {
            cout << "No such directory exits";
            return;
        }
        else
        {
            while ((entry = readdir(dir)) != NULL)
            {
                if (entry->d_name[0] != '.')
                {
                    cout << entry->d_name << endl;
                }
            }
        }
        closedir(dir);
    }
}