
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	double op1, op2;
	double resultado;
	pid_t pid=0;

	if(argc != 3)
	{
		fprintf(stderr, "El número de argumentos del programa no es correcto.\n");
		exit(-1);
	}
	op1 = atof(argv[1]);
	op2 = atof(argv[2]);

	pid= fork(); //primer hijo

	if(pid==-1) // si ha fallado el primer hijo
	{
		fprintf(stderr, "Error en el fork. 1\n");
		exit(-1);
	}

	if (pid==0) // si es el hijo primero
	{
		resultado= op1+op2;
		fprintf(stdout,"Soy el huijo que suma (%d). El resultado es: %f\n", pid, resultado);
	}
	else // si es el padre
	{
		pid = fork(); //segundo hijo
		if (pid==-1)// si ha fallado el segundo hijo
		{
			fprintf(stderr, "Error en el fork. 2\n");
			exit(-1);
		}
		if (pid==0) // si es el hijo segundo
		{
			resultado= op1-op2;
			fprintf(stdout,"Soy el hijo que resta (%d). El resultado es: %f\n", pid, resultado);
		}
		else // si es el padre
		{
			pid = fork(); //tercer hijo
			if (pid==-1) // si ha fallado el tercer hijo
			{
				fprintf(stderr, "Error en el fork. 3\n");
				exit(-1);
			}
			if (pid==0) // si es el hijo tercero
			{
				resultado= op1*op2;
				fprintf(stdout,"Soy el hijo que multiplica (%d). El resultado es: %f\n", pid, resultado);
			}
			else // si es el padre
			{
				pid = fork(); //cuarto hijo
				if (pid==-1) // si ha fallado el cuarto hijo
				{
					fprintf(stderr, "Error en el fork. 4\n");
					exit(-1);
				}
				if (pid==0) // si es el hijo cuarto
				{
					resultado= op1/op2;
					fprintf(stdout,"Soy el hijo que divide (%d).El resultado es: %f\n", pid, resultado);
				}
				else // si es el padre
				{
					//finalización de los hijos
					pid = wait(NULL);
					fprintf(stdout, "El hijo %d ha terminado.\n", pid);
					pid = wait(NULL);
					fprintf(stdout, "El hijo %d ha terminado.\n", pid);
					pid = wait(NULL);
					fprintf(stdout, "El hijo %d ha terminado.\n", pid);
					pid = wait(NULL);
					fprintf(stdout, "El hijo %d ha terminado.\n", pid);
				}
			}
		}
	}
}