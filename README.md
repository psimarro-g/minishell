<h1 align="center">
	minishell
</h1>
<h2 align="center">
	<b><i>Creating a shell in C</i></b><br>
</h2>

<p align="center">
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/psimarro-g/minishell?color=green" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/psimarro-g/minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/psimarro-g/minishell?color=blue" />
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/psimarro-g/minishell?color=lightblue" />
	<img alt="GitHub code lines" src="https://tokei.rs/b1/github/psimarro-g/minishell?branch=parser&color=orange" height="20"/>
</p>

<p align="center">
	Mac OS X 10.15.7 (Darwin Kernel Version 19.6.0)<br>
</p>

<br>


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

<h2 align="center">
	<b><i>Contributors</i></b><br>
</h2>

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table align="center">
  <tbody>
	<td align="center" valign="top" width="14.28%"><a href="https://github.com/psimarro-g"><img src="https://avatars.githubusercontent.com/u/94054765?v=4" width="100px;" alt="Pablo Simarro"/><br /><sub><b>psimarro-g</b></sub></a><br /></td>
	<td align="center" valign="top" width="14.28%"><a href="https://github.com/damontoro"><img src="https://avatars.githubusercontent.com/u/57947618?v=4" width="100px;" alt="David Montoro"/><br /><sub><b>damontoro</b></sub></a><br /></td>
  </tbody>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->
