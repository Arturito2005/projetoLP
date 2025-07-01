/**
 * @file branchs.h
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file with all the structs of the program and functions for the management of branchs.
 *
 * In this header file, you can find all the defined functions and texts, used in the branchs.c file
*/

#ifndef BRANCHS_H
#define BRANCHS_H

#include "companies.h"

#define MSG_INSERT_NAME_BRANCH "Introduza o nome do ramo -->" /**< Defines the message to request the name branch. */
#define MSG_EL_CNF "Tem certeza que deseja eliminar o %s %s? " /**< Defines the message to request the user's when confirming the deletion of an item in the program.The placeholders %s %s are replaced by the specific details of the item during runtime. */
#define INEX_BRANCH  "O ramo de atividade introduzido não existe!\n" /**< Defines the message that the branch introduced doesn't exist. */
#define MSG_IMP_OPERATION_INSERT_BRANCH "Ainda não foi criado nenhum ramo, logo não é possivel %s nenhum ramo!\n" /**< Defines the message to standardize the error message when trying to perform operations on branches before any branches have been created. */
#define BRANCH_NOT_FOUND "O ramo não foi encontrado!" /**< Defines the message to standardize the mesage that the branch was not found. */

/**
 * @brief Adds a new branch of activity.
 * 
 * @param branchs Pointer to the Branch_Activity struct.
 */
void add_branch(Branch_Activity *branchs);

/**
 * @brief Deletes an existing branch of activity.
 * 
 * @param branchs Pointer to the Branch_Activity struct.
 * @param companies Pointer to the Companies struct.
 */
void delete_branchs(Branch_Activity *branchs, Companies *companies);

/**
 * @brief Edits an existing branch of activity.
 * 
 * @param branchs Pointer to the Branch_Activity struct.
 * @param companies Pointer to the Companies struct.
 */
void edit_branch(Branch_Activity *branchs, Companies *companies);

/**
 * @brief Lists all branches of activity.
 * 
 * @param branchs Branch_Activity struct.
 */
void branch_list(Branch_Activity branchs);

/**
 * @brief Consults a specific branch of activity.
 * 
 * @param branchs Branch_Activity struct.
 */
void consult_branch(Branch_Activity branchs);

#endif /* BRANCHS_H */