#ifndef CVECTOR_H
#define CVECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef CVECTOR_INIT_CAPACITY
#define CVECTOR_INIT_CAPACITY 16
#endif

#define DEFINE_VECTOR(TYPE, NAME)                                                   \
  typedef struct {                                                                  \
    TYPE*  data;                                                                    \
    size_t len;                                                                     \
    size_t cap;                                                                     \
  } NAME##_vec_t;                                                                   \
                                                                                    \
  static inline int NAME##_vec_new(NAME##_vec_t** vec) {                            \
    if (!vec)                                                                       \
      return -1;                                                                    \
    *vec = (NAME##_vec_t*) malloc(sizeof(NAME##_vec_t));                            \
    if (!*vec)                                                                      \
      return -1;                                                                    \
    (*vec)->data = (TYPE*) malloc(sizeof(TYPE) * CVECTOR_INIT_CAPACITY);            \
    if (!(*vec)->data) {                                                            \
      free(*vec);                                                                   \
      return -1;                                                                    \
    }                                                                               \
    (*vec)->len = 0;                                                                \
    (*vec)->cap = CVECTOR_INIT_CAPACITY;                                            \
    return 0;                                                                       \
  }                                                                                 \
                                                                                    \
  static inline int NAME##_vec_grow(NAME##_vec_t* vec) {                            \
    if (!vec)                                                                       \
      return -1;                                                                    \
    size_t new_cap  = vec->cap * 2;                                                 \
    TYPE*  new_data = realloc(vec->data, sizeof(TYPE) * new_cap);                   \
    if (!new_data)                                                                  \
      return -1;                                                                    \
    vec->data = new_data;                                                           \
    vec->cap  = new_cap;                                                            \
    return 0;                                                                       \
  }                                                                                 \
                                                                                    \
  static inline int NAME##_vec_push(NAME##_vec_t* vec, TYPE element) {              \
    if (!vec)                                                                       \
      return -1;                                                                    \
    if (vec->len == vec->cap) {                                                     \
      if (NAME##_vec_grow(vec))                                                     \
        return -1;                                                                  \
    }                                                                               \
    vec->data[vec->len++] = element;                                                \
    return 0;                                                                       \
  }                                                                                 \
                                                                                    \
  static inline int NAME##_vec_pop(NAME##_vec_t* vec, TYPE* out) {                  \
    if (!vec || !out || vec->len == 0)                                              \
      return -1;                                                                    \
    *out = (vec->data[vec->len-- - 1]);                                             \
    if (vec->len < vec->cap / 2) {                                                  \
      size_t new_cap  = vec->cap / 2;                                               \
      TYPE*  new_data = realloc(vec->data, sizeof(TYPE) * new_cap);                 \
      if (!new_data)                                                                \
        return -1;                                                                  \
      vec->data = new_data;                                                         \
      vec->cap  = new_cap;                                                          \
    }                                                                               \
    return 0;                                                                       \
  }                                                                                 \
                                                                                    \
  static inline int NAME##_vec_get(NAME##_vec_t* vec, size_t index, TYPE* out) {    \
    if (!vec || !out || index >= vec->len)                                          \
      return -1;                                                                    \
    *out = vec->data[index];                                                        \
    return 0;                                                                       \
  }                                                                                 \
                                                                                    \
  static inline int NAME##_vec_set(NAME##_vec_t* vec, size_t index, TYPE element) { \
    if (!vec || index >= vec->len)                                                  \
      return -1;                                                                    \
    vec->data[index] = element;                                                     \
    return 0;                                                                       \
  }                                                                                 \
                                                                                    \
  static inline int NAME##_vec_len(NAME##_vec_t* vec, size_t* out) {                \
    if (!vec || !out)                                                               \
      return -1;                                                                    \
    *out = vec->len;                                                                \
    return 0;                                                                       \
  }                                                                                 \
                                                                                    \
  static inline void NAME##_vec_free(NAME##_vec_t** vec) {                          \
    if (vec) {                                                                      \
      free((*vec)->data);                                                           \
      free((*vec));                                                                 \
      *vec = nullptr;                                                               \
    }                                                                               \
  }

