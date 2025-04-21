#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <unistd.h>

#define KWHT  "\x1B[37m"
#define KBLK  "\x1b[30m"
#define KBLU  "\x1B[34m"
#define KCLR  "\e[1;1H\e[2J"
#define KBBLK "\x1b[40m"
#define KBBLU "\x1b[44m"
#define KBRED "\x1b[41m"

#define NSTR  "%s\n"
#ifdef _WIN32
    #define DSYN  "\\"
    #define DSYNI '\\'
#else
    #define DSYN  "/"
    #define DSYNI '/'
#endif



void remove_last_folder(char *path) {
    char *last_slash = strrchr(path, DSYNI);

    if (last_slash != NULL) {
        *last_slash = '\0';
    }
}

int main(void) {
    DIR *d;
    struct dirent *dir;

    char rootDir[256] = DSYN;

    while (1) {
        printf(KBBLK KCLR);

        d = opendir(rootDir);
        int files = 0;

        if (!d) {
            printf(KBRED KBLK NSTR, "  Directory not found ");
            remove_last_folder(rootDir);

            d = opendir(rootDir);
            printf(KBBLK KWHT);
        }

        printf(KBLU NSTR, rootDir);
            
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0) {
                files += 1;
                printf(KWHT "├─" NSTR, dir->d_name);
            }
        }
        closedir(d);

        printf(KBBLU KBLK "\n   %d Files: ", files);
        printf("%s" KBBLK KWHT, "> ");

        char nextDir[82];
        scanf("%s", nextDir);

        if (strcmp(nextDir, "..") == 0) {
            remove_last_folder(rootDir);
        } 
        else {
            if (strcmp(rootDir, "/") != 0) {
                strlcat(rootDir, DSYN, 256);
                strlcat(rootDir, nextDir, 256);
            }
            else {
                strlcat(rootDir, nextDir, 256);
            }
        };
    }

    return(0);
}
