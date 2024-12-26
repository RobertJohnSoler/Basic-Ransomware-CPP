#include <openssl/evp.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>

#define AES_BLOCK_SIZE 16

void encryptFile(unsigned char key_chars[], unsigned char iv[], const char* filename);

// code to test ecrypting an entire file with AES,
// but this time it overwrites the original plaintext data (just like in ransomware)
// uses evp.h, which is already up-to-date and secure
int main(){
    unsigned char key_chars[] = "Hard-coded key here.";     // AES encryption key
    unsigned char iv[] = "some random IV value";            // AES initialization value
    printf("Encrypting... \n");
    encryptFile(key_chars, iv, "dummyfile.txt");             // open the input file (the file that WILL BE encrypted)
    return 0;
}

// function that encrypts a file given an encryption key and initialization value
void encryptFile(unsigned char key_chars[], unsigned char iv[], const char* filename){
    int bytes_read;
    int bytes_written;
    unsigned char input_buffer[AES_BLOCK_SIZE];
    unsigned char output_buffer[AES_BLOCK_SIZE];
    FILE* file_ptr = fopen(filename, "r+b");
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cfb(), NULL, key_chars, iv);

    // while loop that encrypts the file in groups of 16 bytes (since that is the block size for AES) until it reaches the EOF
    // it reads 16 bytes of plaintext from the input file, encrypts it, then overwrites it with the result ciphertext
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
    EVP_CIPHER_CTX_free(ctx);   // release the resources used when done
    fclose(file_ptr);           // closes the file after use
}