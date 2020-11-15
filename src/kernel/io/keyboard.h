#ifndef _KEYBOARD_MAP_H
#define _KEYBOARD_MAP_H

#include "../../common.h"
#include "video.h"
#include "../interrupt.h"
#include "input.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C

extern BYTE keyboard_map[128];

void keyboard_handler_main(void);

#endif
