# FreeRtos
Para controlar el tiempo de ejecución de cada función es necesario usar FreeRtos, ya que se pueden crear tareas **(_Tasks_)** de manera periódicas además de añadirles un nivel de prioridad a cada una de estas.

**Nota:** Otra manera de manejar el orden de ejecución de funciones, es por medio de interrupciones, **Ejemplo:** se asigna una interrupción cuando se sobrecarga un temporizador **_(Timer)_**  para poder ejecutar una función sería algo equivalente a las tareas periódicas  .

## Las tareas que deben ejecutarse son las siguientes
1. Obtención del valor a enviar, en este caso los grados, pero para obtener mas precisión se usara el valor directo del ADC debido a abarca un rango mas amplio 0->4095 **8Bits** pero se puede aumentar hasta **11Bits**, mientras que los grados 0->360
2. Envió de la trama de datos por protocolo USB 
3. Recepción de datos para aplicar un feedback al volante
4. Aplicar el control PID al motor, con los datos recién recibidos 

|Número de tarea|Características|
|--|--|
|1|Debe de ejecutarse 4 veces consecutivamente cada cierto periodo de tiempo|
|2,3,4|Tarea periódica para tener un dispositivo sincrónico|

