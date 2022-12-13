#include "readerwriter.c"

int main() {

    //input scenario
    char line[1000];
    pthread_t thread[1000];

    //open the file
    FILE* file = fopen("scenarios.txt", "r");
    
    //create and initialized lock
    rwlock_t lock;
    rwlock_init(&lock);

    //for loop variable 
    int i;

    while(fscanf(file, "%s", line) != EOF){

        for(i = 0; i < strlen(line); i++){

            int *arg = malloc(sizeof(*arg));
            // Thread creation
            if(line[i] == 'r'){
                pthread_create(&thread[i], NULL, (void*) threadRead, (void*) &lock);
            }
            else{
                pthread_create(&thread[i], NULL, (void*) threadWrite, (void*) &lock);
            }
        }

        // Waiting for scenario to complete
        for(i = 0; i < strlen(line); i++){
            pthread_join(thread[i], NULL);
        }
    }

    // Close file
    fclose(file);

    return 0;
}
    