#define DEFINE_STR_VECTOR                                                            \
  typedef struct {                                                                   \
    char** str;                                                                      \
    size_t len;                                                                      \
    size_t cap;                                                                      \
  } str_vec_t;                                                                       \
                                                                                     \
  static inline int str_vec_new(str_vec_t** vec) {                                   \
    if (!vec)                                                                        \
      return -1;                                                                     \
    *vec = (str_vec_t*) malloc(sizeof(**vec));                                       \
    if (!*vec)                                                                       \
      return -1;                                                                     \
    (*vec)->len = 0;                                                                 \
    (*vec)->cap = CVECTOR_INIT_CAPACITY;                                             \
    (*vec)->str = (char**) calloc((*vec)->cap, sizeof(char*));                       \
    if (!(*vec)->str) {                                                              \
      free(*vec);                                                                    \
      *vec = nullptr;                                                                \
      return -1;                                                                     \
    }                                                                                \
    return 0;                                                                        \
  }                                                                                  \
                                                                                     \
  static inline int str_vec_grow(str_vec_t* vec) {                                   \
    if (!vec)                                                                        \
      return -1;                                                                     \
    size_t new_cap  = vec->cap * 2;                                                  \
    char** new_data = (char**) realloc((char*) vec->str, new_cap * sizeof(char*));   \
    if (!new_data)                                                                   \
      return -1;                                                                     \
    vec->str = new_data;                                                             \
    vec->cap = new_cap;                                                              \
    return 0;                                                                        \
  }                                                                                  \
                                                                                     \
  static inline int str_vec_push(str_vec_t* vec, const char* element) {              \
    if (!vec)                                                                        \
      return -1;                                                                     \
    if (vec->len == vec->cap) {                                                      \
      if (str_vec_grow(vec)) {                                                       \
        return -1;                                                                   \
      }                                                                              \
    }                                                                                \
    size_t needed = strlen(element) + 1;                                             \
    char*  cpy    = malloc(needed);                                                  \
    if (!cpy)                                                                        \
      return -1;                                                                     \
    strcpy(cpy, element);                                                            \
    vec->str[vec->len++] = cpy;                                                      \
    return 0;                                                                        \
  }                                                                                  \
                                                                                     \
  static inline char* str_vec_pop(str_vec_t* vec) {                                  \
    if (!vec || vec->len == 0)                                                       \
      return nullptr;                                                                \
    return vec->str[vec->len-- - 1];                                                 \
  }                                                                                  \
                                                                                     \
  static inline const char* str_vec_get(str_vec_t* vec, size_t index) {              \
    if (!vec || index >= vec->len)                                                   \
      return nullptr;                                                                \
    return vec->str[index];                                                          \
  }                                                                                  \
                                                                                     \
  static inline int str_vec_set(str_vec_t* vec, size_t index, const char* element) { \
    if (!vec || !element || index >= vec->len)                                       \
      return -1;                                                                     \
                                                                                     \
    size_t needed = strlen(element) + 1;                                             \
    char*  cpy    = malloc(needed);                                                  \
    if (!cpy)                                                                        \
      return -1;                                                                     \
    strcpy(cpy, element);                                                            \
    free(vec->str[index]);                                                           \
                                                                                     \
    vec->str[index] = cpy;                                                           \
                                                                                     \
    return 0;                                                                        \
  }                                                                                  \
                                                                                     \
  static inline int str_vec_len(str_vec_t* vec, size_t* out) {                       \
    if (!vec || !out)                                                                \
      return -1;                                                                     \
    *out = vec->len;                                                                 \
    return 0;                                                                        \
  }                                                                                  \
                                                                                     \
  static inline void str_vec_free(str_vec_t** vec) {                                 \
    if (vec && (*vec)) {                                                             \
      for (size_t i = 0; i < (*vec)->len; i++) {                                     \
        free((*vec)->str[i]);                                                        \
      }                                                                              \
      free((char*) (*vec)->str);                                                     \
      free((*vec));                                                                  \
      *vec = nullptr;                                                                \
    }                                                                                \
  }

#endif
