typedef void imc_data_t;
typedef void imc_key_t;

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "imc_avl_map.h"
#include "imc_avl_vector.h"
#include "parser.h"
#include <getopt.h>

// IMPLEM : AVL or RRB or FINGER
#define IMPLEM IMC_AVL
// IMPLEM_NAME : doesn't matter, only here for the prints.
#define IMPLEM_NAME "avl"

// test for debug, bench for benching.
int is_test = 0, is_bench = 0;

//-------------------------------------------------------
//Fonction adaptation
//-------------------------------------------------------

void *make_int_box(int val){
    int *res = malloc(sizeof(int));
    *res = val;
    return res;
}

void *make_string_box(char* val){
    return strdup(val);
}

int compare_int_keys(imc_key_t* k, imc_key_t* v){
    return (*(int*)k) -(*(int *)v);
}

void print_int (int* nb)
{

	printf("%d", *nb);
}

void print_str (char* nb)
{
	printf("%s", nb);
}

int compare_string_keys(imc_key_t* k, imc_key_t* v){
    int res = 0;
    int i = 0;
    while(res==0){
        res = ((char*)k)[i] - ((char*)v)[i];
        if(((char*)k)[i] == '\0'){
            return -1 * (((char*)v)[i] != '\0');
        }
        if(((char*)v)[i] == '\0'){
            return ((char*)k)[i] != '\0';
        }
        i++;
    }
    return res;
}

//----------------------------------------------------------
//Fonction Darius
//----------------------------------------------------------

double eval_vector_cmds(Prog* prog, command** cmds,
			int size, imc_vector_avl_t** vec) {
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);

  for (int i = 0; i < size; i++) {
    command* cmd = cmds[i];
    int obj_in   = cmd->obj_in;
    int obj_out  = cmd->obj_out;
    int obj_aux  = cmd->obj_aux;
    switch (cmd->type) {
    case CREATE:
      vec[obj_out] = imc_vector_avl_create();
      break;
    case UNREF:
      imc_vector_avl_unref(vec[obj_in]);
      break;
    case UPDATE:
      vec[obj_out] = imc_vector_avl_update(vec[obj_in], cmd->index,
				       prog->data_type == INT ?
				       make_int_box(cmd->data.as_int) :
				       make_string_box(cmd->data.as_string) );
      break;
    case PUSH:
      vec[obj_out] = imc_vector_avl_push(vec[obj_in], prog->data_type == INT ?
				     make_int_box(cmd->data.as_int) :
				     make_string_box(cmd->data.as_string));
      break;
    case POP:
      ;void* data;
      vec[obj_out] = imc_vector_avl_pop(vec[obj_in], &data);
      break;
    case MERGE:
      vec[obj_out] = imc_vector_avl_merge(vec[obj_in], vec[obj_aux]);
      break;
    case SPLIT:
      imc_vector_avl_split(vec[obj_in], cmd->index, &vec[obj_out], &vec[obj_aux]);
      break;
    case LOOKUP:
      imc_vector_avl_lookup(vec[obj_in], cmd->index);
      break;
    case SIZE:
      imc_vector_avl_size(vec[obj_in]); // hopefully won't be optimized out.
      break;
    case DUMP:
     if (is_test)
      	imc_vector_avl_dump(vec[obj_in], prog->data_type == INT ? &print_int : &print_str);
      break;
    default: // mostly to remove warnings.
      fprintf(stderr, "Unsupported operation %d. Skipping.\n", cmd->type);
    }
  }

  gettimeofday(&t2, NULL);
  double elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0;
  return elapsed_time;
}


double execute_vector (Prog* prog) {
  imc_vector_avl_t** vec = malloc(prog->nb_var * sizeof(*vec));

  eval_vector_cmds(prog, prog->init, prog->init_size, vec);
  return eval_vector_cmds(prog, prog->bench, prog->bench_size, vec);
}

