/*
INTEGRANTES:
Ana Julia de Oliveira Bellini  				RA 111.774
Natalia Araujo dos Reis  					RA 112.247
Willian Dihanster Gomes de Oliveira  		RA 112.269
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <sys/wait.h>

#define CMD_LEN 256

/*GERAR MATRIZ DE ARGUMENTOS*/
char **get_matcmd(char *str_cmd, const char *separador, int *cont_cmd) {
	int i = 0;
	char *str_cmd_aux = (char *) malloc ((strlen(str_cmd)) * sizeof(char));
    char **matriz_cmd = (char **) malloc (4096 * sizeof(char *)); // matriz de argumentos
    char *tk = NULL;

    strcpy(str_cmd_aux, str_cmd);
    tk = strtok(str_cmd_aux, separador); // separar comandos para montar matriz

    if (tk == NULL) printf("Erro: String Nula");

    while (tk != NULL) {
        *cont_cmd = *cont_cmd + 1; // contar comandos
       	matriz_cmd[i] = tk; // matriz recebe parte do comando
       	tk = strtok(NULL, separador);
       	i++;
    }

    return matriz_cmd;
}

/*COMANDOS SIMPLES*/
void executaComandoSimples(char **cmd_exec) {
	pid_t pid = fork();

	// erro
	if (pid == -1) {
		printf("\nErro de Fork");
		return;
	}

	// processo filho, executa
	else if (pid == 0) {
		if (execvp(cmd_exec[0], cmd_exec) < 0) printf("\nErro de Execução");
		exit(0);
	}

	// processo pai, espera o filho
	else {
		wait(NULL);
		return;
	}
}

/*ANALISAR SE COMANDO DIGITADO POSSUI PIPE*/
int temPipe(char *str_cmd, char **str_pipe) {
	int i;

	for (i = 0; i < 2; i++) {
		str_pipe[i] = strsep(&str_cmd, "|"); // separar comandos, na presença do pipe
		if (str_pipe[i] == NULL)
			break;
	}

	if (str_pipe[1] == NULL) return 0; // não possui pipe
	else return 1; // possui pipe
}

/*COMANDOS COMPOSTOS (COM PIPE)*/
void executaComandoComPipe(char **cmd_1, char **cmd_2) {
    int fd[2]; // vetor para pipe
    pid_t pid1, pid2; // identificador dos processos para cada comando

    // erro
    if (pipe(fd) < 0) {
        printf("\nErro de Pipe");
        return;
    }

    pid1 = fork(); // criar processo para comando antes do pipe

    // erro no processo 1
    if (pid1 < 0) {
        printf("\nErro de Fork (Comando 1)");
        return;
    }

    if (pid1 == 0) {
        close(fd[0]); // fechar escrita do pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]); // fechar leitura do pipe

        // execução do comando antes do pipe
        if (execvp(cmd_1[0], cmd_1) < 0) {
            printf("\nErro de Execução (Comando 1)");
            exit(0);
        }
    }

    else {
        pid2 = fork(); // criar processo para comando depois do pipe

        // erro no processo 2
        if (pid2 < 0) {
            printf("\nErro de Fork (Comando 2)");
            return;
        }

        if (pid2 == 0) {
            close(fd[1]); // fechar leitura do pipe
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]); // fechar escrita do pipe

            // execução do comando depois do pipe
            if (execvp(cmd_2[0], cmd_2) < 0) {
                printf("\nErro de Execução (Comando 2)");
                exit(0);
            }
        }

        else {
            wait(NULL); // esperar processos terminarem
        }
    }
}

/*FUNÇÃO PRINCIPAL*/
int main (int argc, char const *argv[]) {
	char str_cmd[CMD_LEN], str_cmd_aux[CMD_LEN];
	char **str_argv, **str_argv_pipe;
	char *str_pipe[2];
	int i = 0, cont_cmd = 0;

	bzero(str_cmd, CMD_LEN);

	while (1) {
		printf("<comando> ");
		fgets(str_cmd, CMD_LEN, stdin); // leitura do comando no teclado
		strcpy(str_cmd_aux, str_cmd);

		if (strcmp(str_cmd, "Exit\n") == 0) break; // encerrar programa se usuário entrar com "Exit"

		// comando simples
		if (!temPipe(str_cmd_aux, str_pipe)) {
			str_argv = get_matcmd(str_cmd, " ", &cont_cmd); // matriz de argumentos

			if (cont_cmd > 2) strcpy(str_argv[2], str_argv[1]);
			else str_argv[1] = NULL;

			executaComandoSimples(str_argv);

		}

		// comando composto (com pipe)
		else {
			str_argv = get_matcmd(str_pipe[0], " ", &cont_cmd); // criar matriz para comando antes do pipe
	 		str_argv_pipe = get_matcmd(str_pipe[1], " ", &cont_cmd); // criar matriz para comando depois do pipe

	 		str_argv[2] = NULL;
	 		str_argv_pipe[2] = NULL;

			executaComandoComPipe(str_argv, str_argv_pipe);
		}

		cont_cmd = 0;
	}

	return 0;
}
