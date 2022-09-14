# Descripción general para simular el movimiento de pedales
* El objetivo de realizar este componente(indicador de grados) es para hacer pruebas automatizadas. Haciendo una simulación de los movimientos realizados a la hora de conducir
* Con una retroalimentación tanto como física como digital (Mostrando los valores en la terminal)
* Ademas en el futuro este mismo componente se podría usar para mostrar las revoluciones del motor o velocidad, en general el estado de alguna características del auto
## Pasos para simular "pedales" 

### 1. Configurar el encoder magnético (AS5600) que se encarga de obtener el angulo del iman 
- Este encoder se programa por medio de comunicación i2c para leer y escribir a diferentes registros
- Requiere de mover el indicador manualmente al angulo mínimo y máximo
### 2. Constantemente convertir el valor analógico a grados para conocer su posición
- Es necesario que siempre se este ejecutando una tarea que este revisando los grados actuales y compararlos con los grados deseados
### 3. Controlar el motor DC
- Como el motor simulara el movimiento, por ejemplo, el del un volante, este tiene que girar en un sentido o en el otro, con diferentes velocidades y cambios repentinos de sentido de giro
- Se puede aplicar un control PID

## [Materiales necesarios para crear este componente](Hardware%20componentes%20eléctricos/Indicador%20de%20grados.md)
## [Obtención de grados](../Firmware/Obtención%20de%20grados.md)





