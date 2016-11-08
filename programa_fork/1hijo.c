#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int a=5;
	int b=3;

	pid_t pid;
	pid_t pid_hijo_terminado;

	pid = fork();
	if(pid == -1)
	{
		fprintf(stderr, "Error en la creación del hijo.\n");
		exit(-1); 
	}
	if (pid == 0)//Bloque de ejecución del proceso hijo
	{
		fprintf(stdout, "Hola, soy el hijo y mi pid es: %d\n", getpid());
		sleep(2);
	}
	else //Bloque de ejecución del padre
	{

		fprintf(stdout, "Hola, soy el padre y mi pid es: %d\n", getppid());
		fprintf(stdout, "Esperando a que termine el hijo...\n");
		pid_hijo_terminado = wait( NULL);
		fprintf (stdout, "El hijo terminó %d\n", pid_hijo_terminado);
	}

	return 0;
}