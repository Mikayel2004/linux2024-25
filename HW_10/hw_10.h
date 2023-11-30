#include <dirent.h>
#include <iostream>
#include <stack>
#include <string>

class DirectoryIterator 
{
public:
    DirectoryIterator(const std::string& path) 
    {
        visit(path);
    }
    bool hasNext() const 
    {
        return !dirs.empty();
    }
    std::string next() 
    {
        if (!hasNext()) 
        {
            throw std::runtime_error("No more files");
        }

        auto dir = dirs.top();
        dirs.pop();
        while ((entry = readdir(dir)) != nullptr) 
        {
            if (entry->d_type == DT_DIR) 
            {
                std::string name = entry->d_name;
                if (name != "." && name != "..") 
                {
                    visit(dirPath + "/" + name);
                }
            } else 
            {
                return dirPath + "/" + std::string(entry->d_name);
            }
        }
        closedir(dir);
        return next();
    }

private:
    std::stack<DIR*> dirs;
    DIR* dir;
    struct dirent* entry;
    std::string dirPath;
    void visit(const std::string& path) 
    {
        DIR* dir = opendir(path.c_str());
        if (dir == nullptr) 
        {
            throw std::runtime_error("Directory not found: " + path);
        }
        dirs.push(dir);
        dirPath = path;
    }
};
