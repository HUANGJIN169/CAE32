# CAE32

CAE32 es un proyecto de construcción y desarrollo de todas las etapas de un volante para videojuegos de PC,
para el sistema operativo de Linux.

## Las etapas son:

* Diseño PCB (Placa principal)
* Firmware
* Driver (Kernel module)
* Configuración y calibración por medio de una interfaz de usuario (GTK-3)
* Diseño de mecanismos para pedales, palanca de cambios y volante
* Diseño PCB de potencia para el control del motor de retroalimentación (FFB)

## Descripción detallada

### Sensores

**Nota:** Aún no se elige el número de pieza.

* IC de efecto hall para los pedales
* IC de efecto hall para el volante como el AS5600 
* Interruptores para la palanca de cambios

### Microcontroladores

Como microcontrolador principal he elegido el **ESP32-S3** en conjunto con un microcontrolador secundario,
será alguno de la familia **STMF0**, esto para reducir de alguna forma la carga al ESP32, manipulando señales.

### Firmware

Estoy usando el framework de Espressif (ESP-IDF) en conjunto con FreeRtos

Aún no inicio con el desarrollo en el microcontrolador STM

### Interfaz de usuario

La interfaz está desarrollada con el framework (GTK 3), esta permitirá hacer configuraciones, como por ejemplo:

* Visualización de los datos gráficamente y textual (consola)
* Tipo de transmisión (Manual, Automática, Secuencial, custom) **De forma nativa**
* Límites de los pedales, sensibilidad 
* Tipo de pedal
	* Entrada analógica (Potenciómetro, efecto hall)
	* Entrada SPI,I2c (Célula de carga)
* Actualización de firmware

Diseño de interfaz hasta el momento.

**Para compilar el proyecto las instruciones las puedes encontrar [aquí](InterfazGráfica/README.md)**

![interfaz](InterfazGráfica/Previa.png)
