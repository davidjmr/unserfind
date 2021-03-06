/*
 * myfind.c
 *
 *    Programmname: myfind
 *    Aufgabenstellung: Funktionsprogrammierung des "find" Befehl
 *  Created on: Feb 26, 2020
 *      Author: Mahir Tulic   | 1910258009(ic19b009)
 *              David Rüb     | 1910258081(ic19b081)
 *              Manuel Houzar | 1910258089(ic19b089)
*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <error.h>
#include <sys/stat.h>
#include <fnmatch.h>

#define MAXLEN 256
#define NULLCHAR 1

static void no_argv(int argc);
//do_entry(const char * entry_name, const char * const * parms);

static void do_entry(const char * entry_name, char ** parms);
static void do_dir(const char * dir_name, char ** parms);

int main (int argc, char* argv[])
{
    //char* dirname
    no_argv(argc);
    int argvlength = 0;
    char* dirname = NULL;
    dirname = argv[1];
    //dirname = ".";
    if (argv[1] != NULL) argvlength=strlen(argv[1]);
    //fprintf(stderr, "Test Länge: %d\n%c\n",argvlength,argv[1]);
    do_entry(argv[1],argv);
    //do_dir(dirname,argv);

    return 0;
}

static void no_argv(int argc){

    if(argc<2){
        fprintf(stderr, "something went wrong!!! - ARGUMENTS 0");
    exit(1);
    }

}
void do_dir(const char * dir_name, char ** parms) {

    struct stat st;
    char wholepath[MAXLEN];
    DIR *dirp = NULL;
    dirp = opendir(dir_name);
    //int is_dir_flag=0;
    char temp_dir[MAXLEN];
    if (dirp == NULL){
    //if ((dirp = opendir(dir_name)) == NULL) {

        error(0,errno, "Fehler!: %s\n",dir_name);
        //EXIT_FAILURE;
      //  exit(1);
    }
    else {
        printf("wir haben %s gefunden \n",dir_name);
    }
    const struct dirent *dirent;
    errno = 0;
    int testnr = 0;
    while ((dirent = readdir(dirp)) != NULL) {
        testnr++;
        //printf("%d\n", testnr);
        if (strcmp(dirent->d_name, ".") != 0 && (strcmp(dirent->d_name, "..") != 0)) {
            printf("%s/%s\n", dir_name, dirent->d_name);
            snprintf(wholepath, (sizeof(dir_name)+sizeof(dirent->d_name) +NULLCHAR), "%s/%s", dir_name, dirent->d_name);
            if (lstat(wholepath, &st) == -1) {
                error(0,errno, "stat - no such file or directory");
                exit(1);
            }

        }
        if (S_ISDIR(st.st_mode)) {
            do_dir(wholepath,parms);
        }


        errno=0;
    }
    if (errno!=0){
        error(0,errno, "Fault while readdir");
    }
    
    

    if (closedir(dirp) == -1) {
                error(0,errno, "closedir");
        exit(1);
    }
}


void do_entry(const char * entry_name, char ** parms)                                                                                                             
{                                                                                                                                                                 
    struct stat entry_data;
    /* get information about the file and/or directory*/
    if (lstat(entry_name, &entry_data) == -1)
    {
        error("lstat failed");
        return;
    }
    errno=0;                                                                                                                                                      
    int i=0;                                                                                                                                                      
    char buffer[MAXLEN];                                                                                                                                          
    const char possible_entry[10][MAXLEN] = {"-nogroup","-group", "-nouser", "-user", "-name", "-type", "-path", "-print", "-ls"};                                
                                                                                                                                                                  
    while (parms[++i] != NULL){                                                                                                                                   
        if (*parms[i] == '-'){ 
            strcpy(buffer, parms[i]);                                                                                                                                   
            for (int j = 0; j < 10; j++) {                                                                                                                        
                                                                                                                                        
                if ((strcmp(possible_entry[j], buffer)) == 0) {                                                                                                   
                    printf("Gefunden:%s!!\n", possible_entry[j]); //                                                                                              
                                                                                                                                                               
                if (j == 0) {                                                                                                                                      
                                                                                                                                                                  
                   do_nogroup(parms[j + 1]);                                                                                                                      
                                                                                                                                                                  
                } else if (j == 1) {                                                                                                                               
                                                                                                                                                                  
                    do_group(parms[i + 1]);                                                                                                                       
                                                                                                                                                                  
                } else if (j == 2) {                                                                                                                               
                                                                                                                                                                  
                    do_nouser(parms[i + 1]);                                                                                                                      
                                                                                                                                                                  
                } else if (j == 3) {                                                                                                                               
                                                                                                                                                                  
                    do_user(parms[i + 1]);                                                                                                                        
                                                                                                                                                                  
                } else if (j == 4) {                                                                                                                               
                                                                                                                                                                  
                    do_name(parms[i + 1]);                                                                                                                        
                                                                                                                                                                  
                } else if (j == 5) {                                                                                                                               
                                                                                                                                                                  
                    do_name(parms[i + 1]);                                                                                                                        
                                                                                                                                                                  
                } else if (j == 6) {                                                                                                                               
                                                                                                                                                                  
                    do_path(parms[i + 1]);                                                                                                                        
                                                                                                                                                                  
                } else if (j == 7) {                                                                                                                               
                                                                                                                                                                  
                    do_print(parms[i + 1]);                                                                                                                       
                                                                                                                                                                  
                } else if (j == 8) {                                                                                                                               
                                                                                                                                                                  
                    do_ls(parms[i + 1]);                                                                                                                          
                                                                                                                                                                  
                }else{
                    exit(1);
                }   
                }                                                                                                                                                  
            }                                                                                                                                                     
        }                                                                                                                                                         
        else{                                                                                                                                                     
            do_dir(parms[i],parms);                                                                                                                               
        }                                                                                                                                                         
    }                                                                                                                                                             
}                                                                                                                                                                 
    static void do_group(char *parms){
        printf("Group: Gesucht wird nach: %s", parms);
    }
    static void do_nogroup(char *parms) {
        printf("NoGroup:Gesucht wird nach: %s", parms);
    }
    static void do_nouser(char *parms) {
        printf("do_nouser Gesucht wird nach: %s", parms);
    }
    static void do_user(char *parms) {
        printf(" do_user Gesucht wird nach: %s", parms);
    }
    static void do_name(char *parms) {
        printf("do_name Gesucht wird nach: %s", parms);
    }
    static void do_type(char *parms) {
        printf(" do_type Gesucht wird nach: %s", parms);
    }
    static void do_path(char *parms) {
        printf("path Gesucht wird nach: %s", parms);
    }
    static void do_print(char *parms) {
        printf("print Gesucht wird nach: %s", parms);
    }
    static void do_ls(char *parms) {
        printf("ls Gesucht wird nach: %s", parms);
    }
