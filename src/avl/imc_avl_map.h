#ifndef IMC_AVL_MAP
#define IMC_AVL_MAP

#include "imc_avl.h"

//----------------------------------------------------------------------------//
//----------------------------Data Structure----------------------------------//
//----------------------------------------------------------------------------//
typdef struct imc_avl_map_t{
    imc_avl_node_t* tree;
    //TODO may need a comparator function
} imc_avl_map_t;


//----------------------------------------------------------------------------//
//----------------------------Map functions-----------------------------------//
//----------------------------------------------------------------------------//
imc_avl_map_t* imc_avl_map_create();

int imc_avl_map_size(imc_avl_map_t* map);

imc_avl_map_t* imc_avl_map_update(imc_avl_map_t* map,
            imc_key_t* key,
            imc_data_t* data);

imc_data_t* imc_avl_map_lookup(imc_avl_map_t* map,
            imc_key_t* key);

imc_avl_map_t* imc_avl_map_remove(imc_avl_map_t* map,
            imc_key_t* key,
            imc_data_t** data);

imc_key_t*[] imc_avl_map_keys(imc_avl_map_t* map);

// iterator ?
typedef imc_avl_map_iterator_t;

void imc_avl_map_iterate(imc_avl_map_t* map,
            imc_avl_map_iterator_t *iter);

/* user-side memory management */

int imc_avl_map_unref(imc_avl_map_t* map);

void imc_avl_map_dump(imc_avl_map_t* map);

#endif
