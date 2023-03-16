# Compilación del firmware
Para compilar el proyecto es necesario tener el siguiente paquete

**En debian**
```sh
sudo apt install gcc-arm-none-eabi
```

Ahora es el momento de crear el binario (archivo.elf)

```sh
cd Debug
make all
```

