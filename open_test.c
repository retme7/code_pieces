#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <err.h>
#include <linux/kvm.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void check(char* dir_name){
        int fd;
        DIR* dir_next;
        char path[200];
        //len = strlen(argv[1]);
        struct stat buf;
        int x;


        DIR* dirp = opendir(dir_name);
        if(dirp==NULL){
                return;
        }
        struct dirent * dp;
        while ((dp = readdir(dirp)) != NULL)
        {
                if(strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0){
                        continue;
                }
                sprintf(path,"%s/%s",dir_name,dp->d_name);

                x = lstat(path, &buf);
                if(x==0 && S_ISLNK(buf.st_mode)){
                        printf("%s is link\n",path);
                        continue;
                }

                fd = open(path, 0);
                if (fd <0) {

                }else{
                        close(fd);
                        printf("%s success\n",path);
                        if(x==0 && S_ISDIR(buf.st_mode)){
                                printf("%s is dir\n",path);

                                check(path);
                        }
                }
                
        }
        closedir(dirp);

}

void main(int argc,char** argv){
        check(argv[1]);
        return;
}

