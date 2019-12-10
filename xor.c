#include <stdio.h>
#define ENCODE_CHAR  'h'
char *EncodeAndDecode(char *dest);
int main(void){

    char source[100] = {"¹Ý°©½À´Ï´Ù"};
    EncodeAndDecode( source);
    printf("%s\n", source);
    EncodeAndDecode(source);
    printf("%s", source);
    return 0;
}

char *EncodeAndDecode(char *dest){
    int i = 0;
    while( *(dest + i) != '\0' )    {
        *(dest + i) ^= ENCODE_CHAR;
        i++;
    }   
    return dest;
}
