#include <openssl/evp.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#define AES_BLOCK_SIZE 16

int main(){
    int bytes_read;
    int bytes_written;
    unsigned char input_buffer[AES_BLOCK_SIZE];
    unsigned char output_buffer[AES_BLOCK_SIZE];
    unsigned char key_chars[] = "Hard-coded key here.";
    unsigned char iv[] = "some random IV value";
    FILE* infile_ptr = fopen("dummyfile.txt", "rb");
    FILE* outfile_ptr = fopen("dummyfile.enc", "wb");

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;
    int ciphertext_len = 0;
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cfb(), NULL, key_chars, iv);

    while(1){
        bytes_read = fread(input_buffer, 1, AES_BLOCK_SIZE, infile_ptr);
        int status = EVP_EncryptUpdate(ctx, output_buffer, &len, input_buffer, bytes_read);
        ciphertext_len = ciphertext_len + len;
        fwrite(output_buffer, 1, bytes_read, outfile_ptr);
        if (bytes_read < AES_BLOCK_SIZE){
            break;
        }
    }
    EVP_CIPHER_CTX_free(ctx);
    fclose(infile_ptr);
    fclose(outfile_ptr);

    return 0;
}