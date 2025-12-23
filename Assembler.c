//
// Created by salmane on 12/22/25.
//

#define HT_PRIME_1 155
#define HT_PRIME_2 161
#define SYMBOL_TABLE_SIZE 10007
#include "Assembler.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static ht_item* ht_new_item(const char* k, const u_int16_t v);
ht_hash_table* ht_new();
static void ht_del_item(ht_item* item);
void ht_del_hash_table(ht_hash_table* table);
static int ht_hash(const char* key, const int prime, const int size);
static int ht_get_hash(const char* key, const int num_buckets, const int attempt);
void ht_insert(ht_hash_table* ht, const char* key, const u_int16_t value);
ht_item* ht_search(ht_hash_table* ht, const char* key);

int main()
{


}

static ht_item* ht_new_item(const char* k, const u_int16_t v)
{
    ht_item* item = malloc(sizeof(ht_item));
    item->key = strdup(k);
    item->value =v;
    return item;

}

ht_hash_table* ht_new()
{
    ht_hash_table* table = malloc(sizeof(ht_hash_table));
    table->size = SYMBOL_TABLE_SIZE;
    table->count = 0;
    table->items = calloc((size_t) table->size, sizeof(ht_item*));
    return table;
}

static void ht_del_item(ht_item* item)
{
    free(item->key);
    free(item);
}

void ht_del_hash_table(ht_hash_table* table)
{
    for (int i = 0; i < table->size; i++)
    {
        ht_item* item = table->items[i];
        if (item != NULL)
        {
            ht_del_item(item);
        }
    }
    free(table->items);
    free(table);
}

static int ht_hash(const char* key, const int prime, const int size) {
    long hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * prime + key[i]) % size;
    }
    return (int)hash;
}

static int ht_get_hash(const char* key, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(key, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(key, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_hash_table* ht, const char* key, const u_int16_t value) {
    int i = 0;
    int index;
    ht_item* cur_item;
    do {
        index = ht_get_hash(key, ht->size, i++);
        cur_item = ht->items[index];


        //update
        if (cur_item != NULL && strcmp(cur_item->key, key) == 0) {
            cur_item->value = value;
            return;
        }
    } while (cur_item != NULL);

    ht->items[index] = ht_new_item(key, value);
    ht->count++;
}

ht_item* ht_search(ht_hash_table* ht, const char* key)
{
    int index = ht_get_hash(key,ht->size,0);
    ht_item* item= ht->items[index];
    int i = 1;
    while (item != NULL)
    {
        if (strcmp(item->key,key)==0)
        {
            return item;
        }
        index = ht_get_hash(key,ht->size,i);
        item = ht->items[index];
        i++;
    }
    return item;
}


