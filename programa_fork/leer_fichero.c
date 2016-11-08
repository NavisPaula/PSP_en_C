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
	ssize_t bytes_leidos=1;

	if (argc != 2)
	{
		fprintf(stderr, "El uso del programa es incorrecto,\n");
		fprintf(stderr, "Su suo es %s archivo.ext\n", argv[0]);
		exit(-1);
	}

	fichero = open(argv[1], O_RDONLY);
	if (fichero == -1)
	{
		fprintf(stderr, "La apertura ha fallado\n");
		exit(-1);
	}

	while(bytes_leidos !=0)
	{
		bytes_leidos = read(fichero, &buffer, 3*sizeof(char));
		fprintf(stdout, "%s\n", buffer);
	}

	close (fichero);

	return 0;
}