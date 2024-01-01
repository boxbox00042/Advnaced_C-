#ifndef __SPACE__
#define __SPACE__

#define NUM_BYTE_BUF 4
#define CEIL_DIVIDE ((NUM_BYTE_BUF % 8 == 0) ? (NUM_BYTE_BUF / 8) : (NUM_BYTE_BUF / 8 + 1))
#define ELEMENT_SIZE 1024

void free_total_memory_space();
void manage_space(void *ptr);
void print_buffer_status(void);
void our_malloc(int type, void **target, int *mem_location);
void our_free(int type, int mem_location);
int test_location(unsigned char *mask, int mask_length);
void set_bit(unsigned char *mask, int location, int type);
void clear_bit(unsigned char *mask, int location, int length);

#endif