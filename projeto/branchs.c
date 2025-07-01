/**
 * @file branchs.c
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 *
 * @brief branchs.c file, Branch management
 *
 * This file have all the functions to do the branchs management, using system CRUD (CREATE, READ, UPDATE, DELETE)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "branchs.h"
#include "inputs_branch.h"
#include "inputs_geral.h"
#include "inputs_comp.h"
#include "inputs_user.h"
#include "inputs_file_memory.h"

static int i = 0;

/**
 * @brief Adds a new branch of activity.
 *
 * This function allows adding a new branch of activity. If the current number of branches equals the size of the allocated memory for branches, the function doubles the size of the allocated memory.
 *
 * @param branchs Pointer to the Branch_Activity struct.
 *
 * @note The function does not return anything, but modifies the struct passed as a parameter.
 * @note The function assumes that the pointer passed as a parameter is valid and is not NULL.
 */
void add_branch(Branch_Activity *branchs) {
    printf("Adicionar ramo:\n");
    
    do {        
        if (branchs->cont_branch == branchs->size_branch) {
            branchs->size_branch = branchs->size_branch * 2;
            branchs->branch = (Data_Branch *) realloc(branchs->branch, sizeof(Data_Branch) * branchs->size_branch);

            if (branchs->branch == NULL) {
                printf("Erro: Falha ao realocar memória, para os ramos.\n");
            }
        }
        
        do {
            readString(branchs->branch[branchs->cont_branch].name_branch, SIZE_NAME_BRANCH , MSG_INSERT_NAME_BRANCH);
        } while (compare_branch(*branchs, (branchs->branch[branchs->cont_branch].name_branch)) == 1 && branchs->cont_branch > 0);

        fields_branch(branchs, branchs->cont_branch);
        branchs->cont_branch++;
        save_file_branchs(branchs);
    } while (repet_option(1, MSG_REP_INSERT, MSG_REP_BRANCH) == 0);
}   

/**
 * @brief Deletes a branch of activity.
 *
 * This function allows deleting an existing branch of activity. If the branch is not being used by any company, it can be deleted. Otherwise, the function will not delete the branch. If deleted, it shifts the array to remove the branch and updates the branch count.
 *
 * @param branchs Pointer to the Branch_Activity struct.
 * @param companies Pointer to the Companies struct.
 *
 * @note The function does not return anything, but modifies the struct passed as parameters.
 */
void delete_branchs(Branch_Activity *branchs, Companies *companies) {
    int pos_bra = 0, used_bra = 0;
    char name_branch[SIZE_NAME_BRANCH];
    
    if (branchs->cont_branch > 0) { 
        printf("Apagar ramo!\n");
        do {
            readString(name_branch, SIZE_NAME_BRANCH, MSG_INSERT_NAME_BRANCH);
            pos_bra = search_branch_pos(*branchs, name_branch);
            
            if (pos_bra != -1) {
                used_bra = used_bracnh_comp(*companies, name_branch);
                
                if (used_bra == 0) {
                    printf("Tem a certeza que pretende eliminar o ramo %s:\n", branchs->branch[pos_bra].name_branch);         
                    information_branch(*branchs, pos_bra);
                    if(repet_option(0, "", "") == 0) { 
                        for (i = pos_bra; i < (branchs->cont_branch - 1); i++) {
                            branchs->branch[i] = branchs->branch[i + 1];
                        }

                        branchs->cont_branch--;
                        save_file_branchs(branchs);
                        printf("Ramo eliminado com sucesso!\n");
                    }
                }
            }
        } while (repet_option(1, MSG_REP_DELET, MSG_REP_BRANCH) == 0);    
    } else {
        printf(MSG_IMP_OPERATION_INSERT_BRANCH, "eliminar");
    }    
}

/**
 * @brief Edits the details of a branch in the branch activity and company struct.
 * 
 * This function allows the user to edit the details of a branch. If the branch is not being used by any company, 
 * all details of the branch can be edited. However, if the branch is being used by a company, only the state of the 
 * branch can be edited.
 * 
 * @param branchs Pointer to the Branch_Activity struct.
 * @param companies Pointer to the Companies struct.
 * 
 * @note The function will prompt the user to enter the name of the branch they wish to edit. 
 * @note If the branch is found and is not being used by any company, the user will be asked to confirm their decision 
 * to edit the branch. 
 * @note If confirmed, the user can then edit the name and other details of the branch. 
 * @note If the branch is being used by a company, the user will only be able to edit the state of the branch. 
 * @note The function will continue to prompt the user to edit branches until the user chooses to stop.
 */
