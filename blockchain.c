#include "blockchain.h"

#include <sys/stat.h>


Blockchain* init_blockchain() {
    Blockchain *chain = (Blockchain *)malloc(sizeof(Blockchain));
    chain->head = create_genesis_block();
    return chain;
}

Block* create_genesis_block() {
    Block *genesis = (Block *)malloc(sizeof(Block));
    genesis->index = 0;
    strcpy(genesis->prev_hash, "0");
    time_t now = time(NULL);
    strftime(genesis->timestamp, sizeof(genesis->timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    strcpy(genesis->data, "Genesis Block");
    calculate_hash(genesis);
    genesis->next = NULL;
    return genesis;
}

Block* create_block(Block *prev_block, const char *data) {
    Block *new_block = (Block *)malloc(sizeof(Block));
    new_block->index = prev_block->index + 1;
    strcpy(new_block->prev_hash, prev_block->hash);
    time_t now = time(NULL);
    strftime(new_block->timestamp, sizeof(new_block->timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    strncpy(new_block->data, data, 255);
    calculate_hash(new_block);
    new_block->next = NULL;
    return new_block;
}

void add_block(Blockchain *chain, const char *data) {
    Block *current = chain->head;
    while (current->next) {
        current = current->next;
    }
    current->next = create_block(current, data);
}

void calculate_hash(Block *block) {
    char input[1024];
    snprintf(input, sizeof(input), "%d%s%s%s", block->index, block->prev_hash, block->timestamp, block->data);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)input, strlen(input), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(block->hash + (i * 2), "%02x", hash[i]);
    }
    block->hash[64] = '\0';
}

// void extract_file_metadata(const char *file_name, char *metadata) {
//     FILE *file = fopen(file_name, "r");
//     if (!file) {
//         perror("File not found");
//         strcpy(metadata, "File not found");
//         return;
//     }
//     fseek(file, 0, SEEK_END);
//     long file_size = ftell(file);
//     fclose(file);
//     snprintf(metadata, 256, "File: %s, Size: %ld bytes", file_name, file_size);
// }

// int validate_blockchain(Blockchain *chain) {
//     Block *current = chain->head;
//     while (current->next) {
//         Block *next = current->next;
//         char recalculated_hash[65];
//         calculate_hash(current);
//         if (strcmp(current->hash, next->prev_hash) != 0) {
//             return 0; // Tampered
//         }
//         current = next;
//     }
//     return 1; // Valid
// }

void modify_block(Blockchain *chain, int index, const char *new_data) {
    Block *current = chain->head;
    while (current) {
        if (current->index == index) {
            strncpy(current->data, new_data, 255);
            calculate_hash(current);
            return;
        }
        current = current->next;
    }
}

void display_blockchain(Blockchain *chain) {
    Block *current = chain->head;
    while (current) {
        printf("Block %d:\n", current->index);
        printf("  Timestamp: %s\n", current->timestamp);
        printf("  Data: %s\n", current->data);
        printf("  Hash: %s\n", current->hash);
        printf("  Prev Hash: %s\n", current->prev_hash);
        printf("----------------------------\n");
        current = current->next;
    }
}



void extract_file_metadata(const char *file_name, char *metadata) {
    struct stat file_stat;
    if (stat(file_name, &file_stat) != 0) {
        perror("File not found");
        strcpy(metadata, "File not found");
        return;
    }

    // Get file size
    long file_size = file_stat.st_size;

    // Get last modified time
    char mod_time[32];
    strftime(mod_time, sizeof(mod_time), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_mtime));

    // Get creation time (on systems that support it)
    char create_time[32];
    #ifdef __APPLE__
        strftime(create_time, sizeof(create_time), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_birthtime));
    #else
        strftime(create_time, sizeof(create_time), "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_ctime));
    #endif

    snprintf(metadata, 256, "File: %s, Size: %ld bytes, Created: %s, Modified: %s",
             file_name, file_size, create_time, mod_time);
}


int validate_blockchain(Blockchain *chain) {
    Block *current = chain->head;

    while (current) {
        char original_hash[65];
        strcpy(original_hash, current->hash); // Preserve the stored hash

        // Recalculate the hash of the current block
        calculate_hash(current);

        // Compare the recalculated hash with the original stored hash
        if (strcmp(current->hash, original_hash) != 0) {
            printf("Tampering detected in block %d. Stored hash does not match recalculated hash.\n", current->index);
            return 0; // Tampered
        }

        // If this is not the last block, validate the chain link
        if (current->next && strcmp(current->hash, current->next->prev_hash) != 0) {
            printf("Tampering detected in block %d (chain broken).\n", current->index);
            return 0; // Chain broken
        }

        current = current->next;
    }

    return 1; // Valid
}
