/**
 * @file inputs_geral.c
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights Reserved under MIT License.
 *
 * @brief File inputs_geral.c contains functions that can be used in various parts of the code.
 *
 * In inputs_geral.c there are functions that can be used in more than one .c file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "inputs_geral.h"
#include "inputs_user.h"
#include "inputs_comp.h"

static int i;

/**
 * @brief Clears the input buffer.
 *
 * This function reads and discards all remaining characters in the input buffer.
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * @brief Converts a string to uppercase.
 *
 * This function goes through each character of the string. If the first character of each word in the string is lowercase, it is converted to uppercase. (e.g., it receives "joao pedro" and transforms it into "Joao Pedro")
 *
 * @param string The string to be converted to uppercase. The string is passed by reference, therefore, the changes made in the function will affect the original string.
 */
void uppercase(char *string) {   
    if (string[0] > 97 && string[0] < 122) {
        string[0] = string[0] - 32;
    }
    
    for (i = 0; i < strlen(string); i++) {
        if (string[i] == ' ' && (string[i + 1] >= 97 && string[i + 1] <= 122)) {
            string[i + 1] = string[i + 1] - 32;
        }
    }   
}

/**
 * @brief Removes extra spaces from a string.
 *
 * This function goes through the string and removes all extra spaces. It removes spaces at the beginning of the string, at the end of the string, and multiple spaces between words.
 *
 * @param string The string from which extra spaces should be removed. The string is passed by reference, therefore, the changes made in the function will affect the original string.
 */
void remove_extra_spaces(char *string) {   
    int size = strlen(string);

    while (string[0] == ' ') {
        for (i = 0; i < size; i++) {
            string[i] = string[i + 1];        
        }
        size--;
    }
    
    if (string[size] == ' ' || string[size] == 0) {
        while (size > 0 && string[size - 1] == ' ') {
            size--;
        }
        
    }
    
    for (i = 0; i < size; i++) {
        if (string[i] == ' ' && string[i+1] == ' ') {
            for (int y = i; y < size; y++) {
                string[y] = string[y + 1];
            }
            size--;
            i--;
        }
    }  
    
    string[size] = '\0';
}

/**
 * @brief Reads a string and removes extra spaces.
 *
 * This function displays a message to the user, reads a string from stdin and stores it in the string variable. 
 * If the read string ends with a newline character, it is replaced by a null character. 
 * If the read string does not end with a newline character, the cleanInputBuffer() function is called to clear the 
 * input buffer. If the read string is empty, a message is displayed to the user and the reading is repeated.
 * Finally, the remove_extra_spaces() function is called to remove any extra spaces from the read string.
 *
 * @param string The string in which the user's input should be stored. The string is passed by reference, therefore, the changes made in the function will affect the original string.
 * @param size The maximum number of characters to be read, including the final null character.
 * @param msg The message to be displayed to the user before reading the input.       
 */
void readString(char *string, unsigned int size, char *msg) {
    do {
        printf(msg);
        if (fgets(string, size, stdin) != NULL) {
            unsigned int len = strlen(string) - 1;
            if (string[len] == '\n') {
                string[len] = '\0';
            } else {
                cleanInputBuffer();
            }
        } 
        
        if (strlen(string) == 0) {
            printf("Por favor preencha o campo solicitado!\n");
        }        
    } while (strlen(string) == 0);
    
    remove_extra_spaces(string);    
}

/**
 * @brief Reads an integer value from the user that is within a range.
 *
 * This function displays a message to the user, reads an integer value from stdin and checks if the value is within the 
 * specified range. If the reading fails or if the read value is outside the range, an error message is 
 * displayed and the reading is repeated. The function continues to read until a valid value is provided by the user.
 *
 * @param minValue The minimum value that the user can enter.
 * @param maxValue The maximum value that the user can enter.
 * @param msg The message to be displayed to the user before reading the input.
 * @return The integer value read from the user.
 */
