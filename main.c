#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
        struct stat fileStat;

        if (argc != 2)
        {
                fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        if (stat(argv[1], &fileStat) == -1)
        {
                perror("stat");
                exit(EXIT_FAILURE);
        }

        printf("\nInformation about %s\n",argv[1]);
        printf("---------------------------\n");
        printf("File type:                ");

        switch (fileStat.st_mode & S_IFMT)
        {
                case S_IFBLK:  printf("block device\n");
                                break;
                case S_IFCHR:  printf("character device\n");
                                break;
                case S_IFDIR:  printf("directory\n");
                                break;
                case S_IFIFO:  printf("FIFO/pipe\n");
                                break;
                case S_IFLNK:  printf("symlink\n");
                                break;
                case S_IFREG:  printf("regular file\n");
                                break;
                case S_IFSOCK: printf("socket\n");
                                break;
                default:       printf("unknown?\n");
                                break;
        }

        printf("Device ID :               %ld\n", fileStat.st_dev);

        printf("I-node number:            %ld\n", fileStat.st_ino);

        printf("Mode:                     %lo (octal)\n", (unsigned long) fileStat.st_mode);

        printf("No of Links:              %ld\n", (long) fileStat.st_nlink);

        printf("Ownership:                UID=%ld   GID=%ld\n", (long) fileStat.st_uid, (long) fileStat.st_gid);

        printf("Preferred I/O block size: %ld bytes\n", (long) fileStat.st_blksize);

        printf("File size:                %lld bytes\n", (long long) fileStat.st_size);

        printf("Blocks allocated:         %lld\n", (long long) fileStat.st_blocks);

        printf("Last status change:       %s", ctime(&fileStat.st_ctime));

        printf("Last file access:         %s", ctime(&fileStat.st_atime));

        printf("Last file modification:   %s", ctime(&fileStat.st_mtime));

        int file=0;

        if((file=open(argv[1],O_RDONLY)) < -1)
                return 1;

        if(fstat(file,&fileStat) < 0)
                return 1;

        printf("File Permissions:         ");
        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n\n");

        printf("The file %s a symbolic link\n\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

        exit(EXIT_SUCCESS);
}
