/*La función get the next line devuelve la primera línea de un file descriptor cada vez que se llama, si
la usamos repetidamente como por ejemplo en un bucle, podremos leer un archivo completo línea por línea.
Para hacer esta función el procedimiento será: leer el fd y guardarlo en nuestro buffer, guardar en una
variable la primera línea del buffer (será la que devolveremos), y por último borrar del buffer la línea
que acabamos de leer. Para el buffer usaremos una variable estática ya que se necesita conservar su
contenido entre llamadas sucesivas a la función, si no fuese estático el buffer se inicializaría cuando
se vuelva a llamar a la función, perdiendo así la parte del archivo ya leído. También haremos uso del
salto de línea '\n' porque es la manera de saber que la línea ha acabado, pero tenemos que tener en cuenta
que también forma parte de la línea.*/

#include "get_next_line.h"

/*Función que actualiza el buffer: guarda el buffer recortado (quita la línea leída) en una nueva reserva
y libera la anterior reserva del buffer*/
static char	*ft_delete_line(char *buffer)
{
//creamos un iterador i y un buffer nuevo que será para actualizar el que tenemos
	int		i;
	char	*update_buffer;

//hacemos el mismo procedimiento que en 'ft_return_line' para calcular desde donde del buffer va a guardar
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
//con ft_substr copia en update_buffer el buffer desde i hasta la longitud del buffer original - el tamaño
//de la línea leída (reservada con malloc)
	update_buffer = ft_substr(buffer, i, (ft_strlen(buffer) - i));
	if (!update_buffer)
		return (NULL);
//libera el buffer anterior
	free(buffer);
//y devuelve el buffer ya actualizado, convirtiendo el buffer en él en la función 'get_next_line'
	return (update_buffer);
}

/*Esta función te devuelve solo una línea, sirve para hacer el return de get_next_line*/
static char	*ft_return_line(char *buffer)
{
//crea las variables "line" para guardar la línea e "i" para iterar el
	char	*line;
	int		i;

//itera i para calcular el tamaño de la línea y con él poder hacer la reserva de memoria de line, usamos
//el carácter nulo y el de salto de línea como delimitador para saber cuando acaba la línea, entonces si
//después de haber contado encuentra uno detrás guarda un espacio más para él
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
//ft_substr crea una string reservada con malloc con el tamaño i + 1 y copia en ella el contenido de buffer
//desde el índice 0 (desde el inicio) hasta i
	line = ft_substr(buffer, 0, i);
//devuelve la línea con el contenido de la primera línea del buffer
	return (line);
}

/*Esta función lee el contenido del fd línea por línea y la guarda en el buffer usando un buffer temporal
que libera al terminar (cada vez que es llamada lee 1 línea)*/
static char	*ft_buff_read(int fd, char *buffer)
{
//creamos un contador que funcionará según read, que devuelve la cantidad de bytes leídos o -1 si hay
//algún error). y un buffer temporal para pasar del fd al buffer original
	int		cont;
	char	*temp_buff;

//reservamos memoria para el buffer temporal con el tamaño del BUFFER_SIZE + carácter nulo
	temp_buff = malloc(BUFFER_SIZE + 1);
	if (!temp_buff)
		return (NULL);
//si el buffer no está inicializado (como sería al principio) le reserva memoria y lo inicializa
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
//inicializamos el contador a 1 para que pueda entrar en el bucle, dentro se modificará su valor
	cont = 1;
//bucle para guardar lo que read lee del fd en el buffer temporal durante BUFFER_SIZE (lo que sea, como
//si es carracter por caracter), hasta que encuentre que ha guardado un salto de línea o hasta que llegue
//al final del archivo y no lea nada (entonces read devolverá 0)
	while (!ft_strchr(buffer, '\n') && cont > 0)
	{
		cont = read(fd, temp_buff, BUFFER_SIZE);
//control de errores: si read devuelve -1 => error
		if (cont == -1)
		{
			free(buffer);
			free(temp_buff);
			return (NULL);
		}
//le añade carácter nulo al buffer temporal para que sea una string válida y se pueda concatenar
		temp_buff[cont] = '\0';
//se almacena en el buffer original lo que ya había en el buffer (si había algo) y lo que acaba de leer
//que se guarda en el buffer temporal (ft_strjoin_free además hace free a su primer parámetro al terminar)
		buffer = ft_strjoin_free(buffer, temp_buff);
	}
//al salir del bucle libera el buffer temporal
	free(temp_buff)
//y retorna el buffer que tendrá la línea leída
	return (buffer);
}

/*Esta es la función general donde se hacen las llamadas a las demás funciones*/
char	*get_next_line(int fd)
{
//se crean la variables estática buffer y la variable que devuelve get_next_line "line_read"
	static char	*buffer;
	char		*line_read;

//control de errores: fd o BUFFER_SIZE no pueden no ser válidos
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
//función que lee desde el fd y lo guarda en la variable buffer
	buffer = ft_buff_read(fd, buffer);
//control de errores: buffer nulo
	if (!buffer)
		return (NULL);
//función que devuelva una única línea
	line_read = ft_return_line(buffer);
//control de errores: line_read empieza por carácter nulo
	if (line_read[0] == '\0')
	{
		free(buffer);
		free(line_read);
		buffer = NULL;
		return (NULL);
	}
//función que elimine del buffer las líneas que ya han sido escritas
	buffer = ft_delete_line(buffer);
//por último devuelve una sola línea leída
	return (line_read);
}

/*Hacemos un main para comprobar el funcionamiento de el código: abrimos con open el fd con la flag O_RDONLY
y guardamos en text la línea leída. con un bucle hasta que que text deje de existir (cuando se acabe el fd)
imprime line_read, libera text y guarda en text la siguiente line_read (o si no existe, sale del bucle). y
por último cierra el fd*/
// int	main(void)
// {
// 	int		fd;
// 	char	*text;

// 	fd = open("prueba.txt", O_RDONLY);
// 	text = get_next_line(fd);
// 	while (text)
// 	{
// 		printf("%s", text);
// 		free(text);
// 		text = get_next_line(fd);
// 	}
// 	close(fd);
// 	return(0);
// }
