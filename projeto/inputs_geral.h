/**
 * @file inputs_geral.h
 * @author Students: 8230138 amd 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file inputs general
 *
 * This header file stores all the defined messages, values, and functions, from the inputs_geral.c file.
*/

#ifndef INPUTS_GERAL_H
#define INPUTS_GERAL_H

#include "companies.h"
#include "branchs.h"

#define INVALID_VALUE "O número que introduziu não é válido (Introduza um numero de %d a %d)!\n" /**< Defines the message to inform that the entered number is not valid. */
#define MSG_INSERT_NIF "Introduza o nif da empresa -->" /**< Defines the message to request the company's NIF. */

#define MSG_REP_INSERT "inserir" /**< Defines the message for the 'insert' option. */
#define MSG_REP_EDIT "editar" /**< Defines the message for the 'edit' option. */
#define MSG_REP_CONSULT "consultar" /**< Defines the message for the 'consult' option. */
#define MSG_REP_DELET "apagar" /**< Defines the message for the 'delete' option. */

#define MSG_REP_RANK "outra classificação" /**< Defines the message for another classification. */
#define MSG_REP_COMMENT "outro comentario" /**< Defines the message for another comment. */
#define MSG_REP_COMPANY "outra empresa" /**< Defines the message for another company. */
#define MSG_REP_BRANCH "outro ramo" /**< Defines the message for another branch. */

#define MSG_REP_GENERAL "Deseja %s %s (S: Sim/ N: Não)? -->" /**< Defines the general message template for user confirmation. */
#define MSG_REP_CONFIRME "S: Sim/ N: Não -->" /**< Defines the message for user confirmation. */

#define MSG_COMP_WITH_COMMENTARY_DEL "Não é possível eliminar a empresa %s, porque a mesma já possui %d comentarios de utilizadores!\n" /**< Defines the message to inform that it's not possible to delete the company because it already has user comments. */
#define MSG_COMP_WITH_COMMENTARY_ED "Só é possível editar o estado da empresa %s, porque a mesma já possui %d comentarios de utilizadores!\n " /**< Defines the message to inform that it's only possible to edit the company status because it already has user comments. */

#define MSG_REP_OP_OCULT_DEL_COMMENT "Pretende eliminar ou ocultar comentario (Eliminar: 1/ Ocultar: 2)-->" /**< Defines the message to request the user's choice to delete or hide a comment. */
#define MSG_POS_COMMENT "Introduza o id do comentario -->" /**< Defines the message to request the comment ID. */
#define MSG_HIDE_COMMENT "Estado do comentaio --> %s" /**< Defines the message to display the comment status. */
#define MSG_OP_HIDE_COMMENT "Deseja ocultar ou desocultar o comentario (0: Ocultar / 1:Desocultar)? -->" /**< Defines the message to request the user's choice to hide or unhide a comment. */

#define VALUE_HIDE 0 /**< Defines the value for hiding a comment. */
#define VALUE_NOT_HIDE 1 /**< Defines the value for not hiding a comment. */

#define MSG_INSERT_USER_NAME "Introduza o nome do utilizador -->" /**< Defines the message to request the user's name. */
#define MSG_INSERT_EMAIL_USER "Introduza o email do utilizador -->" /**< Defines the message to request the user's email. */
#define MSG_INSERT_TITLE_COMMENT "Introduza o titulo do comentario -->" /**< Defines the message to request the comment title. */
#define MSG_INSER_TEXT_COMMENT "Introduza o texto do comentario -->" /**< Defines the message to request the comment text. */

#define MSG_INSERT_CLASSI "Introduza a calssificação da empresas -->" /**< Defines the message to request the company's classification. */

#define MSG_IMP_OPERATION_INSERT_COMP "Ainda não foi criada nenhuma empresa, logo não é possivel %s nenhuma empresa!\n" /**< Defines the message to inform that no company has been created yet, so it's not possible to perform certain operations. */

#define STATE_ACTIVE "Estado --> Ativa\n" /**< Defines the message to display the active status. */
#define STATE_INACTIVE "Estado --> Inativa\n" /**< Defines the message to display the inactive status. */

#define POS_CLASSI companies->company[pos_nif].cont_classi /**< Defines the position of the company's classification in the struct. */

/**
 * @brief Cleans the input buffer.
 */
void cleanInputBuffer();

/**
 * @brief Converts a string to uppercase.
 *
 * @param string The string to convert.
 */
void uppercase(char *string);

/**
 * @brief Removes extra spaces from a string.
 *
 * @param string The string to process.
 */
void remove_extra_spaces(char *string);

/**
 * @brief Reads a string from the user.
 *
 * @param string The string to read into.
 * @param size The size of the string.
 * @param msg The message to display before reading the string.
 */
void readString(char *string, unsigned int size, char *msg);

/**
 * @brief Gets an integer from the user.
 *
 * @param minValue The minimum valid value.
 * @param maxValue The maximum valid value.
 * @param msg The message to display before getting the integer.
 * @return int The integer entered by the user.
 */
int getInt(int minValue, int maxValue, char *msg);

/**
 * @brief Gets a character from the user.
 *
 * @return char The character entered by the user.
 */
char getChar();

/**
 * @brief Validates a company in the Companies struct.
 *
 * @param companies The Companies struct.
 * @return int Returns 1 if the company is valid, 0 otherwise.
 */
int valid_comp(Companies companies);

/**
 * @brief Checks if a company is active in the Companies struct.
 *
 * @param companies The Companies struct.
 * @return int Returns 1 if the company is active, 0 otherwise.
 */
int active_comp(Companies companies);

/**
 * @brief Repeats an option.
 *
 * @param op The option to repeat.
 * @param option The option string.
 * @param structs The struct string.
 * @return int Returns 1 if the option is repeated, 0 otherwise.
 */
int repet_option(int op, char *option, char *structs);

/**
 * @brief Checks if a branch is active in the Branch_Activity struct.
 *
 * @param id The ID of the branch.
 * @param branchs The Branch_Activity struct.
 * @param pos_nif The position of the NIF in the struct.
 * @return int Returns 1 if the branch is active, 0 otherwise.
 */
int branch_active(int id, Branch_Activity branchs, int pos_nif);

/**
 * @brief Compares a NIF with the NIFs in the Companies struct.
 *
 * @param companies The Companies struct.
 * @param nif_v The NIF to compare.
 * @return int Returns 1 if the NIF is found, 0 otherwise.
 */
int compare_nif(Companies companies, int nif_v);

/**
 * @brief Inserts a NIF into the Companies struct.
 *
 * @param companies The Companies struct.
 * @return int Returns the position of the inserted NIF in the struct.
 */
int insert_nif(Companies companies);

/**
 * @brief Fills the fields of a user in the Companies struct.
 *
 * @param companies A pointer to the Companies struct that stores all companies.
 * @param pos_nif The position of the NIF in the struct.
 * @param pos The position of the user in the struct.
 */
void fields_user(Companies *companies, int pos_nif, int pos);

/**
 * @brief Displays information about a classification in the Companies struct.
 *
 * @param companies The Companies struct that stores all companies.
 * @param pos_nif The position of the NIF in the struct.
 * @param pos The position of the classification in the struct.
 */
void information_classi(Companies companies, int pos_nif, int pos);

#endif /* INPUTS_GERAL_H */