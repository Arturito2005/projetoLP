/**
 * @file inputs_user.c
 * @author Students: 8230138 and 8230127
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * @date 22-10-2023
 * @version 1
 * 
 * @brief File inputs_user.c with all the inputs of the user's options
 *
 * In the inputs_user.c file, all the inputs used in the user options are present.
*/

#include <stdio.h>
#include <string.h>

#include "inputs_user.h"
#include "inputs_comp.h"
#include "inputs_branch.h"
#include "inputs_geral.h"

static int i = 0, j = 0, y = 0;

/**
 * @brief Prints the information of a comment at a given position in the Companies struct.
 * 
 * This function prints the username of the user who made the comment, the title of the comment, and the text of the comment. 
 * The information is retrieved from the Companies struct.
 * 
 * @param companies The Companies struct.
 * @param pos_nif The position of the company in the Companies struct.
 * @param pos_comment The position of the comment in the company's comment array.
 * 
 * @note The function uses the printf function to print the comment information. 
 */
void information_comments(Companies companies, int pos_nif, int pos_comment) {
    printf("Utilizador --> %s\n", companies.company[pos_nif].comment[pos_comment].data_user.user_name);
    printf("Titulo do comentario --> %s\n", companies.company[pos_nif].comment[pos_comment].title);
    printf("Texto do comentario --> %s\n\n", companies.company[pos_nif].comment[pos_comment].text);
}

/**
 * @brief Validates the position of a comment in the Companies struct.
 * 
 * This function iterates over all the comments of a company in the Companies struct and compares the given comment ID with the ID of each comment. 
 * If a match is found, it returns 0. If no match is found, it prints an error message and returns 1.
 * 
 * @param companies The Companies struct.
 * @param pos_nif The position of the company in the Companies struct.
 * @param id_comment The ID of the comment to be validated.
 * 
 * @return int Returns 0 if the comment ID is found, and 1 otherwise.
 * 
 * @note The function uses the printf function to print the error message when the comment ID is not found. 
 */
int validation_pos_comment(Companies companies, int pos_nif, int id_comment) {
    for (i = 0; i < companies.company[pos_nif].cont_coments; i++) {
        if (id_comment == companies.company[pos_nif].comment[i].id_comen) {
            return 0;
        }   
    }
    
    printf("O id de comentario que introduziu não está a associado á empresa %s ou não existe!\n", companies.company[pos_nif].name_compa);
    return 1;
}

/**
 * @brief Validates an email address.
 * 
 * This function checks if the given email address is valid according to certain rules. 
 * The rules include the length of the email, the characters used, the position of '@', and the use of '.'. 
 * If the email is not valid, it prints an error message and returns 1. If the email is valid, it returns 0.
 * 
 * @param email The email address to be validated.
 * 
 * @return int Returns 0 if the email is valid, and 1 otherwise.
 * 
 * @note The function uses the strlen and printf functions from the standard library. 
 */
int validation_email(char *email) {
    
    int find = 0, pos_find = 0;
    
    if (strlen(email) > SIZE_EMAIL) {
        printf("O email introduzido ultrapassa o limite de caracteres %d\n", SIZE_EMAIL);
        return 1;
    }
    
    for (i = 0; i < (strlen(email) - 1); i++) {
        if (email[i] == ' ') {
            printf("Um email válido não possui espaços!\n");
            return 1;
        }
        
        if ((email[i] < 97 || email[i] > 122) && email[i] != '.' && email[i] != '_' && email[i] != '@') {
            printf("Apenas letras (a-z), números (0-9) e caracteres especiais ('.' e '_'), são permitidos no nome do email!\n");
            return 1;
        }
        
        if (email[i] == '@') {
            if ((i - 1) < SIZE_MIN_EMAIL) {
                printf("O nome do email tem de ter no minimo %d caracteres!\n", SIZE_MIN_EMAIL + 1);
                return 1;
            }
            
            if ((i - 1) > SIZE_MAX_EMAIL) {
                printf("O nome do email tem de ter no maximo %d caracteres!\n", SIZE_MAX_EMAIL + 1);
                return 1;
            }
            
            if (i == (strlen(email) - 1)) {
                printf("Após o '@' é obrigatorio ter um dominio!\n");
                return 1;
            }

            find++;
            pos_find = i;
        }
    }
    
    if (find != 1) {
        printf("Um email valido tem de ter um e só mente um @!\n");
        return 1;
    } else {
        for (i = pos_find; i < strlen(email); i++) {   
            if (email[i] == '.' && email[i + 1] == '.') {
                printf("Um email válido não pode ter dois '.' seguidos!\n");
                return 1;
            }
        }
    }
    
    return 0;
}

