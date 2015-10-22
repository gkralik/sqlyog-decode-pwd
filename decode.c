#include <stdio.h>

/**
 * Decodes passwords as stored in
 * USERDIR\Application Data\SQLyog\sqlyog.ini
 *
 * Taken from SqlYog source
 * (https://github.com/webyog/sqlyog-community/blob/0165fb02932b4539d6f1cf2202cee3cf0e31bfdf/src/CommonHelper.cpp)
 *
 * @author Gregor Kralik <g.kralik@gmail.com>
 * @license GPL-2.0
 */

int decode_password(char *encrypted_password, char *cleartext);
void rotate_bit_left(unsigned char *str);
void rotate_bit_right(unsigned *str);
size_t decode_base64(const char *src, char *dest);
void decode_quantum(unsigned char *dest, const char *src);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("usage: %s encrypted_password\n", argv[0]);
        return 1;
    }
    else
    {
        char cleartext[512] = {0};

        decode_password(argv[1], cleartext);
        printf("%s\n", cleartext);

        return 0;
    }
}

int decode_password(char *encrypted_password, char *cleartext)
{
    decode_base64(encrypted_password, cleartext);
    rotate_bit_left((unsigned char*) cleartext);

    return 1;
}

void rotate_bit_left(unsigned char *str)
{
    int count;

    for(count = 0; str[count]; count++) {
        str[count] = (((str[count])<<(1)) | ((str[count])>>(8 - (1))));
    }

    return;
}

void rotate_bit_right(unsigned *str)
{
    int count;

    for(count = 0; str[count]; count++) {
        str[count] = (((str[count])>>(1)) | ((str[count])<<(8 - (1))));
    }

    return;
}

// decode a base64 buffer
size_t decode_base64(const char *src, char *dest)
{
	int length = 0;
	int equalsTerm = 0;
	int i;
	int numQuantums;
	unsigned char lastQuantum[3];
	size_t rawlen=0;

	while((src[length] != '=') && src[length])
		length++;
	while(src[length+equalsTerm] == '=')
		equalsTerm++;

	numQuantums = (length + equalsTerm) / 4;

	rawlen = (numQuantums * 3) - equalsTerm;

	for(i = 0; i < numQuantums - 1; i++) {
		decode_quantum((unsigned char *)dest, src);
		dest += 3; src += 4;
	}

	decode_quantum(lastQuantum, src);
	for(i = 0; i < 3 - equalsTerm; i++)
		dest[i] = lastQuantum[i];

	return rawlen;
}

void decode_quantum(unsigned char *dest, const char *src)
{
	unsigned int    x = 0;
	int     i;
	for(i = 0; i < 4; i++) {
		if(src[i] >= 'A' && src[i] <= 'Z')
			x = (x << 6) + (unsigned int)(src[i] - 'A' + 0);
		else if(src[i] >= 'a' && src[i] <= 'z')
			x = (x << 6) + (unsigned int)(src[i] - 'a' + 26);
		else if(src[i] >= '0' && src[i] <= '9')
			x = (x << 6) + (unsigned int)(src[i] - '0' + 52);
		else if(src[i] == '+')
			x = (x << 6) + 62;
		else if(src[i] == '/')
			x = (x << 6) + 63;
		else if(src[i] == '=')
			x = (x << 6);
	}

	dest[2] = (unsigned char)(x & 255);
	x >>= 8;
	dest[1] = (unsigned char)(x & 255);
	x >>= 8;
	dest[0] = (unsigned char)(x & 255);
}
