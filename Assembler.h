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

static ht_item* ht_new_item(const char* k, const u_int16_t v);
ht_hash_table* ht_new();
static void ht_del_item(ht_item* item);
void ht_del_hash_table(ht_hash_table* table);
static int ht_hash(const char* key, const int prime, const int size);
static int ht_get_hash(const char* key, const int num_buckets, const int attempt);
void ht_insert(ht_hash_table* ht, const char* key, const u_int16_t value);
ht_item* ht_search(ht_hash_table* ht, const char* key);
int load(u_int16_t* ROM);
uint16_t binary_to_uint16(const char *str);


#endif //INC_16_BIT_COMPUTER_SIMULATOR_HASH_TABLE_H