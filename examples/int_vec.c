#include "cvector.h"
#include <stddef.h>
#include <stdio.h>

#define NUM_COUNT 25
#define POP_COUNT 3
#define TEST_INDEX 5
#define TEST_VALUE 999

DEFINE_VECTOR(int, int)

int main(void) {
  int_vec_t* int_vec = NULL;

  if (int_vec_new(&int_vec) != 0) {
    printf("Failed to create vector\n");
    return 1;
  }

  const int nums[NUM_COUNT] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                               14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

  printf("Pushing %d numbers to vector...\n", NUM_COUNT);
  for (size_t i = 0; i < NUM_COUNT; i++) {
    if (int_vec_push(int_vec, nums[i]) != 0) {
      printf("Failed to push element %zu\n", i);
      int_vec_free(&int_vec);
      return 1;
    }
  }

  size_t len;
  int_vec_len(int_vec, &len);
  printf("Vector length: %zu\n", len);

  printf("Vector contents: ");
  for (size_t i = 0; i < len; i++) {
    int value;
    if (int_vec_get(int_vec, i, &value) == 0) { printf("%d ", value); }
  }
  printf("\n");

  printf("Setting element at index %d to %d...\n", TEST_INDEX, TEST_VALUE);
  int_vec_set(int_vec, TEST_INDEX, TEST_VALUE);

  printf("Popping %d elements: ", POP_COUNT);
  for (int i = 0; i < POP_COUNT; i++) {
    int popped;
    if (int_vec_pop(int_vec, &popped) == 0) { printf("%d ", popped); }
  }
  printf("\n");

  int_vec_len(int_vec, &len);
  printf("Final length: %zu\n", len);

  printf("Remaining elements: ");
  for (size_t i = 0; i < len; i++) {
    int value;
    if (int_vec_get(int_vec, i, &value) == 0) { printf("%d ", value); }
  }
  printf("\n");

  int_vec_free(&int_vec);

  return 0;
}
