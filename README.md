# Compiler for a high-level language

---
This was an area of programming I had very little knowledge of at the beginning of this project. It came with a set of problems that I'd never had to encounter and learned a lot, as such this is far from good code and if I were to start from scratch I'd have done many things differently. Regardless I enjoyed building this and am proud of it.

## Purpose
The main focus of this project is the implementation of a compiler, but I need something to compiler. For this I have designed a relatively simple high-level language; in line with the ideas of literate programming, first put foward by Donald Knuth, this language will be designed with 'readability' in mind. 



---

## Important syntax
- All executable lines of code end with a semi-colon;
- White spacing is enforced with the exception of seperators eg. function \<identifier\>\(\<identifier\>\)\{\<expression\>;\}

---

## Key words

These words have predefined meanings that are used by the compiler and thus cannot be used as identifiers in a readable script.

- var
- while
- if
- return
- function
---

## Data types
variables are dynamically typed, with syntax: var \<identifier\>;
#### their type is seperated into 3 fundamental types:
```
-  number (int or float, depending on assignment)
-  bool (true or false)
-  text (string)
```
#### a variable instantiated but not given a value is undefined.
---

## Variable declaration
- When declared outside of a group, variables are dynamically declared with the "var" key word
```
var aVar;  //invalid, variables MUST be given a value
var myNumb = 10; 
var myText = "Hello, World!";
var myBool = true;
```

---

## Variable operations

#### numbers
```
var myNumber = 10;

nyNumber += 10;    # Addition
myNumber -= 5;     # Subtraction
myNumber /= 2;     # Division
myNumber *= 4;     # Multiplication
myNumber %= 3;	   # Modulus
```

---

---

## Equality and inequality checking
- Checking is done with if keyword
- Expression to be evaluated contained within parentheses
```
if (myVar == 10){
//do code
}

if (myVar == 10 && otherLogic()){
// do code
}

if (myVar != 10){
//do code
}
```

---

---

## Functions
#### Without parameters

```
# Declaring a function
function myFunction{
//function body
}

# Calling a function
myFunction();
```

#### With parameters
- variables are instantiated in the function declaration, so keyword 'var'is required
```
# Declaring a function with parameters
function myFunctionWithParams (var a, var b){
//statement
}

# calling a function with parameters
var myNumb = 10;
myFunction(myNumb,"argument!");
```

---

## Returning
- return types do not need to be declared
```
function returnSeven(){
return 7;
}
```
---

#### Loops

##### while loop
- you can do everything you need to with a while loop :~)
```
while (logical_expression) {
//statement
}
```


