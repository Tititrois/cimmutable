#ifndef IMC_AVL_MAP
#define IMC_AVL_MAP

#include "imc_avl.h"


//----------------------------------------------------------------------------//
//----------------------------Data Structure----------------------------------//
//----------------------------------------------------------------------------//
typedef struct imc_avl_map_t{
    imc_avl_node_t* tree;
    int (*comparator)(imc_key_t*, imc_key_t*);
} imc_avl_map_t;


//----------------------------------------------------------------------------//
//----------------------------Map functions-----------------------------------//
//----------------------------------------------------------------------------//
imc_avl_map_t* imc_avl_map_create(int (*comparator)(imc_key_t*, imc_key_t*));

int imc_avl_map_size(imc_avl_map_t* map);

imc_avl_map_t* imc_avl_map_update(imc_avl_map_t* map,
            imc_key_t* key,
            imc_data_t* data,
            imc_data_t** prev_data);

imc_data_t* imc_avl_map_lookup(imc_avl_map_t* map,
            imc_key_t* key);

imc_avl_map_t* imc_avl_map_remove(imc_avl_map_t* map,
            imc_key_t* key,
            imc_data_t** data);

imc_key_t** imc_avl_map_keys(imc_avl_map_t* map);

imc_avl_map_t* imc_avl_map_merge(imc_avl_map_t* src_map,
                                 imc_avl_map_t* merged_map);
// iterator
typedef struct imc_avl_map_iterator_t {
    imc_key_t* current_key;
    imc_data_t* current_data;
} imc_avl_map_iterator_t;

imc_avl_map_iterator_t* imc_avl_map_iterator_init();

void imc_avl_map_iterator_destroy(imc_avl_map_iterator_t* iter);

void imc_avl_map_iterate(imc_avl_map_t* map,
            imc_avl_map_iterator_t *iter);

/* user-side memory management */

int imc_avl_map_unref(imc_avl_map_t* map);

void imc_avl_map_dump(imc_avl_map_t* map,
					  void (*print_key)(imc_key_t*),
					  void (*print_data)(imc_data_t*));


#endif
