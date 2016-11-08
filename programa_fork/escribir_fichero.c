#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int fichero;
	char buffer[3];
	ssize_t bytes_escritos=1;

	if (argc != 3)
	{
		fprintf(stderr, "El uso del programa es incorrecto,\n");
		fprintf(stderr, "Su uso es %s archivo.ext texto a escribir\n", argv[0]);
		exit(-1);
	}

	fichero = open(argv[1], O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG);
	if (fichero == -1)
	{
		fprintf(stderr, "La apertura ha fallado\n");
		exit(-1);
	}

	bytes_escritos = write(fichero, argv[2], 3*sizeof(char));

	close (fichero);

	return 0;
}