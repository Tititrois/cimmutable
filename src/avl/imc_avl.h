#ifndef IMC_AVL

#define IMC_AVL 1

typedef imc_data_t;
typedef imc_key_t;

//----------------------------------------------------------------------------//
//----------------------------Data Structure----------------------------------//
//----------------------------------------------------------------------------//
typedef struct imc_avl_node_t{
    int balance; // Show if the tree is equilibrate (0) or
                 //  balance to the left (-1) or right (1).
    int ref_counter; //Used to free unreferenced internal nodes.

    struct imc_avl_node_t * left; // Left branch pf the tree.
    struct imc_avl_node_t * right; // right branch pf the tree.
    imc_data_t* data; // data stored in the node.
    imc_key_t* key; // key used to sort the nodes.

} imc_avl_node_t ;



//----------------------------------------------------------------------------//
//--------------------------Primitive FUnctions-------------------------------//
//----------------------------------------------------------------------------//
int imc_avl_size(imc_avl_node_t* tree);

int imc_avl_height(imc_avl_node_t* tree);

imc_data_t* imc_avl_lookup(imc_avl_node_t* tree, imc_key_t* key,
                           int (*comparator)(imc_key_t*, imc_key_t*) );

void imc_avl_keys(imc_avl_node_t* tree, imc_key_t** tab, int* indice);

/* stack operations */

// add at the end <--- DOXYGENIZE PLEASE!
imc_avl_node_t* imc_avl_insert( imc_avl_node_t* tree,
                                imc_data_t* data, imc_key_t* key,
                                int (*comparator)(imc_key_t*, imc_key_t*),
                                // Data replaced during the insertion
                                imc_data_t** prev_data);

imc_avl_node_t* imc_avl_remove( imc_avl_node_t* tree,
                                imc_key_t* key,
                                int (*comparator)(imc_key_t*, imc_key_t*),
                                imc_data_t** removed_data);

int imc_avl_split(  imc_avl_node_t* tree_in,
                    imc_key_t* key,
                    imc_avl_node_t** tree_out1,
                    imc_avl_node_t** tree_out2,
                    int (*comparator)(imc_key_t*, imc_key_t*));

int check_invariant(imc_avl_node_t* tree,
                int (*comparator)(imc_key_t*, imc_key_t*));

imc_avl_node_t* imc_avl_merge(  imc_avl_node_t* tree_src,
                                imc_avl_node_t* tree_merged,
                                int (*comparator)(imc_key_t*, imc_key_t*));

imc_avl_node_t* imc_avl_copy (imc_avl_node_t* tree);

/* user-side memory management */

int imc_avl_unref(imc_avl_node_t* tree);

void imc_avl_dump(imc_avl_node_t* tree,
                  void (*print)(imc_key_t*, char* b));
#endif
