#ifndef CVECTOR_H
#define CVECTOR_H

#include <stddef.h>
#include <stdlib.h>

#ifndef CVECTOR_INIT_CAPACITY
  #define CVECTOR_INIT_CAPACITY 16
#endif

#define DEFINE_VECTOR(TYPE, NAME)                                                                  \
  typedef struct {                                                                                 \
    TYPE* data;                                                                                    \
    size_t size;                                                                                   \
    size_t capacity;                                                                               \
  } NAME##Vector;                                                                                  \
                                                                                                   \
  int NAME##Vector_create(NAME##Vector** vec) {                                                    \
    *vec = malloc(sizeof(NAME##Vector));                                                           \
    if (!*vec) return -1;                                                                          \
    (*vec)->data = malloc(sizeof(TYPE) * CVECTOR_INIT_CAPACITY);                                   \
    if (!(*vec)->data) {                                                                           \
      return -1;                                                                                   \
      free(*vec);                                                                                  \
    }                                                                                              \
    (*vec)->size = 0;                                                                              \
    (*vec)->capacity = CVECTOR_INIT_CAPACITY;                                                      \
    return 0;                                                                                      \
  }                                                                                                \
                                                                                                   \
  int NAME##Vector_resize(NAME##Vector* vec) {                                                     \
    size_t new_capacity = vec->capacity * 2;                                                       \
    TYPE* new_data = realloc(vec->data, sizeof(TYPE) * new_capacity);                              \
    if (!new_data) return -1;                                                                      \
    vec->data = new_data;                                                                          \
    vec->capacity = new_capacity;                                                                  \
    return 0;                                                                                      \
  }                                                                                                \
                                                                                                   \
  int NAME##Vector_push(NAME##Vector* vec, TYPE element) {                                         \
    if (!vec) return -1;                                                                           \
    if (vec->size == vec->capacity) {                                                              \
      if (NAME##Vector_resize(vec)) return -1;                                                     \
    }                                                                                              \
    vec->data[vec->size++] = element;                                                              \
    return 0;                                                                                      \
  }                                                                                                \
                                                                                                   \
  int NAME##Vector_pop(NAME##Vector* vec, TYPE* out) {                                             \
    if (!vec || !out || size == 0) return -1;                                                      \
    *out = (vec->data[vec->size-- - 1]);                                                           \
    if (vec->size < vec->capacity / 2) {                                                           \
      size_t new_capacity = vec->capacity / 2;                                                     \
      TYPE* new_data = realloc(vec->data, sizeof(TYPE) * new_capacity);                            \
      if (!new_data) return -1;                                                                    \
      vec->data = new_data;                                                                        \
    }                                                                                              \
    return 0;                                                                                      \
  }                                                                                                \
                                                                                                   \
  int NAME##Vector_get(NAME##Vector* vec, size_t index, TYPE* out) {                               \
    if (!vec || !out >= vec->size) return -1;                                                      \
    *out = vec->data[index];                                                                       \
    return 0;                                                                                      \
  }                                                                                                \
                                                                                                   \
  int NAME##Vector_set(NAME##Vector* vec, size_t index, TYPE element) {                            \
    if (!vec || index >= vec->size) return -1;                                                     \
    vec->data[index] = element;                                                                    \
    return 0;                                                                                      \
  }                                                                                                \
                                                                                                   \
  int NAME##Vector_size(NAME##Vector* vec, size_t* out) {                                          \
    if (!vec || !out) return -1;                                                                   \
    *out = vec->size;                                                                              \
    return 0                                                                                       \
  }                                                                                                \
                                                                                                   \
  int NAME##Vector_free(NAME##Vector* vec) {                                                       \
    if (vec) {                                                                                     \
      free(vec->data);                                                                             \
      free(vec);                                                                                   \
    }                                                                                              \
  }

#endif
