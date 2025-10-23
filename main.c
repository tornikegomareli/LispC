#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "mpc.h"

/*
* 1. DEFINE THE GRAMMAR
 *    -------------------------------
 *    - number   : A decimal number (optional negative, optional decimal point)
 *    - operator : One of the arithmetic symbols: + - * / %
 *    - expr     : Either a number OR a list: (operator expr expr ...)
 *    - lispy    : The root rule - an operator followed by expressions
 *
 * 2. PARSER SETUP
 *    -------------------------------
 *    a) Create parser objects for each grammar rule
 *    b) Define the language using MPC's domain-specific language
 *    c) The parser will convert input strings into Abstract Syntax Trees (AST)
 *
 * 3. REPL (Read-Eval-Print Loop) IMPLEMENTATION
 *    -------------------------------
 *    a) READ:  Get input from user using readline()
 *    b) PARSE: Convert input string to AST using mpc_parse()
 *    c) EVAL:  Traverse AST and compute the result
 *    d) PRINT: Display the result
 *    e) LOOP:  Repeat until user exits
 *
 * 4. AST EVALUATION ALGORITHM (Recursive)
 *    -------------------------------
 *    Base Case:    If node is a number -> return its value
 *    Recursive Case: If node is an expression ->
 *                   a) Get the operator from 2nd child
 *                   b) Evaluate 3rd child to get initial value
 *                   c) For each remaining child that's an expr:
 *                      - Recursively evaluate it
 *                      - Apply operator to accumulate result
 *                   d) Return final result
 *
 * 5. TREE STRUCTURE (for reference)
 *    -------------------------------
 *    Input: (+ 5 (* 2 3))
 *    AST:
 *         lispy
 *           |
 *         expr
 *        /  |  \
 *       (   +   5   expr  )
 *                  /  |  \
 *                 ( * 2 3 )
 *
 * 6. MEMORY MANAGEMENT
 *    -------------------------------
 *    - Free input string after each iteration
 *    - Delete AST after evaluation
 *    - Clean up parsers on exit
 *    - Handle both success and error cases
 *
 * 7. ERROR HANDLING
 *    -------------------------------
 *    - Check if parsing succeeded
 *    - Print parse errors if failed
 *    - Clean up error objects
 *
 * EXAMPLE EVALUATIONS:
 * - Input: (+ 5 3)           -> Output: 8
 * - Input: (* 2 (+ 3 4))     -> Output: 14
 * - Input: (- 10 3 2)        -> Output: 5
 * ============================================================================
 */

int number_of_nodes(mpc_ast_t* t) {
  if(t->children_num == 0) {
    return 1;
  }

  if(t->children_num >= 1) {
    int total = 1;

    for(int i = 0; i < t->children_num; i++) {
      total = total + number_of_nodes(t->children[i]);
    }

    return total;
  }

  return 0;
}

/// strcmp
/// atoi
/// strstr

long eval_op(long x, char* op, long y) {
  if(strcmp(op, "+") == 0) { 
    return x + y;
  }

  if(strcmp(op, "-") == 0) { 
    return x - y;
  }

  if(strcmp(op, "*") == 0) { 
    return x * y;
  }

  if(strcmp(op, "/") == 0) { 
    return x / y;
  }

  return 0;
}

long eval(mpc_ast_t* t) {
  if(strstr(t->tag, "number")) {
    return atoi(t->contents);
  }

  char* op = t->children[1]->contents;
  long x = eval(t->children[2]);

  int i = 3;
  while(strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}

 int main() {
  // Number
  // operator
  // expr 
  // lispy
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

 mpca_lang(MPCA_LANG_DEFAULT,
    " \
      number: /-?[0-9]+(\\.[0-9]+)?/ ; \
      operator: '+' | '-' | '*' | '/' | '%' ; \
      expr: <number> | '(' <operator> <expr>+ ')' ; \
      lispy: /^/ <operator> <expr>+ /$/ ; \
    ",
    Number, Operator, Expr, Lispy);


  printf("Lispy 0.0.1\n");
  printf("Press CTRL-c to quit from RESPL\n");

  while(1) {
    char* input = readline("lispy > ");
    add_history(input);

    mpc_result_t r;

    if(mpc_parse("<stdin>", input, Lispy, &r)) {
      long result = eval(r.output);

      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }


  return 0;
 }

























































// int number_of_nodes(mpc_ast_t* t) {
//   if (t->children_num == 0) {
//     return 1;
//   }

//   if (t->children_num >= 1) {
//     int total = 1;
//     for (int i = 0; i < t->children_num; i++) {
//       total = total + number_of_nodes(t->children[i]);
//     }
//     return total;
//   }
//   return 0;
// }

// long eval_op(long x, char* op, long y) {
//   if (strcmp(op, "+") == 0) { return x + y; }
//   if (strcmp(op, "-") == 0) { return x - y; }
//   if (strcmp(op, "*") == 0) { return x * y; }
//   if (strcmp(op, "/") == 0) { return x / y; }
//   return 0;
// }

// long eval(mpc_ast_t* t) {
//   if(strstr(t->tag, "number")) {
//     return atoi(t->contents);
//   }

//   char* op = t->children[1]->contents;

//   long x = eval(t->children[2]);

//   int i = 3;

//   while(strstr(t->children[i]->tag, "expr")) {
//     x = eval_op(x, op, eval(t->children[i]));
//     i++;
//   }

//   return x;
// }

// int main() {
//   /* Create Some Parsers */
//   mpc_parser_t* Number = mpc_new("number");
//   mpc_parser_t* Operator = mpc_new("operator");
//   mpc_parser_t* Expr = mpc_new("expr");
//   mpc_parser_t* Lispy = mpc_new("lispy");

//   mpca_lang(MPCA_LANG_DEFAULT,
//     " \
//       number: /-?[0-9]+(\\.[0-9]+)?/ ; \
//       operator: '+' | '-' | '*' | '/' | '%' ; \
//       expr: <number> | '(' <operator> <expr>+ ')' ; \
//       lispy: /^/ <operator> <expr>+ /$/ ; \
//     ",
//     Number, Operator, Expr, Lispy);

//   puts("Lispy version 0.0.0.0.1");
//   puts("Press CTLR-c to Exit\n");


//   while(1) {
//     char* input = readline("lispy> ");

//     add_history(input);

//     /// Parse user input
//     mpc_result_t r;
//     if (mpc_parse("<stdin>", input, Lispy, &r)) {
//       long result = eval(r.output);

//       printf("%li\n", result);

//       //mpc_ast_print(r.output);
//       //mpc_ast_delete(r.output);

//       mpc_ast_delete(r.output);
//     } else {
//       /// If parsing failed print error
//       mpc_err_print(r.error);
//       mpc_err_delete(r.error);
//     }

//     free(input);
//   }

//   mpc_cleanup(
//     4,
//     Number,
//     Operator,
//     Expr,
//     Lispy
//   );

//   return 0;
// }
