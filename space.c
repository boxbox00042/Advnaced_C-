#include "main.h"

unsigned char *buffer;
int NUM_BYTE_BUF;
int CEIL_DIVIDE;
unsigned char *byte_buf_mask;

void dump_manage_space(void *ptr, int size)
{
    buffer = ptr;
    NUM_BYTE_BUF = size / ELEMENT_SIZE;
    if (NUM_BYTE_BUF % 8 == 0)
    {
        CEIL_DIVIDE = NUM_BYTE_BUF / 8;
    }
    else
    {
        CEIL_DIVIDE = NUM_BYTE_BUF / 8 + 1;
    }
    byte_buf_mask = buffer;
}
void change_element_offset(int size, int flag, unsigned long long offset)
{
    unsigned char set_bit = 0x01;
    int i, j;
    set_bit = set_bit << 2;
    i = 2;
    void *ptr;
    while (i < NUM_BYTE_BUF)
    {
        j = i / 8;
        if (((i - 8) % 8 == 0))
        {
            set_bit = 0x01;
        }

        if (byte_buf_mask[j] & set_bit)
        {

            ptr = buffer + (i * BLOCK_SIZE);
            if (((folder *)(ptr))->type == 0)
            {

                for (int k = 0; k < FOLDER_SIZE; k++)
                {
                    if (((folder *)(ptr))->entry_array[k] != NULL)
                    {
                        if (flag == 0)
                        {
                            folder *entry = ((folder *)(ptr))->entry_array[k];
                            entry = (folder *)((unsigned long long)entry - offset);
                            ((folder *)(ptr))->entry_array[k] = entry;
                        }
                        else
                        {
                            folder *entry = ((folder *)(ptr))->entry_array[k];
                            entry = (folder *)((unsigned long long)entry + offset);
                            ((folder *)(ptr))->entry_array[k] = entry;
                        }
                    }
                }
            }
        };
        i++;
        set_bit = set_bit << 1;
    }
};
void manage_space(void *ptr, int size)
{
    buffer = ptr;
    NUM_BYTE_BUF = size / ELEMENT_SIZE;
    if (NUM_BYTE_BUF % 8 == 0)
    {
        CEIL_DIVIDE = NUM_BYTE_BUF / 8;
    }
    else
    {
        CEIL_DIVIDE = NUM_BYTE_BUF / 8 + 1;
    }

    byte_buf_mask = buffer;
    for (int i = 0; i < CEIL_DIVIDE; i++)
    {
        byte_buf_mask[i] = 0;
    }
    void *null_ptr = NULL;
    int location = 0;
    our_malloc(0, &null_ptr, &location);
};

void put_dump_metadata_space(int size)
{
    void *data = buffer + BLOCK_SIZE;
    ((meta_data *)(data))->head_ptr = (unsigned long long)buffer;
}
void generateRandomString(char *arr, int length)
{
    srand(5);

    for (int i = 0; i < length; i++)
    {
        char randomchar = rand() % 128;
        arr[i] = randomchar;
    }
}
void put_metadata_space(int size)
{
    void *ptr = NULL;
    int location;
    our_malloc(1, &ptr, &location);
    meta_data *data = ptr;
    data->head_ptr = (unsigned long long)buffer;
}
void free_total_memory_space()
{
    free(buffer);
}
int used_block()
{
    int i, j, total = 0;
    unsigned char mask = 0x80;

    for (i = CEIL_DIVIDE - 1; i >= 0; i--)
    {

        for (j = 7; j >= 0; j--)
        {

            if ((i * 8 + j + 1) <= NUM_BYTE_BUF)
            {
                if ((byte_buf_mask[i] & mask) >> (j) == 1)
                {
                    total++;
                }
            }
            mask = mask >> 1;
        }

        mask = 0x80;
    }

    return total;
}
void print_buffer_status(void)
{
    int i, j, total = 0;
    unsigned char mask = 0x80;

    printf("      byte_buf_mask: ");
    for (i = CEIL_DIVIDE - 1; i >= 0; i--)
    {

        for (j = 7; j >= 0; j--)
        {

            if ((i * 8 + j + 1) <= NUM_BYTE_BUF)
            {
                printf("%d ", (byte_buf_mask[i] & mask) >> (j));
            }
            mask = mask >> 1;
        }
        printf(", ");
        mask = 0x80;
    }

    printf("\n");
}

