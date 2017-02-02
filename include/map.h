
#ifndef _MAP_H
#define _MAP_H

typedef imc_map_t;
typedef imc_key_t;
typedef imc_data_t;

// Q: how to bind the real implementation ?
imc_map_t* imc_map_create();

int imc_map_size(imc_map_t* map);

imc_map_t* imc_map_update(imc_map_t* map,
            imc_key_t* key,
            imc_data_t* data);

imc_data_t* imc_map_lookup(imc_map_t* map,
            imc_key_t* key);

imc_map_t* imc_map_remove(imc_map_t* map,
            imc_key_t* key,
            imc_data_t** data);

imc_key_t*[] imc_map_keys(imc_map_t* map);

// iterator ?
typedef imc_map_iterator_t;

void imc_map_iterate(imc_map_t* map,
            imc_map_iterator_t *iter);

/* user-side memory management */

int imc_map_unref(imc_map_t* map);

void imc_map_dump(imc_map_t* map);

#endif
