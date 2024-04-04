#include <stdio.h>

int main(void){

    // Initialize and declare variables
    int num1 = 0;
    int num2 = 0;
    char operator = 0;
    

    while(operator == 0){
        
        // Obtaining num1, operator, and num2 from user input
        printf("Enter your calculation:\n");
        scanf("%d", &num1);
        scanf(" %c ", &operator);
        scanf("%d", &num2);

        

        if (operator == '+')
        {

            printf("> %d %c %d = %d\n", num1, operator, num2, num1 + num2);
            operator = 0;
        }
        else if (operator == '-')
        {

            printf("> %d %c %d = %d\n", num1, operator, num2, num1 - num2);
            operator = 0;
        }
        else if (operator == '*')
        {

            printf("> %d %c %d = %d\n", num1, operator, num2, num1 * num2);
            operator = 0;
        }
        else if (operator == '/')
        {
            if (num2 == 0)
            {

                printf("> ERROR: Can't divide by 0!\n");
            }
            else
            {

                printf("> %d %c %d = %d\n", num1, operator, num2, num1 / num2);
                operator = 0;
            }
        }
        else if (operator == '%')
        {

            printf("> %d %c %d = %d\n", num1, operator, num2, num1 % num2);
            operator = 0;
        }
        else if (operator == '&')
        {

            printf("> %d %c %d = %d\n", num1, operator, num2, num1 & num2);
            operator = 0;
        }
        else if (operator == '~')
        {

                printf("> %c %d = %d\n", operator, num2, ~(num2));
                operator = 0;
        } else
        {
            printf("Invalid calculation! \"%d %c %d\"\n", num1, operator, num2);

        } // END IF CONDITIONALS

    } // END WHILE

    return 0;
    
} // END MAIN