int getInt(int minValue, int maxValue, char *msg) {
    int value;
    printf(msg);
    while (scanf("%d", &value) != 1 || value < minValue || value > maxValue) {
        printf(INVALID_VALUE, minValue, maxValue);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return value;
}

/**
 * @brief Reads a character.
 *
 * This function reads a character from stdin and stores it in the value variable. Then, the cleanInputBuffer() function is 
 * called to clear the input buffer. The function returns the read character.
 *
 * @return The character read from the user.
 */
char getChar() {
    char value;
    value = getchar();
    cleanInputBuffer();       
    return value;
}

/**
 * @brief Checks if there is any active company with an active branch
 *
 * This function goes through the 'Companies' struct and counts how many are inactive or have their branches also 
 * inactive. If all companies are inactive or have an inactive branch, the function returns 1, otherwise, it returns 0.
 *
 * @param companies The 'Companies' struct that contains all created companies, to be checked.
 * @return 1 if all companies are inactive or have an inactive branch, 0 otherwise.
 */
int valid_comp(Companies companies) {
    int invalid = 0;
    for (i = 0; i < companies.cont_comp; i++) {
        if (companies.company[i].state == INACTIVE || companies.company[i].branch.state == INACTIVE) {
            invalid++;
        }    
    }
    
    if (invalid == companies.cont_comp) {
        return 1;
    }
    
    return 0;    
}

/**
 * @brief Checks if there is any active company
 *
 * This function goes through the 'Companies' struct and counts how many are inactive.
 * If all companies are inactive, the function returns 1, otherwise, it returns 0.
 *
 * @param companies The 'Companies' struct that contains all created companies, to be checked.
 * @return 1 if all companies are inactive, 0 otherwise.
 */
int active_comp(Companies companies) {
    int invalid = 0;
    for (i = 0; i < companies.cont_comp; i++) {
        if (companies.company[i].state == INACTIVE) {
            invalid++;
        }    
    }
    
    if (invalid == companies.cont_comp) {
        return 1;
    }
    
    return 0;    
}
/**
 * @brief This function performs the repetition of an option based on user input
 * Then, it enters a do-while loop that continues until "rep" is 'S', 's', 'N' or 'n'.
 * Inside the loop, it uses a switch case structure to handle different cases based on the value of "op". 
 * If "op" is 0, it prints a confirmation message. If "op" is 1, it prints a general message with "option" and "structs".
 * Then, it assigns a character value to "rep" using the "getChar()" function. If "rep" is a lowercase letter, 
 * it converts it to uppercase. If "rep" is not 'S' or 'N', it prints an invalid option message.
 * If "rep" is 'S', the function returns 0, and repeats the user's option. If "rep" is 'N', the function returns 1. 
 * The loop continues until "rep" is 'S' or 'N'.
 *
 * @param op The operation code to determine the type of message to be printed.
 * @param option A pointer to a character string representing the option.
 * @param structs A pointer to a character string representing the structs.
 * @return 0 if the repetition character is 'S', 1 if it is 'N'.
 */
int repet_option(int op, char *option, char *structs) {        
    char rep = ' ';
    do {
         switch (op) {  
            case 0: {
                printf(MSG_REP_CONFIRME);
                break;
            }
            case 1: {
                printf(MSG_REP_GENERAL, option, structs);
                break;
            }
            default: {
                break;
            }
        }     
        
        rep = getChar();
        
        if (rep > 97 && rep < 122) {
            rep = rep - 32;
        } else if (rep != 's' && rep != 'S' && rep != 'N' && rep != 'n') {
            printf("Opção Inválida (Introduza S ou s para Sim e N ou n para Não)!\n");
        }
        
        if (rep == 'S') {
            return 0;
        } else if (rep == 'N'){
            return 1;
        }
    } while (rep != 'S' || rep != 'N');    
}

/**
 * @brief Checks if the NIF (Fiscal Identification Number) provided by the user exists in the Companies struct
 *
 * It uses a loop to go through the entire Companies struct to check if the NIF of any of the companies stored in the struct
 * is equal to the NIF entered by the user. If they are equal, it prints a message indicating that the entered NIF 
 * belongs to the company and returns the index 'i' of the company in the struct.
 * If "nif_v" is not equal to the NIF of the current company and the loop has reached the last company in the struct, it prints an 
 * error message indicating that the NIF was not found and returns -1.
 *
 * @param companies The 'Companies' struct that contains all created companies.
 * @param nif_v The NIF to be compared with the NIFs of the companies.
 * @return The index of the company if the NIF is found, -1 otherwise.
 */
int compare_nif(Companies companies, int nif_v) { 
    for (i = 0; i < companies.cont_comp; i++) {
        if (nif_v == companies.company[i].nif) {
            printf("O Nif %d, que introduziu, pretence à empresa %s\n", companies.company[i].nif, companies.company[i].name_compa); 
            return i;
        } else if (nif_v != companies.company[i].nif && (i == (companies.cont_comp - 1))) {
            printf(ERROR_MSG_NIF_NOT_FIND, nif_v);
            return -1;
        }
    }
}

/**
 * @brief This function prompts the user to enter a NIF (Fiscal Identification Number) and checks if it exists in the Companies struct.
 *
 * Then, it calls the "getInt" function to prompt the user to enter a NIF.
 * Finally, it calls the "compare_nif" function with 'companies' and 'nif' as parameters and returns the result of the compare_nif function.
 * 
 * @param companies The 'Companies' struct that contains all created companies.
 * @return The index of the company if the NIF is found, -1 otherwise.
 */
int insert_nif(Companies companies) {    
    int nif = 0;

    nif = getInt(MIN_VALUE_NIF, MAX_VALUE_NIF, MSG_INSERT_NIF_COMPANY);       

    return compare_nif(companies, nif);
}

/**
 * @brief This function reads and validates the user's email and username.
 * 
 * It first enters a do-while loop where it calls the "readString" function to read the user's email. 
 * The loop continues until the "validation_email" function returns 0, indicating that the entered email is valid.
 * After the loop, it calls the "readString" function again to read the username.
 * Both the username and the email are stored in the Companies struct in the Classification comp_class field
 * @param companies A pointer to the 'Companies' struct that contains all created companies.
 * @param pos_nif The position of the specific company in the 'Companies' struct.
 * @param pos The position of the specific user in the company.
 */
void fields_user(Companies *companies, int pos_nif, int pos) {
    do {
        readString(companies->company[pos_nif].comp_class[pos].data_user.email_user, SIZE_EMAIL, MSG_INSERT_EMAIL_USER);
    } while (validation_email(companies->company[pos_nif].comp_class[pos].data_user.email_user) == 1);
    
    readString(companies->company[pos_nif].comp_class[pos].data_user.user_name, SIZE_USER, MSG_INSERT_USER_NAME);                        
}

/**
 * @brief Prints the user's name and the rating of a specific company.
 *
 * This function prints the user's name and the rating of a specific company.
 * The rating and the user's name are identified by the position of the company in the array of ratings (comp_class) of the struct companies.
 *
 * @param companies 'Companies' struct that contains all companies.
 * @param pos_nif Position of the company in the 'companies' struct.
 * @param pos Position of the rating in the array of ratings (comp_class) of the struct companies.
 */
void information_classi(Companies companies, int pos_nif, int pos) {
    printf("User --> %s\n", companies.company[pos_nif].comp_class[pos].data_user.user_name);
    printf("Classificação --> %d\n", companies.company[pos_nif].comp_class[pos].class);
}