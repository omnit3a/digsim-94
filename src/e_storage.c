// e_storage.c
// handles saving of player data such as highscores
// 
// 
// created: 19/12/2025

// standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// external libraries
#include <raylib.h>

// internal headers
#include <e_storage.h>

bool e_storage_save_value (uint32_t position, int value) {
  bool success = false;
  int data_size = 0;
  uint32_t new_data_size = 0;
  uint8_t * file_data = LoadFileData(STORAGE_DATA_FILE, &data_size);
  uint8_t * new_file_data = NULL;

  if (file_data != NULL) {
    if (data_size <= (position * sizeof(int))) {
      new_data_size = (position + 1) * sizeof(int);
      new_file_data = (uint8_t *) RL_REALLOC(file_data, new_data_size);
      
      if (new_file_data != NULL) {
	int * data_ptr = (int *) new_file_data;
	data_ptr[position] = value;
      } else {
	TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", STORAGE_DATA_FILE, data_size, position * sizeof(int));
	
	new_file_data = file_data;
	new_data_size = data_size;
      }
    } else {
      new_file_data = file_data;
      new_data_size = data_size;
      int * data_ptr = (int *) new_file_data;
      data_ptr[position] = value;
    }

    success = SaveFileData(STORAGE_DATA_FILE, new_file_data, new_data_size);
    RL_FREE(new_file_data);

    TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);    
  } else {
    TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", STORAGE_DATA_FILE);

    data_size = (position + 1) * sizeof(int);
    file_data = (uint8_t *) RL_MALLOC(data_size);
    int * data_ptr = (int *) file_data;
    data_ptr[position] = value;

    success = SaveFileData(STORAGE_DATA_FILE, file_data, data_size);
    UnloadFileData(file_data);

    TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
  }

  return success;
}

int e_storage_load_value (uint32_t position) {
  int value = 0;
  int data_size = 0;
  uint8_t * file_data = LoadFileData(STORAGE_DATA_FILE, &data_size);

  if (file_data != NULL) {
    if (data_size < ((int) (position * 4))) {
      TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
    } else {
      int * data_ptr = (int *) file_data;
      value = data_ptr[position];
    }

    UnloadFileData(file_data);

    TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
  }

  return value;
}
