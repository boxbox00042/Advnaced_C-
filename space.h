#ifndef __SPACE__
#define __SPACE__



#define ELEMENT_SIZE 1024




void free_total_memory_space();
void manage_space(void *ptr,int size);
void print_buffer_status(void);
void our_malloc(int type, void **target, int *mem_location);
void our_free(int type, int mem_location);
int test_location(unsigned char *mask, int mask_length);
void set_bit(unsigned char *mask, int location, int type);
void clear_bit(unsigned char *mask, int location, int length);
int used_block();
void exitAndStore(void * fs_ptr, int size);
void EncryptDecryptContent(unsigned char *content, int size);
unsigned long long loadDump(unsigned char **fs_ptr, int *size);
void dump_manage_space(void *ptr, int size);
void generateRandomString(char * arr, int length);
void put_metadata_space(int size);
void change_element_offset(int size,int flag,unsigned long long offset);
void put_dump_metadata_space(int size);
#endif