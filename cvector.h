#ifndef CVECTOR_H
#define CVECTOR_H

#include <stddef.h>
#include <stdlib.h>

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

#define DEFINE_STR_VECTOR \
  typedef struct {        \
    char** str;           \
    size_t len;           \
    size_t cap;           \
  } str_vec_t;


#endif