/**
 * @brief Consults the information of a company by its name in the Companies struct.
 * 
 * This function prompts the user to enter the name of a company. It then iterates over all the companies in the Companies struct and compares the given company name with the name of each company. 
 * If a match is found and the company and its branch are both active, it prints the company's information, all its comments, and all its classifications. 
 * If no match is found, it prints an error message.
 * 
 * @param companies The Companies struct.
 * 
 * @note The function uses the strcmp and printf functions from the standard library. 
 */
void consult_comp_name(Companies companies) {
    char name_comp[SIZE_NAME_COMP], j = 0;
    
    readString(name_comp, SIZE_NAME_COMP, "Insira o nome da empresa -->");
    for (i = 0; i < companies.cont_comp; i++) {
        if (strcmp(name_comp, companies.company[i].name_compa) ==  0 && companies.company[i].branch.state == ACTIVE && companies.company[i].state == ACTIVE) {
            printf("Empresa nº%d\n", i + 1);
            information_company(companies, i);

            for (y = 0; y < companies.company[i].cont_coments; y++) {
                printf("Comentario nº%d\n", y + 1);
                information_comments(companies, i, y);
            }
            
            for (y = 0; y < companies.company[i].cont_classi; y++) {
                printf("Classificação nº%d\n", y + 1);
                information_classi(companies, i, y);
            }
            
            j++;
        }
    }
    
    if (j == 0) {
        printf("Não foi encontrada nenhuma empresa com o nome %s\n", name_comp);
    }
}

/**
 * @brief Consults the information of companies by their category in the Companies struct.
 * 
 * This function prompts the user to enter a category. It then iterates over all the companies in the Companies struct and compares the given category with the category of each company. 
 * If a match is found and the company and its branch are both active, it prints the company's information, all its comments, and all its classifications. 
 * If no match is found, it prints an error message.
 * 
 * @param companies The Companies struct.
 * 
 * @note The function uses the getInt and printf functions from the standard library. 
 */
void consult_comp_category(Companies companies) {
    int cat_type = 0, j = 0;
    
    cat_type = getInt(MIN_CATEGORY, MAX_CATEGORY, MSG_INSERT_CATEGORY_COMPANY);
    for (i = 0; i < companies.cont_comp; i++) {
        if (cat_type == companies.company[i].category && companies.company[i].branch.state == ACTIVE && companies.company[i].state == ACTIVE) {
            printf("Empresa nº%d\n", i + 1);
            information_company(companies, i); 
            
            for (y = 0; y < companies.company[i].cont_coments; y++) {
                printf("Comentario nº%d\n", y + 1);
                information_comments(companies, i, y);
            }
            
            for (y = 0; y < companies.company[i].cont_classi; y++) {
                printf("Classificação nº%d\n", y + 1);
                information_classi(companies, i, y);
            }
            
            j++;
        }
    }
    
    if (j == 0) {
        printf("Não foi encontrada nenhuma empresa com a categoria %d\n", cat_type);
    }   
}

/**
 * @brief Consults the information of companies by their locality in the Companies struct.
 * 
 * This function prompts the user to enter a locality. It then iterates over all the companies in the Companies struct and compares the given locality with the locality of each company. 
 * If a match is found and the company and its branch are both active, it prints the company's information, all its comments, and all its classifications. 
 * If no match is found, it prints an error message.
 * 
 * @param companies The Companies struct.
 * 
 * @note The function uses the readString, strcmp, and printf functions from the standard library. 
 */
void consult_comp_locality(Companies companies) {
    char loc[SIZE_LOC], j = 0;
    
    readString(loc, SIZE_LOC, "Insira a localidade da empresa -->");
    uppercase(loc);
    
    for (i = 0; i < companies.cont_comp; i++) {
        if (strcmp(loc, companies.company[i].locality) == 0 && companies.company[i].branch.state == ACTIVE && companies.company[i].state == ACTIVE) {
            printf("Empresa nº%d\n", i + 1);
            information_company(companies, i); 
            
            for (y = 0; y < companies.company[i].cont_coments; y++) {
                printf("Comentario nº%d\n", y + 1);
                information_comments(companies, i, y);
            }
            
            for (y = 0; y < companies.company[i].cont_classi; y++) {
                printf("Classificação nº%d\n", y + 1);
                information_classi(companies, i, y);
            }
            
            j++;
        }
    }

    if (j == 0) {
        printf("Não foi encontrada nenhuma empresa com na localidade de %s\n", loc);
    }
}