void edit_branch(Branch_Activity *branchs, Companies *companies) {
    int pos_bra = 0, used_bra = 0;
    char name_branch[SIZE_NAME_BRANCH];
       
    if (branchs->cont_branch > 0) {
        printf("Editar ramo!\n"); 
        do {
            readString(name_branch, SIZE_NAME_BRANCH, "Introduz o ramo -->");
            pos_bra = search_branch_pos(*branchs, name_branch);
            
            if (pos_bra != -1) {
                used_bra = used_bracnh_comp(*companies, name_branch);
                
                if (used_bra == 0) {
                    printf("Tem a certeza que pretende editar o ramo %s:\n", branchs->branch[pos_bra].name_branch);
                    information_branch(*branchs, pos_bra);
                    if (repet_option(0, "", "") == 0) {                     
                        readString(branchs->branch[pos_bra].name_branch, SIZE_NAME_BRANCH, MSG_INSERT_NAME_BRANCH);
                        fields_branch(branchs, pos_bra); 
                        save_file_branchs(branchs);
                    }
                } else {
                    printf("Como o ramo está a ser usado só é possível editar o seu estado!\n");
                    branchs->branch[pos_bra].state = getInt(0, 1, MSG_INSERT_STATE_BRANCH);

                    if (branchs->branch[pos_bra].state == INACTIVE) {    
                        for (i = 0; i < companies->cont_comp; i++) {
                            if(strcmp(companies->company[i].branch.name_branch, branchs->branch[pos_bra].name_branch) == 0) {
                                companies->company[i].branch.state = INACTIVE;
                            }         
                        }
                    } else {
                        for (i = 0; i < companies->cont_comp; i++) {
                            if(strcmp(companies->company[i].branch.name_branch,branchs->branch[pos_bra].name_branch) == 0) {
                                companies->company[i].branch.state = ACTIVE;
                            }         
                        }
                    }
                    save_file_comp(companies);
                    save_file_branchs(branchs);
                }
            }
        } while (repet_option(1, MSG_REP_EDIT, MSG_REP_BRANCH) == 0);
    } else {
        printf(MSG_IMP_OPERATION_INSERT_BRANCH, "alterar");
    }
}

/**
 * @brief Lists all the branches in the Branch_Activity struct.
 * 
 * This function iterates over all the branches in the Branch_Activity struct. 
 * If there are no branches, it prints a message indicating that branches need to be inserted before they can be listed.
 * 
 * @param branchs The Branch_Activity struct.
 * 
 * @note The function will print the total number of branches and then list each branch one by one. 
 * @note For each branch, it will print the branch number and then call the information_branch function to print the details of the branch.
 */
void branch_list(Branch_Activity branchs) {
    if (branchs.cont_branch > 0) {
        printf("Total de ramos --> %d\n", branchs.cont_branch);
        
        for (i = 0; i < branchs.cont_branch; i++) {
            printf("Ramo nº%d\n", i + 1);
            information_branch(branchs, i); 
        }
    } else {
        printf(MSG_IMP_OPERATION_INSERT_BRANCH, "listar");
    }
}

/**
 * @brief Consults the details of a branch in the Branch_Activity struct.
 * 
 * This function allows the user to consult the details of a branch. The user is prompted to enter the name of the branch they wish to consult. 
 * If the branch is found, its details are printed. The function will continue to prompt the user to consult branches until the user chooses to stop.
 * 
 * @param branchs The Branch_Activity struct.
 * 
 * @note The function will prompt the user to enter the name of the branch they wish to consult. 
 * @note If the branch is found, it will print the details of the branch by calling the information_branch function. 
 * @note The function will continue to prompt the user to consult branches until the user chooses to stop.
 */
void consult_branch(Branch_Activity branchs) {
    int pos_bra = 0;
    char name_branch[SIZE_NAME_BRANCH];
    
    if (branchs.cont_branch > 0) {
        do {
            readString(name_branch, SIZE_NAME_BRANCH, "Introduz o ramo -->");
            pos_bra = search_branch_pos(branchs, name_branch);   
    
            if (pos_bra != -1) { 
                printf("Dados do ramo:\n");
                information_branch(branchs, pos_bra);
            }
        } while (repet_option(1, MSG_REP_CONSULT, MSG_REP_BRANCH) == 0);        
    } else {
        printf(MSG_IMP_OPERATION_INSERT_BRANCH, "listar");
    }
}