/**
 * @file op_admins.c
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 *
 * @brief File op_admins.c, contains the admin menu and its sub-menus
 *
 * This file contains the administrator’s menu and its corresponding sub-menus (Company catalog menu, branches menu and 
 * reports menu) 
*/

#include <stdio.h>

#include "op_admins.h"
#include "inputs_comp.h"
#include "inputs_geral.h"
#include "reports.h"

/**
 * @brief Company catalog management menu.
 * 
 * This function provides a menu to manage the company catalog.
 * 
 * This option contains a while loop, which only ends when the user selects the option to exit the program or return to
 * the previous menu (administrator menu).
 * Within the while loop, a message is presented for the menu options and then the user is asked to enter an option.
 * Option 1 allows the creation of a company, option 2 allows the deletion of a company, option 3 allows editing a company,
 * option 4 allows listing all created companies, option 5 consults the data of a company, option 6 deletes/hides
 * a comment from a company, options 6 and 7 end the while loop, with option 6 returning to the administrator menu
 * and 7 ending the program.
 * 
 * @param op_cat Pointer to an integer that stores the catalog menu choice.
 * @param companies Pointer to the Companies struct that contains the data of all companies.
 * @param branchs Pointer to the Branch_Activity struct that contains the data of all branches.
 */
void manage_cat(int *op_cat, Companies *companies, Branch_Activity *branchs) {    
    *op_cat = 0;
    
    while (*op_cat < 7 || *op_cat > 8) {    
        printf("Gerir catálogo da empresa\n");
        *op_cat = getInt(MIN_OP_CAT, MAX_OP_CAT, MSG_MENU_CATALOG);
        
        switch (*op_cat) {
            case 1: {
                add_companies(companies, *branchs);
                break;
            } 
            case 2: {
                delete_companies(companies);
                break;
            }
            case 3: {
                edit_companies(companies, *branchs);
                break;
            }
            case 4: {
                list_companies(*companies);
                break;        
            }
            case 5: {
                consult_companies(*companies);
                break;
            }
            case 6: {
                ocul_del_companies(companies, branchs);
                break;
            }
            case 7: {
                printf("Voltou ao menu do administrador\n");
                break;
            }
            case 8: {
                break;
            }
            default: {
                printf("Opção invalida!\n");
                break;
            }
        }
    }    
}

/**
 * @brief Manages the operations related to branches of activity.
 * 
 * The operations include adding a branch, deleting a branch, editing a branch, listing all branches, and consulting a specific branch.
 * The operations are performed by a menu based in the user option, it starts with a while cicle, that have all the options to perform various operations related to branchs of activity, go back to the previous menu, and finish the program.
 * 
 * The first option allow the user to add a branch of activity 
 * The second option allow the user to delete a branch of activity 
 * The third option allow the user to edit a branch of activity 
 * The fourth option allow the user to list all the existing branchs of activity 
 * The fifth option allow the user to list all the existing branchs of activity 
 * The sixth option allow the user to go back to the previous menu 
 * The seventh option allow the user to end the program
 * If the user enters a different number, the program print option invalid and repeat the while cicle
 * 
 * @param op_branch Pointer to an integer that represents the operation chosen by the user.
 * @param branchs Pointer to the Branch_Activity structure that represents the branches of activity.
 * @param companies Pointer to the Companies structure that represents the companies.
 */
void manage_branch(int *op_branch, Branch_Activity *branchs, Companies *companies) {   
    *op_branch = 0;
    
    while (*op_branch < 6 || *op_branch > 7) {    
        printf("Gerir ramos de atividade!\n");
        *op_branch = getInt(MIN_OP_MENU_BRANCH, MAX_OP_MENU_BRANCH, MSG_MENU_BRANCH);
        
        switch (*op_branch) {
            case 1: {
                add_branch(branchs);
                break;
            }    
            case 2: {
                delete_branchs(branchs, companies);
                break;
            }
            case 3: {
                edit_branch(branchs, companies);
                break;
            }
            case 4: {
                branch_list(*branchs);
                break;
            }
            case 5: {
                consult_branch(*branchs);
                break;
            } 
            case 6: {
                printf("Voltou ao menu do administrador\n");
                break;
            }
            case 7: {
                break;
            }           
            default: {
                printf("Opção invalida!\n");
                break;
            }
        }
    }    
}

