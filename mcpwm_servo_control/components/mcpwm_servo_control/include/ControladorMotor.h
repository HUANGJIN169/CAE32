/*float VoltajeAGrados(adc1_channel_t channel,float *grados);*/
int MoverMotorPorTiempo(int milisegundos,bool sentidoDeGiro,float cicloDeTrabajo);
bool MoverMotorAGrados(int gradosDeseados,float cicloDeTrabajo);
void FrenarMotor();
void MoverSentidoHorario(float cicloDeTrabajo);
void MoverSentidoAntihorario(float cicloDeTrabajo);
void ConfPinEntrada ();