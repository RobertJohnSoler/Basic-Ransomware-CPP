#include <openssl/evp.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#define AES_BLOCK_SIZE 16

// code to test ecrypting an entire file with AES
// uses evp.h, which is already up-to-date and secure
int main(){
    int bytes_read;
    int bytes_written;
    unsigned char input_buffer[AES_BLOCK_SIZE];
    unsigned char output_buffer[AES_BLOCK_SIZE];
    unsigned char key_chars[] = "Hard-coded key here.";     // AES encryption key
    unsigned char iv[] = "some random IV value";            // AES initialization value
    FILE* infile_ptr = fopen("dummyfile.txt", "rb");        // open the input file (the file that contains the data to be encrypted)
    FILE* outfile_ptr = fopen("dummyfile.enc", "wb");       // open the output file (the file that will contain the encrypted data)

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();             // create the AES cipher
    int len;
    int ciphertext_len = 0;
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cfb(), NULL, key_chars, iv);    // initialize the AES cipher

    // while loop that encrypts the file in groups of 16 bytes (since that is the block size for AES) until it reaches the EOF
    // it reads 16 bytes from the input file, encrypts it, writes it to the output file, and repeats
    while(1){
        bytes_read = fread(input_buffer, 1, AES_BLOCK_SIZE, infile_ptr);
        int status = EVP_EncryptUpdate(ctx, output_buffer, &len, input_buffer, bytes_read);
        ciphertext_len = ciphertext_len + len;
        fwrite(output_buffer, 1, bytes_read, outfile_ptr);
        if (bytes_read < AES_BLOCK_SIZE){
            break;
        }
    }
    
    EVP_CIPHER_CTX_free(ctx);       // release the resources used when done
    fclose(infile_ptr);             // close both files
    fclose(outfile_ptr);

    return 0;
}