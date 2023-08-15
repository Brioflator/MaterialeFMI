#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

bool isDirectory(const string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;
    }
    return S_ISDIR(info.st_mode);
}

void identifyFolders(const string& folderPath) {
    DIR* dir = opendir(folderPath.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_name[0] != '.') {
                string fullPath = folderPath + "/" + entry->d_name;
                if (isDirectory(fullPath)) {
                    cout << entry->d_name << " este folder." << endl;
                } else {
                    cout << entry->d_name << " nu este folder." << endl;
                }
            }
        }
        closedir(dir);
    } else {
        cerr << "Eroare la deschiderea directorului: " << folderPath << endl;
    }
}

int main() {
    string folderPath = "P:\anatomie";
    cin.getline(fodlerPath);
    identifyFolders(folderPath);
    return 0;
}

