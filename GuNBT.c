#include "GuNBT.h"
#include "GuCE.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define int8_t unsigned char
#define int16_t unsigned short
#define int32_t unsigned int
#define int64_t unsigned long long


//TODO: DON'T ADD END TO COMPOUND!!!!!!!!!!!!!
char * gnbt_read_name(unsigned char * stream)
{
    int16_t length = *stream;
    stream += 2;
    char * name = malloc(length + 1);
    memcpy(name, stream, length)
    stream += length;
    name[length] = '\0';
    return name;
}


int gnbt_read_byte_array(gnbt_node * node, unsigned char * stream)
{
    int16_t length = *stream;
    stream += 2;
    node->nbt_payload.nbt_byte_array.length = length;
    node->nbt_payload.nbt_byte_array.data = malloc(length + 1);
    memcpy(node->nbt_payload.nbt_byte_array.data, stream, length)
    stream += length;
    return length;
}

int gnbt_read_string(gnbt_node * node, unsigned char * stream)
{
    int16_t length = *stream;
    stream += 2;
    node->nbt_payload.nbt_string.length = length;
    node->nbt_payload.nbt_string.data = malloc(length + 1);
    memcpy(node->nbt_payload.nbt_string.data, stream, length)
    stream += length;
    name[length] = '\0';
    return length;
}

int gnbt_read_list(gnbt_node * node, unsigned char * stream)
{
    node->nbt_payload.nbt_list.type = *++stream;
    int16_t length = *stream;
    stream += 2;
    node->nbt_payload.nbt_list.length = length;
    node->nbt_payload.nbt_list.data = malloc(length * sizeof(gnbt_node));
    int i = 0;
    gnbt_node * a = node->nbt_payload.nbt_list.data;
    for (i = 0; i < length; i++)
    {
        a->type = *++stream;
        gnbt_read_node_type(a, stream);
    }

}

int gnbt_read_compound(gnbt_node * node, unsigned char * stream)
{
    gnbt_node * a = node->nbt_payload.nbt_compound.data;
    int i = 0:
    while (1)
    {
        a->type = *++stream;
        if (a->type == gnbt_type_end)
            break;
        node->nbt_payload.nbt_compound.data = malloc(++i * sizeof(gnbt_node));
        ++a = gnbt_read_node(stream);
    }
}

int gnbt_read_int_array(gnbt_node * node, unsigned char * stream)
{
    int16_t length = *stream;
    stream += 2;
    node->nbt_payload.nbt_int_array.length = length;
    node->nbt_payload.nbt_int_array.data = malloc((length + 1) * 2);
    memcpy(node->nbt_payload.nbt_int_array.data, stream, length * 2)
    stream += length * 2;
    return length;
}


gnbt_node * gnbt_read_node(unsigned char * stream)
{
    gnbt_node * node = malloc(sizeof(gnbt_node));
    node->type = *++stream;
    node->name = (node->type != gnbt_type_end) ? gnbt_readname(stream) : "";
    return gnbt_read_node_type(node, stream);
}

gnbt_node * gnbt_read_node_type(gnbt_node * node, unsigned char * stream)
{
    switch (node->type)
    {
        case gnbt_type_end:
            return node;
        case gnbt_type_byte:
            node->nbt_payload.tag_byte = *++stream;
            break;
        case gnbt_type_short:
            node->nbt_payload.tag_short = *((int16_t)stream);
            stream += 2;
            break;
        case gnbt_type_int:
            node->nbt_payload.tag_int = *((int32_t)stream);
            stream += 4;
            break;
        case gnbt_type_long:
            node->nbt_payload.tag_long = *((int64_t)stream);
            stream += 8;
            break;
        case gnbt_type_float:
            node->nbt_payload.tag_float = *((float)stream);
            stream += 4;
            break;
        case gnbt_type_double:
            node->nbt_payload.tag_double = *((double)stream);
            stream += 8;
            break;
        case gnbt_type_byte_array:
            stream += gnbt_read_byte_array(node, stream);
            break;
        case gnbt_type_string:
            stream += gnbt_read_string(node, stream);
            break;
        case gnbt_type_list:
            stream += gnbt_read_list(node, stream);
            break;
        case gnbt_type_compound:
            stream += gnbt_read_compound(node, stream);
            break;
        case gnbt_type_int_array:
            stream += gnbt_read_int_array(node, stream);
            break;
    }
    return node;
}

void gnbt_parse_file(FILE * fp)
{
    long readsize;
    unsigned char * stream = inflatenbt(fp, &readsize);
    gnbt_node * tree = gnbt_read_node(stream);
    //:D
}

void gnbt_save_tree(nbt_node * tree, const char * path)
{

}

void gnbt_free(nbt_node * node)
{
    free(node->name);
    int i = 0;
    switch(node->type)
    {
        case gnbt_type_byte_array:
            for (i = 0; i < node->nbt_payload.tag_byte_array.length; i++)
                free(node->nbt_payload.tag_byte_array.data[i]);
            break;
        case gnbt_type_string:
            free(node->nbt_payload.tag_string.data);
            break;
        case gnbt_type_list:
            for (i = 0; i < node->nbt_payload.tag_list.length; i++)
                gnbt_free(node->nbt_payload.tag_list.data[i]);
            break;
        case gnbt_type_compound:
            for (i = 0; i < node->nbt_payload.tag_compound.length; i++)
                gnbt_free(node->nbt_payload.tag_compound.data[i]);
            break;
        case gnbt_type_int_array:
            for (i = 0; i < node->nbt_payload.tag_int_array.length; i++)
                free(node->nbt_payload.tag_int_array.data[i]);
            break;
    }
    free(node);
}

gnbt_node * nbt_find_by_name(nbt_node * tree, const char * name)
{

}

gnbt_node * nbt_add_to_compound(nbt_node * tree, nbt_node * node)
{

}

int main(int argc, char ** argv)
{
    if (argc == 1)
    {
        FILE * fp = fopen(argv[1], "rb");
        gnbt_parse_file(fp);
    } else
        printf("NONO!");
    return 0;
}
