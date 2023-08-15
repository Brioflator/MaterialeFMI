#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int isDirectory(const char* path) {
    struct stat info;
    if (stat(path, &info) != 0) {
        return 0;
    }
    return S_ISDIR(info.st_mode);
}

void identifyFolders(const char* folderPath) {
    DIR* dir = opendir(folderPath);
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] != '.') {
                char fullPath[1024];
                snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, entry->d_name);
                if (isDirectory(fullPath)) {
                    printf("%s este folder.\n", entry->d_name);
                } else {
                    printf("%s nu este folder.\n", entry->d_name);
                }
            }
        }
        closedir(dir);
    } else {
        fprintf(stderr, "Eroare la deschiderea directorului: %s\n", folderPath);
    }
}

int main() {
    const char* folderPath = "P:/anatomie";
    identifyFolders(folderPath);
    return 0;
}
