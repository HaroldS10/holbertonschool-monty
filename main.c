#include "monty.h"
/**
 * main - monty interperter
 * @ac: the number of arguments
 * @av: the arguments
 * Return: void
 */
int main(int argc, char *argv[])
{
        stack_t *stack = NULL;
        static char *string[3000] = {NULL};
        int n = 0;
        FILE *fd;
        size_t bufsize = 3000;

        if (argc != 2)
        {
                fprintf(stderr, "USAGE: monty file\n");
                exit(EXIT_FAILURE);
        }
        fd = fopen(argv[1], "r");
        if (fd == NULL)
        {
                fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
                exit(EXIT_FAILURE);
        }


        for (n = 0; getline(&(string[n]), &bufsize, fd) > 0; n++)
                ;
        n--;
        execute(string, stack);
        free_list(string);
        fclose(fd);
        return (0);
}

/**
 * execute - executes opcodes
 * @string: contents of file
 * @stack: the list
 * Return: void
 */

void execute(char *string[], stack_t *stack)
{
        int ln, n, i;

        instruction_t st[] = {
                {"pall", pall},
                {"swap", swap},
                {"pop", pop},
                {"null", NULL},
		{"pint", pint},
		{"add", add},
        };

        for (ln = 1, n = 0; string[n + 1]; n++, ln++)
        {
                if (_strcmp("push", string[n]))
                        push(&stack, ln, pushint(string[n], ln));
                else if (_strcmp("nop", string[n]))
                        ;
                else
                {
                        i = 0;
                        while (!_strcmp(st[i].opcode, "null"))
                        {
                                if (_strcmp(st[i].opcode, string[n]))
                                {
                                        st[i].f(&stack, ln);
                                        break;
                                }
                                i++;
                        }
                        if (_strcmp(st[i].opcode, "null") && !_strcmp(string[n], "\n"))
                        {
                                fprintf(stderr, "L%u: unknown instruction %s", ln, strtok(string[n]," "));
                                if (!nlfind(string[n]))
                                        fprintf(stderr, "\n");
                                exit(EXIT_FAILURE);
                        }
                }
        }
        free_stack(stack);
}
