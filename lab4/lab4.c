#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXTRA_HEAP 256
#define BLOCK_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

int main(void) {
  void *old_brk = sbrk(0);
  if (old_brk == (void *)-1) {
    perror("sbrk(0)");
    exit(EXIT_FAILURE);
  }

  if (sbrk(EXTRA_HEAP) == (void *)-1) {
    perror("sbrk(EXTRA_HEAP)");
    exit(EXIT_FAILURE);
  }

  struct header *first = (struct header *)old_brk;
  struct header *second = (struct header *)((char *)old_brk + BLOCK_SIZE);

  first->size = BLOCK_SIZE;
  first->next = NULL;

  second->size = BLOCK_SIZE;
  second->next = first;

  size_t header_sz = sizeof(struct header);
  unsigned char *first_data = (unsigned char *)first + header_sz;
  unsigned char *second_data = (unsigned char *)second + header_sz;
  size_t data_len = BLOCK_SIZE - header_sz;

  memset(first_data, 0x00, data_len);
  memset(second_data, 0x01, data_len);

  printf("first block:    %p\n", (void *)first);
  printf("second block:   %p\n", (void *)second);
  printf("first block size: %llu\n", first->size);
  printf("first block next: %p\n", (void *)first->next);
  printf("second block size: %llu\n", second->size);
  printf("second block next: %p\n", (void *)second->next);

  return 0;
}
