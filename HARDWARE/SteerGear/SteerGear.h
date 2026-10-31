#ifndef STEER_GEAR_H
#define STEER_GEAR_H

#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif

void SteerGear_Init(void);
void SteerGear_SetPosition(uint8_t position);

#ifdef __cplusplus
}
#endif

#endif
