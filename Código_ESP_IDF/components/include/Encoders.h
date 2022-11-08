
/*Definición de pines de activacion de los encoders*/
#define PIN_ENABLE_ACELERADOR  4
#define PIN_ENABLE_FRENO       5
#define PIN_ENABLE_CLUTCH      6
#define PIN_ENABLE_VOLANTE     7



struct Encoder
{
  int ResolucionBits;		/*Valor necesario para obtener el valor mapeado */
  char TPedal[1];		/*Variable para identificar el pedal, Ejemplo: A=Acelerador F=Freno, C=Clutch */
  int ValorBrutoADC;		/*Aquí se almacena la lectura bruta del pin que */
  int ValorMapeado;		/*Aquí se almacena el valor el cual se concatenara con la trama que se enviara al bus de datos USB */
  int Error;			/*Se guarda el error para que sea verificado y reportado al kernel */
  int PinADC;			/*Pin que se usa para la lectura analogica */
  int Giro;			/*>>>>>ESTE VALOR SOLO SE USA EN EL VOLANTE, PARA INDENTIFICAR EN CUANTOS GIROS DE 360° SE HAN REALIZADO<<<<< */
  int ValorInicial;		//
  int ValorFinal;		//Valores para identificar el tope físico de cada pedal aka:Hardlock  
  int PinActivacion;	/*Pin para activar y desactivar cada encoder para evitar choques en el bus ADC */
  int CanalADC;
  int GradosDeGiro;
};


extern struct Encoder *ptr_acelerador;
extern struct Encoder *ptr_freno;
extern struct Encoder *ptr_clutch;
extern struct Encoder *ptr_volante;


void imprimirValoresEncoder(struct Encoder *Pedal);
void IniciarAsignacionMemoria();
void InicializacionCanalADC (struct Encoder *Pedal1);
void InicializacionPedalesVolante();
void test_en (struct Encoder *lalito);
/*----------------------------Tareas a ejecutar constantemente por Freertos--------------------------------*/
//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>
void LeerValorBrutoADC (struct Encoder *Pedal);
void CalcularValorMapeado(struct Encoder *Pedal);
//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>
/*---------------------------------------------------------------------------------------------------------*/
