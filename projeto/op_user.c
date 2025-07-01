/**
 * @file op_user.c
 * @author Students: 8230138 and 8230127
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * @date 22-10-2023
 * @version 1
 * @brief op_user.c file, User menu and companies management functions.
 *  
 * This op_user.c file contains the user menu and all its options (Search company, Rate company and Comment company) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op_user.h"
#include "inputs_geral.h"
#include "inputs_user.h"
#include "inputs_comp.h"
#include "inputs_file_memory.h"

/**
 * @brief Searches for companies in the Companies struct based on user input.
 * 
 * This function prompts the user to choose a search option. Depending on the option chosen, it calls the appropriate function to search for companies by name, category, or locality. 
 * It keeps track of the number of searches performed for each option in the Search_comp struct. After each search, it saves the updated Search_comp struct. to a file.
 * 
 * @param companies Pointer to the Companies struct.
 * @param search_comps Pointer to the Search_comp struct.
 * 
 * @note The function uses the getInt function to get the search option from the user, and the repet_option function to ask the user if they want to perform another search. 
 */
void search_comp(Companies *companies, Search_comp *search_comps) {
    int op_search = 0;

    //meter guardar em ficheiro search_comp
    printf("Pesquisar empresa");   
    do {        
        op_search = getInt(MIN_OP_SEARCH, MAX_OP_SEARCH, MSG_MENU_SEARCH_COMP);
        switch (op_search) {
            case 1: {
                do { 
                    consult_comp_name(*companies);
                    search_comps->cont_name++;
                    save_search_comp(search_comps);
                } while(repet_option(1, MSG_REP_CONSULT, "outra empresa pelo nome") == 0);                
                break; 
            }
            case 2: {
                do { 
                    consult_comp_category(*companies);
                    search_comps->cont_category++;
                    save_search_comp(search_comps);
                } while (repet_option(1, MSG_REP_CONSULT, "outra empresa pela categoria") == 0);    
                break;
            }
            case 3: {
                do { 
                    consult_comp_locality(*companies); 
                    search_comps->cont_loc++;
                    save_search_comp(search_comps);
                } while (repet_option(1, MSG_REP_CONSULT, "outra empresa pela localidade") == 0);                   
                break;
            } default: {
                break;
            }
        }
    } while(repet_option(1, MSG_REP_CONSULT, MSG_REP_COMPANY) == 0);   
}

/**
 * @brief Ranks companies in the Companies struct based on user input.
 * 
 * This function prompts the user to rank a company. If the company and its branch are both active, it allows the user to rank the company. 
 * The ranking information is then saved to a file. If the company or its branch is inactive, it prints an error message. 
 * If there are no companies, it prints a message indicating that companies need to be inserted before they can be ranked.
 * 
 * @param companies Pointer to the Companies struct.
 *
 * @note The function uses the insert_nif, fields_user, getInt, information_classi, repet_option, and printf functions from the standard library. 
 */
void rank_comp(Companies *companies) {
    int pos_nif = 0;
    
    if (companies->cont_comp > 0) {
        printf("Classificar empresa\n");
        do {
            pos_nif = insert_nif(*companies);
            if (pos_nif != -1 && companies->company[pos_nif].state == ACTIVE && companies->company[pos_nif].branch.state == ACTIVE) {
                do {
                    if (companies->company[pos_nif].cont_classi == companies->company[pos_nif].size_classi) {
                        companies->company[pos_nif].size_classi = companies->company[pos_nif].size_classi * 2;
                        companies->company[pos_nif].comp_class = (Classification *) realloc(companies->company[pos_nif].comp_class, sizeof(Classification) * companies->company[pos_nif].size_classi * 2);

                        if (companies->company[pos_nif].comp_class == NULL) {
                            printf("Erro: Falha ao realocar memória.\n");
                        }
                    }
                     
                    fields_user(companies, pos_nif, POS_CLASSI);
                    companies->company[pos_nif].comp_class[POS_CLASSI].class = getInt(0, 5, MSG_INSERT_CLASSI);
                    printf("Classificação realizada a empresa %s\n",companies->company[pos_nif].name_compa);
                    printf("Email --> %s\n", companies->company[pos_nif].comp_class[POS_CLASSI].data_user.email_user);
                    information_classi(*companies, pos_nif, POS_CLASSI);
                    companies->company[pos_nif].cont_classi++;
                    save_file_comp(companies); 
                } while (repet_option(1, MSG_REP_INSERT, "outra classificação à mesma empresa") == 0);
            } else if (pos_nif != -1 && companies->company[pos_nif].state == INACTIVE) {
                printf("Empresa Inativa!\n");                
            } else if (pos_nif != -1 && companies->company[pos_nif].branch.state == INACTIVE) {
                printf("O ramo da empresa está inativo!\n");
            }
        } while (repet_option(1, MSG_REP_INSERT, MSG_REP_RANK) == 0); 
    } else {
        printf(MSG_IMP_OPERATION_INSERT_COMP, "classificar");
    } 
}

