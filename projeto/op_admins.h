/**
 * @file op_admins.h
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file inputs options admins
 *
 * This header file stores all the defined messages, values, and functions, from the op_admins.c file.
*/

#ifndef ADMINS_H
#define ADMINS_H

#include "companies.h"
#include "op_user.h"

#define MIN_OP_CAT 1 /**< Defines the minimum value for the catalog option. */
#define MAX_OP_CAT 8 /**< Defines the maximum value for the catalog option. */

#define MIN_OP_MENU_BRANCH 1 /**< Defines the minimum value for the branch menu option. */
#define MAX_OP_MENU_BRANCH 7 /**< Defines the maximum value for the branch menu option. */

#define MIN_OP_REPORT 1 /**< Defines the minimum value for the report option. */
#define MAX_OP_REPORT 5 /**< Defines the maximum value for the report option. */

#define MIN_OP_MENU_ADMIN 1 /**< Defines the minimum value for the admin menu option. */
#define MAX_OP_MENU_ADMIN 5 /**< Defines the maximum value for the admin menu option. */

#define MSG_MENU_CATALOG "Introduza uma opcao (1: Adicionar empresa/ 2: Apagar/ 3: Editar/ 4: Listar/ 5: Consultar/ 6: Ocultrar/eliminar comentario/7: Voltar/ 8: Sair) -->" /**< Defines the message for the catalog menu. */
#define MSG_MENU_BRANCH "Introduza uma opcao (1: Adicionar ramo/ 2: Apagar ramo/ 3: Editar ramo/ 4: Listar ramos/ 5: Consultar ramo/ 6: Voltar/ 7: Sair)-->" /**< Defines the message for the branch menu. */
#define MSG_MENU_REPORT "Introduza uma opção (1: Relatorio Classificação/ 2: Relatorio Comentario/ 3: Relatorio pesquisa utililizador/ 4: Voltar/ 5: Sair) -->" /**< Defines the message for the report menu. */
#define MSG_MENU_ADMIN "Introduza uma opção (1: Gerir catálogo da empresa/ 2: Gerir ramos de atividade/ 3: Visualizar relatórios/ 4: Voltar/ 5: Sair) -->" /**< Defines the message for the admin menu. */

/**
 * @brief Manages the catalog of companies and branches of activity.
 *
 * @param op_cat A pointer to the catalog option.
 * @param companies A pointer to the Companies struct.
 * @param branchs A pointer to the Branch_Activity struct.
 */
void manage_cat(int *op_cat, Companies *companies, Branch_Activity *branchs);

/**
 * @brief Manages the branches of activity.
 *
 * @param op_branch A pointer to the branch option.
 * @param branchs A pointer to the Branch_Activity struct.
 * @param companies A pointer to the Companies struct.
 */
void manage_branch(int *op_branch, Branch_Activity *branchs, Companies *companies);

/**
 * @brief Views the reports of companies and searches.
 *
 * @param op_report A pointer to the report option.
 * @param companies A pointer to the Companies struct.
 * @param search_comp The Search_comp struct.
 */
void view_reports(int *op_report, Companies *companies, Search_comp search_comp);

/**
 * @brief Manages the admin menu.
 *
 * @param op_adm A pointer to the admin menu option.
 * @param op_cat A pointer to the catalog option.
 * @param op_branch A pointer to the branch option.
 * @param op_report A pointer to the report option.
 * @param companies A pointer to the Companies struct.
 * @param branchs A pointer to the Branch_Activity struct.
 * @param search_comp The Search_comp struct.
 */
void menu_admin(int *op_adm, int *op_cat, int *op_branch, int *op_report, Companies *companies, Branch_Activity *branchs, Search_comp search_comp);

#endif /* ADMINS_H */

