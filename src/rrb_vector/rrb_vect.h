#ifndef _RRB_VECT_H
#define _RRB_VECT_H

typedef imc_node_t;
typedef imc_data_t;

typedef struct imc_intern {
    int depth; //nb niveau en dessous
    int refs; // nb de references qui pointent sur la struct
    int is_unbalanced;
    int* meta; //meta data
    imc_node_t* childs;
} imc_intern_t;

typedef struct imc_leaf {
    imc_data_t* data;
} imc_leaf_t;

typedef union imc_node {
    imc_intern_t intern;
    imc_leaf_t leaf; 
} imc_note_t;

#endif
