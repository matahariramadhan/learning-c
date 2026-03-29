#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
        int password_length;
        int max_password_length = 30;
        printf("===Password "
               "Generator===\npassword lenght: ");
        if (scanf("%d", &password_length) != 1) {
                printf("invalid input\n");
                return 1;
        }

        if (password_length <
            1) { // this should not less than 1 or it will error
                printf("Minimum password length is 1\n");
                return 1;
        }

        if (password_length > max_password_length) {
                printf("Max password length is %d\n", max_password_length);
                return 1;
        }

        srand((unsigned int)time(NULL));

        char password[password_length +
                      1]; // plus 1 to add \0 in the end of string
        char charset[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'k', 'l', 'm',
                          'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
                          'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                          'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                          'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1',
                          '2', '3', '4', '5', '6', '7', '8', '9', '0'};
        for (int i = 0; i < password_length; i++) {
                password[i] =
                    charset[rand() % sizeof charset / sizeof charset[0]];
        }

	password[password_length] = '\0';

        printf("Your password: %s\n", password);
        return 0;
}
