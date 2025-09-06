#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cvector.h"

#define TOSTR(x) #x
#define ELEM_NUM 25
#define INDEX 5

DEFINE_STR_VECTOR

int main() {
  str_vec_t* str_vec = nullptr;

  if (str_vec_new(&str_vec)) {
    fprintf(stderr, "Error: str_vec_new");
  }

  str_vec_push(str_vec, "string1");
  str_vec_push(str_vec, "string2");
  str_vec_push(str_vec, "string3");
  str_vec_push(str_vec, "string4");
  str_vec_push(str_vec, "string5");
  str_vec_push(str_vec, "string6");
  str_vec_push(str_vec, "string7");
  str_vec_push(str_vec, "string8");
  str_vec_push(str_vec, "string9");
  str_vec_push(str_vec, "string10");
  str_vec_push(str_vec, "string11");
  str_vec_push(str_vec, "string12");
  str_vec_push(str_vec, "string13");
  str_vec_push(str_vec, "string14");
  str_vec_push(str_vec, "string15");
  str_vec_push(str_vec, "string16");
  str_vec_push(str_vec, "string17");
  str_vec_push(str_vec, "string18");
  str_vec_push(str_vec, "string19");
  str_vec_push(str_vec, "string20");
  str_vec_push(str_vec, "string21");
  str_vec_push(str_vec, "string22");
  str_vec_push(str_vec, "string23");
  str_vec_push(str_vec, "string24");
  str_vec_push(str_vec, "string25");

  printf("\n\n====After init====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %ld: %s\n", i, str_vec->str[i]);
  }

  char* popped = str_vec_pop(str_vec);

  printf("\n\n====After pop====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %ld: %s\n", i, str_vec->str[i]);
  }
  str_vec_push(str_vec, "str_new");
  printf("popped: %s\n", popped);
  free(popped);

  printf("\n\n====After push====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %ld: %s\n", i, str_vec->str[i]);
  }

  const char* getted = str_vec_get(str_vec, INDEX);
  printf("getted: %s\n", getted);

  if (str_vec_set(str_vec, INDEX, "set the string")) {
    fprintf(stderr, "Error: str_vec_set");
  }

  printf("\n\n====After set====\n\n");
  for (size_t i = 0; i < str_vec->len; i++) {
    printf("elem %ld: %s\n", i, str_vec->str[i]);
  }

  size_t len;
  if (str_vec_len(str_vec, &len)) {
    fprintf(stderr, "Error: str_vec_len");
  }

  str_vec_free(&str_vec);

  return EXIT_SUCCESS;
}
