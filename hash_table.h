//
// Created by salmane on 12/22/25.
//

#ifndef INC_16_BIT_COMPUTER_SIMULATOR_HASH_TABLE_H
#define INC_16_BIT_COMPUTER_SIMULATOR_HASH_TABLE_H
#include <stdint.h>

typedef struct
{
    uint16_t* key;
    uint16_t* value;
}ht_item;
typedef struct
{
    int size;
    int count;
    ht_item** items;
}ht_hash_table;
#endif //INC_16_BIT_COMPUTER_SIMULATOR_HASH_TABLE_H