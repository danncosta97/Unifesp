#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int getqtd(char **str, int size){
    int i=0,k=0,j=size;
    printf(">>here<<");
    for(i=1;i<size;i++){ //desconsidera primeiro arg, arquivo
        printf("%s",str[i]);
    }
    for(i=1;i<size;i++){ //desconsidera primeiro arg, arquivo
        if(strcmp(str[i],"|")==0) k++;
    }
    printf("##%d##",k);
    return k;
}


char **getcom (char **str, int qtdarg){
    int i=1, j=0, k=0;
    char **com=(char**)malloc(50*sizeof(char*));
    char *buffer=(char*)malloc(50*sizeof(char));


    while(i<qtdarg){
        if((strcmp(str[i],"|")!=0) && (i!=qtdarg)){
            printf("\n&&%d %d&&\n",i,qtdarg);
            strcat(buffer,str[i]);
            strcat(buffer," ");
        }
        else{
            printf("OO%sOO",buffer);
            com[k]=buffer;
            printf("@@%s@@",com[k]);
            buffer[0] = '\0';
            memset(buffer,0,strlen(buffer));
            k++;
        }
        if(i+1==qtdarg){
            printf("OO%sOO",buffer);
            printf("@@%s@@",com[k-1]);
        }
        i++;
    }
    return com;
}

int get_pipe_pos(char **argv) {
	int i=0;
	while (argv[i]) {
		if (*argv[i] == '|') return i;
		i++;
	}
	return -1;
}

void print_matcommand(char **command){
	int i=0;
	while(command[i]) {
		printf("%s\n", command[i]);
		i++;
	}
}

int pipe_it(char **com1, char **com2){
    int fd[2];
    if (pipe(fd) < 0){
		perror("pipe");
		return -1;
	}
    pid_t filho1, filho2;
    filho1 = fork();

    printf("%s",com1[0]);

	if (filho1 == 0) { // filho1 executa comando 1
		close(fd[0]); //nao vai ler no pipe
		dup2(fd[1], STDOUT_FILENO); // duplica saida padrao do filho 1 para escrita do pipe
		if (execvp(com1[0], com1) < 0) {
			perror("execvp filho1");
			return -1;
		}
	} else if (filho1 > 0) { // pai shell p/ filho 1
		close(fd[1]); // pai nao vai escrever
		waitpid(filho1, NULL, 0);
	}

	filho2 = fork();
	if (filho2 == 0) { // filho2 executa comando 2
		close(fd[1]); // nao vai escrever no pipe
		dup2(fd[0], STDIN_FILENO); //duplica leitura do pipe sobre entrada padrao
		if (execvp(com2[0], com2) < 0){
			perror("execvp filho2");
			return -1;
		}
	} else if (filho2 > 0) { // pai shell p/ filho 2
		close(fd[0]); // pai nao vai ler
		waitpid(filho2, NULL, 0);
	}
	return 0;
}

int main(int argc, char **argv){
	if (argc == 1) {
		printf("Uso: %s <comando1> <parametros> ... '|' <comando2> <parametros> ... \n", argv[0]);
		return 0;
	}
	int n,i=0,k=0,l=0;
    int qtd=getqtd(argv, argc);;




	char **command, **com1, **com2;
	pid_t filho1, filho2;

    //printf("sadaonfsfdo");
   // for(i=1;i<argc;i++){ //desconsidera primeiro arg, arquivo
    //    printf("%s\n",argv[i]);
    //}

	command = &argv[1];
	n = get_pipe_pos(command);
	if (n == -1) return 0;


    printf("&&%d&&",qtd);

    //command=getcom(argv,argc);

    //printf("\n%s",command[0]);

    i=0;
    k=0;
    while(k<qtd){

        if(i==0){
            com1 = &command[0];
            printf("%s",com1[0]);
            while(strcmp(command[i],"|")!=0){
              i++;
            }
            command[i]=NULL;
            com2 = &command[i+1];
        }
        else{
           /* l=i;
            com1=&command[l+1];
            printf("%s", com1[0]);
            while(strcmp(command[i],"|")!=0){
                i++;
            }
            command[i]=NULL;
            com2 = &command[i+1];
            printf("%s", com2[0]);*/
        }
        pipe_it(com1,com2);
        k++;
    }

	return 0;
}
