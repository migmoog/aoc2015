#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int has_n_zeroes(unsigned char hash[MD5_DIGEST_LENGTH], int n)
{
    int full_bytes = n / 2;
    int read_nibble = n % 2 != 0;
    for (int i = 0; i < full_bytes; i++) {
        if (hash[i] != 0)
            return 0;
    }

    if (read_nibble && (hash[full_bytes] & 0xF0) != 0x00)
        return 0;
    
    return 1;
}

void hash_problem(unsigned char hash[MD5_DIGEST_LENGTH], char *input, int num)
{
    char *key = malloc(sizeof(char) * (strlen(input) + num + 1));
    sprintf(key, "%s%d", input, num);
    MD5((unsigned char *)key, strlen(key), hash);
    free(key);
}

int find_lowest(char *input, int zeroes)
{
    unsigned char hash[MD5_DIGEST_LENGTH];
    int out = 0;
    do
    {
        hash_problem(hash, input, out);
        if (has_n_zeroes(hash, zeroes))
            break;
        else
            out++;
    } while (1);

    return out;
}

void has_n_zeroes_tests() {
    // testing has_n_zeroes
    unsigned char hash[MD5_DIGEST_LENGTH];
    hash_problem(hash, "abcdef", 609043);
    assert(has_n_zeroes(hash, 5));
    hash_problem(hash, "abcdef", 9962624);
    assert(has_n_zeroes(hash, 6));
}

void d4(char *input)
{
    // has_n_zeroes_tests();
    printf("Day 4 part 1: %d\n", find_lowest(input, 5));
    printf("Day 4 part 2: %d\n", find_lowest(input, 6));
}