/**
 * @brief Allows users to comment on companies in the Companies struct.
 * 
 * This function prompts the user to comment on a company. If the company and its branch are both active, it allows the user to comment on the company. 
 * The comment information is then saved to a file. If the company or its branch is inactive, it prints an error message. 
 * If there are no companies, it prints a message indicating that companies need to be created before they can be commented on.
 * 
 * @param companies Pointer to the Companies struct.
 * 
 * @note The function uses the insert_nif, readString, validation_email, information_comments, repet_option, and printf functions from the standard library. 
 */
void comment_comp(Companies *companies) {
    int pos_nif = 0;
    
    if (companies->cont_comp > 0) {
        do { 
            printf("Comentar empresa\n");
            pos_nif = insert_nif(*companies);

            if (pos_nif != -1 && companies->company[pos_nif].state == ACTIVE && companies->company[pos_nif].branch.state == ACTIVE) {                    
                do {
                    if (companies->company[pos_nif].cont_coments == companies->company[pos_nif].size_comments) {
                        companies->company[pos_nif].size_comments = companies->company[pos_nif].size_comments * 2;
                        companies->company[pos_nif].comment = (Comments *) realloc(companies->company[pos_nif].comment, sizeof(Comments) * companies->company[pos_nif].size_comments * 2);

                        if (companies->company[pos_nif].comment == NULL) {
                            printf("Erro: Falha ao realocar memória.\n");
                        }
                    }
                    
                    companies->company[pos_nif].comment[POS_COMENT].id_comen = companies->company[pos_nif].cont_coments;

                    do {
                        readString(companies->company[pos_nif].comment[POS_COMENT].data_user.email_user, SIZE_EMAIL, MSG_INSERT_EMAIL_USER);
                    } while(validation_email(companies->company[pos_nif].comment[POS_COMENT].data_user.email_user) == 1);

                    readString(companies->company[pos_nif].comment[POS_COMENT].data_user.user_name, SIZE_USER, MSG_INSERT_USER_NAME);                         
                    readString(companies->company[pos_nif].comment[POS_COMENT].title, SIZE_TITLE, MSG_INSERT_TITLE_COMMENT);
                    readString(companies->company[pos_nif].comment[POS_COMENT].text, SIZE_TEXT, MSG_INSER_TEXT_COMMENT);
                    companies->company[pos_nif].comment[POS_COMENT].hide = NOT_HIDE; 

                    printf("Comentario realizado à empresa %s\n", companies->company[pos_nif].name_compa);
                    printf("Email do utilizador --> %s\n", companies->company[pos_nif].comment[POS_COMENT].data_user.email_user);
                    information_comments (*companies, pos_nif, POS_COMENT);
                    companies->company[pos_nif].cont_coments++;   
                    save_file_comp(companies);
                } while (repet_option(1, MSG_REP_INSERT, "outro comentario à mesma empresa") == 0);     
            } else if (pos_nif != -1 && companies->company[pos_nif].state == INACTIVE) {
                printf("Empresa Inativa!\n");                
            } else if (pos_nif != -1 && companies->company[pos_nif].branch.state == INACTIVE) {
                printf("Impossível comentar a empresa, pois o seu ramo está inativo!\n");
            }
        } while (repet_option(1, MSG_REP_INSERT, MSG_REP_COMMENT) == 0); 
    } else {
        printf("Ainda não foi criada nenhuma empresa, logo não é possivel criar um comentario\n!");
    } 
}

/**
 * @brief Displays a menu for the user and performs actions based on the user's choice.
 * 
 * This function welcomes the user and prompts them to choose an option from the menu. Depending on the option chosen, it calls the appropriate function to search for companies, rank companies, or comment on companies. 
 * If the user chooses to return to the main menu, it prints a message and exits the loop. If the user enters an invalid option, it prints an error message.
 * 
 * @param op_user Pointer to an integer that holds the user's menu choice.
 * @param companies Pointer to the Companies struct.
 * @param branchs Pointer to the Branch_Activity struct.
 * @param search_comps Pointer to the Search_comp struct.
 * 
 * @note The function uses the getInt and printf functions from the standard library. 
 */
void menu_user(int *op_user, Companies *companies, Branch_Activity *branchs, Search_comp *search_comps) {
    *op_user = 0;
    printf("Bem-vindo Utilizador!\n");
    while (*op_user < 4 || *op_user > 5) {
        *op_user = getInt(MIN_OP_MENU_USER, MAX_OP_MENU_USER, MSG_MENU_USER);
        
        switch (*op_user) {
            case 1: {  
                search_comp(companies, search_comps);
                break;
            }
            case 2: {
                rank_comp(companies);
                break;
            }
            case 3: {
                comment_comp(companies);
                break;
            }
            case 4: {
                printf("Voltar ao menu principal!\n");
                break;
            }
            case 5: {
                break;
            }
            default: {
                printf("Opção inválida (introduza um numero entre 1 e 5)!");
                break;
            }
        }
    }
}
