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
        FILE *file = NULL;
        while (1) {
                switch (read_input(path, sizeof path)) {
                case 0:
                        break;
                case 1:
                        fprintf(stderr, "Error reading input.\n");
                        return 1;
                case 2:
                        fprintf(stderr, "Input filename too long\n");
                        printf("Input filename: ");
                        continue;
                case 3:
                        fprintf(stderr,
                                "Internal error: capacity should not 0\n");
                        return 1;
                default:
                        return 1;
                }

                int home_count = convert_to_home(path, sizeof path);
                if (home_count > 1) {
                        fprintf(stderr, "Found more than 1 ~.\n");
                        printf("Input filename: ");
                        continue;
                }

                file = fopen(path, "rb");
                if (file == NULL) {
                        fprintf(stderr, "Error opening file\n");
                        printf("Input filename: ");
                        continue;
                }

                break;
        }

        char input_key[3];
        printf("Input the key (0 to 9): ");
        long value;
        while (1) {
                switch (read_input(input_key, sizeof input_key)) {
                case 0:
                        break;
                case 1:
                        fprintf(stderr, "Error reading input\n");
                        fclose(file);
                        return 1;
                case 2:
                        fprintf(stderr,
                                "Key too long, should be one digit.\n");
                        printf("Key: ");
                        continue;
                case 3:
                        fprintf(stderr, "Capacity should not be 0\n");
                        fclose(file);
                        return 1;
                default:
                        fclose(file);
                        return 1;
                }

                char *end;
                value = strtol(input_key, &end, 10);
                if (end == input_key || *end != '\0' || value < 0 ||
                    value > 9) {
                        fprintf(stderr, "Invalid key.\n");
			printf("Key (0 - 9): ");
			continue;
                }
                break;
        }
        unsigned char key = (unsigned char)value;

        char output_path[256];
        printf("Output filename: ");
        FILE *output = NULL;
        while (1) {
                switch (read_input(output_path, sizeof output_path)) {
                case 0:
                        break;
                case 1:
                        fprintf(stderr, "Error reading input\n");
                        fclose(file);
                        return 1;
                case 2:
                        fprintf(stderr, "Input too long. Try again\n");
                        printf("Output filepath: ");
                        continue;
                case 3:
                        fprintf(stderr, "Capacity should not 0\n");
                        fclose(file);
                        return 1;
                default:
                        fclose(file);
                        return 1;
                }

                int home_count =
                    convert_to_home(output_path, sizeof output_path);
                if (home_count > 1) {
                        fprintf(stderr,
                                "Found more than 1 ~. Try again.\n");
                        printf("Output filepath: ");
                        continue;
                }
                output = fopen(output_path, "wb");
                if (output == NULL) {
                        fprintf(stderr, "Error opening output file\n");
                        fclose(file);
                        return 1;
                }

                break;
        }

        unsigned char buffer[4096];
        unsigned char encrypted[4096];
        size_t nread;
        while ((nread = fread(buffer, 1, sizeof buffer, file)) > 0) {
                for (size_t i = 0; i < nread; i++) {
                        encrypted[i] = (char)buffer[i] ^ key;
                }
                if (fwrite(encrypted, 1, nread, output) != nread) {
                        fprintf(stderr, "Error writing output file\n");
                        fclose(file);
                        fclose(output);
                        return 1;
                }
        }

        if (ferror(file)) {
                fprintf(stderr, "Error reading file.\n");
                fclose(file);
                fclose(output);
                return 1;
        }

        fclose(file);
        fclose(output);
        printf("Encrypting file to %s is succesful\n", output_path);

        return 0;
}