double eval_map_cmds(Prog* prog, command** cmds,
		     int size, imc_avl_map_t** map) {
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);
  imc_data_t* data=NULL;
  for (int i = 0; i < size; i++) {
    command* cmd = cmds[i];
    int obj_in   = cmd->obj_in;
    int obj_out  = cmd->obj_out;
    switch (cmd->type) {
    case CREATE:
      map[obj_out] =
	imc_avl_map_create(
	 prog->key_type  == INT ? &compare_int_keys  : &compare_string_keys  );
      break;
    case UNREF:
      imc_avl_map_unref(map[obj_in]);
      break;
    case UPDATE:

      map[obj_out] =
	imc_avl_map_update(
	  map[obj_in],
	  prog->key_type  == INT ? make_int_box(cmd->key.as_int) :
	                           make_string_box(cmd->key.as_string),
	  prog->data_type == INT ? make_int_box(cmd->data.as_int) :
	                           make_string_box(cmd->data.as_string) ,
      &data
    );
      break;
    case REMOVE:
      map[obj_out] =
	imc_avl_map_remove(map[obj_in], prog->key_type == INT ?
		       make_int_box(cmd->key.as_int) :
		       make_string_box(cmd->key.as_string), &data );
      break;
    case LOOKUP:
      imc_avl_map_lookup(map[obj_in], prog->key_type == INT ?
		     make_int_box(cmd->key.as_int) :
		     make_string_box(cmd->key.as_string) );
      break;
    case SIZE:
      imc_avl_map_size(map[obj_in]);
      break;
    case DUMP:
      //imc_avl_map_dump(map[obj_in]);
      break;
  default: // mostly to remove warnings.
      fprintf(stderr, "Unsupported operation %d. Skipping.\n", cmd->type);
    }
  }

  gettimeofday(&t2, NULL);
  double elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0;
  return elapsed_time;
}


double execute_map (Prog* prog) {
  imc_avl_map_t** map = malloc(prog->nb_var * sizeof(*map));

  eval_map_cmds(prog, prog->init, prog->init_size, map);
  return eval_map_cmds(prog, prog->bench, prog->bench_size, map);
}


int main (int argc, char* argv[]) {

	char* filename = NULL;

  struct option long_options[] = {
    { "file", required_argument, NULL, 'f' },
    { "test", no_argument, NULL, 't'},
    { "bench", no_argument, NULL, 'b'} };

  char c;
  int option_index = 0;
  while ((c = getopt_long(argc, argv, "f:bt", long_options, &option_index)) != -1) {
    switch (c) {
    case 'f': 
      filename = optarg;
      break;
    case 't': 
      is_test = 1;
      break;
    case 'b':
      is_bench = 1;
      break;
    default:
      fprintf(stderr, "Unknown option %c. Ignoring it.\n", c);
      exit (EXIT_FAILURE);
    }
  }
  if ( filename == NULL) {
    fprintf(stderr, "Filename missing. Aborting.\n");
    exit (EXIT_FAILURE);
  }

  Prog* prog = read_file(filename);

  if (! ( prog->implem & IMPLEM )) {
    fprintf(stderr, "Benchmark '%s' doesn't support %s. Aborting\n",
	    argv[1], IMPLEM_NAME);
    exit (EXIT_FAILURE);
  }

  if ( ! is_test && ! is_bench ) {
    fprintf(stderr, "Mode isn't specified. Assuming test.\n");
    is_test = 1;
}

  double time = 0;
  if (is_test) {
    if (prog->struc == VECTOR) {
      time = execute_vector(prog);
    } else {
      time = execute_map(prog);
    }
    printf("Time elapsed: %.3fms\n", time);
  }
  else if (is_bench) {
    for (int i = 0; i < 100; i++) {
      if (prog->struc == VECTOR) {
	time += execute_vector(prog);
      } else {
	time += execute_map(prog);
      }
    }
    time /= 1000;
    printf("Total time: %.6fs\n", time);
    printf("Average time: %.6fs\n", time / 100);
  }

  return 0;

}
