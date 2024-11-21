#include "blockchain.h"
#include <ctype.h>

int main() {
    Blockchain *chain = init_blockchain();
    int choice, index;
    char file_name[256], metadata[256], new_data[256];

    while (1) {
        printf("\nBlockchain Menu:\n");
        printf("1. Add Block with File Metadata\n");
        printf("2. Validate Blockchain\n");
        printf("3. Modify Block\n");
        printf("4. Display Blockchain\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        // Read choice and check for invalid input
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        // Clear input buffer
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                // Use fgets to read the file name
                fgets(file_name, sizeof(file_name), stdin);
                // Remove the newline character at the end
                file_name[strcspn(file_name, "\n")] = '\0';
                extract_file_metadata(file_name, metadata);
                add_block(chain, metadata);
                printf("Block added successfully.\n");
                break;
            case 2:
                if (validate_blockchain(chain)) {
                    printf("Blockchain is valid.\n");
                } else {
                    printf("Blockchain is tampered!\n");
                }
                break;
            case 3:
                printf("Enter block index to modify: ");
                if (scanf("%d", &index) != 1) {
                    printf("Invalid input. Please enter a number.\n");
                    while (getchar() != '\n');
                    break;
                }
                // Clear input buffer
                while (getchar() != '\n');
                printf("Enter new data: ");
                fgets(new_data, sizeof(new_data), stdin);
                new_data[strcspn(new_data, "\n")] = '\0';
                modify_block(chain, index, new_data);
                printf("Block modified successfully.\n");
                break;
            case 4:
                display_blockchain(chain);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
