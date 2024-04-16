#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

typedef enum chemical_characters {
    CHEMICAL_A, CHEMICAL_T, CHEMICAL_C, CHEMICAL_G
} chemical_characters;
const char chemicals[4] = {'A', 'T', 'C', 'G'};

char* get_print_binary_string(FILE* stream, char u8) {
    static char buffer[9];
    for (int i = 0; i < 9; i++) {
        switch (i)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                buffer[i] = (u8 & 0b10000000) ? '1' : '0';
                u8 <<= 1;
                break;
            case 9:
                buffer[7] = '\0';
        }
    }
    if (stream)
        printf("%s", buffer);
    return buffer;
}

char fill_bits_less_than(char* u8) {
    const char original = *u8;
    while ((*u8 & 0b00000001) == 0)
    {
        *u8 |= original;
        *u8 >>= 1;
    }
    return original;
}

char get_complement(char chemical) {
    #define MAGIC_XOR 0b01010101;
    return chemical ^ MAGIC_XOR;
}

char* get_print_sequence_string(FILE* stream, char sequence_packed) {
    static char buffer[5];
    for (int i = 4; i >= 0; i--) {
        switch (i)
        {
            case 0:
            case 1:
            case 2:
            case 3:
                buffer[i] = chemicals[sequence_packed & 0b00000011];
                if (stream)
                sequence_packed >>= 2;
                break;
            case 4:
                buffer[4] = '\0';
        }
    }
    if (stream)
        fprintf(stream, "%s", buffer);
    return buffer;
}

int main() {
    char sequence_buffer[5];
    char* complement_string_ptr;
    for (unsigned long sequence = 0; sequence < 256; sequence++) {
        char s = (char)sequence;
        strncpy(sequence_buffer, get_print_sequence_string(stdout, s), 4);
        printf(" -> ");
        sequence_buffer[4] = '\0';
        char c = get_complement(s);
        complement_string_ptr = get_print_sequence_string(stdout, c);

        for (int i = 0; i < 4; i++)
        {
            char expected_complement_chemical;
            switch (sequence_buffer[i])
            {
            case 'A':
                expected_complement_chemical = 'T';
                break;
            case 'T':
                expected_complement_chemical = 'A';
                break;
            case 'C':
                expected_complement_chemical = 'G';
                break;
            case 'G':
                expected_complement_chemical = 'C';
                break;
            default:
                printf("ERROR: unnexpected chemical %c found in sequence buffer\n", sequence_buffer[i]);
                exit(EXIT_FAILURE);
            }

            assert(complement_string_ptr[i] == expected_complement_chemical);
        }

        printf(" tested %03d/255\r", sequence);
    }
    printf("\n");

    return 0;
}
