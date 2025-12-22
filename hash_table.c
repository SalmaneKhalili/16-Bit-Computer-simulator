//
// Created by salmane on 12/22/25.
//

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

static ht_item* ht_new_item(const char* k, const u_int16_t v)
{
    ht_item* item = malloc(sizeof(ht_item));
    item-> key = strdup(k);
    item->value =v;
    return item;

}
