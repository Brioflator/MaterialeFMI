#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

bool isDirectory(const string& path) {
    return fs::is_directory(path);
}

void identifyFolders(const string& folderPath) {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (!entry.is_hidden()) {
            string fullPath = entry.path().string();
            if (isDirectory(fullPath)) {
                cout << entry.path().filename() << " este folder." << endl;
            } else {
                cout << entry.path().filename() << " nu este folder." << endl;
            }
        }
    }
}

int main() {
    string folderPath = "P:/anatomie";
    identifyFolders(folderPath);
    return 0;
}
