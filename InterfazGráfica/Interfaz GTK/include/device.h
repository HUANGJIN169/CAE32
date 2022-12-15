// search for a device with the name of "Cae32"
#include <stdbool.h>
#include <stdint.h>
typedef struct Device {

  int fd;
  int shifter;
  int brake;
  int acelerator;
  int steering;
  int clutch;
  bool isHID;
  bool found;
  uint8_t version;
  uint8_t axis;
  uint8_t buttons;
} Device;

typedef struct gainDevice {
  float acelerator;
  float clutch;
  float brake;
} gainDevice;
int typeDevice(int fd, char name[60], Device *cae, bool isHID);
int searchHIDDevice(const char *path, Device *cae, bool DeviceType);
void showDevInfo(Device *cae);
