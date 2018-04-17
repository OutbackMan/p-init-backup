# Ryan's C Style Guide

This is a short document describing my preferred coding style for C projects. Coding style is very personal, and I don't not want to force my views onto anybody. However, this is what goes for code that is be part of projects I maintain.

> **NOTE**: 
	* This guide assumes you are using a C99 compatible C compiler.
	gcc, clang, microsoft, xcode

## Opening Remarks
	* Good programmers write consistent code that humans can understand.
	* Don't write for future needs.
	* Go against common idioms for readability.
	* A difficult to read program indicates you don't understand it enough to make it simple.
	* Try to only use constructs that adhere to sequence, iteration and selection, i.e. [structured programming](link).
	* Rid yourself of 'irritation of doubt'.

## Table of Contents
[Program Structure](#program-structure)
[Formatting](#formatting)
[Naming](#naming)
[Files](#files)
[Variables](#variables)
[Macros](#macros)
[Functions](#functions)
[If](#if)
[For-While-DoWhile](#for-while-dowhile)
[Switch](#switch)
[Struct-Union](#struct-union)
[Comments](#comments)
[Final Remarks](#final-remarks)

### Program Structure
* All `.h` files are to be located in an `include/` directory.
All `.c` files are to be located in a `src/` directory.
Sub-directories represent modules. Their structure should be mirrored in both `include/` and `src/`.
For example:
```bash
include/utils/misc/logger.h
src/utils/misc/logger.c
```
* Drop in or static 3rd party libraries are to be located in a `lib/` directory. They are exempt from the aforementioned rules regarding `include/` and `src/` directories.
For example:
```bash
# Cross Platform C Profiler - https://github.com/Celtoys/Remotery
lib/remotery/Remotery.h
lib/remotery/Remotery.c
```
### Formatting
* 4 spaces to indent, not tabs. 
* Lines should be wrapped at 80 characters.
* Ensure that lines have no trailing whitespace, and use unix-style (LF) line endings.
* Don't put multiple statements, assignments or side effects on one line.
* Try not to have more than 3 layers of nesting.
* Organise code in logical chunks of less than 7 lines long, separated by new lines.
* Don't use spaces between function parentheses or array brackets if enclosing a single operand.
For example:
```c
// Bad
unsigned large_factorial = factorial( 15 ); 

// Acceptable
unsigned large_factorial = factorial((10 + 3) * (1 + 7));
```
* Always use parentheses for `sizeof`.
For example:
```c
size_t int_size = sizeof(int);
size_t example_size = sizeof(struct Example);
```
* Separate function definitions and prototypes by a new line.
* Use `;` to represent an empty statement.
* Prefer prefix increment/decrement operator when it does not matter.
For example:
```c
for (int counter = 0; counter < 10; ++counter) {
	;	
}
```
### Naming
* Names should be descriptive and concise.
* Avoid hungarian notation.
* Order storage class specifier, type qualifier and then type specifier.
For example:
```c
static const int age = 15;
```
* All the symbols, types and functions that the project makes available publicly should be prefixed with `project_` (or `PROJECT_` in case of macros, structs/unions and constants).
* Non-static functions for internal use, i.e. not in public API, should be prefixed with `project__`.
* Static functions should be prefixed with current file name, e.g. `filename_`.
* For file names use lower case `hyphen-delimiters`.
* For variable and function names use lower `snake_case`.
* For structs use `PascalCase`.
* For enums, constants and public macros use upper `SNAKE_CASE`.
* For private macros, use a prefixed lower snake case `__snake_case`.
* For function-like macro parameters, use lower `snake_case` if non-macro, otherwise use upper `SNAKE_CASE`.
* For booleans, use prepositions that indicate its truthyness.
For example:
```c
// Bad
bool door_state = false;
// Acceptable
bool door_is_open = false;
```
* For opaque typedefs (hide what object is), end with `_t`. For clear typed typedefs, abbreviate name. 
For example:
```c
// Opaque
typedef uint8_t *bitfield_t;
// Clear
typedef uint16_t u16;
```
* Use more descriptive names than i, j and k for loops unless very short.
* Only use well known abbreviations. If unsure, check [Wikipedia](https://en.wikipedia.org/wiki/Lists_of_abbreviations).
### Files
* Every `.c` should have a corresponding `.h` file, except for files with only a `main()` function and unit tests.
* `.h` files should be self-contained, i.e. compile on their own.
* `.h` files that are meant for inclusion should end in `.inc` and be used sparingly.
* `.h` should contain no definitions except for `static inline` functions and macros.
* Header guards should adhere to the following format: `__path_to_file_file_name_h__`
For example:
```c
// In file "include/utils/misc/logger.h"
#ifndef __utils_misc_logger_h__
#define __utils_misc_logger_h__
#endif
``` 
* Avoid forward declarations.
* Include `const` and `restrict` modifiers in function prototypes if applicable.
* Order `#include` statements according to the following template:
```c
// In file "include/utils/misc/logger.c"

// Corresponding .h file
#include "utils/misc/logger.h"
// BLANK LINE
// Standard library
#include <stdio.h>
#include <stdlib.h>
// BLANK LINE
// Other 3rd party libraries
#include <SDL2/SDL.h> 
#include <SDL2/SDL_Image.h> 
// BLANK LINE
// Other project files
#include "utils/misc/common.h"

// NOTE: All sections should then be listed alphabetically.
```
* Order function declarations and prototypes by public/private, semantic and then alphabetical relation.
* Use utf-8 encoding.
### Variables
* Use each variable for a single purpose.
* Avoid magic numbers.
* Use `bool` for truthyness, not `int`.
* Initialise on declaration.
* Declare in narrowest scope possible. 
* Avoid globals in preference for block scoped, static storage variables.
For example:
```c
// Bad
static const char* ANSI_COLOUR_CLEAR = "\x1b[0m";
static const char* ANSI_COLOUR_RED = "\x1b[31m";

void log_message(const char msg[restrict static 1])
{
	printf("%sColoured text!%s\n", ANSI_COLOUR_RED, ANSI_COLOUR_CLEAR);
}

// Acceptable
void log_message(const char msg[restrict static 1])
{
	static const char* ANSI_COLOUR_CLEAR = "\x1b[0m";
	static const char* ANSI_COLOUR_RED = "\x1b[31m";
	
	printf("%sColoured text!%s\n", ANSI_COLOUR_RED, ANSI_COLOUR_CLEAR);
}
```
* Define pointers like `int* name`. 
* For `struct` and `union` use designated initialisers.
For example:
```c
typedef struct {
	int x;
	iny y;
} Example;

Example example = {
	.x = 10,
	.y = 20
};
```
* For arrays with `enum` indexes, use designated initialisers.
For example:
```c
enum {
	REGISTER_A,
	REGISTER_B,
	REGISTER_C,
	REGISTER_COUNT
};

uint16_t registers[REGISTER_COUNT] = {
	[REGISTER_A] = 0xffff,
	[REGISTER_B] = 0x00ff,
	[REGISTER_C] = 0xaaaa
};
```
* Use internal linkage for all code that does not need to be referenced elsewhere.
* Use `calloc()` over `malloc()`.
* Don't type-cast the result of `calloc()` and `realloc()`.
### Macros
* Use `static inline` functions over macros if feasible.
* Begin the body of function-like macros on a new line.
* Align `#define` with 0th column. 
* Ensure macro content ends with ';', i.e. don't expect the user to include it.
For example:
```c
// Bad
#define INSERT_BREAKPOINT raise(SIGABRT)
INSERT_BREAKPOINT;

// Acceptable
#define INSERT_BREAKPOINT raise(SIGABRT);
INSERT_BREAKPOINT
```
### Functions
* Write short functions
* Place brackets on individual lines.
* Perform any error-checking at the start of the function.
* If parameter names extend 80 characters, indent to start of function name (or single indent if none fit)
For example:
```c
// Lengthy parameters
int process_parameters(int long_param1, int long_param2, int long_param3, 
	int long_param1, int long_param2, int long_param3);

// Lengthy function
int this_is_a_very_very_very_very_very_long_function_name(
	int param1,
	int param2,
	int param3
);

```
* Only `static inline` functions < 3 lines.
* If a function can fail, have input output parameter and return project specific status code.
For example:
```c
int object_create(Object input_output[restrict static 1], 
	const char* name[restrict static 1]) __attribute__((warn_unused_result))
{
	static const unsigned MAX_NAME_LENGTH = 20U;

	input_output->name = calloc(MAX_NAME_LENGTH, sizeof(char));

	if (input_output->name == NULL) {
		return PROJECT_ENONMEM;	
	} else {
		return PROJECT_SUCCESS;	
	}
}
```
* Arrange parameters as input-output, input and output.
* If a parameter is to be not null, indicate with `[static 1]`
* Use named parameters for prototypes.
### If
* Explicitly compare, unless obviously a boolean value.
For example:
```c
// Bad
if (*p) {
	puts("Not null!");	
}

// Preferred
if (*p != NULL) {
	puts("Not null!");	
}

// Acceptable
if (door_is_open) {
	puts("Door is open!");	
}
```
### For-While-DoWhile
* Always use egyptian brackets, even if body is one statement.
* Ensure loops perform a single task.
* In general, use `for` when acting a known number of times and `while` for an unknown number of times.
* Empty body should be commented.
* Use `while(true)` for an infinite loop.
* Avoid `do while` loops.
### Switch
* Ensure case statements have the same indentation as the switch statement.
* If fallthrough is intended, use an empty `FALLTHROUGH_INTENDED` macro. 
For example:
```c
switch (some_val) {
case 'a':
	puts("received a");
	break;
case 'b':
	puts("received b");
	FALLTHROUGH_INTENDED
default:
	puts("default");		
}
```
* Always include `default:`, unless switching on an `enum`.
### Struct-Union
* Always typedef.
For example:
```c
typedef struct {
	int x;
	int y;
} StructName;
```
* Have constructor functions take struct as argument and return project specific status code.
### Comments
* Only comment non-obvious code. Ensure that the reader doesn't have to make guesses. Make sure that the purpose and logic are clear to a reasonably skilled professional.
* When writing comments use properly constructed sentences, including punctuation. Furthermore, don't make assumptions or make
    implications about race, gender, religion, political orientation or anything
    else that isn't relevant to the project.
* Use `//` line comments at end of declaration or statement.
For example:
```c
// Bad

// Measured in kilograms
double mass_of_earth = 6.0E+24;

// Acceptable

double mass_of_earth = 6.0E+24;	// Measured in kilograms
```
* For compound types or functions, describe purpose and example usage.
For example:
```c
/* Description of function
	- Example:
		struct ExampleStruct es = {0};

		if (example_struct_create(es, 10) != SUCCESS) {
			puts("example_struct_create was not successful");	
		}	
*/
int example_struct_create(ExampleStruct es[restrict static 1], const int param) __attribute__((warn_unused_result));
```
* Use TODO comments for short term/not ideal, yet working code.
For example:
```c
// TODO(GitUserName): If time permits, change to use sparse integer set.
```
* Start file with project comment boilerplate.
For example:
```c
/*******************************************************************************

Copyright (C) 2018, GitUserName <GitUserEmail>

path/to/file/file-name: 
	"File description"

PROJECT-NAME:
	"Project description" (i.e. repository description on GitHub)

License:
	"This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package."

*******************************************************************************/
```
### Final Remarks
In general, I try to avoid the excessive use of gcc extensions wherever the C11 standard offers a suitably safe, efficient, concise and structured alternative (in relation to [structured programming](https://en.wikipedia.org/wiki/Structured_programming) alternative.

> **NOTE**
* Many of the guidelines expressed here have been distilled into [GNU indent](link) rules inside a [wrapper script](link) I have created. This file is distributed in all of my C projects. It is intended to be used as a code linter.
For example:
```bash
# Inside of root project directory
# Give executable permissions (first time using only)
chmod +x scripts/linter
# Execute
scripts/linter
```
