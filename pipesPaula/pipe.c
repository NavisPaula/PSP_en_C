#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int fd[2]; //Pipe
	char buffer[20];
	pid_t pid;
	int retorno;

	retorno = pipe(fd);//creo el pipe

	if(retorno == -1)
	{
		fprintf(stderr, "Error en el pipe\n");
		exit(-1);
	}

	pid = fork();

	switch(pid)
	{
		case -1:
				fprintf(stderr, "Error en el fork\n");
				exit(-1);
			break;
		case 0: //proceso hijo
				fprintf(stdout, "Soy el hijo\n");
				//el buffer leera hasta que encunetre un \0
				char mensaje1[] ="Hola, soy tu hijo.\0";
				char mensaje2[] = "¿Que tal?\0";
				//se escribe siempre en fd 1. y se lee en fd 0, siempre
				write(fd[1], mensaje1, (strlen(mensaje1)+1)*sizeof(char));
				fprintf(stdout, "Enviando mensaje 1\n");
				write(fd[1], mensaje2, (strlen(mensaje2)+1)*sizeof(char));
				fprintf(stdout, "Enviando mensaje 2\n");

			break;
		default: //proceso padre
				fprintf (stdout, "Soy el padre\n");
				sleep(2);
				//se escribe siempre en fd 1 y se lee en fd 0, siempre
				read(fd[0], &buffer, sizeof(buffer));
				fprintf(stdout, "%s\n", buffer);
				//wait(NULL);
			break;

	}

	return 0;
}