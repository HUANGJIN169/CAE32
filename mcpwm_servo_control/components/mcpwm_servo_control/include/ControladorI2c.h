esp_err_t i2c_lectura(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
void i2c_escritura(uint8_t addr,uint8_t reg_addr,uint8_t data);
void RutinaDeConfiguracionManual(void);
void RutinaDeConfiguracionAutomatica();
void ConfiguracionMaxAng();
void LeerRawAngle();
void EscribirTramaDeDatosAEncoder(uint8_t reg_addr0,uint8_t reg_addr1,uint8_t dato0,uint8_t dato1);
