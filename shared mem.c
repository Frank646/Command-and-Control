#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAX 1024

struct message_buffer {
    long msg_type;
    long msg_data;
};

void remove_ipc(int, int, int);
void writer(int, int);
void reader(int, long *);
int readline(char[], int);
void parent(int, int char * );
void child(int, int, char * );

int main(){
    return 0;

}

int main{

    int msg_id1, msg_id2, msg_id3, shm_id;

    msg_id1 = msget(ipc_private, 0600)
    msg_id2 = msget(ipc_private, 0600)
    msg_id3 = msget(ipc_private, 0600)
    shm_id = shmget(ipc_private, MAX, 0600);
    if (msg_id1 == -1 || msg_id2 == -1 || msg_id3 == -1)
    {
        perror("msget");
        exit(EXIT_FAILURE);

    }
    if (shm_id == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    
    }

    char *shmaddr = shmat(shm_id, NULL, 0);

    switch (fork()){
        case -1:
        perror("fork")
        exit(EXIT_FAILURE);

        case 0:
        child(msg_id1, msg_id2, shmaddr);
        exit(EXIT_FAILURE);
        
        default:
        parent(msg_id1, msg_id2, msg_id3, shmaddr);
        exit(EXIT_SUCCESS);
    }
    remove_ipc(msg_id1, msg_id2, msg_id3, shm_id);
    return 0;
}


void remove_ipc(int msg_id1, int msg_id2, int msg_id3, int shm_id){
    if(msg_id1 != -1){
        msgctl(msg_id1, ipc_RMID, NULL);
    }

    if(msg_id2 != -1){
        msgctl(msg_id2, ipc_RMID, NULL);
    }

    if(msg_id3 != -1){
        msgctl(msg_id3, ipc_RMID, NULL);
    }

    if(shm_id != -1){
        shmctl(shm_id, ipc_RMID, NULL);
    }
}

int readline(char text[], int n_bytes){
    int r, length;
    if (fgets(text, n_bytes, stdin) == NULL){
        r = EOF;
    }
    else{
        length = strlen(text);
        if (length > 0&& text[length - 1] == '\n')
            text[length - 1] = '\0';
        r =!EOF; 
    }
    return r;
}

void writer(int msg_id, int n_bytes){
    struct message_buffer m;
    m.msg_type = 1;
    m.msg_data = n_bytes;
    if (msgsnd(msg_id, &m n_bytes, 0) == -1)
    {
        perror("msgsnd")
        exit(EXIT_FAILURE);
    }
}
void reader(int msg_id, long *data)
{
    struct message_buffer m;
    if (msgrcvd(msg_id, &m, MAX 0, 0) == -1)
    {
        perror("msgrcvd");
        exit(EXIT_FAILURE);
    }
    *data = m.msg_data; //assigns the data points
}

void parent(int msg_id1, int msg_id2, int msg_id3, char *shmaddr)
{
    long data;
    while(readline(shmaddr, MAX) !=EOF)
    {
        puts("writing to the queue......");
        writer(msg_id1, strlen(shmaddr));
        puts("Reading......");
        reader(msg_id2, &data);
    }
    writer(msg_id1, 0)
}
void child(int msg_id1, int msg_id2, int msg_id3, char *shmaddr)
{
    long length;
    reader(msg_id1, &length);
    if (length > 0)
    {
        printf("The Data is stored in shared memory: %s\n", shmaddr);
        printf("The data has been receiveed from the queue: %ld\n", length)
    }
    writer(msg_id2)

}