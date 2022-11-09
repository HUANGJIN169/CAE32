
/*Definición de pines de activacion de los encoders
 int PIN_ENABLE_ACELERADOR=12;
 int PIN_ENABLE_FRENO=14;
 int PIN_ENABLE_CLUTCH=26;
 int PIN_ENABLE_VOLANTE=27;
*/


struct Encoder
{
  int ResolucionBits;		  /*Valor necesario para obtener el valor mapeado */
  char TPedal[1];		      /*Variable para identificar el pedal, Ejemplo: A=Acelerador F=Freno, C=Clutch */
  int ValorBrutoADC;		  /*Aquí se almacena la lectura bruta del pin que */
  int ValorMapeado;		    /*Aquí se almacena el valor el cual se concatenara con la trama que se enviara al bus de datos USB */
  int Error;			        /*Se guarda el error para que sea verificado y reportado al kernel */
  int PinADC;			        /*Pin que se usa para la lectura analogica */
  int Giro;			          /*>>>>>ESTE VALOR SOLO SE USA EN EL VOLANTE, PARA INDENTIFICAR EN CUANTOS GIROS DE 360° SE HAN REALIZADO<<<<< */
  int ValorInicial;		    
  int ValorFinal;		      /*Valores para identificar el tope físico de cada pedal aka:Hardlock*/  
  int PinActivacion;	    /*Pin para activar y desactivar cada encoder para evitar choques en el bus ADC */
  int CanalADC;           /*El canal corresponde a un pin y se mostrara en la terminal al ejecutar InicializacionCanalADC*/
  int GradosDeGiro;       /*Corresponde a la configuración de los grados maximos de giro*/
};


extern struct Encoder *ptr_acelerador;
extern struct Encoder *ptr_freno;
extern struct Encoder *ptr_clutch;
extern struct Encoder *ptr_volante;


//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>
void imprimirValoresEncoder(struct Encoder *Pedal);
void IniciarAsignacionMemoria();
void InicializacionCanalADC (struct Encoder *Pedal1); 
void InicializacionPedalesVolante();
//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<GPIO>>>>>>>>>>>>>>>>>>>
void IniciarPines();
void ActivarODesactivarEncoder(struct Encoder *Pedal,unsigned char estado); //Habilita o desabilita la comunicación con un encoder
//void ActivarODesactivarEncoder(struct Encoder *Pedal,uint8_t estado); //Habilita o desabilita la comunicación con un encoder
//<<<<<<<<<<<<<<<<<<<GPIO>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<i2c>>>>>>>>>>>>>>>>>>>>
void LeerEstadoAS5600 (struct Encoder *Pedal);    /*Lee los registros del encoder relacionados a la posición del imán y si exiten carga un valor a la estructura Encoder*/
void i2c_Master_Inicio();
//<<<<<<<<<<<<<<<<<<<i2c>>>>>>>>>>>>>>>>>>>>





/*----------------------------Tareas a ejecutar constantemente--------------------------------*/
//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>
void LeerValorBrutoADC (struct Encoder *Pedal);
void CalcularValorMapeado(struct Encoder *Pedal);
//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>
/*---------------------------------------------------------------------------------------------------------*/
