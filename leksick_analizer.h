#ifndef LEKSICK_ANALIZER_HEADER
#define LEKSICK_ANALIZER_HEADER


const int TOKENATOR_ARRAY_SIZE = 100;
const size_t MAX_TOKEN_LENGTH  = 30;

struct variable_t
{
    char*        name;
    int          fimoznost;
};

struct cmd_t
{
    char    name [ MAX_TOKEN_LENGTH ];
    int     number_of_cmd;
};

enum errors_t
{
    DONE = 0,
};
struct func_t
{
    char*        name;
    int          vars_amount;
};

enum type_t
{
    NUM     = 1,
    OPERAND = 2,
    FUNC    = 3,
};
union var_op_const_t
{
    variable_t   variable;
    func_t       operation;
    int          constant;
};

struct tree_elem_t
{
    type_t       type;
    var_op_const_t  xer_ovtsy;
    bool         is_poison;
};

struct syntaksis_t
{
    const char*     functions;
    const char*     inits;
};

struct tree_t
{
    tree_elem_t*    array_data;
    tree_elem_t*    token_aray;
    //char*           vars_array; ??????????????????????????????????
    syntaksis_t     syntaksis;
    int             size;
    tree_elem_t*    g_root;
};


tree_elem_t* token_aray_ctor ( size_t size );
errors_t tokenize_input_file        ( FILE* input_file );
errors_t convert_to_tokens ( tree_t* tree, tree_elem_t* tokens_aray, FILE* input_file );
size_t   get_file_size              ( FILE* input_file );

#endif
