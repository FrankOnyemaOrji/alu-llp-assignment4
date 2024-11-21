#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

// Block structure
typedef struct Block {
    int index;
    char prev_hash[65];
    char timestamp[32];
    char data[256];
    char hash[65];
    struct Block *next;
} Block;

// Blockchain structure
typedef struct Blockchain {
    Block *head;
} Blockchain;

// Function prototypes
Blockchain* init_blockchain();
Block* create_genesis_block();
Block* create_block(Block *prev_block, const char *data);
void add_block(Blockchain *chain, const char *data);
void calculate_hash(Block *block);
void extract_file_metadata(const char *file_name, char *metadata);
int validate_blockchain(Blockchain *chain);
void modify_block(Blockchain *chain, int index, const char *new_data);
void display_blockchain(Blockchain *chain);

#endif
