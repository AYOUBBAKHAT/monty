/*
 * Monty Interpreter: A simple stack-based interpreter for Monty bytecode.
 *
 * This program includes functions to open and read a Monty bytecode file,
 * parse each line to determine the appropriate function to call, and execute
 * the corresponding operation. The interpreter supports stack and queue
 * formats, with various operations such as push, pop, swap, arithmetic,
 * and printing functionalities. It utilizes a stack and queue data structure
 * to manipulate and display the state of the data.
 *
 * File: monty.c
 */
#include "monty.h"

/**
 * read_file - Reads a Monty bytecode file line by line.
 * @fd: Pointer to the file descriptor.
 * Return: void
 */

void read_file(FILE *fd)
{
 int line_number, format = 0;
 char *buffer = NULL;
 size_t len = 0;

 for (line_number = 1; getline(&buffer, &len, fd) != -1; line_number++)
 {
  format = parse_line(buffer, line_number, format);
 }
 free(buffer);
}


/**
 * parse_line - Separates each line into tokens and determines the operation to perform.
 * @buffer: Line from the Monty bytecode file.
 * @line_number: Line number.
 * @format: Storage format (stack or queue).
 * Return: Returns 0 if the opcode represents a stack operation, 1 for queue operations.
 */

int parse_line(char *buffer, int line_number, int format)
{
 char *opcode, *value;
 const char *delim = "\n ";

 if (buffer == NULL)
  err(4);

 opcode = strtok(buffer, delim);
 if (opcode == NULL)
  return (format);
 value = strtok(NULL, delim);

 if (strcmp(opcode, "stack") == 0)
  return (0);
 if (strcmp(opcode, "queue") == 0)
  return (1);

 find_func(opcode, value, line_number, format);
 return (format);
}

/**
 * find_func - Finds the appropriate function for the given opcode.
 * @opcode: The opcode to search for.
 * @value: Argument of the opcode.
 * @ln: Line number.
 * @format: Storage format (stack or queue).
 * Return: void
 */
void find_func(char *opcode, char *value, int ln, int format)
{
 int i;
 int flag;

 instruction_t func_list[] = {
  {"push", add_to_stack},
  {"pall", print_stack},
  {"pint", print_top},
  {"pop", pop_top},
  {"nop", nop},
  {"swap", swap_nodes},
  {"add", add_nodes},
  {"sub", sub_nodes},
  {"div", div_nodes},
  {"mul", mul_nodes},
  {"mod", mod_nodes},
  {"pchar", print_char},
  {"pstr", print_str},
  {"rotl", rotl},
  {"rotr", rotr},
  {NULL, NULL}
 };

 if (opcode[0] == '#')
  return;

 for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
 {
  if (strcmp(opcode, func_list[i].opcode) == 0)
  {
   call_fun(func_list[i].f, opcode, value, ln, format);
   flag = 0;
  }
 }
 if (flag == 1)
  err(3, ln, opcode);
}


/**
 * call_fun - Calls the required function based on the opcode.
 * @func: Pointer to the function to be called.
 * @op: String representing the opcode.
 * @val: String representing a numeric value.
 * @ln: Line number for the instruction.
 * @format: Format specifier (0 for stack, 1 for queue).
 * Return: void
 */
void call_fun(op_func func, char *op, char *val, int ln, int format)
{
 stack_t *node;
 int flag;
 int i;

 flag = 1;
 if (strcmp(op, "push") == 0)
 {
  if (val != NULL && val[0] == '-')
  {
   val = val + 1;
   flag = -1;
  }
  if (val == NULL)
   err(5, ln);
  for (i = 0; val[i] != '\0'; i++)
  {
   if (isdigit(val[i]) == 0)
    err(5, ln);
  }
  node = create_node(atoi(val) * flag);
  if (format == 0)
   func(&node, ln);
  if (format == 1)
   add_to_queue(&node, ln);
 }
 else
  func(&head, ln);
}
