#ifndef E_STORAGE_H_
#define E_STORAGE_H_

#include <stdint.h>

// defines
#define STORAGE_DATA_FILE "data/storage.data"

typedef enum {
  STORAGE_POSITION_SCORE =      0,
  STORAGE_POSITION_HIGH_SCORE = 1,
} StorageData;

bool e_storage_save_value (uint32_t position, int value);
int e_storage_load_value (uint32_t position);

#endif
