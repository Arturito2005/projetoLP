/**
 * @file companies.h
 * @author Students: 8230138 and 8230127
 * @date 22-10-2023
 * @version 1
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 * 
 * @brief Header file with all the structs of the program and functions for the management of companies.
 *
 * In this header file you can find all the structs present in the program, such as the company struct, 
 * comments, rating and comments, as well as all the constants at the level of the size of some variables of 
 * these structs. You can also find in this header file, all the functions for the management of companies and 
 * also the function to hide/delete comments from companies.
*/

#ifndef EMPRESAS_H
#define EMPRESAS_H

#define SIZE_NAME_COMP 10 /**< Defines the maximum size of the company name. */
#define SIZE_ROAD 25 /**< Defines the maximum size of the company's street name. */
#define SIZE_LOC 15 /**< Defines the maximum size of the company's locality name. */
#define SIZE_COD_POS 9 /**< Defines the maximum size of the company's postal code. */
#define SIZE_CATEGORY 20 /**< Defines the maximum size of the company's category. */

#define SIZE_TITLE 15 /**< Defines the maximum size of the comment title. */
#define SIZE_TEXT 50 /**< Defines the maximum size of the comment text. */

#define SIZE_NAME_BRANCH 20 /**< Defines the maximum size of the activity branch name. */

#define SIZE_USER 25 /**< Defines the maximum size of the username. */
#define SIZE_EMAIL 50 /**< Defines the maximum size of the user email. */

#define MIN_VALUE_NIF 100000000 /**< Defines the minimum value for the company's NIF. */
#define MAX_VALUE_NIF 999999999 /**< Defines the maximum value for the company's NIF. */

#define SIZE_MAX_EMAIL 29 /**< Defines the maximum size of the user's email. */
#define SIZE_MIN_EMAIL 5 /**< Defines the minimum size of the user's email. */

#define MIN_CATEGORY 1 /**< Defines the minimum category for the company. */
#define MAX_CATEGORY 5 /**< Defines the maximum category for the company. */

#define POS_COMENT companies->company[pos_nif].cont_coments /**< Defines the position of the comment in the company. */

#define ERROR_MSG_NIF_NOT_FIND "O nif %d não está associado a nenhuma empresa!\n" /**< Defines the error message when the NIF is not associated with any company. */

#define MSG_INSERT_NIF_COMPANY "Introduza o nif da empresa -->" /**< Defines the message to request the company's NIF. */
#define MSG_INSERT_NAME_COMAPNY "Introduza o nome da empresa -->" /**< Defines the message to request the company's name. */
#define MSG_INSERT_CATEGORY_COMPANY "Introduza a categoria da empresa (1: Micro/ 2: Empresa de Pequeno Porte/ 3: PME/ 4: Grande empresa/ 5: Sociedade Limitada)-->" /**< Defines the message to request the company's category. */
#define MSG_INSERT_ROAD_COMPANY "Introduza a rua da empresa -->" /**< Defines the message to request the company's street. */
#define MSG_INSERT_LOC_COMPANY "Introduza a localidade da empresa -->" /**< Defines the message to request the company's locality. */
#define MSG_INSERT_COD_POSTAL_COMPANY "Introduza o codigo postal da empresa -->" /**< Defines the message to request the company's postal code. */
#define MSG_INSERT_STATE_COMPANY "Introduza o estado da empresa (0: Ativa/ 1: Inativa)-->" /**< Defines the message to request the company's state. */

/**
 * @brief Enumeration for the usage state of the activity branch and companies.
 */
typedef enum {
    ACTIVE = 0, /**< The State is active. */
    INACTIVE = 1 /**< The State is inactive. */
} State;

/**
 * @brief Enumeration for the company categories.
 */
typedef enum {
    MICRO = 1, /**< Micro company. */
    SMALL_BUSINESS = 2, /**< Small business. */
    PME = 3, /**< Small and medium-sized enterprises. */
    BIG_COMPANY = 4, /**< Big company. */
    LIMITED_SOCIETY = 5 /**< Limited society. */
} categories;

/**
 * @brief Enumeration for the comment hide state.
 */
