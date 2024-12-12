#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h> 
#include <fcntl.h>




const char *prompt = "enseash % ";
#define BUFSIZE 1048


void print_message(){
    //Print a welcome message when the shell starts.
    char buf[BUFSIZE] = "Bienvenue dans le shell ENSEA. \n Pour quitter, tapez 'exit'. \n ";
    write(STDOUT_FILENO, buf, strlen(buf));
}


int get_start_time(struct timespec *start) {
    //Record the start time of the command execution.
    if (clock_gettime(CLOCK_MONOTONIC, start) == -1) {
        perror("Error measuring start time");
        exit(EXIT_FAILURE); 
    }
    return 0;
}

int get_end_time(struct timespec *end) {
        //Record the end time of the command execution.
    if (clock_gettime(CLOCK_MONOTONIC, end) == -1) {
        perror("Error measuring end time");
        return -1;
    }
    return 0;
}

void cut_command(char *buf, char **argv, int *argc) {
    //Split the input command string into arguments for execution.
    *argc = 0; 
    char *token = strtok(buf, " "); 
    while (token != NULL && *argc < BUFSIZE - 1) {
        argv[(*argc)++] = token; // Store each token as an argument
        token = strtok(NULL, " "); 
    }
    argv[*argc] = NULL; 
}

void exec_command(char *buf, ssize_t size_command){
    //Execute the command entered.
    int pid, status; 
    buf [size_command-1] = '\0'; 
    char *argv[BUFSIZE];
    int argc;
    long msPerSecond = 1000;
    long nsPerMillisecond = 1000000;


    //Attempt at question 7 incorrect.
    /* int fd_in = -1, fd_out = -1;
    char ** new_buf = (char**)malloc(20* sizeof(char*)); 
    int j=0; */

    cut_command(buf, argv, &argc);
    struct timespec start, end;
    get_start_time(&start);

    //Q7
    /*if (strcmp("exit", buf) == 0 || size_command == 0) {
    write(1, "en revoir", strlen("en revoir"));
    exit(EXIT_FAILURE);
}

for (int i = 0; argv[i] != NULL; i++) { 
    if (strcmp(argv[i], "<") == 0) {
        fd_in = open(argv[++i], O_RDONLY);
        if (fd_in < 0) {
            perror("Erreur open file");
            return;
        }
    }
    else if (strcmp(argv[i], ">") == 0) {  
        fd_out = open(argv[++i], O_WRONLY | O_CREAT | O_TRUNC, 0644); 
        if (fd_out < 0) {
            perror("Erreur open file");
            return;
        } else {
            new_buf[j++] = argv[1];
        }
    }
}*/
    pid = fork(); 
  
    if (pid<0){ // If fork fails
         perror("Fork Error");
         exit(EXIT_FAILURE);
    }
    if (pid == 0){
        // This is the child process where the command is executed.
       
        //To put the program in sleep and allow killing the child with a signal, this will then return sign instead of exit
        //printf("%d \n", getpid());
        //sleep(80);
      

        //execlp(buf, buf,(char*) NULL);
        execvp(argv[0], argv); //execvp allows passing multiple arguments to the command.
        perror("Unknown command");
        exit(EXIT_FAILURE);

    }
    else { //parent process
        wait(&status);

        //Q7
        /* if(fd_in != -1){
            dup2(fd_in, STDIN_FILENO); // le descripteur est dupliqué sur l'entrée
            close(fd_in);
        }

        if (fd_out != -1){
            dup2(fd_out, STDOUT_FILENO); // le descripteur est dupliqué sur la sortie
            close(fd_out);
        } */
        //execvp (argv[0], argv);
       // exit (EXIT_FAILURE);

        get_end_time(&end);

        long duration = (end.tv_sec - start.tv_sec) * msPerSecond +
                        (end.tv_nsec - start.tv_nsec) / nsPerMillisecond;

        if (WIFEXITED(status)) {  // If the child process exited normally
            int exit_code = WEXITSTATUS(status);
            printf("enseash [exit:%d|%d ms] %% \n", exit_code, duration);
        } else if (WIFSIGNALED(status)) { // If the child process was terminated by a signal
            int signal_code = WTERMSIG(status);
            printf("enseash [sign:%d|%d ms] %% \n", signal_code, duration);
        }
        //free(new_buf);
        fflush(stdout);
}
}

int main(){
    print_message(); 
    char buf[BUFSIZE]; 
    ssize_t size_command; 
    while(1){
            write(STDOUT_FILENO, prompt, strlen(prompt));
            size_command = read(STDOUT_FILENO, buf, BUFSIZE);
            exec_command(buf, size_command);

            // If the user types "exit" or presses Ctrl+D --> exit the shell
            if(strcmp("exit",buf)==0 || size_command == 0){
                write(1, "Bye bye... \n ", strlen( "Bye bye... \n "));
                exit(EXIT_FAILURE);
                             }
    }
}






