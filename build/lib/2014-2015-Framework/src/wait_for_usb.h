#ifndef WAIT_FOR_USB
#define WAIT_FOR_USB

#ifdef __cplusplus

#include <cstdlib>

extern "C" {
#endif

bool wait_for_usb(const char* filename);

#ifdef __cplusplus
}
#endif

#endif
