// search for a device with the name of "Cae32"
#include <gtk/gtk.h>
#include <poll.h>
#include <stdbool.h>
#include <stdint.h>
typedef struct Device {
  int fd;
  char path[50];
  bool isHID;
  bool found;
  guint32 version;
  guint8 axis;
  guint8 buttons;
} Device;

typedef struct gainDevice {
  float acelerator;
  float clutch;
  float brake;
} gainDevice;
typedef struct forthread {
  Device *device;
  struct pollfd *pfd;
} forthread;
int typeDevice(int fd, char name[60], Device *cae, bool isHID);
int searchHIDDevice(Device *cae, bool DeviceType);
void showDevInfo(Device *cae);

// void searchDevice(gpointer *data);
int searchDevice(Device *cae);
void *initpoll(Device *cae);
