#include <openssl/aes.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

// code to test decrypting an entire file with AES
// uses aes.h, which is already deprecated, so we're not using it for our ransomware simulation
int main(){
    int bytes_read;
    int bytes_written;
    unsigned char input_buffer[AES_BLOCK_SIZE];
    unsigned char output_buffer[AES_BLOCK_SIZE];
    unsigned char key_chars[] = "Hard-coded key here.";     // AES decryption key
    unsigned char iv[] = "some random IV value";            // AES initialization value
    FILE* infile_ptr = fopen("dummyfile.enc", "rb");        // open the input file (the file that containts the encrypted data)
    FILE* outfile_ptr = fopen("dummyfile2.txt", "wb");      // oipen the output file (the file that will contain the decrypted data)

    AES_KEY key;
    AES_set_encrypt_key(key_chars, 128, &key);              // sets the decryption key to the given value
    int num = 0;

    // while loop that decrypts the file in groups of 16 bytes (since that is the block size for AES) until it reaches the EOF
    // it reads 16 bytes from the input file, decrypts it, writes it to the output file, and repeats
    while(1){
        bytes_read = fread(input_buffer, 1, AES_BLOCK_SIZE, infile_ptr);
        AES_cfb128_encrypt(input_buffer, output_buffer, bytes_read, &key, iv, &num, AES_DECRYPT);
        bytes_written = fwrite(output_buffer, 1, bytes_read, outfile_ptr);
        if (bytes_read < AES_BLOCK_SIZE){
            break;
        }
    }
    // close both files after using them
    fclose(infile_ptr);
    fclose(outfile_ptr);

    return 0;
}