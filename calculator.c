#include <stdio.h>

// Function declarations for basic arithmetic operations
float add(float n1, float n2) {
    return n1 + n2;
}

float subtract(float n1, float n2) {
    return n1 - n2;
}

float multiply(float n1, float n2) {
    return n1 * n2;
}

float divide(float n1, float n2) {
    return n1 / n2;
}

// Function pointer type for operations
typedef float (*Operation)(float, float);

// Structure to represent an operation
struct OperationEntry {
    char symbol;
    Operation op;
};

// Array of operation entries
struct OperationEntry operations[] = {
    {'+', add},
    {'-', subtract},
    {'*', multiply},
    {'/', divide}
};

// Function to perform a specific operation
float performOperation(float n1, float n2, Operation op) {
    return op(n1, n2);
}

// Function to print the ASCI calculator logo
void printLogo() {
    printf(
        " .----------------.  .----------------.  .----------------.  .----------------. \n"
        "| .--------------. || .--------------. || .--------------. || .--------------. |\n"
        "| |              0. | | |     ______   | || |      __      | || |   _____      | |\n"
        "| |_________________| | |   .' ___  |  | || |     /  \\     | || |  |_   _|     | |\n"
        "|  ___ ___ ___   ___  | |  / .'   \\_|  | || |    / /\\ \\    | || |    | |       | |\n"
        "| | 7 | 8 | 9 | | + | | |  | |         | || |   / ____ \\   | || |    | |   _   | |\n"
        "| |___|___|___| |___| | |  \\ `.___.'\\  | || | _/ /    \\ \\_ | || |   _| |__/ |  | |\n"
        "| | 4 | 5 | 6 | | - | | |   `._____.'  | || ||____|  |____|| || |  |________|  | |\n"
        "| |___|___|___| |___| | |              | || |              | || |              | |\n"
        "| | . | 0 | = | | / | | | '--------------' || '--------------' || '--------------' |\n"
        "| |___|___|___| |___| |  '----------------'  '----------------'  '----------------' \n"
        "|_____________________|"
    );
}

// Function to handle the calculation process
void calculation() {
    // Display the calculator logo
    printLogo();

    float num1, num2;
    // Get the first number from the user
    printf("\nWhat's the first number?: ");
    scanf("%f", &num1);

    // Display available operations to the user
    for (int i = 0; i < sizeof(operations) / sizeof(operations[0]); i++) {
        printf("%c ", operations[i].symbol);
    }

    char operation_symbol;
    // Get the desired operation from the user
    printf("\nPick an operation from the line above: ");
    scanf(" %c", &operation_symbol);

    // Get the second number from the user
    printf("What's the second number?: ");
    scanf("%f", &num2);

    Operation calculation_function = NULL;

    // Find the corresponding function for the selected operation
    for (int i = 0; i < sizeof(operations) / sizeof(operations[0]); i++) {
        if (operations[i].symbol == operation_symbol) {
            calculation_function = operations[i].op;
            break;
        }
    }

    if (calculation_function != NULL) {
        // Perform the initial calculation
        float first_answer = performOperation(num1, num2, calculation_function);
        // Display the result
        printf("%.2f %c %.2f = %g\n", num1, operation_symbol, num2, first_answer);

        char repeat;
        // Ask the user if they want to continue with the result
        printf("Type 'y' to continue calculating with %.2f, or type 'n' to exit.: ", first_answer);
        scanf(" %c", &repeat);

        // Continue the calculation loop as long as the user wants to
        while (repeat != 'n') {
            // Get the next operation from the user
            printf("Pick an operation: ");
            scanf(" %c", &operation_symbol);

            float num3;
            // Get the next number from the user
            printf("What's the next number?: ");
            scanf("%f", &num3);

            // Find the corresponding function for the selected operation
            for (int i = 0; i < sizeof(operations) / sizeof(operations[0]); i++) {
                if (operations[i].symbol == operation_symbol) {
                    calculation_function = operations[i].op;
                    break;
                }
            }

            if (calculation_function != NULL) {
                // Perform the next calculation
                float second_answer = performOperation(first_answer, num3, calculation_function);
                // Display the result
                printf("%.2f %c %.2f = %g\n", first_answer, operation_symbol, num3, second_answer);
                // Ask the user if they want to continue with the new result
                printf("Type 'y' to continue calculating with %.2f, or type 'n' to exit.: ", second_answer);
                scanf(" %c", &repeat);

                first_answer = second_answer;
            } else {
                printf("Invalid operation.\n");
                break;
            }
        }
    } else {
        printf("Invalid operation.\n");
    }
}

// Main function
int main() {
    // Start the calculation process
    calculation();
    return 0;
}
