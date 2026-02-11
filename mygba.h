#ifndef MYGBA_H
#define MYGBA_H

// Базовые определения для Android
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Определения для SDL
#include <SDL2/SDL.h>

// Базовые типы
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

// Макросы для работы с памятью
#define MEM_EWRAM 0x02000000
#define MEM_IWRAM 0x03000000
#define MEM_IO 0x04000000
#define MEM_PAL 0x05000000
#define MEM_VRAM 0x06000000
#define MEM_OAM 0x07000000
#define MEM_ROM 0x08000000

// Определения для Android
#ifndef ANDROID
#define ANDROID
#endif
#define USING_SDL
#define USE_VIRTUAL_SCREEN
#define HAS_DISKIO
#define HAS_STYLUS
#define HAS_PRINTF

#ifdef iPOWDER
#define USE_VIRTUAL_SCREEN
#define USE_EXTENDED_HEIGHT
#endif

#ifdef ANDROID
#define USE_VIRTUAL_SCREEN
#endif

// Not all SDL systems have the keyboard.
#if !defined(iPOWDER) && !defined(ANDROID)
#define HAS_KEYBOARD
#endif

#ifdef LINUX
#define stricmp(a, b) strcasecmp(a, b)
#endif

#ifdef _WIN32_WCE
char *strdup(const char *s);
#define stricmp _stricmp
#endif

// #define STRESS_TEST

#define INT_TYPE_VBL		0
#define INT_TYPE_HBL		1

#define WIN_BG0 0x01
#define WIN_BG1 0x02
#define WIN_BG2 0x04
#define WIN_BG3 0x08
#define WIN_OBJ 0x10

#include <memory.h>

#include "hamfake.h"

#endif // MYGBA_H 