/**
 * @brief Reports menu.
 * 
 * This function provides 3 distinct reports on the user's use of the options.
 * 
 * This option contains a while loop, which only ends when the user selects the option to exit the program or return to
 * the previous menu (administrator menu).
 * Within the while loop, a message is presented for the menu options and then the user is asked to enter an option.
 * Option 1 creates a report on the classification of companies, option 2 creates a report on the comments of companies,
 * option 3 creates a report on the search options of companies, options 4 and 5 end the while loop,
 * with option 4 returning to the administrator menu and 5 ending the program.
 * 
 * @param op_report Pointer to an integer that stores the user's report menu choice.
 * @param companies Pointer to the Companies struct that contains the data of all companies.
 * @param search_comp Search_comp struct, which contains the total counters of each company search option.
 * 
 * @note It is only possible to access the classification report if there is at least one company with one or more ratings.
 * @note It is only possible to access the comments report if there is at least one company with one or more comments.
 * @note It is only possible to access the search report if the user has already searched for at least one company.
 */
void view_reports(int *op_report, Companies *companies, Search_comp search_comp) {
    printf("Visualizar relatório\n");
    *op_report = 0;
    
    while (*op_report < 4 || *op_report > 5) {
        *op_report = getInt(MIN_OP_REPORT, MAX_OP_REPORT, MSG_MENU_REPORT);
       
        switch (*op_report) {
            case 1: {
                if (exist_classi(*companies) == 0) {
                    report_classi(*companies);
                } else {
                    printf("Ainda não existem classificações!\n");
                } 
                break;
            }
            case 2: {
                if (exist_comm(*companies) == 0) {
                    report_comment(*companies);
                } else {
                    printf("Ainda não existem comentarios!\n");
                }
                break;
            }
            case 3: {
                if (search_comp.cont_name > 0 || search_comp.cont_category > 0 || search_comp.cont_loc > 0) {
                    report_search(search_comp);
                } else if (search_comp.cont_name == 0 && search_comp.cont_category == 0 && search_comp.cont_loc == 0) {
                    printf("É necessario o uilizador realizar pelo menos uma pesquisa por uma empresa para usar esta opção!\n");
                }
                break;
            }
            case 4: {
                printf("Voltar menu admin!\n");
                break;
            }
            case 5: {
                break;
            }
            default: {
                break;
            }
        } 
    }
}

/**
 * @brief Administrator's menu.
 * 
 * This function provides 3 distinct reports on the user's use of the options.
 * 
 * This option contains a while loop, which only ends when the user selects the option to exit the program or return to
 * the previous menu (administrator's menu).
 * Within the while loop, a message is displayed for the administrator's menu options and then the user is asked to enter
 * an option.
 * Option 1 redirects the user to the company catalog management menu, option 2 redirects the user to the activity branch
 * management menu and option 3 redirects the user to the reports menu.
 * Options 4 and 5 end the while loop, with option 4 returning to the main menu and option 5 closing the program.
 *
 * @param op_adm Pointer to the administrator's option.
 * @param op_cat Pointer to the category option.
 * @param op_branch Pointer to the activity branch option.
 * @param op_report Pointer to the reports option.
 * @param companies Pointer to the Companies struct.
 * @param branchs Pointer to the Branch_Activity struct.
 * @param search_comp Search_comp struct.
 * 
 * @note The user can only access the reports menu if there is at least one company with its active status,
 * or if a search for a company has already been carried out by the user's option.
 */
void menu_admin(int *op_adm, int *op_cat, int *op_branch, int *op_report, Companies *companies, Branch_Activity *branchs, Search_comp search_comp) {
    *op_adm = 0;
    
    printf("Bem-vindo Administrador!\n");
    while ((*op_adm < 4 || *op_adm > 5) && *op_cat != 8 && *op_report != 5 && *op_branch != 7) { 
        *op_adm = getInt(MIN_OP_MENU_ADMIN, MAX_OP_MENU_ADMIN, MSG_MENU_ADMIN);
        
        switch (*op_adm) {
            case 1: {
                manage_cat(op_cat, companies, branchs);
                break;
            }
            case 2: {
                manage_branch(op_branch, branchs, companies);
                break;
            }
            case 3: {
                if((companies->cont_comp > 0 && active_comp(*companies) == 0) || ((search_comp.cont_category + search_comp.cont_loc + search_comp.cont_name) > 0)) {
                    view_reports(op_report, companies, search_comp);
                } else {
                    printf("Ainda não existem empresas!\n");
                }  
                break;
            }
            case 4: {
                printf("Voltar ao menu principal\n");
                break;
            }
            case 5: {
                break;
            }
            default: {
                printf("Opção inválida (introduza um numero entre %d e %d)!\n", MIN_OP_MENU_ADMIN, MAX_OP_MENU_ADMIN);
                break;
            }
        }
    }
}