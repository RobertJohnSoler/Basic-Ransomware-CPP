#include <openssl/aes.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

int main(){
    int bytes_read;
    int bytes_written;
    unsigned char input_buffer[AES_BLOCK_SIZE];
    unsigned char output_buffer[AES_BLOCK_SIZE];
    unsigned char key_chars[] = "Hard-coded key here.";
    unsigned char iv[] = "some random IV value";
    FILE* infile_ptr = fopen("dummyfile.enc", "rb");
    FILE* outfile_ptr = fopen("dummyfile2.txt", "wb");

    AES_KEY key;
    AES_set_encrypt_key(key_chars, 128, &key);
    int num = 0;

    while(1){
        bytes_read = fread(input_buffer, 1, AES_BLOCK_SIZE, infile_ptr);
        AES_cfb128_encrypt(input_buffer, output_buffer, bytes_read, &key, iv, &num, AES_DECRYPT);
        bytes_written = fwrite(output_buffer, 1, bytes_read, outfile_ptr);
        if (bytes_read < AES_BLOCK_SIZE){
            break;
        }
    }
    fclose(infile_ptr);
    fclose(outfile_ptr);

    return 0;
}