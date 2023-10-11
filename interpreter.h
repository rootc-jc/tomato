#ifndef INTERPRETER_H
#define INTERPRETER_H

#define TOMATO_READ_LINE_BUFFER 1024
#define TOMATO_ARG_ELEMENT_BUFFER 1024
#define TOMATO_ARG_BUFFER 1024

char *read_line(void)
{
    int buffersize = TOMATO_READ_LINE_BUFFER;
    char c;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffersize);

    if (!buffer)
    {
        fprintf(stderr, "tomato: buffer not allocated\n");
    }

    while (true)
    {
        c = getchar();

        if (c == EOF || c == '\n')
        {
            c = '\0';
            buffer[position] = c;
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;
        if (position >= buffersize)
        {
            buffersize = buffersize + TOMATO_READ_LINE_BUFFER;
            buffer = realloc(buffer, buffersize);
            if (!buffer)
            {
                fprintf(stderr, "tomato: buffer not allocated\n");
            }
        }
    }
}

// just returns the first word of line
// to made into a splitter where it returns array of all words.
char *tomato_tokenize(char *line)
{
    int arg_element_size = TOMATO_ARG_ELEMENT_BUFFER;

    /*
    int arg_size = TOMATO_ARG_ELEMENT_BUFFER;
    char **args = (char *)malloc(sizeof(char) * arg_element_size * arg_size);
    if (!args)
    {
        fprintf(stderr, "tomato: buffer not allocated\n");
    }
    */

    char *element = (char *)malloc(sizeof(char) * arg_element_size);
    if (!element)
    {
        fprintf(stderr, "tomato: buffer not allocated\n");
    }
    int i = 0;
    char c = line[i];
    while (c != ' ' && c != '\0')
    {
        element[i] = c;
        i++;
        c = line[i];
    }
    return element;
}

// temporary
bool str_compare(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    int def = *(const unsigned char*)s1 - *(const unsigned char*)s2;
    if (def==0)
    {
        return true;
    }
    return false;
}

// temporarily checks if the arg is "exit" and returns
int execute(char *args){
    char *exit = "exit";
    if (str_compare(args,exit))
    {
        return 0;
    }
    return 1;
}

void tomato_loop(void)
{
    int status = 1;
    char *line;
    char *args;
    while (status)
    {
        printf("> ");
        line = read_line();
        args = tomato_tokenize(line);
        status = execute(args);
    }
}

#endif