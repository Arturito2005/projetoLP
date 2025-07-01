/**
 * @file companies.c
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 *
 * @brief File companies.c, contains the functions for managing companies.
 *
 * This file contains all the necessary functions to manage companies in the program (Insert, Delete, Update, Consult, 
 * List) and also to delete/hide the comments of the companies.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "companies.h"
#include "inputs_geral.h"
#include "inputs_comp.h"
#include "inputs_user.h"
#include "inputs_file_memory.h"
 
static int i = 0;

/**
 * @brief Adds companies to the Companies struct.
 *
 * This function adds a new company to the Companies struct. 
 * The function checks if there are valid activity branches before adding the company.
 * If the current capacity of the Companies struct is reached, the function reallocates memory to accommodate more companies.
 * The function also initializes the company's comments and ratings.
 *
 * @param companies A pointer to the Companies struct that stores all companies.
 * @param branchs The Branch_Activity struct that stores all activity branches.
 *
 * @note The function will print an error message and return if memory reallocation fails.
 * @note The function will print a message and return if there are no active activity branches.
 */
void add_companies(Companies *companies, Branch_Activity branchs) {
    printf("Adicionar empresa\n");

    if (branchs.cont_branch > 0 && valids_branch(branchs) == 0) {
        do {
            if (companies->cont_comp == companies->size_company) {
                companies->size_company = companies->size_company * 2;
                companies->company = (Data_companies *) realloc(companies->company, sizeof(Data_companies) * companies->size_company);

                if (companies->company == NULL) {
                    printf("Erro: Falha ao realocar memória.\n");
                }
            }

            do {
                companies->company[companies->cont_comp].nif = getInt(MIN_VALUE_NIF, MAX_VALUE_NIF, MSG_INSERT_NIF_COMPANY);
            } while (compare_nif(*companies, companies->company[companies->cont_comp].nif) != -1 && companies->cont_comp > 0);

            fields_company(companies, branchs, companies->cont_comp);

            companies->company[companies->cont_comp].cont_coments = 0;
            companies->company[companies->cont_comp].cont_classi = 0;
            companies->company[companies->cont_comp].size_classi = 1;
            companies->company[companies->cont_comp].size_comments = 1;

            companies->company[companies->cont_comp].comment = (Comments *) malloc(sizeof(Comments) * companies->company[companies->cont_comp].size_comments);
            companies->company[companies->cont_comp].comp_class = (Classification *) malloc(sizeof(Classification) * companies->company[companies->cont_comp].size_classi);
            companies->cont_comp++;
            save_file_comp(companies);
        } while (repet_option(1, MSG_REP_INSERT, MSG_REP_COMPANY) == 0);
    } else if (branchs.cont_branch == 0) {
        printf("Impossível criar uma nova empresa, ainda não existem ramos ativos!\n");
    }
}

/**
 * @brief Deletes companies from the Companies struct.
 *
 * This function deletes an existing company from the Companies struct. 
 * The function checks if there are companies before attempting to delete one.
 * If the company to be deleted has no comments, the function asks the user for confirmation before proceeding with the deletion.
 * If the company to be deleted has comments, the function prints a message and does not delete the company.
 * After a company is deleted, the function saves the updated Companies struct to a file.
 *
 * @param companies A pointer to the struct Companies that stores all companies.
 *
 * @note The function will print a message and return if there are no companies to delete.
 */
void delete_companies(Companies *companies) {
    int pos_nif = 0;
    
    if (companies->cont_comp > 0) {
        do {     
            printf("Opção elimnar!\n");
            pos_nif = insert_nif(*companies);
            if (pos_nif != -1 && companies->company[pos_nif].cont_coments == 0) {
                printf("Tem a certeza que pretende eliminar a empresa:\n");
                information_company(*companies, pos_nif);        

                if (repet_option(0, "", "") == 0) { 
                    for (i = pos_nif; i < (companies->cont_comp - 1); i++) {
                        companies->company[i] = companies->company[i + 1];
                    }
                    
                    companies->cont_comp--;
                    save_file_comp(companies);
                    printf("Empresa eliminada com sucesso!\n");
                }    
            } else if (pos_nif != -1 && companies->company[pos_nif].cont_coments > 0) {
                printf(MSG_COMP_WITH_COMMENTARY_DEL, companies->company[pos_nif].name_compa, companies->company[pos_nif].cont_coments);
            }
        } while (repet_option(1, MSG_REP_DELET, MSG_REP_COMPANY) == 0);
    } else { 
        printf(MSG_IMP_OPERATION_INSERT_COMP, "eliminar");
    } 
}

