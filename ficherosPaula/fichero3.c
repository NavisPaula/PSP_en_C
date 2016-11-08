#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int fd;
	char mensaje[]="Hola clase";
	int char_escritos=1;
	int longitud;

	fd = open("./fich2.txt", O_WRONLY | O_TRUNC);

	if (fd == -1)
	{
		fprintf(stderr, "Error!!\n");
		exit(-1);
	}

	longitud = strlen(mensaje);
	while (char_escriots !=0)
	{
		char_escritos = write(fd, mensaje,longitud*sizeof(char));
		longitud= longitud - char_escritos;
	}
	
	close(fd);

	return 0;
}
