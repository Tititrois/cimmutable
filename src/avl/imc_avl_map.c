#include "imc_avl_map.h"
#include <stdlib.h>
#include <stdio.h>

imc_avl_map_t* imc_avl_map_create(int (*comparator)(imc_key_t*, imc_key_t*)){
    imc_avl_map_t* map = malloc(sizeof(imc_avl_map_t));
    map->comparator = comparator;
    map->tree = NULL;
    return map;
}

int imc_avl_map_size(imc_avl_map_t* map){
    return imc_avl_size(map->tree);
}

imc_avl_map_t* imc_avl_map_update(imc_avl_map_t* map,
            imc_key_t* key,
            imc_data_t* data,
            imc_data_t** prev_data){
    imc_avl_map_t* new_map = imc_avl_map_create(map->comparator);
    new_map->tree = imc_avl_insert(map->tree, data, key,
                                   map->comparator, prev_data);
    return new_map;
}

imc_data_t* imc_avl_map_lookup(imc_avl_map_t* map,
            imc_key_t* key){
    return imc_avl_lookup(map->tree, key,map->comparator);
}

imc_avl_map_t* imc_avl_map_remove(imc_avl_map_t* map,
                                  imc_key_t* key,
                                imc_data_t** data){
    imc_avl_map_t* new_map = imc_avl_map_create(map->comparator);
    new_map->tree = imc_avl_remove(map->tree, key, map->comparator, data);
    return new_map;
}

imc_key_t** imc_avl_map_keys(imc_avl_map_t* map){
    int indice = 0;
    int size = imc_avl_map_size(map);
    imc_key_t** tab = malloc(sizeof(imc_key_t*)*size);
    imc_avl_keys(map->tree, tab, &indice);
    return tab;
}

imc_avl_map_t* imc_avl_map_merge(imc_avl_map_t* src_map,
                                 imc_avl_map_t* merged_map){
    if(src_map == NULL){
        return merged_map;
    }
    if(merged_map == NULL){
        return src_map;
    }
    if(src_map->comparator != merged_map->comparator){
        fprintf(stderr,
                "Can't merge two maps with different comparator functions.\n");
        return NULL;
    }
    imc_avl_map_t* new_map = imc_avl_map_create(src_map->comparator);
    new_map->tree = imc_avl_merge(src_map->tree, merged_map->tree,
                                  src_map->comparator);
    return new_map;
}

//----------------------------------------------------------------------------//
//----------------------------Iterator functions------------------------------//
//----------------------------------------------------------------------------//
imc_avl_map_iterator_t* imc_avl_map_iterator_init() {
    return malloc(sizeof(imc_avl_map_iterator_t));
}

void imc_avl_map_iterator_destroy(imc_avl_map_iterator_t* iter) {
    return free(iter);
}

int imc_avl_map_iterate_rec(imc_avl_node_t* tree, imc_avl_map_iterator_t *iter,
                            int (*comparator)(imc_key_t*, imc_key_t*)){
    if(tree == NULL){
        return 0;
    }
    if(iter->current_data == NULL && iter->current_key == NULL){
        while(tree->left != NULL){
            tree = tree->left;
        }
        iter->current_key = tree->key;
        iter->current_data = tree->data;
        return 1;
    }
    int diff =comparator(tree->key, iter->current_key);
    if (diff > 0){
            if(! imc_avl_map_iterate_rec(tree->left,iter,comparator)){
                iter->current_data = tree->data;
                iter->current_key = tree->key;
            }
            return 1;
    } else {
        if(diff == 0){
            iter->current_data = NULL;
            iter->current_key = NULL;
        }
        return imc_avl_map_iterate_rec(tree->right,iter,comparator);
    }
    return 0;
}

void imc_avl_map_iterate(imc_avl_map_t* map, imc_avl_map_iterator_t *iter){
    if(iter == NULL){
        return;
    }
    if( ! imc_avl_map_iterate_rec(map->tree, iter, map->comparator)){
        iter->current_data = NULL;
        iter->current_key = NULL;
    }
}

/* user-side memory management */

int imc_avl_map_unref(imc_avl_map_t* map){
    imc_avl_unref(map->tree);
    free(map);
    return 1;
}


void imc_avl_map_dump_rec(imc_avl_node_t* tree,
                          void (*print_key)(imc_key_t*),
                          void (*print_data)(imc_data_t*)){
    if (tree != NULL) {
        imc_avl_map_dump_rec(tree->left, print_key, print_data);
        printf(" (");
        print_key(tree->key);
        printf(" : ");
        print_data(tree->data);
        printf(") ");
        imc_avl_map_dump_rec(tree->right, print_key, print_data);
    }

}

void imc_avl_map_dump(imc_avl_map_t* map,
                      void (*print_key)(imc_key_t*),
                      void (*print_data)(imc_data_t*)){
    printf("[");
    imc_avl_map_dump_rec(map->tree, print_key, print_data);
    printf("]\n");
}