/**
 * @brief Edits companies in the Companies struct.
 *
 * This function edits an existing company in the Companies struct. 
 * The function checks if there are companies and valid activity branches before attempting to edit a company.
 * If the company to be edited has no comments, the function asks the user for confirmation before proceeding with the edit.
 * If the company to be edited has comments, the function allows the user to change the state of the company.
 * After a company is edited, the function saves the updated Companies struct to a file.
 *
 * @param companies A pointer to the Companies struct that stores all companies.
 * @param branchs The Branch_Activity struct that stores all activity branches.
 *
 * @note The function will print a message and return if there are no companies to edit.
 * @note The function will print a message and return if there are no active activity branches.
 */
void edit_companies(Companies *companies, Branch_Activity branchs) {
    int pos_nif = 0;
    
    if (companies->cont_comp > 0 && branchs.cont_branch > 0 && valids_branch(branchs) == 0) {        
        printf("Editar empresa\n");
        printf("Total de empresas --> %d\n", companies->cont_comp);

        do {
            pos_nif = insert_nif(*companies);
            if (pos_nif != -1 && companies->company[pos_nif].cont_coments == 0) {
                printf("Tem a certeza que deseja alterar a empresa:\n");
                information_company(*companies, pos_nif);
                
                if(repet_option(0, "", "") == 0) {   
                    fields_company(companies, branchs, pos_nif);
                }

                save_file_comp(companies);
            } else if (pos_nif != -1 && companies->company[pos_nif].cont_coments > 0) {
                printf(MSG_COMP_WITH_COMMENTARY_ED, companies->company[pos_nif].name_compa, companies->company[pos_nif].cont_coments);
                companies->company[pos_nif].state = getInt(0, 1, MSG_INSERT_STATE_COMPANY); 
                save_file_comp(companies);
            }
        } while (repet_option(1, MSG_REP_EDIT, MSG_REP_COMPANY) == 0);
    } else if (companies->cont_comp == 0) {
        printf(MSG_IMP_OPERATION_INSERT_COMP, "editar");
    } else {
        printf("Como ainda não existem ramos ativos, não é possível editar!");
    }
}

/**
 * @brief Consults companies in the Companies struct.
 *
 * This function consults an existing company in the Companies struct. 
 * The function checks if there are companies before attempting to consult one.
 * If the company to be consulted is found, the function prints the company's information, including comments and ratings.
 * The function also calculates and prints the average of the company's ratings.
 *
 * @param companies The Companies struct that stores all companies.
 *
 * @note The function will print a message and return if there are no companies to consult.
 */
void consult_companies(Companies companies) {    
    int pos_nif = 0;
    float valor_classi = 0;
    
    if (companies.cont_comp > 0) {        
        printf("Consultar empresa\n");         
        do {      
            pos_nif = insert_nif(companies);

            if (pos_nif != -1) {
                printf("Dados da empresa:\n");
                information_company(companies, pos_nif);

                printf("Total de comentarios --> %d\n", companies.company[pos_nif].cont_coments);

                for (i = 0; i < companies.company[pos_nif].cont_coments; i++) {                        
                    printf("Comentario nº%d\n", i + 1);
                    printf("Email do utilizador --> %s\n", companies.company[pos_nif].comment[i].data_user.email_user);
                    information_comments(companies, pos_nif, i);
                }
                
                for (i = 0; i < companies.company[pos_nif].cont_classi; i++) {
                    printf("Email do utilizador --> %s\n", companies.company[pos_nif].comp_class[i].data_user.email_user);
                    information_classi(companies, pos_nif, i);
                    valor_classi = valor_classi + (float)(companies.company[pos_nif].comp_class[i].class);
                }

                if (companies.company[pos_nif].cont_classi > 0) {
                    printf("Média de classificação da empresa --> %0.2f\n", valor_classi / companies.company[pos_nif].cont_classi);
                } else {
                    printf("Média de classificação da empresa --> 0\n");
                }
                
                valor_classi = 0;
            }
        } while (repet_option(1, MSG_REP_CONSULT, MSG_REP_COMPANY) == 0); 
    } else {
        printf(MSG_IMP_OPERATION_INSERT_COMP, "consultar");
    }   
}

/**
 * @brief Lists the companies in the Companies struct.
 *
 * This function lists all existing companies in the Companies struct. 
 * The function checks if there are companies before attempting to list.
 * For each company, the function prints the company's information, the total number of comments, and the average of the ratings.
 *
 * @param companies The Companies struct that stores all companies.
 *
 * @note The function will print a message and return if there are no companies to list.
 */
