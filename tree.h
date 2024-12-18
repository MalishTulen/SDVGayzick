#ifndef TREE_HEADER
#define TREE_HEADER

const int               POISON_VALUE        = -66;
const int               MAX_NAME_LEN        = 30;
const int               DATA_CAPACITY       = 300;
const int               MAX_INPUT_LENGTH    = 50;
const int               CMD_COMMAND_LEN     = 50;
const int               VARS_ARRAY_CAPACITY = 20;
const long long         POISON_PTR          = 0xD01BAEB7;

enum leaf_t
{
    LEAF     = 5,
    NOT_LEAF = 10,
};

errors_t tree_ctor          ( tree_t* ptr_tree );
errors_t tree_checker       ( tree_t* ptr );
leaf_t   check_if_leaf      ( tree_elem_t* ptr_node );
errors_t reader             ( FILE* ptr_input_file, tree_t* tree );
tree_elem_t*  create_new_node    ( tree_t* tree, type_t type, var_op_const_t object, tree_elem_t* left, tree_elem_t* right );
errors_t array_dump         ( tree_t* tree, tree_elem_t* node );
errors_t delete_sub_tree    ( tree_elem_t* node );
errors_t delete_node        ( tree_elem_t* node );
tree_elem_t*  copy_sons_balls    ( tree_t* tree, tree_elem_t* node );

#endif
