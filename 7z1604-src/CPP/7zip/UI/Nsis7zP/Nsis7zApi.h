#ifndef _NSIS7Z_API_H__
#define _NSIS7Z_API_H__
#include <windows.h>
#include <tchar.h>
#include "pluginapi.h"

void Extract7zAndCallBack(HWND hwndParent, int string_size, char *variables, stack_t **stacktop, extra_parameters *extra);

#endif