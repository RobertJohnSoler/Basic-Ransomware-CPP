#include <openssl/evp.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>

#define AES_BLOCK_SIZE 16

void encryptFile(unsigned char key_chars[], unsigned char iv[], const char* filename);
void printArr(unsigned char arr[]);

int main(){
    unsigned char key_chars[] = "Hard-coded key here.";
    unsigned char iv[] = "some random IV value";
    printf("Encrypting... \n");
    encryptFile(key_chars, iv, "dummyfile.txt");
    return 0;
}

void encryptFile(unsigned char key_chars[], unsigned char iv[], const char* filename){
    int bytes_read;
    int bytes_written;
    unsigned char input_buffer[AES_BLOCK_SIZE];
    unsigned char output_buffer[AES_BLOCK_SIZE];
    FILE* file_ptr = fopen(filename, "r+b");
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cfb(), NULL, key_chars, iv);

    while(1){
        long pos = ftell(file_ptr);
        bytes_read = fread(input_buffer, 1, AES_BLOCK_SIZE, file_ptr);
        int status = EVP_EncryptUpdate(ctx, output_buffer, &len, input_buffer, bytes_read);
        fseek(file_ptr, pos, SEEK_SET);
        fwrite(output_buffer, 1, bytes_read, file_ptr);
        fseek(file_ptr, pos+bytes_read, SEEK_SET);
        if (bytes_read < AES_BLOCK_SIZE){
            break;
        }
    }
    EVP_CIPHER_CTX_free(ctx);
    fclose(file_ptr);
}

void printArr(unsigned char arr[]){
    for (int i = 0; arr[i] != 0; ++i) {
        std::cout << arr[i]; // Cast to int to print numeric values
    }
    printf("\n");
}