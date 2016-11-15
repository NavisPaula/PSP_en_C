#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int segundos;

void controlar_senal (int cod_senal)
{
	switch(cod_senal)
	{
		case SIGINT:
				fprintf(stdout, "Hola\n");
			break;
		case SIGTSTP:
				fprintf(stdout, "Adios\n");
			break;
		case SIGALRM:
				system("clear");
				segundos++;
				fprintf(stderr, "%.2d:%.2d\n", segundos/60, segundos%60);
			break;
		case SIGKILL:
				fprintf(stderr, "Adios, muero\n");
			break;
	}
}

int main(int argc, char const *argv[])
{
	signal(SIGINT, controlar_senal);
	signal(SIGTSTP, controlar_senal);
	signal(SIGALRM, controlar_senal);
	signal(SIGKILL, controlar_senal);
	while(1){
		alarm(1);
		pause();
	}
	return 0;
}