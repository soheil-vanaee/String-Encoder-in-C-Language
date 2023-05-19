#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* encode_base64(const char* user_string) {
    size_t input_length = strlen(user_string);
    size_t encoded_length = (((input_length + 2) / 3) * 4) + 1;

    char* encoded_string = (char*)malloc(encoded_length);
    if (encoded_string == NULL) {
        printf("Memory allocation failed.");
        return NULL;
    }

    size_t i = 0, j = 0;
    uint32_t buffer = 0;
    uint8_t buffer_length = 0;

    for (i = 0; i < input_length; i++) {
        buffer = (buffer << 8) | user_string[i];
        buffer_length += 8;

        while (buffer_length >= 6) {
            encoded_string[j++] = base64_chars[(buffer >> (buffer_length - 6)) & 0x3F];
            buffer_length -= 6;
        }
    }

    if (buffer_length > 0) {
        buffer <<= 6 - buffer_length;
        encoded_string[j++] = base64_chars[buffer & 0x3F];
        buffer_length += 6;
    }

    while (buffer_length % 8 != 0) {
        encoded_string[j++] = '=';
        buffer_length += 6;
    }

    encoded_string[j] = '\0';

    return encoded_string;
}
uint8_t decode_base64_char(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    } else if (c >= '0' && c <= '9') {
        return c - '0' + 52;
    } else if (c == '+') {
        return 62;
    } else if (c == '/') {
        return 63;
    } else {
        return 255; // Invalid character
    }
}

char* decode_base64(const char* encoded_string) {
    size_t input_length = strlen(encoded_string);
    size_t decoded_length = (input_length / 4) * 3;

    if (encoded_string[input_length - 1] == '=') {
        decoded_length--;
    }
    if (encoded_string[input_length - 2] == '=') {
        decoded_length--;
    }

    char* decoded_string = (char*)malloc(decoded_length + 1);
    if (decoded_string == NULL) {
        printf("Memory allocation failed.");
        return NULL;
    }

    size_t i = 0, j = 0;
    uint32_t buffer = 0;
    uint8_t buffer_length = 0;

    for (i = 0; i < input_length; i++) {
        char c = encoded_string[i];
        if (c == '=') {
            break;
        }

        buffer = (buffer << 6) | decode_base64_char(c);
        buffer_length += 6;

        if (buffer_length >= 8) {
            buffer_length -= 8;
            decoded_string[j++] = (buffer >> buffer_length) & 0xFF;
        }
    }
    decoded_string[j] = '\0';

    return decoded_string;
}


char* encode_xor(const char* user_string, const char* key) {
    size_t input_length = strlen(user_string);
    size_t key_length = strlen(key);

    char* encoded_string = (char*)malloc(input_length + 1);
    if (encoded_string == NULL) {
        printf("Memory allocation failed.");
        return NULL;
    }

    size_t i;
    for (i = 0; i < input_length; i++) {
        encoded_string[i] = user_string[i] ^ key[i % key_length];
    }

    encoded_string[input_length] = '\0';

    return encoded_string;
}

char* decode_xor(const char* encoded_string, const char* key) {
    return encode_xor(encoded_string, key); // XOR decryption is the same as XOR encryption
}

char* encode_caesar(const char* user_string, int shift) {
    size_t length = strlen(user_string);

    // Allocate memory for the encoded string
    char* encoded_string = (char*)malloc(length + 1);
    if (encoded_string == NULL) {
        printf("Memory allocation failed.");
        return NULL;
    }

    // Perform Caesar encoding
    for (size_t i = 0; i < length; i++) {
        char c = user_string[i];
        if (c >= 'a' && c <= 'z') {
            encoded_string[i] = 'a' + (c - 'a' + shift) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            encoded_string[i] = 'A' + (c - 'A' + shift) % 26;
        } else {
            encoded_string[i] = c;
        }
    }
    encoded_string[length] = '\0';

    return encoded_string;
}

char* decode_caesar(const char* encoded_string, int shift) {
    size_t length = strlen(encoded_string);

    // Allocate memory for the decoded string
    char* decoded_string = (char*)malloc(length + 1);
    if (decoded_string == NULL) {
        printf("Memory allocation failed.");
        return NULL;
    }

    // Perform Caesar decoding
    for (size_t i = 0; i < length; i++) {
        char c = encoded_string[i];
        if (c >= 'a' && c <= 'z') {
            decoded_string[i] = 'a' + (c - 'a' - shift + 26) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            decoded_string[i] = 'A' + (c - 'A' - shift + 26) % 26;
        } else {
            decoded_string[i] = c;
        }
    }
    decoded_string[length] = '\0';

    return decoded_string;
}

int main() {
    system("clear");

    printf("1: base64\n");
    printf("2: xor\n");
    printf("3: caesar\n");

    char choice[10];
    printf("=> ");
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0';

    char user_string[100];
    printf("Enter a string: ");
    fgets(user_string, sizeof(user_string), stdin);
    user_string[strcspn(user_string, "\n")] = '\0';

    if (strcmp(choice, "1") == 0) {
        char* encoded_string = encode_base64(user_string);
        printf("Base64 encoded string: %s\n", encoded_string);

        char* decoded_string = decode_base64(encoded_string);
        printf("Base64 decoded string: %s\n", decoded_string);

        free(encoded_string);
        free(decoded_string);
    }
    else if (strcmp(choice, "2") == 0) {
        char key[100];
        printf("Enter the XOR key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        char* encoded_string = encode_xor(user_string, key);
        printf("XOR encoded string: %s\n", encoded_string);

        char* decoded_string = decode_xor(encoded_string, key);
        printf("XOR decoded string: %s\n", decoded_string);

        free(encoded_string);
        free(decoded_string);
    }
    else if (strcmp(choice, "3") == 0) {
        int shift;
        printf("Enter the Caesar shift: ");
        scanf("%d", &shift);

        getchar(); // Consume the newline character from the previous input

        char* encoded_string = encode_caesar(user_string, shift);
        printf("Caesar encoded string: %s\n", encoded_string);

        char* decoded_string = decode_caesar(encoded_string, shift);
        printf("Caesar decoded string: %s\n", decoded_string);

        free(encoded_string);
        free(decoded_string);
    }
    else {
        printf("Invalid choice!\n");
    }

    return 0;
}
