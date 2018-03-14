
/*
|  FILE        :   ListTool2B.h
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

#ifndef __LISTTOOL2B_H                  //  Ensures that this file will be
#define __LISTTOOL2B_H                  //    included only ONCE in each file.


//
//  ENUM:
//
enum ListType  { LIFO, FIFO, Sorted };  //  Allowed list-types.


//
//  CLASS  -  Necessary predeclarations:
//
class NumElement;
class TextElement;


//
// @CLASS
//  Base class 'Element':
//
class Element {
  private:
    char elementType;                      //  Type of element: 'B'(ase),
                                           //    'N'(umeric) or 'T'(ext).
    friend class NumElement;               //  Only these two classes can
    friend class TextElement;              //    manipulate 'elementType'.

  public:
    Element();                             //  Sets element type.
    virtual ~Element();                    //  Virtual, empty destr.
    char getType();                        //  Return element type.
    virtual int compare(Element* element); //  Dummy body.
    virtual void display();             //  Displayed only if function is NOT
};                                      //   redefined insided derived classes:


//
// @CLASS
//  Base class for all numeric sorted elements:
//
class NumElement: public Element  {
  protected:
    int number;                            //  ID-number.

  public:
    NumElement();                          //  Needs and reads the ID-number.
    NumElement(int no);                    //  Created with an ID.
    virtual int compare(Element* element); //  Compares own number
};                                         //    with element's.


//
// @CLASS
//  Base class for all text/string sorted elements:
//
class TextElement: public Element  {
  private:
    void strcpy2(char* s, const char* t);   //  Selfmade  "strcpy"

  protected:
    char* text;                             //  Pointer to ID-text/string.

  public:
    TextElement();                          //  Needs/reads the ID-name/text.
    TextElement(const char* t);             //  Created with an ID.
    ~TextElement();                         //  Deletes the text ID.
    virtual int compare(Element* element);  //  Compares own name/text
};                                          //    with element's.


//
// @CLASS
//
class List  {
  private:
    struct Node  {                          //  Internal @struct 'node'.
                                            //  Element from the program that
      Element*  listElement;                //    is stored inside THIS node.
      Node*     next;                       //  Nodes are linked together.
    };

    Node*     first;                        //  Pointer to first element/head.
    Node*     last;                         //  Pointer to tail. Only relevant
                                            //    for sorted lists.
    ListType  listType;                     //  'LIFO', 'FIFO' or 'Sorted'.
    int       elementsInList;               //  Number of elements in the list.

    Node*     findPosition(Element* element); //  Internal function. Used by
                                              //    several other functions.
  public:
    List();                                   //  Constructors.
    List(ListType li);
    ~List();                                  //  Destructor.

          // 15 functions available for the user/program (some are overloaded).
          //  For different type of lists are the following functions relevant:
                                           //  LIFO/FIFO   Num Sort   Text Sort
    bool isEmpty();                        //      X          X           X
    int noOfElements();                    //      X          X           X
    bool add(Element* element);            //      X          X           X
    Element* remove();                     //      X
    Element* remove(int no);               //                 X
    Element* remove(const char* text);     //                             X
    Element* removeNo(int no);             //                 X           X
    bool destroy();                        //      X
    bool destroy(int no);                  //                 X
    bool destroy(const char* text);        //                             X
    bool inList(int no);                   //                 X
    bool inList(const char* text);         //                             X
    bool displayElement(int no);           //      X          X
    bool displayElement(const char* text); //                             X
    void displayList();                    //      X          X           X
};


#endif
