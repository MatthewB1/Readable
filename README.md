# Compiler for a high-level language

---

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
- flip
- function
- group
- list

---

## Comments
- Anything interpreted by the compiler as a comment will not be executed as a part of the program.
```
// This is a single-line comment

/*
this is a multi-line comment
*/
```

---

## Data types
- number (int or float, depending on assignment)
- bool (true or false)
- text (string)
---

## Complex types
- Group (operates like a c-style struct)

---

## Data structures
- List

---

## Variable declaration
- When declared outside of a group, variables are dynamically declared with the "let" and "be" key words
```
myNumb = 10;
myText = "Hello, World!";
myFlag = true;
```
- Casting is supported upon assigning from a variable
```
myNumb = 10;
toText = (text)myNumb;
```

---

## Variable opertions

#### numbers
```
let myNumber = 10;

nyNumber += 10;    # Addition
myNumber -= 5;     # Subtraction
myNumber /= 2;     # Division
myNumber *= 4;     # Multiplication
myNumber %= 3;	   # Modulus
```

#### bools
- keyword 'flip' followed by a bool variable inverts the current state of the bool
```
myFlag = true.

myFlag = false.    # Assign a value
flip myFlag.        # Flip the current value
```


---

## Group declaration
- When declared inside of a group, members must state their type
```
group myGroup{
number varOne;
flag varTwo;
text varThree;
}
```

---

## Equality and inequality checking
- Checking is done with if keyword
- Scoping logic within brackets is not required, but is valid
```
if myVar == 10{
# do code
}

if (myVar == 10 && otherLogic()){
# do code
}

if myVar != 10{
# do code
}
```

---

## Printing

- printing is done with the print keyword.
- Arguments are concatonated and separated with a space.
- it is not required to surround the print arguments with brackets, but it is valid

```
print "Hello world!".

let age = 10.
print "Jimmy was " age " years old".
```

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
```
# Declaring a function with parameters
function myFunctionWithParams a, b{
//statement
}

# calling a function with parameters
let myNumb = 10;
myFunction(myNumb,"argument!");
```

---

## Returning
- return types do not need to be declared, but if they, the value returned from a function is cast to the stated data type

function returnSeven 

---

## Lists

#### About:

- A dynamically sized container
- Lists can contain elements of different data types

#### Functionality:

- Adding an item to the list
- Removing an item from the list
- Checking if the list contains a value
- Access elements through index eg list[0];

#### Declaration

```
# Declaring an empty list
var list = [];
```


#### Adding items to the end of a list
```
list += 5;
list push 5;
```

#### Removing items from the list
```
mylist remove 7;
```

#### Checking list contents
```
if myList contains 10{
//statement
}
```

#### Accessing items in a list
```
myNumber = myList[0];
```

---

#### Loops

##### while loop

while expression {
statement
}



