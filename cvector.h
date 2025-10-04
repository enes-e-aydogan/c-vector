#ifndef CVECTOR_H
#define CVECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef VEC_INIT_CAP
#define VEC_INIT_CAP 16
#endif

#define VEC_DEF(TYPE, NAME)                                                   \
    typedef struct {                                                          \
        TYPE*  data;                                                          \
        size_t len;                                                           \
        size_t cap;                                                           \
    } NAME##_t;                                                               \
                                                                              \
    static inline int NAME##_new(NAME##_t** vec) {                            \
        if (!vec)                                                             \
            return -1;                                                        \
        (*vec) = (NAME##_t*) malloc(sizeof(NAME##_t));                        \
        if (!*vec)                                                            \
            return -1;                                                        \
        (*vec)->data = (TYPE*) malloc(sizeof(TYPE) * VEC_INIT_CAP);           \
        if (!(*vec)->data) {                                                  \
            free(*vec);                                                       \
            return -1;                                                        \
        }                                                                     \
        (*vec)->len = 0;                                                      \
        (*vec)->cap = VEC_INIT_CAP;                                           \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int NAME##_grow(NAME##_t* vec) {                            \
        if (!vec)                                                             \
            return -1;                                                        \
        size_t new_cap  = vec->cap * 2;                                       \
        TYPE*  new_data = realloc(vec->data, sizeof(TYPE) * new_cap);         \
        if (!new_data)                                                        \
            return -1;                                                        \
        vec->data = new_data;                                                 \
        vec->cap  = new_cap;                                                  \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int NAME##_push(NAME##_t* vec, TYPE element) {              \
        if (!vec)                                                             \
            return -1;                                                        \
        if (vec->len == vec->cap) {                                           \
            if (NAME##_grow(vec))                                             \
                return -1;                                                    \
        }                                                                     \
        vec->data[vec->len++] = element;                                      \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int NAME##_pop(NAME##_t* vec, TYPE* out) {                  \
        if (!vec || !out || vec->len == 0)                                    \
            return -1;                                                        \
        *out = (vec->data[vec->len-- - 1]);                                   \
        if (vec->len < vec->cap / 2) {                                        \
            size_t new_cap  = vec->cap / 2;                                   \
            TYPE*  new_data = realloc(vec->data, sizeof(TYPE) * new_cap);     \
            if (!new_data)                                                    \
                return -1;                                                    \
            vec->data = new_data;                                             \
            vec->cap  = new_cap;                                              \
        }                                                                     \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int NAME##_del(NAME##_t* vec, size_t index, TYPE* out) {    \
        if (!vec || !out || index >= vec->len)                                \
            return -1;                                                        \
        *out = (vec->data[index]);                                            \
        if (index < vec->len - 1) {                                           \
            memmove(&vec->data[index], &vec->data[index + 1],                 \
                    (vec->len - index - 1) * sizeof(TYPE));                   \
        }                                                                     \
        vec->len--;                                                           \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int NAME##_get(NAME##_t* vec, size_t index, TYPE* out) {    \
        if (!vec || !out || index >= vec->len)                                \
            return -1;                                                        \
        *out = vec->data[index];                                              \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int NAME##_set(NAME##_t* vec, size_t index, TYPE element) { \
        if (!vec || index >= vec->len)                                        \
            return -1;                                                        \
        vec->data[index] = element;                                           \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline int NAME##_len(NAME##_t* vec, size_t* out) {                \
        if (!vec || !out)                                                     \
            return -1;                                                        \
        *out = vec->len;                                                      \
        return 0;                                                             \
    }                                                                         \
                                                                              \
    static inline void NAME##_free(NAME##_t** vec) {                          \
        if (vec) {                                                            \
            free((*vec)->data);                                               \
            free((*vec));                                                     \
            *vec = NULL;                                                      \
        }                                                                     \
    }

