# cvector

A lightweight, header-only dynamic vector library for C with type-safe generic vectors via macros.

## Features

- **Header-only** - Just include `cvector.h`
- **Type-safe** - Generate strongly-typed vectors for any type
- **Dynamic sizing** - Auto-grows/shrinks as needed
- **Built-in string vector** - Pre-defined string vector type (`svec_t`)
- **Minimal overhead** - Static inline functions

## Usage

```c
#include "cvector.h"

// Define a vector type for integers
VEC_DEF(int, int_vec)

int main(void) {
    int_vec_t* vec = NULL;
    
    // Create vector
    int_vec_new(&vec);
    
    // Push elements
    int_vec_push(vec, 42);
    int_vec_push(vec, 100);
    
    // Get element
    int value;
    int_vec_get(vec, 0, &value);  // value = 42
    
    // Set element
    int_vec_set(vec, 1, 200);
    
    // Pop element
    int popped;
    int_vec_pop(vec, &popped);  // popped = 200
    
    // Delete element at index
    int removed;
    int_vec_del(vec, 0, &removed);  // removed = 42
    
    // Get length
    size_t len;
    int_vec_len(vec, &len);
    
    // Free vector
    int_vec_free(&vec);
    return 0;
}
```

## String Vector

For strings, use the pre-defined `svec_t` type:

```c
#include "cvector.h"

SVEC_DEF  // Define string vector

int main(void) {
    svec_t* vec = NULL;
    svec_new(&vec);
    
    svec_push(vec, "hello");
    svec_push(vec, "world");
    
    const char* str = svec_get(vec, 0);  // "hello"
    
    char* popped = svec_pop(vec);  // Returns owned string
    free(popped);  // Caller must free
    
    svec_free(&vec);
    return 0;
}
```

## API Reference

For a vector type `NAME`:

- `NAME##_new(NAME##_t** vec)` - Create new vector
- `NAME##_push(NAME##_t* vec, TYPE element)` - Add element to end
- `NAME##_pop(NAME##_t* vec, TYPE* out)` - Remove and return last element
- `NAME##_get(NAME##_t* vec, size_t index, TYPE* out)` - Get element at index
- `NAME##_set(NAME##_t* vec, size_t index, TYPE element)` - Set element at index
- `NAME##_del(NAME##_t* vec, size_t index, TYPE* out)` - Delete element at index
- `NAME##_len(NAME##_t* vec, size_t* out)` - Get vector length
- `NAME##_free(NAME##_t** vec)` - Free vector and set to NULL

All functions return `0` on success, `-1` on error (except `svec_pop`/`svec_get`/`svec_del` which return pointers).

## Configuration

Set initial capacity before including the header:

```c
#define VEC_INIT_CAP 32
#include "cvector.h"
```

Default is 16 elements.

## License

See LICENSE file.
