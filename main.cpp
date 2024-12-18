#include <stdio.h>

#include "leksick_analizer.h"
//TODO - schitat file
int main()
{
    FILE* input_file = fopen ( "input_file.txt", "r" );

    tokenize_input_file ( input_file );
}
