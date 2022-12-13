#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <semaphore.h>

//Create struct for readers/writers lock
typedef struct _rwlock_t {
    sem_t lock;             //binary semaphore (basic lock)
    sem_t writelock;        //allow ONE writer/MANY readers
    int readers_count;      //number of readers in critical section
    sem_t fair;             //obtain permits in FIFO order
} rwlock_t;

void rwlock_init (rwlock_t *rw) {
    rw->readers_count = 0;
     //if the second parameter is 0, the semaphore can't be shared between processes
     //if the second parameter is nonzero, the semaphore can be shared between processes
     //the thired parameter is the initialized value = 1
    sem_init(&rw->lock, 0, 1); 
    sem_init(&rw->writelock, 0, 1);
    sem_init(&rw->fair, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
    //use sem wait to block the calling thread until
    //the count in the semaphore pointed to by "rw->lock" 
    //becomes greater than zero, then atomically decrement it
    //return zero after completing sucessfully
    sem_wait(&rw->fair);
    sem_wait(&rw->lock);
    rw->readers_count++;
    if (rw->readers_count == 1) {    //first reader gets writelock
        sem_wait(&rw->writelock);
    }
    sem_post(&rw->lock);
    sem_post(&rw->fair);
    //sem_post is used to increse a semaphore
    //atomically increment (unlock) the semaphore pointed to by "rw->lock"
    //if any threads are blocked on the semaphore, one of them is unblock
    //return zero after completing successfully
}

void rwlock_release_readlock(rwlock_t *rw)  {
    sem_wait(&rw->lock);
    rw->readers_count--;
    if (rw->readers_count == 0) {     //last reader lets it go
        sem_post(&rw->writelock);
    }
    sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
    sem_wait(&rw->fair);
    sem_wait(&rw->writelock);
    sem_post(&rw->fair);
}

void rwlock_release_writelock(rwlock_t *rw) {
    sem_post(&rw->writelock);
}

void reading_writing(int action) {
    int i, j;
    int x = 0, T = rand() % 10000;
    for (i = 0; i < T; i++) {
        for (j = 0; j < T; j++) {
            x = i*j;
        }
    }
    if (action == 0) {
        printf("Reader is reading\n");
    }
    else if (action == 1) {
        printf("Writer is  writing\n");
    }
}


void *threadRead(rwlock_t *readLock) {
    rwlock_acquire_readlock(readLock);
    printf("Reader is created\n");

    reading_writing(0);
    //printf("Reader is reading\n");

    rwlock_release_readlock(readLock);
    printf("Reader finished reading\n");

    return NULL;
}

void *threadWrite(rwlock_t *writeLock) {
    rwlock_acquire_writelock(writeLock);
    printf("Writer is created\n");

    reading_writing(1);
    //printf("Writer is writing\n");

    rwlock_release_writelock(writeLock);
    printf("Writer finished writing\n");

    return NULL;
}