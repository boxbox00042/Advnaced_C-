#include "main.h"

// unsigned char buffer[ELEMENT_SIZE * NUM_BYTE_BUF];
// unsigned char byte_buf_mask[CEIL_DIVIDE] = {0};

unsigned char *buffer;
unsigned char byte_buf_mask[CEIL_DIVIDE] = {0};
void manage_space(void *ptr)
{

    buffer = ptr;
};
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

    location = test_location(byte_buf_mask, type);
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
            //     printf("i = %d,total=%d\n", i, total);
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
    //  printf("location is = %d\n", location);
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
