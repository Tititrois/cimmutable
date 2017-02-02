#ifndef imc_vector_avl
#define imc_vector_avl

#include "imc_avl.h"

//----------------------------------------------------------------------------//
//----------------------------Data Structure----------------------------------//
//----------------------------------------------------------------------------//
typedef struct imc_vector_avl_t{
    imc_avl_node_t* tree;
    int last_value;
} imc_vector_avl_t;


//----------------------------------------------------------------------------//
//--------------------------Vector functions----------------------------------//
//----------------------------------------------------------------------------//
imc_vector_avl_t* imc_vector_avl_create();

int imc_vector_avl_size(imc_vector_avl_t* vec);

imc_vector_avl_t* imc_vector_avl_update(imc_vector_avl_t* vec, int index,
                                        imc_data_t* data);

imc_data_t* imc_vector_avl_lookup(imc_vector_avl_t* vec, int index);

/* stack operations */

// add at the end <--- DOXYGENIZE PLEASE!
imc_vector_avl_t* imc_vector_avl_push(imc_vector_avl_t* vec,
			      imc_data_t* data);

imc_vector_avl_t* imc_vector_avl_pop(imc_vector_avl_t* vec,
			     imc_data_t** data);

int imc_vector_avl_split(imc_vector_avl_t* vec_in,
		     int index,
		     imc_vector_avl_t** vec_out1,
		     imc_vector_avl_t** vec_out2);

imc_vector_avl_t* imc_vector_avl_merge(imc_vector_avl_t* vec_front,
			       imc_vector_avl_t* vec_tail);

/* user-side memory management */

int imc_vector_avl_unref(imc_vector_avl_t* vec);

void imc_vector_avl_dump(imc_vector_avl_t* vec,
                      void (*print_data)(imc_data_t*));
#endif
