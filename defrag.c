#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int sum = 0;


void * expoloreSubDirecory(void * arg) {
    pthread_mutex_lock(&mutex);
    char * input = (char *) arg;
    if( access( input, F_OK ) == -1 ) {
        pthread_mutex_unlock(&mutex);
        return NULL;

    } 
    DIR *dr = opendir(input); 
    struct dirent *de;

    if(!dr){
        printf("input %s: \n",input);
        closedir(dr);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    while ((de = readdir(dr)) != NULL)
    {    
       printf("%s\n",de->d_name);
    }
    closedir(dr);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int a, char** args) {
    if(args[1]== NULL){
            printf("./parser: an input path is required!");
            return 0;
    }
    char file[1000] = "./";
    char * input = args[1];
    // char ** subDir = malloc(0);
    strcat(file, input);
    DIR *dr = opendir(input); 
    struct dirent *de;
    //expoloreSubDirecory((void *) file);
    int index =0;
     pthread_t thread;
    
    while ((de = readdir(dr)) != NULL) {
        char * s = malloc(0);
        // s = "hello";
        // s[0]='\0';
        int copyIndex=0;
        for(;input[copyIndex] != '\0';copyIndex++){
            s=realloc(s,copyIndex+1);
            s[copyIndex] = input[copyIndex];
        }
        s=realloc(s,copyIndex+1);
        s[copyIndex] = '/';
        copyIndex++;
        int copyIndex2=0;
        for(;de->d_name[copyIndex2] != '\0';copyIndex2++){
            s=realloc(s,copyIndex+copyIndex2+1);
            s[copyIndex+copyIndex2] = de->d_name[copyIndex2];
        }
        s=realloc(s,copyIndex+copyIndex2+1);
        s[copyIndex+copyIndex2]='\0';
        // strcat(s, input); /* copy name into the new var */
        // strncat(s, "/",sizeof(char)); /* add the extension */
        // strncat(s, de->d_name,sizeof(de->d_name)); /* add the extension */
        if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..") !=0){
            index++;
            pthread_create(&thread, NULL, expoloreSubDirecory, (void *) s);
            printf("\n\n");
            pthread_join(thread, NULL);

            // subDir = realloc(subDir,index*sizeof(char *));
            // subDir[index-1] = malloc(sizeof(s)+1);
                // subDir[index-1][0] = '\0';
            // strcpy(subDir[index-1],s);
        }
        free(s);
    }
    
        
    closedir(dr);
    //  pthread_t thread;
    for(int i=0;i<index;i++){
        //expoloreSubDirecory((void *) subDir[i]);
       // char * str = subDir[i];
    //     pthread_create(&thread, NULL, expoloreSubDirecory, (void *) subDir[i]);
    //     printf("\n\n");
    //    pthread_join(thread, NULL);
    }

    for(int i=0;i<index;i++){
       // printf("%s\n",subDir[i]);
      // free(subDir[i]);
    }
    // free(subDir);
    //pthread_exit(NULL);

    // pthread_t thread;
    // pthread_t thread2;
    // int offset  =1;
    // pthread_create(&thread,NULL,myTurn,(void *) &offset);
    // int offset2 = -1;
    // pthread_create(&thread2,NULL,myTurn,(void *) &offset2);
    // pthread_join(thread, NULL);
    // pthread_join(thread2, NULL);

}
