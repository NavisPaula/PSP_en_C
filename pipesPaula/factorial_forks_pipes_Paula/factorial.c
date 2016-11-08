#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int fd[2]; //declaramos le pipe
	int retorno;
	unsigned long long int resultado = 1;
	unsigned long long int resultado_hijo;
	int objetivo = atoi(argv[1]);
	int medio_objetivo;
	pid_t pid;

	if (argc != 2)
	{
		fprintf(stderr, "El número de parámetros tiene que ser 1\n");
	}
	if (objetivo>20)
	{
		fprintf(stderr, "El número es demasiado grande. Máx: 20\n");
	}

	retorno = pipe(fd);
	if (retorno == -1)
	{
		fprintf(stderr, "Error en el pipe\n");
		exit(-1);
	}

	medio_objetivo=objetivo/2;
	pid=fork();
	switch(pid)
	{
		case -1:
				fprintf(stderr, "Error en el fork\n");
				exit(-1);
			break;
		case 0: //proceso hijo. Parte alta del factorial
				for(int i=objetivo; i>medio_objetivo; i--)
				{
					resultado = resultado * i;
				}
				fprintf(stdout, "Hijo: A mi me ha salido %llu\n", resultado );
				//Enviar resultado
				write(fd[1], &resultado, sizeof(unsigned long long int));
			break;
		default: //proceso padre. Parte baja del factorial
				for(int i=medio_objetivo; i>0; i--)
				{
					resultado = resultado * i;
				}
				fprintf(stdout, "Padre: A mi me ha salido %llu\n", resultado );
				//Esperar resultado.
				read(fd[0], &resultado_hijo, sizeof(unsigned long long int));
				//Multiplicar los diferentes resultados
				wait(NULL);
				resultado=resultado*resultado_hijo;
				fprintf(stdout, "EL factorial de %d es: %llu\n", objetivo, resultado);
			break;
	}

	return 0;
}