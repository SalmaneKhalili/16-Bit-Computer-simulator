//
// Created by salmane on 12/22/25.
//

#ifndef INC_16_BIT_COMPUTER_SIMULATOR_HASH_TABLE_H
#define INC_16_BIT_COMPUTER_SIMULATOR_HASH_TABLE_H
#include <stdint.h>
#include <sys/types.h>

typedef struct
{
    char* key;
    uint16_t value;
}ht_item;

typedef struct
{
    int base_size;
    int size;
    int count;
    ht_item** items;
}ht_hash_table;

void ht_insert(ht_hash_table* ht, const char* key, const u_int16_t value);
ht_item* ht_search(ht_hash_table* ht, const char* key);



#endif //INC_16_BIT_COMPUTER_SIMULATOR_HASH_TABLE_H