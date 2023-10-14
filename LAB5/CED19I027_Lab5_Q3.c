// N Sree Dhyuti
// CED19I027
// Lab 5 : Q3

// Inclusion of required libraries
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include<fcntl.h>


int main(int argc, char *argv[])
{ 
    // Opendir and readdir to display the names of files in a particular directory
    printf("\n----------------------------------------------------------------\n");
    printf("\n3.A : opendir() and readdir()\n");
    printf("\nTo display all the files in a directory\n");
    
    DIR *folder;
    struct dirent *dirp;
    
    // If no file is mentioned in command line, show error
    if (argc != 2) 
    {
        fprintf(stderr, "Wrong command line input by user\n");
        return 0;
    }

    folder = opendir(argv[1]);

    while ((dirp = readdir(folder)) != NULL)
        printf("%s\n", dirp -> d_name);

    // Close directory
    closedir(folder);
    
    // open () and close ()
    printf("\n----------------------------------------------------------------\n");
    printf("\n3.B : open() and close()\n");
    int fd1 = open("openclose.txt", O_RDONLY);
    int fd2 = open("openclose.txt", O_WRONLY);
    if (fd1 < 0)
    {
        perror("c1");
        exit(1);
    }
    if (fd2 < 0)
    {
        perror("c1");
        exit(1);
    }
    printf("opened the fd1 = % d\n", fd1);
    printf("opened the fd2 = % d\n", fd2);    
    // Using close system Call
    if (close(fd1) < 0)
    {
        perror("c1");
        exit(1);
    }
    printf("closed the fd1.\n");
    if (close(fd2) < 0)
    {
        perror("c1");
        exit(1);
    }
    printf("closed the fd2.\n");

    printf("\n----------------------------------------------------------------\n");
    printf("\n3.C : read() and wrie()\n");
    int fd, sz;
    char *c = (char *) calloc(100, sizeof(char));
 
    fd = open("openclose.txt", O_RDONLY);
    if (fd < 0) { perror("r1"); exit(1); }
 
    sz = read(fd, c, 200);
    printf("In the opened file, %d bytes were read.\n", sz);
    c[sz] = '\0';
    printf("Those bytes are as follows: \n %s\n", c);
    
    return 0;
}