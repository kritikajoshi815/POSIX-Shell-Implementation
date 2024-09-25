#include <string.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include "header.hpp"

bool search(string directory_to_search, string target)
{
    bool ans = false;
    DIR *dir = opendir(directory_to_search.c_str());

    if (dir == NULL)
    {
        ans = false;
        return ans;
    }

    struct dirent *dir_contents;
    while ((dir_contents = readdir(dir)) != NULL)
    {

        if ((dir_contents->d_name)[0] == '.' || dir_contents->d_name == "..")
        {
            continue;
        }

        if (dir_contents->d_name == target)
        {
            ans = true;
            return ans;
            closedir(dir);
        }
        string path = directory_to_search + "/" + (dir_contents->d_name);

        if (dir_contents->d_type == DT_DIR)
        {
            search(path, target);
        }
    }
    return ans;
}