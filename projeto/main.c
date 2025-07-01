/**
 * @file main.c
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights Reserved. MIT Licensed.
 *
 * @brief This C program allows the management of companies and user reviews and comments
 *
 * This program consists of managing companies, and their respective branches of activity, by the administrator, in 
 * addition to allowing users to search, rate, and comment on companies.
 * In addition to managing companies, administrators also have access to 3 distinct reports on the use of user options 
 * by them, where one of the reports is about the ratings assigned to companies, another about the comments and even 
 * about which search option was most used.
 * 
 * @note The management of companies and branches of activity is carried out through a CRUD system (Create, Read, 
 * Update, Delete) 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op_admins.h"
#include "op_user.h"
#include "companies.h"
#include "branchs.h"
#include "inputs_user.h"
#include "inputs_comp.h"
#include "inputs_geral.h"
#include "inputs_file_memory.h"

#define MIN_OP_MAIN 1 /**< Defines the value of the first option of the main menu. */
#define MAX_OP_MAIN 4 /**< Defines the value of the last option of the main menu. */

#define MSG_MENU_MAIN "Introduza uma opção (1: Administrador/ 2: Utilizador/ 3: Guardar dados/ 4: Sair da aplicação) -->" /**< Defines the text of the main menu of the program. */

/**
 * @brief Main file of the program.
 *
 * In main, all the integer variables of the program's menu options are declared: op, op_adm, op_util, op_cat, 
 * op_branch and op_report, along with the integer variable i.
 * The structs and their counters and size are also initialized: the Companies struct companies, with its field 
 * cont_comp at 0 and size_company at 1, the Branch_Activity struct branchs with its cont_branc at 0 and size_branch at 1
 * and the Search_comp struct search_comp and its fields cont_name at 0, cont_category at 0 and cont_loc at 0.
 * After initializing the variables, the void load_file is executed which allocates memory for some variables 
 * of the companies and branchs structs, in addition to loading all the data stored in the file of the companies, 
 * branchs and search_comp structs. 
 * After load_files, a while loop is initialized that only ends when the option to exit the program is selected in any of the menus of 
 * the application. 
 * Within the while loop, a message appears warning that we are in the main menu and shows all the options of it, 
 * in addition to asking the user to enter one of the 4 menu options.
 * After entering the option, a switch is executed that if the selected option is 1 the user is directed to the menu 
 * of the administrator, if the option is 2 it is directed to the option of the users, if it is 3 all the data 
 * stored in the 3 previously mentioned structs are saved in a file, and if the option 4 is selected the program is
 * closed, but before closing the program all the information of the program is saved in a file and all the 
 * dynamically allocated memory is freed.
 * 
 * @return int Returns EXIT_SUCCESS upon successful execution.
 */
int main() {  
    int op = 0, op_adm = 0, op_util = 0, op_cat = 0, op_branch = 0, op_report = 0, i = 0;
    Companies companies = {.cont_comp = 0, .size_company = 1};
    Branch_Activity branchs = {.cont_branch = 0, .size_branch = 1};
    Search_comp search_comp = {.cont_name = 0, .cont_category = 0, .cont_loc = 0};
    
    load_file(&companies, &branchs, &search_comp);
    
    while (op != 4 && op_adm != 5 && op_util != 5 && op_cat != 8 && op_report != 5 && op_branch != 7) {
        printf("Menu principal\n");
        op = getInt(MIN_OP_MAIN, MAX_OP_MAIN, MSG_MENU_MAIN);
        
        switch (op) {           
            case 1: {
                menu_admin(&op_adm, &op_cat, &op_branch, &op_report, &companies, &branchs, search_comp);
                break;
            }
            case 2: {
                if (companies.cont_comp > 0 && valid_comp(companies) == 0) {
                    menu_user(&op_util, &companies, &branchs, &search_comp);
                } else {
                    printf("Ainda não existem empresas, ou as empresas estão inativas! Logo não é possível aceder as opções do utilizador!\n");
                }
                break;
            }
            case 3: {
                save_file_comp(&companies);
                save_file_branchs(&branchs);
                save_search_comp(&search_comp);
                break;
            }
            case 4: {                
                break;
            }
            default: {
                printf("Opção inválida!\n");
                break;
            }
        }            
    }    
    
    save_file_comp(&companies);
    save_file_branchs(&branchs);
    save_search_comp(&search_comp);
    
    for (i = 0; i < companies.cont_comp; i++) {
        free(companies.company[i].comment);
        free(companies.company[i].comp_class);
    }
    
    free(companies.company);
    free(branchs.branch);
      
    return (EXIT_SUCCESS);
}