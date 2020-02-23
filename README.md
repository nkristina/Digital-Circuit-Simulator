# Digital Circuit Simulator
The object-oriented program which simulates the digital circuit. Inputs are elements, their connections and specifications, and the duration of the simulation. Elements could be: And, Or, Not, Generator, Manual generator, and Sonda. Sonda collects the value of its input and that value is the output of the simulation.

 
Content:
 
 - Main.cpp - calls Test() function
 - Test.cpp - calls simulatior for test examples from specified files 
 - Simulator.h -header file with definition of class Simulator
 - Simulator.cpp - file with bodies of functions of class Simulator
 - Element.h - header file with definision and bodise of functions of class Element 
     Element is an virtual class whit types of elements as a subclasses
 - TreeNode.h - header file with definition of class TreeNode
 - TreeNode.cpp - file with bodies of functions of class TreeNode
 - Tree.h - header file with definition of class Tree
 - Tree.cpp - file with bodies of functions of class Tree
 - Time.h - header file with definition of class Time
 - Time.cpp - file with bodies of functions of class Time
 - Writer.h - header file with definition of class Writer
 - Writer.cpp - file with bodies of functions of class Writer
 - Exception.h - header file with definition of posible exceptions
 - Txt files for testing and output txt files

The simulator is the main class and it calls functions to load circuit and to simulate over time.
Element is the class that contains all Elements subclass definitions with their specifications.
TreeNode is the class with the definition for tree node which contains elements and its inputs as children.
Tree is the class that is used to go through the tree and calculate states of elements.
Time is the class which is used to collect important moment (moment in which generator output is chanced) and to collect all generators which will be changed at that moment.
Writer is the class used to write in output file all moments in which the output of sodas has changed and to what it has changed (0 to 1 or 1 to 0).
Exception is the class for exceptions.
