set(component_srcs "src/ConfADC.c" "src/ConfMCPWM.c" "src/ConfI2c.c" "src/ControladorAngulo.c" "src/ControladorI2c.c" "src/ControladorMotor.c" "src/Usb.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "include" "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver"
                       REQUIRES "")