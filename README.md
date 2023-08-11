# minishell
Writing a shell

PSEUDOCODIGO

    Main:  
            -Inicializar
                cambiar las señales -> haciendo una global para saber si hay algun proceso en ejecucion
                inicializacion de cosas (structs y eso)

            -Bucle infinito:
                -Leer linea -> char *
                -parsear(char *) -> struct
                -ejecutar(struct) -> int (codigo de ultimo programa ejecutado)


    Caracteres especiales son : << >> < > | $ -

    Parsear:   in: char *       out: struct

            - Recorremos el comando
            - Guardamos el string en su sitio activando las flags correspondientes en la estructura principal:
                -Reconocer que es el string (<, << , $var) y coger sus datos correspondientes (si los tiene)
                    -Hasta que no encuentras un caracter especial, sigue siendo el mismo comando
                -Guardarlo en su sitio en la estructura con los datos necesarios (si te lllega <, guardar el siguiente string que será el archivo)
            -Rellenar las estructura con cosas que no se pueden sacar del string directamente (el path por ejemplo)

    
    Ejectuar:   in: struc       out: int

            -Diferenciaria ejecución simple o pipex
            -Llama a pipex si hace falta -> funcion pipex()
            -Single command