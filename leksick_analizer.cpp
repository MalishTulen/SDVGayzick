#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>

#include "leksick_analizer.h"
#include "tree.h"


errors_t tokenize_input_file ( FILE* input_file )
{
    //ptr_check
    tree_t tree = {};
    tree_ctor ( &tree );

    size_t file_size = get_file_size ( input_file );

    tree.token_aray = token_aray_ctor ( file_size );

    convert_to_tokens ( &tree, input_file );

}





size_t get_file_size ( FILE* input_file )
{
    struct stat file_info = {};
    fstat ( fileno( input_file ), &file_info );

    return file_info.st_size;
}

tree_elem_t* token_aray_ctor ( size_t size )
{
    //check ptr

    static tree_elem_t* token_array = ( tree_elem_t* ) calloc ( TOKENATOR_ARRAY_SIZE, sizeof ( tree_elem_t ) );
    for ( int i = 0; i < TOKENATOR_ARRAY_SIZE; i++ )
    {
        token_array [ i ].is_poison = true;
    }

    return token_array;
}

errors_t convert_to_tokens ( tree_t* tree, tree_elem_t* tokens_aray, FILE* input_file )
{
    int cur_line_index = 0;

    char current_char = ( char ) getc ( input_file );
    ungetc ( current_char, input_file );

    while ( current_char != EOF )
    {
        current_char = ( char ) getc ( input_file );

        if ( current_char == '\n' )
            cur_line_index = 0;

        else if ( isspace( current_char ) )
            cur_line_index++;

        if ( isdigit ( current_char ) )
        {
            ungetc( current_char, input_file );
            int length = 0;

            int value = 0;

            scanf ( "%d%n", &value, &length );
fprintf ( stderr, "value = %d, length = %d\n", value, length );
            cur_line_index += length;

            tree_elem_t *new_node = create_new_node ( tree, NUM, {.constant = value}, NULL, NULL);
        }

        else
        {
            char cur_token[ MAX_TOKEN_LENGTH ] = {};

            ungetc ( current_char, input_file );
            int length = 0;

            fscanf ( input_file, "%s%n", cur_token, &length);
            current_char += length;

            tree_elem_t new_node = get_string_token ( tree, cur_token);
        }
    }
}

tree_elem_t get_string_token ( tree_t* tree, char* current_token )
{
    if ( check_first_letter (*current_token))                                                       // ??? ??? ??????? ??? ??????????
    {
        cmd_t* cur_name_ptr = give_me_cmd(&tree->names_table, current_token);

        if (cur_name_ptr == NULL)
            cur_name_ptr = NewNameInTable(&tree->names_table, current_token);

        return NewNode(tree, VAR_OR_FUNC, {.prop_name = cur_name_ptr}, NULL, NULL);
    }

    else                                                                                // ??? ???????? ??? ????????? ????
    {
        const MathOperation   *cur_op     = GetOperationBySymbol  (current_token, MY_CODE_MODE);
        const KeyWord         *key_word   = GetKeyWordBySymbol    (current_token, MY_CODE_MODE);
        const ManageElem      *manage_el  = GetManageElemBySymbol (current_token, MY_CODE_MODE);

        if (cur_op != NULL)
        {
            return NewNode(tree, MATH_OP, {.math_op = cur_op}, NULL, NULL);
        }

        else if (key_word != NULL)
        {
            return NewNode(tree, KEY_WORD, {.key_word = key_word}, NULL, NULL);
        }

        else if (manage_el != NULL)
        {
            return NewNode(tree, MANAGER, {.manager = manage_el}, NULL, NULL);
        }
    }
}

bool check_first_letter ( char sym )
{
    return ( ( 'a' <= sym && sym <= 'z') || ( 'A' <= sym && sym <= 'Z') );
}

cmd_t give_me_cmd ( const char* names_array, char cur_token )
{
    if ( strstr ( names_array, cur_token ) == 0 )

}