void our_malloc(int type, void **target, int *mem_location)
{
    int location;
    if (type == 0)
    {
        type = 1;
        location = 0;
        set_bit(byte_buf_mask, location, type);
        return;
    }
    else
    {
        location = test_location(byte_buf_mask, type);
    }
    if (location >= 0)
    {
        set_bit(byte_buf_mask, location, type);
        *target = &buffer[location * 1024];
        *mem_location = location;
    }
    else
    {
        return;
    }
}

int test_location(unsigned char *mask, int mask_length)
{
    unsigned char check_bit = 0x01;
    int total = 0;
    int i, j = 0;
    for (i = 0; i < NUM_BYTE_BUF; i++)
    {

        if (!(mask[j] & check_bit))
        {
            total++;
        }
        else
        {
            total = 0;
        }
        if (total == mask_length)
        {
            return i - total + 1;
        }

        check_bit = check_bit << 1;
        if (check_bit == 0)
        {
            check_bit = 0x01;
            j++;
        }
    }

    return -1;
}

void set_bit(unsigned char *mask, int location, int length)
{
    unsigned char set_bit = 0x01;
    int i, j;
    set_bit = set_bit << (location % 8);
    for (i = location; i < location + length; i++)
    {
        j = i / 8;
        if (((i - 8) % 8 == 0))
        {
            set_bit = 0x01;
        }
        mask[j] = mask[j] | set_bit;

        set_bit = set_bit << 1;
    }
}

void clear_bit(unsigned char *mask, int location, int length)
{
    unsigned char clear_bit = 0x01;
    int i, j;
    clear_bit = clear_bit << (location % 8);
    for (i = location; i < location + length; i++)
    {
        j = i / 8;
        if (((i - 8) % 8 == 0))
        {
            clear_bit = 0x01;
        }
        mask[j] = mask[j] & (~clear_bit);

        clear_bit = clear_bit << 1;
    }
}

void our_free(int type, int mem_location)
{
    clear_bit(byte_buf_mask, mem_location, type);
}
void EncryptDecryptContent(unsigned char *content, int size)
{
    // input parameter: 1. the content to be translated 2. size
    // use the encryption algorithm to encrypt content
    // encryption algorithm : use XOR ( every content ^ encrypt keys by order )
    int content_length = size;
    int encrypt_keys_length = 1000;
    int i = 0;
    char encrypt_keys[1000];
    generateRandomString(encrypt_keys, 1000);

    for (int j = 0; j < content_length; j++)
    {
        content[j] = content[j] ^ encrypt_keys[i % encrypt_keys_length];
        i++;
    }
}
void exitAndStore(void *fs_ptr, int size)
{
    printf("Plase input the password of this dump file: (less then 15 words)\n");
    char input_password[16];
    scanf(" %s", input_password);
    void *data = fs_ptr + BLOCK_SIZE;
    strcpy(((meta_data *)(data))->password, input_password);

    FILE *dump;
    dump = fopen("my_fs.dump", "wb");
    EncryptDecryptContent(fs_ptr, size);
    fwrite(fs_ptr, sizeof(unsigned char), size, dump);
    fclose(dump);
}

unsigned long long loadDump(unsigned char **fs_ptr, int *size)
{
    char input_password[16];
    printf("Plase input the password: (less then 15 words)\n");
    scanf(" %s", input_password);
    fgetc(stdin);

    FILE *dump;
    dump = fopen("my_fs.dump", "rb");
    if (dump == NULL)
    {
        printf("File system file not found!");
        return -1;
    }

    fseek(dump, 0, SEEK_END);
    *size = ftell(dump);
    fseek(dump, 0, SEEK_SET);
    *fs_ptr = malloc(*size);
    fread(*fs_ptr, sizeof(unsigned char), *size, dump);
    void *data = *fs_ptr + BLOCK_SIZE;
    EncryptDecryptContent(*fs_ptr, *size);
    unsigned long long now_location = ((meta_data *)(data))->head_ptr;
    char load_passwoard[16];
    strcpy(load_passwoard, ((meta_data *)(data))->password);

    if (strcmp(input_password, load_passwoard) != 0)
    {
        printf("password is not correct!\n");
        return -1;
    }
    printf("password is correct!\n");

    fclose(dump);
    return now_location;
}