#ifndef _VECTOR_H
#define _VECTOR_H

#include "../src/rrb_vect.h"

typedef struct imc_rrb_vector {
    int max_depth;
    int m;
    imc_intern_t* root;
} imc_rrb_vector_t;

typedef imc_vector_t;
typedef imc_data_t;

imc_vector_t* imc_vector_create();

int imc_vector_size(imc_vector_t* vec);

imc_vector_t* imc_vector_update(imc_vector_t* vec,
                int index,
                imc_data_t* data);

imc_data_t* imc_vector_lookup(imc_vector_t* vec,
                int index);

/* stack operations */

// add at the end <--- DOXYGENIZE PLEASE!
imc_vector_t* imc_vector_push(imc_vector_t* vec,
                imc_data_t* data);

imc_vector_t* imc_vector_pop(imc_vector_t* vec,
                imc_data_t** data);

int imc_vector_split(imc_vector_t* vec_in,
                int index,
                imc_vector_t** vec_out1,
                imc_vector_t** vec_out2);

imc_vector_t* imc_vector_merge(imc_vector_t* vec_front,
                imc_vector_t* vec_tail);

/* user-side memory management */

int imc_vector_unref(imc_vector_t* vec);

void imc_vector_dump(imc_vector_t* vec);

#endif
