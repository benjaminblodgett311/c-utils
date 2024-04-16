// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum chemicalCharacter {
    A, T, C, G
} chemicalCharacter;
const char chemicals[4] = {'A', 'T', 'C', 'G'};

char* getPrintBinaryString(char u8) {
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
    printf("%s\n", buffer);
    return buffer;
}

char fillBitsLessThan(char* u8) {
    const char original = *u8;
    while ((*u8 & 0b00000001) == 0)
    {
        *u8 |= original;
        *u8 >>= 1;
    }
    return original;
}

char getComplement(char chemical) {
    #define MAGIC_XOR 0b01010101;
    char chemicalXor = chemical ^ MAGIC_XOR;
    if (chemicalXor <= chemical)
        return chemicalXor;
    
    char chemicalDiv = chemicalXor / chemical;
    fillBitsLessThan(&chemicalDiv);
    chemicalXor &= chemicalDiv;
    
    return chemicalXor;
}

char* getPrintSequenceString(char sequencePacked) {
    static char buffer[5];
    for (int i = 4; i >= 0; i--) {
        switch (i)
        {
            case 0:
            case 1:
            case 2:
            case 3:
                buffer[i] = chemicals[sequencePacked & 0b00000011];
                printf("%c ", buffer[i]);
                sequencePacked >>= 2;
                break;
            case 4:
                buffer[4] = '\0';
        }
    }
    printf("%s\n", buffer);
    return buffer;
}

int main() {
    for (char i = 0; i < 256; i++) {
        getPrintSequenceString(i);
        char c = getComplement(i);
        getPrintSequenceString(c);
    }

    return 0;
}
