Pasos:
Instalar python y variables de sistema.
Instalar pip y variables de sistema.
Instalar Pygame.
Instalar (C) MinGW y variables de sistema.
Instalar Visualstudiocode

Instalar Python:

    Visita el sitio web oficial de Python en https://www.python.org/downloads/.

    Haz clic en el botón "Descargar Python" en la sección "Python Releases for Windows".

    En la página de descargas, desplázate hacia abajo hasta la sección "Python Releases for Windows" y selecciona la versión más reciente de Python que sea compatible con tu sistema operativo (por ejemplo, Python 3.9.7).

    Después de seleccionar la versión de Python, desplázate hacia abajo y elige el instalador adecuado para tu sistema operativo. Si estás utilizando una versión de 64 bits de Windows, selecciona el instalador de 64 bits. Si tienes una versión de 32 bits, selecciona el instalador de 32 bits.

    Haz clic en el enlace de descarga para iniciar la descarga del instalador de Python.

    Una vez que se haya descargado el instalador, ábrelo y marca la casilla "Agregar Python x.x al PATH" en la ventana de configuración. Esto permitirá que puedas acceder a Python desde cualquier ubicación en la línea de comandos.

    Sigue las instrucciones del instalador y completa el proceso de instalación de Python.

    Después de la instalación, puedes verificar si Python se instaló correctamente abriendo una ventana de línea de comandos y escribiendo "python --version". Deberías ver la versión instalada de Python.

Instalar PIP:
Abre una ventana de línea de comandos en tu sistema. Puedes hacerlo presionando la tecla de Windows + R, escribiendo "cmd" en el cuadro de diálogo Ejecutar y luego presionando Enter.

En la ventana de línea de comandos, escribe el siguiente comando y presiona Enter para asegurarte de que Python esté correctamente instalado y disponible en la ruta:

python --version

Debería mostrarte la versión de Python que has instalado.

Después de confirmar que Python está instalado, cierra la ventana de línea de comandos.

Abre el navegador web y visita https://bootstrap.pypa.io/get-pip.py. Este es el script de instalación de pip.

Haz clic derecho en la página y selecciona "Guardar como" para descargar el archivo get-pip.py en tu computadora. Asegúrate de recordar la ubicación donde guardas el archivo.

Abre una ventana de línea de comandos nuevamente.

Navega a la ubicación donde guardaste el archivo get-pip.py utilizando el comando cd (change directory). Por ejemplo, si lo guardaste en tu escritorio, escribe el siguiente comando y presiona Enter:

cd C:\Users\TuUsuario\Desktop

Una vez que te encuentres en el directorio correcto, ejecuta el siguiente comando para instalar pip:

python get-pip.py

Esto ejecutará el script de instalación de pip y comenzará el proceso de instalación.

Espera a que la instalación se complete. Verás un mensaje en la línea de comandos indicando que pip se ha instalado correctamente.

Para verificar que pip se haya instalado correctamente, escribe el siguiente comando y presiona Enter:

    pip --version

    Deberías ver la versión de pip instalada en tu sistema.

¡Listo! Ahora tienes pip instalado en tu sistema junto con Python. Puedes usar pip para instalar paquetes y bibliotecas adicionales de Python en tu entorno.

Variable de sistema pip:
Para agregar pip como una variable de sistema en Windows, sigue los siguientes pasos:

    Abre el menú Inicio y busca "Variables de entorno" en la barra de búsqueda. Selecciona la opción "Editar las variables de entorno del sistema" que aparece en los resultados.

    En la ventana "Propiedades del sistema" que se abre, haz clic en el botón "Variables de entorno".

    En la sección "Variables del sistema", selecciona la variable "Path" y haz clic en el botón "Editar".

    En la ventana "Editar variable del sistema", haz clic en el botón "Nuevo".

    Escribe la siguiente ruta en el campo de valor de la nueva variable:

C:\PythonXX\Scripts

Asegúrate de reemplazar "XX" con la versión específica de Python que tienes instalada. Por ejemplo, si tienes Python 3.9 instalado, la ruta sería:

    C:\Python39\Scripts

    Esta ruta apunta a la carpeta "Scripts" dentro de la instalación de Python, donde se encuentra el ejecutable de pip.

    Haz clic en "Aceptar" en todas las ventanas abiertas para guardar los cambios.

Después de completar estos pasos, pip estará disponible como un comando de sistema en cualquier ubicación de la línea de comandos. Esto te permitirá ejecutar pip desde cualquier directorio sin tener que especificar la ruta completa.

Recuerda reiniciar tu computadora para que los cambios surtan efecto.


Instalar MinGW (compilador C):

    Visita el sitio web oficial de MinGW en http://www.mingw.org/.

    En la página de descargas, busca y haz clic en el enlace "Downloads".

    En la sección "Current Release", busca el instalador de "mingw-get-setup.exe" y haz clic en el enlace para descargarlo.

    Una vez que se haya descargado el instalador de MinGW, ábrelo y sigue las instrucciones del instalador para completar la instalación.

    Durante el proceso de instalación, se te pedirá que selecciones los componentes que deseas instalar. Asegúrate de seleccionar al menos los siguientes componentes:
        mingw32-base
        mingw32-gcc-g++
        msys-base

    Continúa siguiendo las instrucciones del instalador y completa el proceso de instalación de MinGW.

    Después de la instalación, verifica si MinGW se instaló correctamente abriendo una ventana de línea de comandos y escribiendo "gcc --version". Deberías ver la versión instalada del compilador C.