void list_companies(Companies companies) {
    float valor_classi = 0;
    
    if (companies.cont_comp > 0) {
        printf("Listar empresa\n");
        printf("Total de empresas --> %d\n", companies.cont_comp);
       
        for (i = 0; i < companies.cont_comp; i++) {
            printf("\nEmpresa nº%d\n", i + 1);
            information_company(companies, i);  
            printf("Total de comentarios -->%d\n", companies.company[i].cont_coments);
            
            for (int y = 0; y < companies.company[i].cont_classi; y++) {
                valor_classi = valor_classi + (float)(companies.company[i].comp_class[y].class);
            }

            if (companies.company[i].cont_classi > 0) {
                printf("Média de classificação da empresa --> %0.2f\n", valor_classi / companies.company[i].cont_classi);
            } else {
                printf("Média de classificação da empresa --> 0\n");
            }  
            valor_classi = 0;
        }
    } else {
        printf(MSG_IMP_OPERATION_INSERT_COMP, "listar");
    }    
}

/**
 * @brief Hides or deletes comments from companies in the Companies struct.
 *
 * This function hides or deletes comments from an existing company in the Companies struct. 
 * The function checks if there are companies before attempting to hide or delete comments.
 * If the company has comments, the function allows the user to choose between hiding or deleting a comment.
 * If the user chooses to delete a comment, the function asks for confirmation before proceeding with the deletion.
 * If the user chooses to hide a comment, the function allows the user to choose between hiding or unhiding the comment.
 * After a comment is hidden or deleted, the function saves the updated Companies struct to a file.
 *
 * @param companies A pointer to the Companies struct that stores all companies.
 * @param branchs A pointer to the Branch_Activity struct that stores all activity branches.
 *
 * @note The function will print a message and return if there are no companies to hide/delete comments.
 */
void ocul_del_companies(Companies *companies, Branch_Activity *branchs) {
    int pos_nif = 0, op_comment = 0, id_comment = 0, op_hide = 0;
    
    if (companies->cont_comp > 0) {
        do {
            printf("Ocultar/Eliminar comentarios\n");
            pos_nif = insert_nif(*companies);
            
            if (pos_nif != -1 && companies->company[pos_nif].cont_coments > 0) {               
                for (i = 0; i < companies->company[pos_nif].cont_coments; i++) {
                    printf("Id Comentario --> %d\n", companies->company[pos_nif].comment[i].id_comen);
                    
                    if (companies->company[pos_nif].comment[i].hide == HIDE) {
                        printf(MSG_HIDE_COMMENT, "Oculatdo\n");
                    } else {
                        printf(MSG_HIDE_COMMENT, "Não Ocultado\n");
                    }
                    
                    printf("Email do utilizador --> %s\n", companies->company[pos_nif].comment[i].data_user.email_user);
                    information_comments (*companies, pos_nif, i);
                }

                op_comment = getInt(1, 2, MSG_REP_OP_OCULT_DEL_COMMENT);

                do {
                    id_comment = getInt(0, (companies->company[pos_nif].cont_coments - 1), MSG_POS_COMMENT);
                } while (validation_pos_comment(*companies, pos_nif, id_comment));

                if (op_comment == 1) { 
                    printf("Tem a certeza que pretende eliminar o comentario da empresa %s:\n", companies->company[pos_nif].name_compa);       
                    printf("Email do utilizador --> %s\n", companies->company[pos_nif].comment[id_comment].data_user.email_user);
                    information_comments(*companies, pos_nif, id_comment);

                    if (repet_option(0, "", "") == 0) {
                        for (i = id_comment; i < (companies->company[pos_nif].cont_coments - 1); i++) {
                            companies->company[pos_nif].comment[i] = companies->company[pos_nif].comment[i + 1];
                            companies->company[pos_nif].comment[i].id_comen--; 
                        }
                        
                        companies->company[pos_nif].cont_coments--;
                        save_file_comp(companies);
                        printf("Comentario eliminado com sucesso!\n");
                    } 
                } else {    
                    op_hide = getInt(VALUE_HIDE, VALUE_NOT_HIDE, MSG_OP_HIDE_COMMENT);

                    if (op_hide == 0) {
                        companies->company[pos_nif].comment[id_comment].hide = HIDE;
                        printf("Comentario ocultado com sucesso!\n");
                    } else {
                        companies->company[pos_nif].comment[id_comment].hide = NOT_HIDE;
                        printf("Comentario desocultar com sucesso!\n");
                    } 
                    save_file_comp(companies);
                }                 
            } else if (pos_nif != -1 && companies->company[pos_nif].cont_coments == 0) {
                printf("Não tem comentarios\n");
            }
        } while (repet_option(1, "ocultar/eliminar", MSG_REP_COMMENT) == 0);
    } else {
        printf(MSG_IMP_OPERATION_INSERT_COMP, "ocultar/eliminar");
    }    
}