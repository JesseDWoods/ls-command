#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int show_all = 0;
// Flag to indicate whether to show all files (including hidden ones)

int main(int argc, char *argv[]) {

    int opt = 0;

    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
        case 'a':
            show_all = 1; // Set the flag to show all files
            break;
        default:
            fprintf(stderr, "Usage: %s [-a] [path]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    const char *path = (optind < argc) ? argv[optind] : ".";
    DIR *dir = opendir(path);
    // DIR is an opaque type representing a directory stream

    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    struct dirent *entry; // struct dirent represents a directory entry
    while ((entry = readdir(dir)) != NULL) {
        if (!show_all && entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name); // d_name is the name of the entry
        } else if (show_all) {
            printf("%s\n", entry->d_name);
        }
    }

    return EXIT_SUCCESS;
}
