#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int clear_input(void) {
        int ch = getchar();
        while (ch != (int)'\n') {
                if (ch == EOF) {
                        return 1;
                }
                ch = getchar();
        }
        return 0;
}

/* Safely read input from user and store string in variable
 * 0: success, line fit cleanly,
 * 1: input read failed,
 * 2: input too long, remainder flushed
 * 3: capacity is 0
 */
int read_input(char *ptr, size_t capacity) {
        if (capacity == 0) {
                return 3;
        }
        if (fgets(ptr, capacity, stdin) == NULL) {
                ptr[0] = '\0';
                return 1;
        }
        char *pointer;
        if ((pointer = strchr(ptr, '\n')) == NULL) {
                ptr[0] = '\0';
                clear_input();
                return 2;
        }
        *pointer = '\0';
        return 0;
}

/* Convert ~ in string to home
 * return: sum of ~ found
 */
int convert_to_home(char *ptr, size_t size) {
        int found = 0;
        char buffer[256];
        int buff_count = 0;
        for (size_t i = 0; i < size; i++) {
                if (ptr[i] == '\0') {
                        buffer[buff_count] = '\0';
                        for (size_t i = 0; i < sizeof buffer; i++) {
                                if (buffer[i] == '\0') {
                                        ptr[i] = '\0';
                                        break;
                                }
                                ptr[i] = buffer[i];
                        }
                        return found;
                }
                if (ptr[i] == '~') {
                        char *home = getenv("HOME");
                        size_t j = 0;
                        while (home[j] != '\0') {
                                buffer[buff_count] = home[j];
                                buff_count++;
                                j++;
                        }
                        found++;
                        continue;
                }
                buffer[buff_count] = ptr[i];
                buff_count++;
        }

        return found;
}

int main(void) {
        printf("===File Encryption Tool===\nInput filepath :");
        char path[256];
        int status;
        while ((status = read_input(path, sizeof path)) != 0) {
                if (status == 2) {
                        fprintf(stderr, "Input too long. Try again.\n");
                        printf("Input filepath: ");
                        continue;
                }
                return 1;
        }

        char input_key[3];
        printf("Input the key (0 to 9): ");
        while ((status = read_input(input_key, sizeof input_key)) != 0) {
                if (status == 2) {
                        fprintf(stderr, "key too long. Try again.\n");
                        printf("Input the key (0 to 9) ");
                        continue;
                }
                return 1;
        }

        char *end;
        long value = strtol(input_key, &end, 10);
        if (end == input_key || *end != '\0' || value < 0 || value > 255) {
                fprintf(stderr, "Invalid key!");
                return 1;
        }
        unsigned char key = (unsigned char)value;

        char output_path[256];
        printf("Output filename: ");
        while ((status = read_input(output_path, sizeof output_path)) !=
               0) {
                if (status == 2) {
                        fprintf(stderr,
                                "Output filename too long. Try again.\n");
                        printf("Output filename: ");
                        continue;
                }
                return 1;
        }

        convert_to_home(path, sizeof path);
        FILE *file = fopen(path, "rb");
        if (file == NULL) {
                fprintf(stderr, "Fail to open file\n");
                return 1;
        }

        convert_to_home(output_path, sizeof output_path);
        FILE *output = fopen(output_path, "wb");
        if (output == NULL) {
                fprintf(stderr, "Error opening output file");
                fclose(file);
                return 1;
        }

        unsigned char buffer[4096];
        unsigned char encrypted[4096];
        size_t nread;
        while ((nread = fread(buffer, 1, sizeof buffer, file)) > 0) {
                for (size_t i = 0; i < nread; i++) {
                        encrypted[i] = (char)buffer[i] ^ key;
                }
                fwrite(encrypted, 1, nread, output);
        }

        fclose(file);
        fclose(output);
        printf("Encrypting file to %s is succesful\n", output_path);

        return 0;
}
