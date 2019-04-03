
#include "StringStack.h"

//-----------------------------------------------------------
// Constructor function.
//-----------------------------------------------------------

Stack::Stack() {
    Head = NULL;
    Length = 0;
}

//----------------------------------------------
// Constructor function.
//----------------------------------------------

Stack::Stack(const Stack & stack) {
    // Create first node
    StackNode *copy = new StackNode();
    Head = copy;

    // Walk list to copy nodes
    StackNode *ptr = stack.Head;
    while (ptr != NULL) {
        copy->Next = new StackNode();
        copy = copy->Next;
        copy->ch = ptr->ch;
        copy->Next = NULL;
        ptr = ptr->Next;
    }

    // Tidy first node
    copy = Head;
    Head = copy->Next;
    delete copy;
}

//-----------------------------------------------------------
// Destructor function.
//-----------------------------------------------------------

Stack::~Stack() {
    // Walk stack deleting data
    while (Head != NULL) {
        StackNode *Temp = Head;
        Head = Head->Next;
        delete Temp;
    }

    // Reset head
    Head = NULL;
    Length = 0;
}

//-----------------------------------------------------------
// Check to see if stack is full.
//-----------------------------------------------------------

bool Stack::IsFull() {
    return (false);
}

//-----------------------------------------------------------
// Check to see if stack is empty.
//-----------------------------------------------------------

bool Stack::IsEmpty() {
    return (Length == 0);
}

//-----------------------------------------------------------
// Push data into the stack.
//-----------------------------------------------------------

void Stack::Push(string ch) {
    // Check for full stack
    if (IsFull())
        return;

    // Allocate space for data
    StackNode *Temp = new StackNode;
    if (Temp == NULL)
        return;

    // Insert data at head of list
    Temp->ch = ch;
    Temp->Next = Head;
    Head = Temp;
    Length++;
}

//-----------------------------------------------------------
// Pop data from the stack.
//-----------------------------------------------------------

void Stack::Pop(string &ch) {
    // Check for empty stack
    if (IsEmpty())
        return;

    // Extract information from node
    ch = Head->ch;

    // Pop item from linked list
    StackNode *Temp = Head;
    Head = Head->Next;
    delete Temp;
    Length--;
}

//-----------------------------------------------------------
// Return data from top of stack.
//-----------------------------------------------------------

void Stack::Top(string &ch) {
    // Check for empty stack
    if (IsEmpty())
        return;

    // Return information from node
    ch = Head->ch;
}

//-----------------------------------------------------------
// Return the number of elements in stack.
//-----------------------------------------------------------

int Stack::GetLength() {
    return Length;
}

//-----------------------------------------------------------
// Print all records in the stack.
//-----------------------------------------------------------

void Stack::Print() {
    // Walk the stack printing data
    cout << "stack: ";
    StackNode *Temp = Head;
    while (Temp != NULL) {
        cout << Temp->ch << " ";
        Temp = Temp->Next;
    }
    cout << endl;
}

//-----------------------------------------------------------
// Main program.
//-----------------------------------------------------------

int main() {
    
    Stack s;
    char ch;
    string filename;

    // Prompt user for file name
    cout << "Enter file name: ";
    cin >> filename;
    
    // Open the file inputted and check if there were problems reading the file
   ifstream din;
   din.open(filename.c_str());
   if (din.fail())
      return 0;
   
   string temp = "";
   string topVal = "";
   
   // Loop until end of the file
   while(!din.eof())
   {
       temp = "";
       topVal = "";
       // Read in character
       din.get(ch);
             
       // If the character is '<'
       if(ch == '<')
       {
           // Loop to read next character if ch is not ' ' nor '>'
            while(ch != ' ' && ch != '>')
            {
                din.get(ch);
                if(ch != '>' && ch != ' ')
                    temp = temp + ch;       // Concatenate character to temp
            }
            
            // set topVal to the word at the top of the stack
            s.Top(topVal);
            cout << "tag: " << temp << endl;
            
            // Program compatible with the following 5 empty tags: 'br', 'hr', 'img', 'input', and 'meta'
                if(temp != "br" && temp != "hr" && temp != "img" && temp != "input" && temp != "meta")
                {
                    s.Push(temp);
                }
                else
                    cout << "\'"+temp+"\'" << " EMPTY TAG (NOT PUSHED)" << endl;  // If empty tag detected, don't push
            
            // Check for end tags. Temporarily pushed end tag and remove along with its pair.
            if(temp[0] == '/')
            {
               if('/' + topVal == temp)
               {
                    s.Pop(temp);
                    s.Pop(topVal);
               }
               else
               {
                   s.Pop(temp);
                   cout << "\'"+temp+"\'" + " DOESN'T MATCH (UNBALANCED): SOURCE OF ISSUE: " + "\'"+topVal+"\'" << endl;    // Error message for unbalanced tag
               }
            }
            s.Print();          // Print contents of the stack
       }
   }
   
   if(s.IsEmpty())
       cout << "Your HTML tags seem to be balanced!" << endl; // If the stack is empty
   else
       cout << "ERRORS PRESENT IN THE PROGRAM!" << endl;    // If stack is not empty
   // Close file
    din.close();

}