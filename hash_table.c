//
// Created by salmane on 12/22/25.
//

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

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

    table->size = 53;
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


