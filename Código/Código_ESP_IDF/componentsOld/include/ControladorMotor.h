/*float VoltajeAGrados(adc1_channel_t channel,float *grados);*/
int  MoverMotorPorTiempo(int milisegundos,int sentidoDeGiro,float cicloDeTrabajo);
bool MoverMotorAGrados(int gradosDeseados,float cicloDeTrabajo);
void FrenarMotor();
void MoverSentidoGiro(float cicloDeTrabajo, int sentidoDeGiro);
void ConfPinEntrada ();