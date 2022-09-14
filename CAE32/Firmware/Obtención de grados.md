# Obtención de grados
### El encoder magnético ofrece 3 maneras de obtener el ángulo
* Comunicación i2c leyendo dos registros
* Variación de voltaje en el pin OUT proporcional al ángulo **Se usará esta opción**
* Variación de ciclo de trabajo en cada pulso que es proporcional al ángulo
### Para usar estas opciones es necesario realizar una configuración por medio de comunicación i2c
**Nota:** Es posible programarlo solo usando el pin OUT pero la configuración es casi nula

### Para obtener mas información de este encoder aquí esta la [hoja de datos del AS5600](https://datasheet.lcsc.com/lcsc/2004071505_AMS-AS5600-ASOT_C499458.pdf) 

## Proceso de configuración
La configuración para esta aplicación depende del movimiento de los pedales, normalmente no excede los **360°** (mas de una vuelta) de rotación, así que para aprovechar la mayor resolución (el valor obtenido se acercara mas al real) hay que usar solo el rango de grados necesario en este caso **260°** 

|N. Paso|Instrucciones|
|--|--|
|1|Seguir los pasos para limitar el rango máximo del angulo como se muestra [aquí](https://datasheet.lcsc.com/lcsc/2004071505_AMS-AS5600-ASOT_C499458.pdf#page=24) con un valor 2958 -> 1Bit **0B** 2Bit **8E** , estos valores se obtiene con esta [regla de 3](https://datasheet.lcsc.com/lcsc/2004071505_AMS-AS5600-ASOT_C499458.pdf#page=24)| 
|2|Seguir los pasos para elegir la posición inicial y final como se muestra [aquí](https://datasheet.lcsc.com/lcsc/2004071505_AMS-AS5600-ASOT_C499458.pdf#page=22)|
|3|Guardar la configuración permanente usando el el paso de BURN_ANGLE, mostrado en las referencias externas mostradas en los pasos anteriores|
|4|Los valores cargados para el registro CONF son: salida analógica en un rango de 10% a 90%, aunque todavía se podría mejorar la precisión haciendo unos cambios|

**Notas:** 
1. Este proceso se hace por medio de la comunicación i2c.
2. El paso numero 2 se puede hacer de dos maneras.
* Manualmente, moviendo el indicador a la parte inicial y final, en el arranque del ESP-32 presionando un botón 
* Automáticamente, usando el motor para que por un tiempo definido se mueva hasta un tope en la zona inicial, cambie de sentido y tope con la zona final 
3. El imán siempre debe de estar presente, de lo contrario no se guardaran los datos
4. Se elige un rango 10% a 90% por que el ADC del ESP-32 no puede leer voltaje menor a 0.1 V , además se usa un divisor de voltaje para disminuir el rango de voltaje superior y sea posible medir.
## Después de la configuración
**Conozco dos maneras de obtener los grados**
1. Usar interrupciones con ayuda de un timer para hacer la conversión de voltaje a grados y usar ese valor como entrada para el controlador PID
2. Usar FreeRtos y asignar como tarea,hacer la conversión de voltaje a grados para el PID
## [Aplicación de controlador PID](Control%20PID.md)
## [Uso de FreeRtos](Uso%20de%20FreeRtos.md)







