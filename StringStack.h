
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//-----------------------------------------------------------
// Stack data node definition
//-----------------------------------------------------------
struct StackNode
{
   string ch;
   StackNode *Next;
};

//-----------------------------------------------------------
// Define the Stack class interface 
//-----------------------------------------------------------
class Stack
{
 public:
   // Constructors
   Stack();
   Stack(const Stack & stack);
   ~Stack();

   // Methods
   bool IsFull();
   bool IsEmpty();
   void Push(string ch);
   void Pop(string &ch);
   void Top(string &ch);
   int GetLength();
   void Print();

 private:
   StackNode *Head;
   int Length;
};