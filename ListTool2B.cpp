/*
|  FILE        :   ListTool2B.CPP
|
|  AUTHOR      :   Frode Haug, NTNU
                   Some changes by Jonas Solsvik, NTNU
|
|  IMPORT      :   None
|  EXPORT      :   None
|
|  DESCRIPTION :
|          Toolkit for handling of lists (LIFO, FIFO and NUMERIC/TEXT SORTED).
|          For more details:  see "LISTTOOL.HTM" (in norwegian).
|
|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/

//
//  INCLUDE:
//
#include <iostream>                              //  cout, cin
#include <cstring>                               //  strlen, strcmp
#include "ListTool2B.h"                          //  Definition of classes.

using namespace std;


//
// CLASS Element - DEFINITION OF MEMBER-FUNCTIONS
//
//
// @Constructor
//
Element::Element()  {
  elementType = 'B';                             //  Sets element type.
}

//
// @Destructor
//
Element::~Element()  {     }                     //  Virtual. Empty body.


//
// @Function
//
char Element::getType()  {
  return  elementType;                           //  Return element type.
}


//
// @Function
//
int Element::compare(Element* element)  {        //  Virtual. Dummy body.
  element = element;  return 0;
}


//
// @Function
//  Virtual. Used only if function is NOT redefined inside derived classes:
//
void Element::display()  {
  cout << "\nLISTTOOL - WARNING:\n\t'Display()' not "
       << "implemented inside derived class.";
}


//
// CLASS NumElement - DEFINITION OF MEMBER-FUNCTIONS
//
//
// @Constructor
//
NumElement::NumElement()  {                  //  Needs and reads the ID-number.
  cout << "\nID-number:  ";  cin >> number;  cin.ignore();  elementType = 'N';
}


//
// @Constructor
//
NumElement::NumElement(int no)  {            //  Created with an ID.
  number = no;  elementType = 'N';
}


//
// @Function
//  Virtual. Compares own number with the one in @param 'element':
//
int NumElement::compare(Element* element)  {
  NumElement* numElement = (NumElement*) element;
  int diff = number - numElement->number;
  if (diff > 0)          return 1;  //  Bigger
  else if (diff == 0)    return 0;  //  Equal
  else                   return -1; //  Smaller
}


//
// CLASS TextElement - DEFINITION OF MEMBER-FUNCTIONS
//
//
// @Function
//  Selfmade  "strcpy":
//
void TextElement::strcpy2(char* s, const char* t)  {
  while (*t)  *s++ = *t++;   *s = '\0';
}


//
// @Constructor
//
TextElement::TextElement()  {                 //  Needs/reads the ID-name/text.
  char id[80];   cout << "\nID-text:  ";   cin.getline(id, 80);
  text = new char[strlen(id) + 1];
  strcpy2(text, id);    elementType = 'T';
}


//
// @Constructor
//
TextElement::TextElement(const char* t)  {    //  Created with an ID.
  text = new char[strlen(t) + 1];
  strcpy2(text, t);    elementType = 'T';
}


//
// @Destructor
//
TextElement::~TextElement()  {
  delete [] text;                             //  Deletes the text ID.
}

//
// @Function
//  Virtual. Compares own name/text with the one in @param 'element':
//
int TextElement::compare(Element* element)  {
  TextElement* textElement = (TextElement*) element;
  return  strcmp(text, textElement->text);
}



//
// CLASS List - DEFINITION OF MEMBER-FUNCTIONS
//
//
// @Function
//  Searches in a sorted list for the position for insertion of the element
//    pointed to by @parm 'element'.
//  RETURNS A POINTER TO THE NODE BEFORE THE RELEVANT POSITION.
//
List::Node* List::findPosition(Element* element)  {
  Node* current = first;           //  Starts at the head. As long as the
                                   //    inserted element is greater than the
                                   //    next one, and the tail is not reached:
  while (element->compare(current->next->listElement) > 0  &&
         current->next != last)
  current = current->next;         //  Update to next node.
  return current;                  //  Returns relevant pointer.
}


//
// @Constructor
//  List created without the type:
//
List::List()  {
  cout << "\nLISTTOOL - ERROR:\n\tYou MUST give 'LIFO', "
       << "'FIFO' or 'Sorted' when creating a 'List'.";
}


//
// @Constructor
//  Initially empty list is created:
//
List::List(ListType li)  {               //  Members are initialized:
  listType = li;   first = last = nullptr;   elementsInList = 0;
}


//
// @Destructor
//  Destructor to delete the list:
//
List::~List()  {
  Node* node;
  if (first)  {                         //  If something in the list.
    do  {
      node = first;                     //  'node' points to the node that
                                        //     soon will be deleted.
      first = first->next;              //  Updates first to the next node.
      delete node->listElement;         //  Deletes the content of the node.
      delete node;                      //  Deletes the node.
    } while (first);                    //  Proceed until all nodes are removed

    first = last = nullptr;             //  Zeroes the pointers.
  }
}


//
// @Function
//  Returns if list is empty or not:
//
bool List::isEmpty()  {
  return  (elementsInList == 0);
}


//
// @Function
//  Returns current number of elements in the list:
//
int List::noOfElements()  {
  return  elementsInList;
}


//
// @Function
//  Add @param 'element' into the list:
//
bool List::add(Element* element)  {
  Node*    newNode;                         //  Pointer to new created node.
  Node*    position;                        //  Pointer to the node BEFORE the
                                            //    position for insertion.
  char elementType;                         //  Relevant list type.
  bool added = false;                       //  Adding was successful or not.
                                            //  'element' REALLY points
  if (element)  {                           //     to something:
    switch (listType)  {
      case LIFO:
        newNode = new Node;                 //  Creates new list-node.
        newNode->listElement = element;     //  Fills with data.
        newNode->next = first;              //  Adds to the beginning.
        first = newNode;                    //  Updates "first"
        ++elementsInList;                   //  Increments the number.
        added = true;                       //  Adding was successful.
        break;

      case FIFO:
        newNode = new Node;                 //  Creates new list-node.
        newNode->listElement = element;     //  Fills with data.
        newNode->next = nullptr;            //  Initiates next-pointer.

        if (last)                           //  If list NOT empty:
          last->next = newNode;             //  Adds to the end.
        else                                //  List is empty:
          first = newNode;                  //  Adds as the first one.

        last = newNode;                     //  Updates "last".
        ++elementsInList;                   //  Increments the number.
        added = true;                       //  Adding was successful.
        break;

      case Sorted:
        elementType = element->getType();   // Gets the element type.
        if (elementType == 'N'  ||  elementType == 'T')  {     // Legal type:
          if (first == nullptr)  {          //  Empty list:
            first = new Node;               //  Creates head
            last = new Node;                //    and tail.
            first->next = last;             //  Linking them together.
            last->next = nullptr;           //  Terminating the list.
            if (elementType == 'N')  {      //  Numeric list:
              first->listElement = new NumElement(0);      //  Fill head/tail:
              last->listElement  = new NumElement(0);
            } else {                        //  Text/string list:
              first->listElement = new TextElement("");    //  Fill head/tail:
              last->listElement  = new TextElement("");
            }
          }
                           //  Element of same type as those those in the list:
          if (elementType ==  first->listElement->getType())  {
            newNode = new Node;              //  Creates new list-node.
            newNode->listElement = element;  //  Fills with data.
                                             //  Finds the position where
                                             //    'element' will be inserted:
            position = findPosition(element);
            newNode->next = position->next;  //  Inserts 'element':
            position->next = newNode;
            ++elementsInList;                //  Increments the number.
            added = true;                    //  Adding was succesful.
          } else                             //  Element of another type
                                             //    than those in the list:
            cout << "\nLISTTOOL - WARNING:\n\tTrying "
                 << "to add element of wrong type "
                 << "into a sorted list.";
        } else                               //  Illegal element type:
          cout << "\nLISTTOOL - ERROR:\n\tElements in "
               << "Sorted lists MUST be derived\n\tfrom "
               << "'NumElement' or 'TextElement'.";
        break;

      default:
        cout << "\nLISTTOOL - ERROR:\n\tThis message (1) "
             << "should never occur !";
        break;
    }
  }  else                              //  Function was called with no element:
     cout << "\nLISTTOOL - WARNING:\n\t'Add()' called with no element.";
  return added;                        //  Returning with status of adding.
}


//
// @Function
//  Returns (if possible) the FIRST element in a LIFO-/FIFO-list:
//
Element* List::remove()  {
  Element* element = nullptr;            //  Pointer to the removed element.
  Node*  removeNode;                     //  Node that will be removed.

  if (listType == LIFO  ||  listType == FIFO)  {   //  Legal list type:
    if (!isEmpty())  {                   //  Something in the list:
      element = first->listElement;      //  Gets relevant element.
      removeNode = first;                //  Pointer to soon removed node.
      first = first->next;               //  Updates the first-pointer.

      if (first == nullptr) last = nullptr;        //  The list are now empty.
        delete removeNode;               //  Deletes the first node.
        --elementsInList;                //  Decrements the number.
     }
  } else                                 //  Illegal use of the function:
    cout << "\nLISTTOOL - WARNING:\n\t'Remove()' shall "
         << "only be called for LIFO or FIFO lists.";
  return element;                        //  Returns element or nullptr.
}


//
// @Function
//  Returns (if possible) element with @param ID='no' in a numeric sorted list:
//
Element* List::remove(int no)  {
  Element* element = nullptr;            //  Pointer to the removed element.
  NumElement* numElement;                //  Temporary element with equal ID.
  Node*  removeNode;                     //  Node that will be removed.
  Node*  position;                       //  Pointer to the node BEFORE the
                                         //    possible relevant one.
  if (first)  {                          //  At least head and tail:
                                         //  Legal list type:
    if (listType == Sorted  &&  first->listElement->getType() == 'N')  {
      if (!isEmpty())  {                     //  Something in the list:
        numElement = new NumElement(no);     //  Creates temporary element with
                                             //    equal ID to the searhed one.
        position = findPosition(numElement); //  Finds the position BEFORE
                                             //  the possible node/element.
                                        // The next is the really searched one:
        if (numElement->compare(position->next->listElement) == 0)  {
          removeNode = position->next;      // Pointer to the soon removed one.
          element = removeNode->listElement;  // Gets the element.
          position->next = removeNode->next;  // Skips node from the list.
          delete removeNode;                  // Deletes the node.
          --elementsInList;               // Decrements the number in the list.
        }
        delete numElement;                // Deletes the temporary element.
      }
    } else                                    // Illegal use of the function:
      cout << "\nLISTTOOL - WARNING:\n\t'Remove(number)' shall "
           << "only be called for NUMERIC SORTED lists.";
  }
  return element;                             //  Returns element or nullptr.
}


//
// @Function
//  Returns (if possible) element with ID='t' in a text sorted list:
//
Element* List::remove(const char* text)  {
  Element* element = nullptr;            //  Pointer to the removed element.
  TextElement* textElement;              //  Temporary element with equal ID.
  Node*  removeNode;                     //  Node that will be removed.
  Node*  position;                       //  Pointer to the node BEFORE the
                                         //    possible relevant one.
  if (first)  {                          //  At least head and tail:
                                         //  Legal list type:
    if (listType == Sorted  &&  first->listElement->getType() == 'T')  {
      if (!isEmpty())  {                      //  Something in the list:
        textElement = new TextElement(text);  // Creates temporary element with
                                              //   equal ID to the searhed one.
        position = findPosition(textElement); //  Finds the position BEFORE
                                              //  the possible node/element.
                                        // The next is the really searched one:
        if (textElement->compare(position->next->listElement) == 0)  {
          removeNode = position->next;      // Pointer to the soon removed one.
          element = removeNode->listElement;  // Gets the element.
          position->next = removeNode->next;  // Skips node from the list.
          delete removeNode;                  //  Deletes the node.
          --elementsInList;             //  Decrements the number in the list.
        }
        delete textElement;             //  Deletes the temporary element.
      }
    } else                              //  Illegal use of the function:
      cout << "\nLISTTOOL - WARNING:\n\t'Remove(text)' shall "
           << "only be called for TEXT/STRING SORTED lists.";
  }
  return element;                       //  Returns element or nullptr.
}


//
// @Function
//  Returns (if possible) element no. @param - 'no' in a num/text sorted list:
//
Element* List::removeNo(int no)  {
  Element* element = nullptr;               //  Pointer to the removed element.
  Node*  removeNode;                        //  Node that will be removed.
  Node*  position;                          //  Pointer to the node BEFORE the
                                            //    possible relevant one.
  if (listType == Sorted)  {                //  Legal list type:
    if (!isEmpty())  {                      //  Something in the list:
      if (elementsInList >= no)  {          //  Number 'n' exsists:
        position = first;                   //  Start search at the head.
                                            //  Loop to the node BEFORE.
        for (int i = 1;  i < no;  i++, position = position->next)
             ;                              //  NOTE: Empty body !
        removeNode = position->next;        // Pointer to the soon removed one.
        element = removeNode->listElement;  // Gets the element.
        position->next = removeNode->next;  // Skips the node from the list.
        delete removeNode;                  //  Deletes the node.
        --elementsInList;                //  Decrements the number in the list.
      }
    }
  } else                                    //  Illegal use of the function:
    cout << "\nLISTTOOL - WARNING:\n\t'RemoveNo(n)' "
         << "shall only be called for SORTED lists.";
  return element;                           //  Returns element or nullptr.
}


//
// @Function
//  Destroys (if possible) the FIRST element in a LIFO-/FIFO-list:
//
bool List::destroy()  {
  Element* element;                       //  Pointer to the destroyed element.
  bool destroyed = false;                 //  Destroying was successful or not.

  if (listType == LIFO  ||  listType == FIFO)  {   //  Legal list type:
    if (!isEmpty())  {                             //  Something in the list:
      element = remove();                          //  Gets first element.
      delete element;                              //  Delete element.
      destroyed = true;                            //  Destroying was successful.
    }
  } else                                  //  Illegal use of function.
    cout << "\nLISTTOOL - WARNING:\n\t'Destroy()' shall "
         << "only be called for LIFO or FIFO lists.";
  return destroyed;                       //  Return with status of destroying.
}


//
// @Function
//  Destroys (if possible) the element with
//  @param ID='no' from a numeric sorted list:
//
bool List::destroy(int no)  {
  Element* element;                     //  Pointer to the destroyed element.
  bool destroyed = false;               //  Destroying was successful or not.

  if (first)  {                         //  At least head and tail:
                                        //  Legal list type:
    if (listType == Sorted  &&  first->listElement->getType() == 'N')  {
      if (!isEmpty())  {                //  Something in the list:
        element = remove(no);           //  Get (if possible) relevant element.
        if (element)  {                 //  Element found:
          delete element;               //  Delete element.
          destroyed = true;             //  Destroying was successful.
        }
      }
    } else                              //  Illegal use of function.
      cout << "\nLISTTOOL - WARNING:\n\t'Destroy(no)' shall "
           << "only be called for NUMERIC SORTED lists.";
  }
  return destroyed;                     //  Return with status of destroying.
}


//
// @Function
//  Destroys (if possible) the element with
//  ID='text' from a text/string sorted list:
//
bool List::destroy(const char* text)  {
  Element* element;                     //  Pointer to the destroyed element.
  bool destroyed = false;               //  Destroying was successful or not.

  if (first)  {                         //  At least head and tail:
                                        //  Legal list type:
    if (listType == Sorted  &&  first->listElement->getType() == 'T')  {
      if (!isEmpty())  {                //  Something in the list:
        element = remove(text);         //  Get (if possible) relevant element.
        if (element)  {                 //  Element found:
          delete element;               //  Delete element.
          destroyed = true;             //  Destroying was successful.
        }
      }
    } else                              //  Illegal use of function.
      cout << "\nLISTTOOL - WARNING:\n\t'Destroy(text)' shall "
           << "only be called for TEXT/STRING SORTED lists.";
  }
  return destroyed;                     //  Return with status of destroying.
}


//
// @Function
//  Looks for element with ID='no' in a numeric sorted list:
//
bool List::inList(int no)  {
  NumElement* numElement;          //  Temporary element with equal ID.
  Node* position;                  //  Pointer to node BEFORE the possible one.
  bool isThere = false;            //  Element found or not.

  if (first)  {                    //  At least head and tail:
                                   //  Legal list type:
    if (listType == Sorted  &&  first->listElement->getType() == 'N')  {
      if (!isEmpty())  {                     //  Something in the list:
        numElement = new NumElement(no);     //  Creates temporary element with
                                             //    equal ID to the searhed one.
        position = findPosition(numElement); //  Finds the position BEFORE
                                             //  the possible node/element.
                                        // The next is the really searched one:
        if (numElement->compare(position->next->listElement) == 0)
           isThere = true;                 //  Searching was successful.
        delete numElement;                 //  Deletes the temporary element.
      }
    } else                                 //  Illegal use of the function.
      cout << "\nLISTTOOL - WARNING:\n\t'InList(no)' shall "
            << "only be called for NUMERIC SORTED lists.";
  }
  return isThere;                          //  Return the status of the search.
}


//
// @Function
//  Looks for element with ID='text' in a text/string sorted list:
//
bool List::inList(const char* text)  {
  TextElement* textElement;        //  Temporary element with equal ID.
  Node* position;                  //  Pointer to node BEFORE the possible one.
  bool isThere = false;            //  Element found or not.

  if (first)  {                    //  At least head and tail:
                                   //  Legal list type:
    if (listType == Sorted  &&  first->listElement->getType() == 'T')  {
      if (!isEmpty())  {                     //  Something in the list:
        textElement = new TextElement(text); //  Creates temporary element with
                                             //    equal ID to the searhed one.
        position = findPosition(textElement); //  Finds the position BEFORE
                                              //  the possible node/element.
                                        // The next is the really searched one:
        if (textElement->compare(position->next->listElement) == 0)
           isThere = true;              //  Searching was successful.
        delete textElement;             //  Deletes the temporary element.
      }
    } else                              //  Illegal use of the function.
      cout << "\nLISTTOOL - WARNING:\n\t'InList(text)' shall "
           << "only be called for TEXT/STRING SORTED lists.";
  }
  return isThere;                       //  Return the status of the search.
}


//
// @Function
//  Displays element no. @param 'no' in a LIFO-or FIFO-list, OR
//  displays elementwith ID='no' in a numeric sorted list:
//
bool List::displayElement(int no)  {
  NumElement* numElement;                 //  Temporary element with equal ID.
  Node*  current;                         //  Pointer to relevant node.
  bool displayed = false;                 //  Element displayed or not.

  if (!isEmpty())  {                      //  Something in the list.
    if (listType == LIFO  ||  listType == FIFO)  {//  Case: LIFO/FIFO:
      if (elementsInList >= no)  {        //  Element no.'no' IS there:
        current = first;                  //  Start at the first node.
                                          //  Find relevant node:
        for (int i = 1;  i < no;  i++, current = current->next)
              ;                           //  NOTE:  Empty body !
        current->listElement->display();  //  Display the element.
        displayed = true;                 //  Displayment was successful.
      }                                   //  Case:  NUMERIC SORTED list:
    } else if (listType == Sorted  &&  first->listElement->getType() == 'N')  {
      numElement = new NumElement(no);    // Creates temporary element with
                                          //   equal ID to the searhed one.
      current = findPosition(numElement); // Finds the position BEFORE
                                          //   the possible node/element.
      current = current->next;            //  Update to relevant one.
                                        // The node is the really searched one:
      if (numElement->compare(current->listElement) == 0)  {
         current->listElement->display(); //  Display the element.
         displayed = true;                //  Displayment was successful.
      }
      delete numElement;                  //  Delete temporary element.
    } else                                //  Illegal use of the function:
      cout << "\nLISTTOOL - WARNING:\n\t'DisplayElement(no)' shall only "
           << "be called for\n\t LIFO-, FIFO- and NUMERIC SORTED lists.";
  }
  return displayed;                       //  Return status of the displayment.
}


//
// @Function
//  Displays element with ID='text' in a TEXT/STRING SORTED list:
//
bool List::displayElement(const char* text)  {
  TextElement* textElement;               //  Temporary element with equal ID.
  Node*  current;                         //  Pointer to relevant node.
  bool displayed = false;                 //  Element displayed or not.

  if (first)  {                           //  At least head and tail:
                                          //  Legal list type:
    if (listType == Sorted  &&  first->listElement->getType() == 'T')  {
      if (!isEmpty())  {                  //  Something in the list:
          textElement = new TextElement(text);  // Creates temporary element
                                          //  with equal ID to the searhed one.
        current = findPosition(textElement);   //  Finds the position BEFORE
                                               //  the possible node/element.
        current = current->next;               //  Update to relevant one.
                                        // The node is the really searched one:
        if (textElement->compare(current->listElement) == 0)  {
          current->listElement->display();     //  Display the element.
          displayed = true;                    //  Displayment was successful.
        }
        delete textElement;                    //  Delete temporary element.
      }
    } else                                     //  Illegal use of the function:
      cout << "\nLISTTOOL - WARNING:\n\t'DisplayElement(text)' "
           << "shall only be called for TEXT SORTED lists.";
  }
  return displayed;                       //  Return status of the displayment.
}


//
// @Function
//  Displays the WHOLE content of an arbitrary list:
//
void List::displayList()  {
  Node* current = first;                        //  Pointer to current node.

  if (!isEmpty())  {                            //  Something in the list:
    if (listType == Sorted)                     //  If sorted:
      current = current->next;                  //    skip the head.
                                                //  For all nodes/elements:
    for (int i = 1; i <= elementsInList; i++, current = current->next)
        current->listElement->display();        //  Display element.
  }                                             //  Display number of elements:
  //cout << "\n\tNumber of elements in the list:  " << elementsInList;
}
