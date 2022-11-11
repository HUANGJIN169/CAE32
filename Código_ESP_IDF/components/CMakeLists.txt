set(component_srcs "src/Encoders.c" "src/Errores.c" "src/Marchas.c" "src/ComunicacionUSB.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "include" "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver" "esp_adc"
                       REQUIRES "")