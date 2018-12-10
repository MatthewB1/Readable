# Compiler for a high-level language

---

## Purpose
The main focus of this project is the implementation of a compiler, but I need something to compiler. For this I have designed a relatively simple high-level language; in line with the ideas of literate programming, first put foward by Donald Knuth, this language will be designed with 'readability' in mind. 



---

## Important syntax
- All executable lines of code end with a semi-colon;
- White spacing is not required, but is valid

---

## Key words

These words have predefined meanings that are used by the compiler and thus cannot be used as identifiers in a readable script.

- number
- bool
- text
- true
- false
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

## User input

```
let name = ask user "Enter your name".
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
- When declaring a function with parameters the data type must be declared
```
# Declaring a function with parameters
function myTaskWithParams with number a and text b{
//function body
}

# calling a task with parameters
let myNumb = 10.
do myTask with myNumb and "Hello, world!".
```

---

## Returning

---

## Lists

#### About:

- A dynamically sized container
- Lists can a mixture of data types

#### Functionality:

- Adding an item to the list
- Removing an item from the list
- Checking if the list contains a value

#### Exceptions:

- Exception thrown when trying to remove item a list does not contain
- Exception thrown when assigning a list item to the wrong variable type 

#### Declaration

```
# Declaring a list
let myList be list.
```


#### Adding items to a list
```
add 10 to myList.
add "Hello" to myList.
myFLag is false.
add myFlag to myList.
```

#### Removing items from the list
```
remove 10 from myList.
```

#### Checking list contents
```
if myList contains 10:
end.
```

#### Accessing items in a list
```
myNumber is myList item 1.
```

---

#### Loops

##### Do loops



#### Errors:

