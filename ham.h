#ifndef __ham_h__
#define __ham_h__

#include "mygba.h"

// Типы для работы с тайлами и картами
typedef void* tile_info_ptr;
typedef void* map_info_ptr;

// Структура для фонового слоя
struct ham_bg_t {
    tile_info_ptr ti;
    map_info_ptr mi;
};

// Глобальные переменные
extern ham_bg_t ham_bg[4];

// Функции инициализации
void ham_Init();
void ham_StartIntHandler(int type, void* func);
void ham_SetBgMode(int mode);
void ham_LoadBGPal(void* data, int bytes);
map_info_ptr ham_InitMapEmptySet(int type, int size);
tile_info_ptr ham_InitTileEmptySet(int size, int type, int count);

#endif // __ham_h__ 