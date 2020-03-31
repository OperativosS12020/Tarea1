#include <dirent.h>
#include <stdio.h>

char * sortingFiles(){

}

char * getFiles(){
	char * tt;
	DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d){
        while ((dir = readdir(d)) != NULL){
        	//char * t1=malloc(sizeof(char)*)
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}

int getSize(const char* name){
	FILE *fp;
    char ch;
    int size = 0;
    fp = fopen(name, "r");
    if (fp == NULL)
        return -1;
    fseek(fp, 0, 2);    /* file pointer at the end of file */
    size = ftell(fp);   /* take a position of file pointer un size variable */
    fclose(fp);
    return size;
}