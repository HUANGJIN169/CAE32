// search for a device with the name of "Cae32"
#include <stdint.h>
int get_device();

typedef struct Device {

  int fd;
  int shifter;
  int brake;
  int acelerator;
  int steering;
  int clutch;
  uint8_t axis;
  uint8_t buttons;
} Device;