typedef enum {
    HIDE = 0, /**< The comment is hidden. */
    NOT_HIDE = 1 /**< The comment is not hidden. */
} Hide;

/**
 * @brief Struct to store company search information.
 */
typedef struct {
    int cont_name; /**< Counter for the company name. */
    int cont_category; /**< Counter for the company category. */
    int cont_loc; /**< Counter for the company locality. */
} Search_comp;

/**
 * @brief Struct to store the user's information.
 */
typedef struct {
    char user_name[SIZE_USER]; /**< User name. */ 
    char email_user[SIZE_EMAIL]; /**< User email. */
} Data_User;

/**
 * @brief Struct to store the user's rating.
 */
typedef struct {
    int class; /**< User's rating. */
    Data_User data_user; /**< User's data. */
} Classification;

/**
 * @brief Struct to store the user's comments.
 */
typedef struct{
    int id_comen; /**< Comment ID. */
    Data_User data_user; /**< User's data. */
    char title[SIZE_TITLE]; /**< Comment title. */
    char text[SIZE_TEXT]; /**< Comment text. */
    Hide hide; /**< Comment hide state. */
} Comments;

/**
 * @brief Struct to store the activity branch data.
 */
typedef struct{
    char name_branch[SIZE_NAME_BRANCH]; /**< Activity branch name. */
    State state; /**< Activity branch state. */
} Data_Branch;

/**
 * @brief Struct to store the activity branches.
 */
typedef struct {
    int cont_branch; /**< Counter for the number of activity branches. */
    int size_branch; /**< Size of the activity branch struct. */
    Data_Branch *branch; /**< Pointer to the activity branch struct. */
} Branch_Activity;

/**
 * @brief Struct to store the company data.
 */
typedef struct{
    int nif; /**< Company's NIF. */
    char name_compa[SIZE_NAME_COMP]; /**< Company's name. */
    char road[SIZE_ROAD]; /**< Company's street. */
    char locality[SIZE_LOC]; /**< Company's locality. */
    char cod_postal[SIZE_COD_POS]; /**< Company's postal code. */
    categories category; /**< Company's category. */
    Data_Branch branch; /**< Company's activity branch data. */
    State state; /**< Company's state. */
    int cont_coments; /**< Counter for the number of company comments. */
    int cont_classi; /**< Counter for the number of company ratings. */
    int size_comments; /**< Size of the company comments struct. */
    int size_classi; /**< Size of the company ratings struct. */
    Comments *comment; /**< Pointer to the company comments struct. */
    Classification *comp_class; /**< Pointer to the company ratings struct. */
} Data_companies;

/**
 * @brief Struct to store the companies.
 */
typedef struct {
    int cont_comp; /**< Counter for the number of companies. */
    int size_company; /**< Size of the company struct. */
    Data_companies *company; /**< Pointer to the company struct. */
} Companies;

/**
 * @brief Adds companies to the Companies struct.
 *
 * @param companies A pointer to the Companies struct.
 * @param branchs The Branch_Activity struct.
 */
void add_companies(Companies *companies, Branch_Activity branchs);

/**
 * @brief Deletes companies from the Companies struct.
 *
 * @param companies A pointer to the Companies struct.
 */
void delete_companies(Companies *companies);

/**
 * @brief Edits companies in the Companies struct.
 *
 * @param companies A pointer to the Companies struct.
 * @param branchs The Branch_Activity struct.
 */
void edit_companies(Companies *companies, Branch_Activity branchs);

/**
 * @brief Lists the companies in the Companies struct.
 *
 * @param companies The Companies struct.
 */
void list_companies(Companies companies);

/**
 * @brief Consults companies in the Companies struct.
 *
 * @param companies The Companies struct.
 */
void consult_companies(Companies companies);

/**
 * @brief Hides or deletes comments from companies in the Companies struct.
 *
 * @param companies A pointer to the Companies struct.
 * @param branchs A pointer to the Branch_Activity struct.
 */
void ocul_del_companies(Companies *companies, Branch_Activity *branchs);

#endif /* EMPRESAS_H */