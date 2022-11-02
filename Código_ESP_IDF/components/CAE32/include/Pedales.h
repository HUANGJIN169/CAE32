//<<<<<<<<<<<Atención estos son  valores temporales>>>>>>>>>>//
#define PIN_PRIMERA     12
#define PIN_SEGUNDA     11
#define PIN_TERCERA     10
#define PIN_CUARTA      9
#define PIN_QUINTA      8
#define PIN_SEXTA     7
//***********************************************************//


typedef struct Encoder {
    int ResolucionBits;
    char TPedal;
    int &ValorBrutoADC;
    int &ValorMapeado;
    int Error;
    int Canal;
    int Giro;
    int ValorInicial;
    int ValorFinal;
    unsigned int PinActivacion;
}Pedal;


unsigned int caja[6]={ PIN_PRIMERA, PIN_SEGUNDA, PIN_TERCERA,PIN_CUARTA, PIN_QUINTA, PIN_SEXTA };
