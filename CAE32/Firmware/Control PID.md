# Control PID
El controlador PID permitirá un control estable para apuntar a los grados deseados.

A grandes rasgos será una función que tome de entrada los grados actuales, aplique una ecuación y retorna una variable con la cual se podrá variar la velocidad del motor DC
>Ejemplo :
>Cuando se acerquen los grados actuales a los grados deseados, este disminuirá el ciclo de trabajo PWM(se puede interpretar como que disminuye la velocidad) y no sobrepasara los grados deseados

