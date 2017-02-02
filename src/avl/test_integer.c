/*
#include <stdlib.h>
#include <stdio.h>
#include "imc_avl.h"



int compare (int* a , int* b)
{
	return *a - *b;
}

void print (int* nb, char* b)
{

	sprintf(b, "(%03d)", *nb);
}

void parcour_infix(imc_avl_node_t* tree){
    if(tree == NULL) return;
    parcour_infix(tree->left);
    printf("tree->key = %d, tree->balance = %d, tree->ref = %d\n", *tree->key,tree->balance, tree->ref_counter);
    parcour_infix(tree->right);
}

int main ()
{
	imc_data_t* replace;

	imc_data_t* test;

	imc_data_t data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	imc_key_t key[8] = {10, 4, 6, 12, 14, 8, 16, 18};

	imc_avl_node_t* tree = NULL;
    imc_avl_node_t* temp_tree = NULL;
    int i;
	for (i = 0 ; i < 8 ; i++)
	{
        replace = NULL;
		temp_tree = imc_avl_insert(tree, &data[i], &key[i], &compare, &replace);
        imc_avl_unref(tree);
        tree = temp_tree;
        //parcour_infix(tree);
	}

	imc_avl_dump(tree, print);
	test = imc_avl_lookup(tree, &key[3], &compare);
	printf("TESTLOOKUP : %d\n", *test);

	replace = NULL;
	temp_tree = imc_avl_remove(tree, &key[0], &compare, &replace);
    imc_avl_unref(tree);
    tree = temp_tree;

    printf("tree->balance = %d\n", tree->balance);
	imc_avl_dump(tree, print);
    parcour_infix(tree);

    replace = NULL;
    temp_tree = imc_avl_remove(tree, &key[3], &compare, &replace);
    imc_avl_unref(tree);
    tree = temp_tree;
    printf("tree->balance = %d\n", tree->balance);
    imc_avl_dump(tree, print);
    parcour_infix(tree);


	//printf("%d\n", (int) *result);


	return 0;
}*/


/*
#include <stdlib.h>
#include <stdio.h>
#include "imc_avl.h"
#include "imc_avl_map.h"



int compare (int* a , int* b)
{
	return *a - *b;
}

void print (int* nb)
{

	printf("%d", *nb);
}

void print2 (int* nb, char* b)
{

	sprintf(b, "(%03d)", *nb);
}

void parcour_infix(imc_avl_node_t* tree)
{    if(tree == NULL) return;
    parcour_infix(tree->left);
    printf("tree->key = %d, tree->balance = %d, tree->ref = %d\n", *tree->key, tree->balance, tree->ref_counter);
    parcour_infix(tree->right);
}

int main ()
{
	imc_data_t* replace;

	imc_data_t data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	imc_key_t key[8] = {10, 3, 6, 12, 14, 2, 16, 18};

	imc_avl_map_t* map_merged = imc_avl_map_create(compare);
	imc_avl_map_t* map = imc_avl_map_create(compare);
	imc_avl_map_t* map2 = imc_avl_map_create(compare);
    int i;

	for (i = 0 ; i < 4 ; i++)
	{
        replace = NULL;
		map = imc_avl_map_update(map, &key[i], &data[i], &replace);
		//imc_avl_map_dump(map, print, print);
        //parcour_infix(tree);

	}

	for (i = 4 ; i < 8 ; i++)
	{
        replace = NULL;
		map2 = imc_avl_map_update(map2, &key[i], &data[i], &replace);
		//imc_avl_map_dump(map, print, print);
        //parcour_infix(tree);
	}


	imc_avl_map_dump(map, print, print);
	imc_avl_map_dump(map2, print, print);


	replace = NULL;
	map_merged = imc_avl_map_merge(map, map2);
    //imc_avl_map_dump(map_merged, print, print);
    //parcour_infix(tree);


	imc_avl_dump(map->tree, print2);
	imc_avl_dump(map2->tree, print2);

	printf("MERGE DES DEUX ARBRES\n");
	imc_avl_dump(map_merged->tree, print2);


	//printf("%d\n", (int) *result);


	return 0;
}

*/



#include <stdlib.h>
#include <stdio.h>
#include "imc_avl.h"
#include "imc_avl_vector.h"



int compare (int* a , int* b)
{
	return *a - *b;
}

void print (int* nb)
{

	printf("%d", *nb);
}

void print2 (int* nb, char* b)
{

	sprintf(b, "(%03d)", *nb);
}

void parcour_infix(imc_avl_node_t* tree)
{    if(tree == NULL) return;
    parcour_infix(tree->left);
    printf("tree->key = %d, tree->balance = %d, tree->ref = %d\n", *tree->key, tree->balance, tree->ref_counter);
    parcour_infix(tree->right);
}

int main ()
{
	imc_data_t* test;
	imc_data_t data[8] = {8, 3, 9, 23, 2, 8, 5, 13};
	imc_data_t* result;

	imc_vector_avl_t* vector = imc_vector_avl_create();
    int i;

	for (i = 0 ; i < 8 ; i++)
	{
		imc_vector_avl_dump(vector, print);
		vector = imc_vector_avl_push(vector, &data[i]);
		//imc_avl_map_dump(map, print, print);
        //parcour_infix(tree);



	}

	test = imc_vector_avl_lookup(vector, 3);

	printf("TEST 22 : %d\n", *test);


	/*
	printf("\n\nTOTO\n");
	vector = imc_vector_avl_pop(vector, &result);
	printf("LastData : %d\n", *result);

	vector = imc_vector_avl_pop(vector, &result);
	printf("LastData : %d\n", *result);

	vector = imc_vector_avl_pop(vector, &result);
	printf("LastData : %d\n", *result);

	//printf("%d\n", (int) *result);

	for (i = 5 ; i < 8 ; i++)
	{

		vector = imc_vector_avl_push(vector, &data[i]);
		//imc_avl_map_dump(map, print, print);
        //parcour_infix(tree);

        imc_vector_avl_dump(vector, print);

	}*/


	return 0;
}