MinGW variables del sistema:

    Abre el Explorador de archivos en tu sistema.

    Navega hasta la ubicación donde se instaló MinGW. Por defecto, la ruta de instalación es "C:\MinGW", pero si elegiste una ruta de instalación diferente, navega a esa ubicación.

    En la carpeta de instalación de MinGW, busca la subcarpeta llamada "bin". La ruta completa de la carpeta sería "C:\MinGW\bin".

    Copia la ruta completa de la carpeta "bin" de MinGW.

    Busca "Variables de entorno" en la barra de búsqueda de Windows y selecciona la opción "Editar las variables de entorno del sistema" que aparece en los resultados.

    En la ventana "Propiedades del sistema" que se abre, haz clic en el botón "Variables de entorno".

    En la sección "Variables del sistema", selecciona la variable "Path" y haz clic en el botón "Editar".

    En la ventana "Editar variable del sistema", haz clic en el botón "Nuevo".

    Pega la ruta completa de la carpeta "bin" de MinGW que copiaste anteriormente en el campo de valor de la nueva variable. Asegúrate de que la ruta esté separada por punto y coma (;) de otras rutas existentes si las hay.

    Haz clic en "Aceptar" en todas las ventanas abiertas para guardar los cambios.

Después de completar estos pasos, la carpeta "MinGW/bin" se agregará a la variable PATH del sistema. Esto permitirá que puedas acceder a los ejecutables de MinGW (como gcc, g++, etc.) desde cualquier ubicación en la línea de comandos.

Recuerda reiniciar tu computadora para que los cambios surtan efecto.


Instalar Pygame:
Abre una ventana de línea de comandos en tu sistema. Puedes hacerlo presionando la tecla de Windows + R, escribiendo "cmd" en el cuadro de diálogo Ejecutar y luego presionando Enter.

Para instalar pygame, ejecuta el siguiente comando:

pip install pygame

Esto descargará e instalará la biblioteca pygame en tu entorno de Python.


extra:

Tutorial para agregar(En general) variables del sistema(PATH):

    Busca "Variables de entorno" en la barra de búsqueda de Windows y selecciona la opción "Editar las variables de entorno del sistema" que aparece en los resultados.

    En la ventana "Propiedades del sistema" que se abre, haz clic en el botón "Variables de entorno".

    En la sección "Variables del sistema", selecciona la variable "Path" y haz clic en el botón "Editar".

    En la ventana "Editar variable del sistema", haz clic en el botón "Nuevo".

    Escribe la ruta de la carpeta que deseas agregar a la variable PATH. Por ejemplo, si quieres agregar la carpeta "C:\MiCarpeta" a la variable PATH, escribe "C:\MiCarpeta" y haz clic en "Aceptar".

    Haz clic en "Aceptar" en todas las ventanas abiertas para guardar los cambios.

Después de completar estos pasos, la carpeta que has agregado se incluirá en la variable PATH del sistema. Esto permitirá que puedas ejecutar comandos y acceder a programas ubicados en esa carpeta desde cualquier ubicación en tu sistema. Recuerda reiniciar tu computadora para que los cambios surtan efecto.

PASO FINAL:
Instalar visualstudio code
abrir la carpeta del proyecto
instalar todos los paquetes que VS te recomienda (reiniciar vs si es necesario)
Abrir nuevo terminal en VS:
Ctrl + shift + ñ
Compilar un exe para el archivo c:
gcc main.c hashmap.c -o exe.exe   
correr el archivo exe:
(puedes arrastar el .exe a un terminal)
c:\Users\tuuser\rutaDeTuProyecto\exe.exe
Abrir nuevo terminal en VS:
Ctrl + shift + ñ
abrir el main.py:
python main.py

LISTOOOO!
AL EMPEZAR EL .EXE (QUE SE DEBE HACER PRIMERO), SE DEBEN CREAR JUGADOR Y ENEMIGO DESDE CONSOLA PORQUE FALTAN LAS FUNCIONES DE IMPORATR DESDE CSV.
	
Asegurarse se emepzar el main.py con el estado.txt en "nombre", se actualiza en tiempo real, asi que si se equivocaron o estan testeando cosas pueden cambiar archivo por otro estado [bonfire,nombre,mapa,combate] para ver el estado, pero este solo será funcional si se llama desde c.

Faltan cmabiar varios imprimir en c por sprintf(buffer,...
y agregar despues el printArchivo(buffer)
esto permite la comunicacion de consola desde python.

AUN NO ESTA IMPLEMENTADO LA FUNCIONALIDAD DE LOS BOTONES, TODO SE HACE POR CONSOLA AUN.