/**
 * @file op_user.h
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file inputs options user
 *
 * This header file stores all the defined messages, values, and functions, from the op_user.c file.
*/

#ifndef OP_UTIL_H
#define OP_UTIL_H

#include "companies.h"

#define MIN_OP_MENU_USER 1 /**< Defines the minimum value for the menu user option. */
#define MAX_OP_MENU_USER 5 /**< Defines the maximum value for the menu user option. */

#define MIN_OP_SEARCH 1 /**< Defines the minimum value for the option search company. */
#define MAX_OP_SEARCH 3 /**< Defines the maximum value for the option search company. */

#define MSG_MENU_USER "Introduza uma opção (1: Pesquisar empresa/ 2: Classificar empresa/ 3: Comentar empresa/ 4: Voltar/ 5: Sair do programa) -->" /**< Defines the message for the user menu. */
#define MSG_MENU_SEARCH_COMP "Introduza uma opção (1: Nome empresa/ 2: Categoria empresa/ 3: Localidade) -->" /**< Defines the message for the option search company. */ 

/**
 * @brief Function to search for companies.
 * 
 * @param companies Pointer to the Companies struct.
 * @param search_comps Pointer to the Search_comp struct.
 */
void search_comp(Companies *companies, Search_comp *search_comps);

/**
 * @brief Function to rank companies.
 * 
 * @param companies Pointer to the Companies struct.
 */
void rank_comp(Companies *companies);

/**
 * @brief Function to comment on companies.
 * 
 * @param companies Pointer to the Companies struct.
 */
void comment_comp(Companies *companies);

/**
 * @brief Function to display the user menu and handle user operations.
 * 
 * @param op_user Pointer to the user's chosen operation.
 * @param companies Pointer to the Companies struct.
 * @param branchs Pointer to the Branch_Activity struct.
 * @param search_comps Pointer to the Search_comp struct.
 */
void menu_user(int *op_user, Companies *companies, Branch_Activity *branchs, Search_comp *search_comps);

#endif /* OP_UTIL_H */

