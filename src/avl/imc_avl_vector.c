#include "imc_avl_vector.h"
#include <stdlib.h>
#include <stdio.h>


int int_comparator(imc_key_t *first_key, imc_key_t* second_key){
    if(first_key > second_key){
        return 1;
    }
    return first_key < second_key ? -1 : 0 ;
}

/*void print3 (int* nb, char* b)
{
    sprintf(b, "(%03d)", nb);
}*/


/* stack operations */
imc_vector_avl_t* imc_vector_avl_create(){
    imc_vector_avl_t * vect = malloc(sizeof(imc_vector_avl_t));
    vect->tree = NULL;
    vect->last_value = -1;
    return vect;
}

int imc_vector_avl_size(imc_vector_avl_t* vec){
    return vec->last_value + 1;
}

imc_vector_avl_t* imc_vector_avl_update(imc_vector_avl_t* vec, int index,
                                        imc_data_t* data){
    imc_vector_avl_t *new_version = malloc(sizeof(imc_vector_avl_t));
    imc_data_t *prev_data=NULL;
    new_version->tree = imc_avl_insert(vec->tree, data, index,
                                       &int_comparator, &prev_data);
    new_version->last_value = index > vec->last_value ? index : vec->last_value;

    return new_version;
}

imc_data_t* imc_vector_avl_lookup(imc_vector_avl_t* vec, int index){
    return imc_avl_lookup(vec->tree, index, int_comparator);
}

// add at the end <--- DOXYGENIZE PLEASE!
imc_vector_avl_t* imc_vector_avl_push(imc_vector_avl_t* vec,
			      imc_data_t* data){
    imc_vector_avl_t *new_version = malloc(sizeof(imc_vector_avl_t));
    imc_data_t *prev_data=NULL;
    new_version->tree = imc_avl_insert(vec->tree, data, vec->last_value+1,
                                       &int_comparator, &prev_data);
    new_version->last_value = vec->last_value+1;

    //imc_avl_dump(new_version->tree, print3);
    return new_version;
}

imc_vector_avl_t* imc_vector_avl_pop(imc_vector_avl_t* vec,
			     imc_data_t** data){
    imc_vector_avl_t *new_version = malloc(sizeof(imc_vector_avl_t));
    new_version->tree = imc_avl_remove(vec->tree, vec->last_value,
                                    &int_comparator, data);
    new_version->last_value = vec->last_value-1;
    return new_version;
}

int imc_vector_avl_split(imc_vector_avl_t* vec_in,
            		     int index,
            		     imc_vector_avl_t** vec_out1,
            		     imc_vector_avl_t** vec_out2){

    if(index<0 || vec_in == NULL || index >= vec_in->last_value){
        return 1;
    }

    imc_avl_node_t* head_tree,* tail_tree;

    if(imc_avl_split(vec_in->tree,index,&head_tree,&tail_tree, &int_comparator) == 1)
        return 1;

    (*vec_out1) = imc_vector_avl_create();
    (*vec_out1)->last_value = index;
    (*vec_out1)->tree = head_tree;

    (*vec_out2) = imc_vector_avl_create();
    (*vec_out2)->last_value = vec_in->last_value - index-1;
    (*vec_out2)->tree = tail_tree;

    return 0;
}

void incr_keys(imc_avl_node_t *tree, int incr_value){
    if(tree == NULL)
        return;
    tree->key += incr_value;
    incr_keys(tree->left,incr_value);
    incr_keys(tree->right,incr_value);
}

imc_vector_avl_t* imc_vector_avl_merge(imc_vector_avl_t* vec_front,
			                           imc_vector_avl_t* vec_tail){
    imc_avl_node_t *copy_tail = imc_avl_copy(vec_tail->tree);
    incr_keys(copy_tail,vec_front->last_value+1);

    imc_vector_avl_t *new_version = imc_vector_avl_create();
    new_version->tree = imc_avl_merge(vec_front->tree,copy_tail,&int_comparator);
    new_version->last_value = vec_front->last_value + vec_tail->last_value +1;

    imc_avl_unref(copy_tail);
    return new_version;
}

/* user-side memory management */

int imc_vector_avl_unref(imc_vector_avl_t* vec){
    imc_avl_unref(vec->tree);
    free(vec);
    return 1;
}



void imc_vector_avl_dump_rec(imc_avl_node_t* tree,
                          void (*print_data)(imc_data_t*)){
    if (tree != NULL) {
        imc_vector_avl_dump_rec(tree->left, print_data);
        printf(" (");
        printf("%d", tree->key);
        printf(" : ");
        print_data(tree->data);
        printf(") ");
        imc_vector_avl_dump_rec(tree->right, print_data);
    }

}




void imc_vector_avl_dump(imc_vector_avl_t* vec,
                      void (*print_data)(imc_data_t*)){
    printf("[");
    imc_vector_avl_dump_rec(vec->tree, print_data);
    printf("]\n");
}
