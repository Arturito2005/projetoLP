/**
 * @file inputs_comp.c 
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief File inputs_comp.c with all the inputs of the companies.
 *
 * In the inputs_comp.c file, all the inputs used in the companies options are present.
*/

#include <stdio.h>
#include <string.h>

#include "inputs_comp.h"
#include "inputs_geral.h"

static int i = 0;

/*
 * @brief Checks if there is at least one company with comments
 *
 * This function goes through all the companies in the Companies struct.
 * If it finds a company that has one or more comments, it returns 0.
 * If none of the companies have comments, it returns 1.
 *
 * @param companies The Companies struct.
 * @return Returns 0 if there is at least one company with one or more comments, otherwise it returns 1.
 */
int exist_comm(Companies companies) {
    for (i = 0; i < companies.cont_comp; i++) {
        if (companies.company[i].cont_coments > 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief Checks if there is at least one company with ratings
 *
 * This function goes through all the companies in the Companies struct.
 * If it finds a company that has one or more ratings, it returns 0.
 * If none of the companies have ratings, it returns 1.
 *
 * @param companies The Companies struct that contains all the companies.
 * @return Returns 0 if there is at least one company with one or more ratings, otherwise it returns 1.
 */
int exist_classi(Companies companies) {
    for (i = 0; i < companies.cont_comp; i++) {
        if (companies.company[i].cont_classi > 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief Checks if the postal code entered by the user is valid
 *
 * This function checks if the provided postal code meets the necessary criteria.
 * The valid postal code must have 8 characters, where it cannot contain spaces between them, the first 4 characters and the last 3 are numbers, and there must be a hyphen between the fourth and fifth character.
 *
 * @param cod_postal The postal code provided by the user as a string.
 * @return Returns 0 if the postal code is valid, otherwise it returns 1 and prints an appropriate error message.
 */
int validation_cod_postal(char *cod_postal) {  
    
    if (strlen(cod_postal) != (SIZE_COD_POS - 1)) {
        printf("O código postal é constituido por 8 caracteres!\n"); 
        return 1;
    }

    for (i = 0; i < (SIZE_COD_POS - 1); i++) {
        if (cod_postal[i] == ' ')
        {
            printf("O código postal não tem espaços!\n");
            return 1;
        }
        
        
        if (i != 4) {
            if (cod_postal[i] < 48 || cod_postal[i] > 57) {
                printf("O caracter %c tem de ser um numero de 0 a 9!\n", cod_postal[i]);
                return 1;
            }
        } else if (cod_postal[4] != '-'){
            printf("No código postal os 4 primeiros são sempre separados dos últimos 3 por um hífen!\n");   
            return 1;
        }
    }
    
    return 0;
}

/**
 * @brief Displays information of a specific company
 *
 * This function takes the 'Companies' struct and a position index.
 * It prints detailed information about the company at the provided position.
 * The information includes the NIF, the name, the category, the field of activity, the address (street, locality, postal code), and the
 * status of the company (Active or Inactive).
 *
 * @param companies The 'Companies' data struct.
 * @param pos The position of the company in the 'Companies' struct.
 */
void information_company(Companies companies, int pos) {
    printf("Nif--> %d\n", companies.company[pos].nif);
    printf("Nome--> %s\n", companies.company[pos].name_compa);
    
    switch (companies.company[pos].category) {
        case MICRO: {
            printf(MSG_CATEGORY, "Micro\n");
            break;
        }
        case SMALL_BUSINESS: {
            printf(MSG_CATEGORY, "Empresa de Pequeno Porte\n");
            break;
        }
        case PME: {
            printf(MSG_CATEGORY, "PME\n");
            break;
        }
        case BIG_COMPANY: {
            printf(MSG_CATEGORY, "Grande Empresa\n");
            break;
        }
        case LIMITED_SOCIETY: {
            printf(MSG_CATEGORY, "Sociedade Limitada\n");
            break;
        }
        default: {
            break;
        }    
    }
    
    printf("Ramo de atividade --> %s\n", companies.company[pos].branch.name_branch);
    printf("Rua--> %s\n", companies.company[pos].road);
    printf("Localidade--> %s\n", companies.company[pos].locality);
    printf("Cod_Postal--> %s\n", companies.company[pos].cod_postal);
    
    if (companies.company[pos].state == ACTIVE) {
        puts(STATE_ACTIVE);
    } else {
        puts(STATE_INACTIVE);
    }
}

/**
 * @brief Checks if there is at least 1 active branch of activity
 *
 * This function goes through all branches of activity in the 'Branch_Activity' struct.
 * If it finds an active branch of activity (branchs.branch[i].state == ACTIVE), it returns 0.
 * If none of the branches of activity are active, it prints a message indicating that there are no active branches and returns 1.
 *
 * @param branchs The 'Branch_Activity' struct.
 * @return Returns 0 if there is at least one active branch of activity, otherwise it returns 1.
 */
int valids_branch(Branch_Activity branchs) {
    for (i = 0; i < branchs.cont_branch; i++) {
        if (branchs.branch[i].state == ACTIVE) {
            return 0;
        }        
    }
    
    printf("Não existem ramos ativos!\n");
    return 1;
}

/**
 * @brief Validates whether the branch of activity entered by the user exists.
 *
 * This function checks if the provided branch of activity exists in the Branch_Activity struct 
 * (strcmp(name_branch, branchs.branch[i].name_branch) == 0) and if it is active (branchs.branch[i].state == ACTIVE). 
 * If it finds a branch of activity that matches the provided name and is active, it assigns this branch to the company at 
 * the provided position in the Companies strcut and returns the index of the branch.
 * If the branch of activity is not found, it prints a message indicating that the branch does not exist or is inactive and returns -1.
 *
 * @param companies Pointer to the struct Companies that contains all companies.
 * @param branchs The struct Branch_Activity that contains all branches of activity.
 * @param name_branch The name of the branch of activity provided by the user as a string.
 * @param pos_comp The position of the company in the Companies strcut that should be validated.
 * @return Returns the index of the branch if the branch of activity is valid, otherwise it returns -1.
 */
int validation_branch(Companies *companies, Branch_Activity branchs, char *name_branch, int pos_comp) {
    for (i = 0; i < branchs.cont_branch; i++) {
        if (strcmp(name_branch, branchs.branch[i].name_branch) == 0 && branchs.branch[i].state == ACTIVE) {
            companies->company[pos_comp].branch = branchs.branch[i];
            return i;
        }    
    }
    
    printf("O ramo que introduziu não existe ou o ramo encontra-se inativo!\n");
    return -1;
}

/**
 * @brief Store and validates information about a specific company.
 *
 * This function is used in the 'add_companies' and 'edit_companies' voids, where its main objective is to take advantage of the 
 * common fields of these options and reduce the size of the code.
 * This function collects various pieces of information about a company, validates them, and stores them in the Companies struct.
 * It prompts the user to enter the company's name, category, branch of activity, address (street, locality and postal code), and state (active or inactive).
 * It also validates the branch of activity and postal code using the 'validation_branch' and 'validation_cod_postal' functions, respectively.
 * If the entered branch of activity or postal code is not valid, it will continue to prompt the user to enter a valid one.
 * After all the information is collected and validated, it calls the 'information_company' function to display the information of the newly created company.
 *
 * @param companies Pointer to the Companies struct that contains all companies.
 * @param branchs The Branch_Activity struct that contains all branches of activity.
 * @param pos The position of the company in the Companies struct that should be updated.
 */
void fields_company(Companies *companies, Branch_Activity branchs, int pos) {
    char na_branch[SIZE_NAME_BRANCH];
    
    readString(companies->company[pos].name_compa, SIZE_NAME_COMP, MSG_INSERT_NAME_COMAPNY);    
    companies->company[pos].category = getInt(MIN_CATEGORY, MAX_CATEGORY, MSG_INSERT_CATEGORY_COMPANY);
   
    printf("Ramos disponíveis:\n");
    for (i = 0; i < branchs.cont_branch; i++) {
        if (branchs.branch[i].state == ACTIVE) {
            printf("Nome ramo --> %s\n", branchs.branch[i].name_branch);
        }
    }
    printf("\n");
    
    do {
        readString(na_branch, SIZE_NAME_BRANCH, "Introduza o ramo -->");
    } while(validation_branch(companies, branchs, na_branch, pos) == -1);

    printf("Morada da empresa.\n");
    readString(companies->company[pos].road, SIZE_ROAD, MSG_INSERT_ROAD_COMPANY);
    readString(companies->company[pos].locality, SIZE_LOC, MSG_INSERT_LOC_COMPANY);
    uppercase(companies->company[pos].locality);
    
    do {
        readString(companies->company[pos].cod_postal, SIZE_COD_POS, MSG_INSERT_COD_POSTAL_COMPANY);    
    } while (validation_cod_postal(companies->company[pos].cod_postal));   
    
    companies->company[pos].state = getInt(0, 1, MSG_INSERT_STATE_COMPANY);

    information_company(*companies, pos);
}