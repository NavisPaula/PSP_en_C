#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int tuberia;
	char mensaje[]="Hola receptro!\0";
	tuberia = open("./pipe", O_RDWR);
	if(tuberia==-1)
	{
		fprintf(stderr, "Eror en la apertura del pipe\n");
		exit(-1);
	}
	fprintf(stdout, "Enviando mensaje...\n");
	write(tuberia, mensaje, sizeof(char)*(strlen(mensaje)+1));
	fprintf(stderr, "¡Hecho!\n\n");
	close(tuberia);

	return 0;
}