#define SVEC_DEF                                                                       \
    typedef struct {                                                                   \
        char** str;                                                                    \
        size_t len;                                                                    \
        size_t cap;                                                                    \
    } svec_t;                                                                          \
                                                                                       \
    static inline int svec_new(svec_t** vec) {                                         \
        if (!vec)                                                                      \
            return -1;                                                                 \
        *vec = (svec_t*) malloc(sizeof(**vec));                                        \
        if (!*vec)                                                                     \
            return -1;                                                                 \
        (*vec)->len = 0;                                                               \
        (*vec)->cap = VEC_INIT_CAP;                                                    \
        (*vec)->str = (char**) calloc((*vec)->cap, sizeof(char*));                     \
        if (!(*vec)->str) {                                                            \
            free(*vec);                                                                \
            *vec = NULL;                                                               \
            return -1;                                                                 \
        }                                                                              \
        return 0;                                                                      \
    }                                                                                  \
                                                                                       \
    static inline int svec_grow(svec_t* vec) {                                         \
        if (!vec)                                                                      \
            return -1;                                                                 \
        size_t new_cap  = vec->cap * 2;                                                \
        char** new_data = (char**) realloc((char*) vec->str, new_cap * sizeof(char*)); \
        if (!new_data)                                                                 \
            return -1;                                                                 \
        vec->str = new_data;                                                           \
        vec->cap = new_cap;                                                            \
        return 0;                                                                      \
    }                                                                                  \
                                                                                       \
    static inline int svec_push(svec_t* vec, const char* element) {                    \
        if (!vec)                                                                      \
            return -1;                                                                 \
        if (vec->len == vec->cap) {                                                    \
            if (svec_grow(vec)) {                                                      \
                return -1;                                                             \
            }                                                                          \
        }                                                                              \
        size_t needed = strlen(element) + 1;                                           \
        char*  cpy    = malloc(needed);                                                \
        if (!cpy)                                                                      \
            return -1;                                                                 \
        strcpy(cpy, element);                                                          \
        vec->str[vec->len++] = cpy;                                                    \
        return 0;                                                                      \
    }                                                                                  \
                                                                                       \
    static inline char* svec_pop(svec_t* vec) {                                        \
        if (!vec || vec->len == 0)                                                     \
            return NULL;                                                               \
        return vec->str[vec->len-- - 1];                                               \
    }                                                                                  \
                                                                                       \
    static inline char* svec_del(svec_t* vec, size_t index) {                          \
        if (!vec || index >= vec->len)                                                 \
            return NULL;                                                               \
        char* out = vec->str[index];                                                   \
        if (index < vec->len - 1) {                                                    \
            memmove((void*) &vec->str[index], (const void*) &vec->str[index + 1],      \
                    (vec->len - index - 1) * sizeof(char*));                           \
        }                                                                              \
        vec->len--;                                                                    \
        return out;                                                                    \
    }                                                                                  \
                                                                                       \
    static inline const char* svec_get(svec_t* vec, size_t index) {                    \
        if (!vec || index >= vec->len)                                                 \
            return NULL;                                                               \
        return vec->str[index];                                                        \
    }                                                                                  \
                                                                                       \
    static inline int svec_set(svec_t* vec, size_t index, const char* element) {       \
        if (!vec || !element || index >= vec->len)                                     \
            return -1;                                                                 \
                                                                                       \
        size_t needed = strlen(element) + 1;                                           \
        char*  cpy    = malloc(needed);                                                \
        if (!cpy)                                                                      \
            return -1;                                                                 \
        strcpy(cpy, element);                                                          \
        free(vec->str[index]);                                                         \
                                                                                       \
        vec->str[index] = cpy;                                                         \
                                                                                       \
        return 0;                                                                      \
    }                                                                                  \
                                                                                       \
    static inline int svec_len(svec_t* vec, size_t* out) {                             \
        if (!vec || !out)                                                              \
            return -1;                                                                 \
        *out = vec->len;                                                               \
        return 0;                                                                      \
    }                                                                                  \
                                                                                       \
    static inline void svec_free(svec_t** vec) {                                       \
        if (vec && (*vec)) {                                                           \
            for (size_t i = 0; i < (*vec)->len; i++) {                                 \
                free((*vec)->str[i]);                                                  \
            }                                                                          \
            free((char*) (*vec)->str);                                                 \
            free((*vec));                                                              \
            *vec = NULL;                                                               \
        }                                                                              \
    }

#endif
