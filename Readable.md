# Readable

---

## Purpose
To create a highly readable, high level scripting language that can be easily understood by people with zero knowledge of scripting or programming.

---

## Important syntax
- All executable lines of code end with a full stop (.)
- All function declarations, group declarations and condition checks end with a colon (:)
- White spacing is not required, but is valid

---

## Key words

These words have predefined meanings that are used by the interpreter and thus cannot be used as identifiers in a readable script.

- is
- end
- task
- group
- number
- flag
- text
- true
- false

---

## Comments
```
# This is a single-line comment
```

---

## Data types

- Number (int or float, depending on assignment)
- Flag (true or false)
- Text (string)

---

## Complex types
- Group (struct)

---

## Data structures
- List

---

## Variable declaration
- When declared outside of a group, variables are dynamically declared with the "let" and "be" key words
```
myNumb is 10.
myText is "Hello, World!".
myFlag is true.
```

---

## Variable opertions

#### Numbers
```
let myNumber be 10.

add 10 to myNumber.         # Addition
take 5 from myNumber.       # Subtraction
divide myNumber by 2.       # Division
multiply myNumber by 4.     # Multiplication
```

#### Flags
```
myFlag is true.

myFlag is false.    # Assign a value
flip myFlap.        # Flip the current value
```


---

## Group declaration
- When declared inside of a group, members must state their type
```
group myGroup:
number varOne.
flag varTwo.
text varThree.
end group.
```

---

## Equality and inequality checking
- Checking is done with if keyword
- End of exeutable code ended with "end" keyword
```
if myVar is 10:
# do code
end.

if myVar isnt 10:
# do code
end.
```

---

## Printing

- All printing is done with the print keyword.
- Arguments are concatonated and separated with a space.

```
print "Hello world!".

let age be 10.
print "Jimmy was " age " years old".
```

---

## User input

```
let name be ask user "Enter your name".
```

---

## Tasks (functions)
#### Without parameters

```
# Declaring a task
task myTask:
end task.

# Calling a task
do myTask.
```

#### With parameters
- When declaring a task with parameters the data type must be declared
```
# Declaring a task with parameters
task myTaskWithParams with number a and text b:
end task.

# calling a task with parameters
let myNumb be 10.
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

