/**
 * @file inputs_branch.c
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief File inputs_branch.c with all the inputs of the branchs
 *
 * In the inputs_branch.c file, all the inputs used in the branchs options are present.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "companies.h"
#include "inputs_branch.h"
#include "inputs_geral.h"

static int i = 0;

/**
 * @brief Compares a given branch name with existing branches in the Branch_Activity struct.
 * 
 * This function iterates over all the branches in the Branch_Activity struct and compares the given branch name with the name of each branch. 
 * If a match is found, it prints a message indicating that the branch already exists and returns 1. 
 * If no match is found, it prints a success message and returns 0.
 * 
 * @param branchs The Branch_Activity struct.
 * @param branch_o The name of the branch to be compared with existing branches.
 * 
 * @return int Returns 1 if the branch already exists, and 0 otherwise.
 * 
 * @note The function uses the strcmp function to compare the branch names. 
 */
int compare_branch (Branch_Activity branchs, char *branch_o) { 
    for (i = 0; i < branchs.cont_branch; i++) {
        if (strcmp(branch_o, branchs.branch[i].name_branch) == 0) {
            printf("O ramo de atividade ja existe!\n"); 
            return 1;
        }
    }
    
    printf(INEX_BRANCH);
    return 0;
}

/**
 * @brief Searches for a branch in the Branch_Activity struct and returns its position.
 * 
 * This function iterates over all the branches in the Branch_Activity struct and compares the given branch name with the name of each branch. 
 * If a match is found, it returns the position of the branch in the struct. If no match is found, it prints an error message and returns -1.
 * 
 * @param branchs The Branch_Activity struct.
 * @param name_branch The name of the branch to be searched.
 * 
 * @return int Returns the position of the branch if found, and -1 otherwise.
 * 
 * @note The function uses the strcmp function to compare the branch names. 
 */
int search_branch_pos(Branch_Activity branchs, char *name_branch) {
    for (i = 0; i < branchs.cont_branch; i++) {
        if (strcmp(name_branch, branchs.branch[i].name_branch) == 0) {
            return i;
        }    
    }
    
    printf("O ramo que introduziu não existe ou o ramo encontra-se inativo!\n");
    return -1;
}

/**
 * @brief Checks if a branch is being used by any company.
 * 
 * This function iterates over all the companies in the Companies struct and compares the given branch name with the branch name of each company. 
 * If a match is found, it prints a message indicating that the branch is being used by at least one company and returns 1. 
 * If no match is found, it returns 0.
 * 
 * @param companies The Companies struct.
 * @param name_branch The name of the branch to be checked.
 * 
 * @return int Returns 1 if the branch is being used by any company, and 0 otherwise.
 * 
 * @note The function uses the strcmp function to compare the branch names. 
 */
int used_bracnh_comp(Companies companies, char *name_branch) {
    for (i = 0; i < companies.cont_comp; i++) {
        if (strcmp(name_branch, companies.company[i].branch.name_branch) == 0) {
            printf("O ramo %s já está a ser usado por pelo menos uma empresa!\n", name_branch);
            return 1;
        }    
    }
    
    return 0;
}

/**
 * @brief Prints the information of a branch at a given position in the Branch_Activity struct.
 * 
 * This function prints the name of the branch and its state (active or inactive). The state is determined by checking the 'state' attribute of the branch.
 * 
 * @param branchs The Branch_Activity struct.
 * @param pos The position of the branch in the Branch_Activity struct.
 * 
 * @note The function uses the printf function to print the branch information. 
 */
void information_branch(Branch_Activity branchs, int pos) {
    printf("Nome do ramo --> %s\n", branchs.branch[pos].name_branch);
    
    if (branchs.branch[pos].state == ACTIVE) {
        printf(STATE_ACTIVE);
    } else {
        printf(STATE_INACTIVE);
    }
}

/**
 * @brief Updates the state of a branch at a given position in the Branch_Activity struct.
 * 
 * This function prompts the user to enter the state of the branch (0 or 1) and updates the 'state' attribute of the branch at the given position.
 * 
 * @param branchs Pointer to the Branch_Activity struct.
 * @param pos The position of the branch in the Branch_Activity struct.
 * 
 * @note The function uses the getInt function to get the state of the branch from the user. 
 */
void fields_branch(Branch_Activity *branchs, int pos) {
    branchs->branch[pos].state = getInt(0, 1, MSG_INSERT_STATE_BRANCH);
}