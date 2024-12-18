#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "leksick_analizer.h"
#include "tree.h"

errors_t tree_ctor ( tree_t* tree )
{
    tree->array_data = ( tree_elem_t* ) calloc ( DATA_CAPACITY, sizeof ( node_t ) );
    tree->syntaksis.functions = "";
    tree->syntaksis.inits = "";
    tree->g_root = &tree->array_data [ 0 ];

    tree->size = 0;

    for ( int i = 0; i < DATA_CAPACITY; i++ )
    {
        tree->array_data [ i ].right            = NULL;
        tree->array_data [ i ].left             = NULL;
        tree->array_data [ i ].type             = POISON_TYPE;
        tree->array_data [ i ].object.constant  = POISON_VALUE;
        tree->array_data [ i ].object.var       = 0;
        tree->array_data [ i ].object.operation = POISON_OPERATION;
    }

    size_t file_size = get_file_size ( input_file );

    tree_elem_t* tokenator = token_aray_ctor ( file_size );

    CHECK ( tree );

    return DONE;
}

errors_t tree_checker ( tree_t* ptr )
{
    if ( !ptr )
        return BAD_TREE_PTR;
    if ( !ptr->array_data )
        return BAD_DATA_PTR;
    if ( ptr->size < 0 )
        return SIZE_UNDER_PLINTUS;

    for ( int i = 0; i < DATA_CAPACITY; i++ )
    {
        if ( ptr->array_data[ i ].left == &ptr->array_data[ i ] )
            return CYCLIC_LEFT;

        if ( ptr->array_data[ i ].right == &ptr->array_data[ i ] )
            return CYCLIC_RIGHT;
    }

    return DONE;
}

leaf_t check_if_leaf ( tree_elem_t* ptr_node )
{
    if ( ptr_node->right == NULL && ptr_node->left == NULL )
        return LEAF;

    return NOT_LEAF;
}

errors_t reader ( FILE* ptr_input_file, tree_t* tree )
{
    assert ( input_file && "bad ptr of input file" );
    assert ( input_data && "bad ptr of data" );

    for ( int i = 0; i < input_data->size; i++ )
    {
        char symbol = 0;

        fscanf ( input_file, " %c", &symbol );

        input_data->data[ i ] = symbol;
    }

    return DONE;
}

tree_elem_t* create_new_node ( tree_t* tree, type_t type, var_op_const_t value, node_t* left, node_t* right )
{
    int error_check = tree_checker ( tree );
    if ( error_check != DONE )
    {
        printf ( "ERROR: %d\n", error_check );
        return 0;
    }

    node_t* new_node = &tree->array_data [ tree->size ];

    new_node->type = type;

    new_node->object = value;

    new_node->left = left;
    new_node->right = right;

    tree->size++;

    return new_node;
}

errors_t delete_sub_tree ( node_t* node )
{
    if ( node->left != NULL )
        delete_sub_tree ( node->left );
    if ( node->right != NULL )
        delete_sub_tree ( node->right );

    delete_node ( node );

    return DONE;
}

errors_t delete_node ( node_t* node )
{
    if ( node->type == NUM )
        node->object.constant = POISON_VALUE;
    else if ( node->type == OP )
        node->object.operation = POISON_OPERATION;
    else if ( node->type == VAR )
        node->object.var = 0;

    node->type = POISON_TYPE;
    node->left = ( node_t* ) POISON_PTR;
    node->right = ( node_t* ) POISON_PTR;

    return DONE;
}

tree_elem_t* copy_sons_balls ( tree_t* tree, node_t* node )
{
    node_t* new_node = create_new_node ( tree, node->type, node->object, NULL, NULL );
    if ( node->left != NULL )
        new_node->left = copy_sons_balls ( tree, node->left );
    if ( node->right != NULL )
        new_node->right = copy_sons_balls ( tree, node->right );

    return new_node;
}

errors_t array_dump ( tree_t* tree, node_t* node )
{
    if ( node->type == NUM )
        printf ( "node: type = NUM, value = %.3lf\n", node->object.constant );
    else if ( node->type == VAR )
        printf ( "node: type = VAR, value = %c\n", node->object.var );
    else if ( node->type == OP )
    {
        printf ( "( \n" );

        if ( node->left != NULL )
            array_dump ( tree, node->left );

        printf ( "node: type = %d, value = %c\n", node->type, tree->operators_array [ node->object.operation - 1 ] );

        if ( node->right != NULL )
            array_dump ( tree, node->right );
        printf ( " )\n" );
    }

    return DONE;
}

