#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cvector.h"

#define ELEM_NUM 25
#define INDEX 5
#define BUF 32

DEFINE_STR_VECTOR

int main() {
  str_vec_t* str_vec = NULL;

  if (str_vec_new(&str_vec)) {
    fprintf(stderr, "Error: str_vec_new\n");
    return EXIT_FAILURE;
  }

  // Push 25 strings
  for (int i = 1; i <= ELEM_NUM; i++) {
    char buf[BUF];
    snprintf(buf, sizeof(buf), "string%d", i);
    str_vec_push(str_vec, buf);
  }

  printf("\n\n====After init====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %zu: %s\n", i, str_vec->str[i]);
  }

  // Pop the last element
  char* popped = str_vec_pop(str_vec);
  printf("\n\n====After pop====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %zu: %s\n", i, str_vec->str[i]);
  }
  printf("popped: %s\n", popped);
  free(popped);  // free the popped string

  // Push a new string
  str_vec_push(str_vec, "str_new");
  printf("\n\n====After push====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %zu: %s\n", i, str_vec->str[i]);
  }

  // Get element at INDEX
  const char* getted = str_vec_get(str_vec, INDEX);
  printf("getted: %s\n", getted);

  // Set element at INDEX
  if (str_vec_set(str_vec, INDEX, "set the string")) {
    fprintf(stderr, "Error: str_vec_set\n");
  }

  printf("\n\n====After set====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %zu: %s\n", i, str_vec->str[i]);
  }

  // Delete element at INDEX using _del (return-value version)
  char* removed = str_vec_del(str_vec, INDEX);
  if (removed) {
    printf("\nDeleted element at index %d: %s\n", INDEX, removed);
    free(removed);  // free the removed string
  }

  printf("\n\n====After _del====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %zu: %s\n", i, str_vec->str[i]);
  }

  // Pop the last element again
  popped = str_vec_pop(str_vec);
  printf("\n\n====After pop again====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %zu: %s\n", i, str_vec->str[i]);
  }
  printf("popped: %s\n", popped);
  free(popped);

  // Vector length
  size_t len;
  if (str_vec_len(str_vec, &len)) {
    fprintf(stderr, "Error: str_vec_len\n");
  }
  printf("\nFinal vector length: %zu\n", len);

  str_vec_free(&str_vec);

  return EXIT_SUCCESS;
}
