#include <stdio.h>
#include <string.h>

void encryptDecrypt(char *message, char *key) {
    int keyLen = strlen(key);
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= key[i % keyLen];
    }
}

int main() {
    char choice[10], message[256], key[32], filename[256];
    printf("Enter 'encrypt' or 'decrypt': ");
    scanf("%s", choice);
    getchar();

    if (strcmp(choice, "encrypt") == 0) {
        printf("Enter the string to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline
        printf("Enter key for encryption: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0'; 
        printf("Enter filename to save encrypted data: ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return 1;
        }

        encryptDecrypt(message, key);
        fwrite(message, sizeof(char), strlen(message), file);
        fclose(file);
    } else if (strcmp(choice, "decrypt") == 0) {
        printf("Enter filename to read encrypted data: ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Error opening file for reading.\n");
            return 1;
        }

        fread(message, sizeof(char), sizeof(message), file);
        fclose(file);

        printf("Enter the key to decrypt: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0'; // Remove newline

        encryptDecrypt(message, key);
        printf("Decrypted message: %s\n", message);
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    return 0;
}