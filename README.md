# Expression Conversion and Evaluation Program

## Overview

This project is a C++ console application that performs various operations on arithmetic expressions, such as conversion between infix, postfix, and prefix notations, as well as the evaluation of these expressions. It provides a menu-driven interface for the user to interact with.

## Features

- **Infix to Postfix Conversion**
- **Infix to Prefix Conversion**
- **Postfix Evaluation**
- **Prefix Evaluation**
- **Postfix to Infix Conversion**
- **Prefix to Infix Conversion**
- **Store and Select Expressions**

## Requirements

- C++ Compiler (e.g., g++)

## Installation

1. Clone the repository or download the source code.
2. Navigate to the directory containing the source code.
3. Compile the program using a C++ compiler:
    ```sh
    g++ -o expression_converter main.cpp -lm
    ```

## Usage

Run the compiled executable:
```sh
./expression_converter
```

You will be presented with a menu that offers several options for manipulating and evaluating arithmetic expressions.

### Menu Options

1. **Enter a new expression**
   - Allows you to input a new infix expression which gets stored in the list of expressions.

2. **Select an expression**
   - Allows you to choose an existing infix expression from the stored list.

3. **Postfix Calculations**
   - Provides a submenu for postfix operations:
     1. **Convert to postfix**
     2. **Evaluate postfix expression**
     3. **Postfix to infix conversion**

4. **Prefix Calculations**
   - Provides a submenu for prefix operations:
     1. **Convert to prefix**
     2. **Evaluate prefix expression**
     3. **Prefix to infix conversion**

5. **Exit**
   - Exits the application.

## Detailed Functionality

### Expression Storage

- Expressions are stored in vectors, allowing you to manage multiple expressions and switch between them as needed.

### Conversion Operations

- **Infix to Postfix** and **Infix to Prefix** conversions are performed using stack data structures to handle operator precedence and parentheses.
  
### Evaluation Operations

- Both postfix and prefix evaluations prompt the user to enter values for the operands, then compute the result using a stack-based approach.

### Conversion Back to Infix

- Both postfix and prefix expressions can be converted back to infix notation to verify correctness or for further manipulation.

## Example Session

1. **Entering a new expression**
    ```
    Enter a new expression: (a+b)*(c+d)
    ```

2. **Selecting an expression**
    ```
    1. a+b
    2. (a+b)*(c+d)
    Select an expression: 2
    ```

3. **Postfix Calculations**
    ```
    ****** POSTFIX MENU *****
    1. Convert to postfix
    2. Evaluate postfix expression
    3. Postfix to infix conversion
    *************************
    Choose an option: 1
    Postfix expression: ab+cd+*
    ```

## Notes

- Ensure the maximum size of the stack (defined by `#define MAX 50`) is not exceeded to prevent overflow.
- The program currently supports single-character operands (a-z, 0-9) and basic arithmetic operators (+, -, *, /, ^).

## Contribution

Feel free to fork the repository and submit pull requests for any enhancements or bug fixes.

## License

This project is open-source and available under the MIT License.

---

For any questions or support, please contact the project maintainer.