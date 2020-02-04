//Copyright 2019, Bradley Peterson, Weber State University, All rights reserved.

#include <sstream>
#include <chrono>
#include <iostream>
#include <set>


using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;
using std::set;

class DestructorTester {
public:
  static unsigned int getCount() {
    return count;
  }
  static unsigned int getTotalCopyCalls() {
    return totalCopyCalls;
  }
  DestructorTester() {
    count++;
  }
  DestructorTester(const DestructorTester& obj) {
    count++;
    totalCopyCalls++;
  }
  void operator=(const DestructorTester& obj) {
    // Not a constructor, so no new object is created here.  No need to increment count.
    totalCopyCalls++;
  }
  ~DestructorTester() {
    count--;
  }
private:
  static unsigned int count;
  static unsigned int totalCopyCalls;
};
unsigned int DestructorTester::count = 0;
unsigned int DestructorTester::totalCopyCalls = 0;

//******************
//The Node class
//******************
template <typename T>
class Node {
public:
  T data{};
  Node<T>* link{ nullptr };
};

//******************
// The linked list base class
//******************
template <typename T>
class LinkedListBase {
public:
  ~LinkedListBase();
  string getStringFromList();
  T getFifthElement() const { cerr << "Error: You didn't override this base class method yet" << endl; T temp{}; return temp; }
  void insertNewFifthElement(const T& data) { cerr << "Error: You didn't override this base class method yet" << endl; }
  void deleteFifthElement() { cerr << "Error: You didn't override this base class method yet" << endl; }
  void swapFourthAndFifthElement() { cerr << "Error: You didn't override this base class method yet" << endl; }
  T getLast() const;
  void insertFirst(const T& data);
  void insertLast(const T& data);
  void deleteFirst();
  void deleteLast();

protected:

  Node<T>* first{ nullptr };
  Node<T>* last{ nullptr };
  int count{ 0 };
};

template <typename T>
LinkedListBase<T>::~LinkedListBase() {
  Node<T>* temp = first;
  while (temp) {
    first = first->link;
    delete temp;
    temp = first;
  }
}
//This method helps return a string representation of all nodes in the linked list, do not modify.
template <typename T>
string LinkedListBase<T>::getStringFromList() {
  stringstream ss;
  if (!this->first) {
    ss << "The list is empty.";
  }
  else {

    Node<T>* currentNode = this->first;
    ss << currentNode->data;
    currentNode = currentNode->link;

    while (currentNode) {
      ss << " " << currentNode->data;
      currentNode = currentNode->link;
    };
  }
  return ss.str();
}

template <typename T>
T LinkedListBase<T>::getLast() const {
  if (this->last) {
    return this->last->data;
  }
  else {
    throw 1;
  }
}
template <typename T>
void LinkedListBase<T>::insertFirst(const T& data) {

  if (!first) {
    // Scenario: The list is empty
    Node<T>* temp = new Node<T>();
    temp->data = data;
    first = temp;
    last = temp;
    count++;
  }
  else {
    // Scenario: One or more nodes
    Node<T>* temp = new Node<T>();
    temp->data = data;
    temp->link = first;
    first = temp;
    count++;
  }
}

template <typename T>
void LinkedListBase<T>::insertLast(const T& data) {
  if (!first) {
    //Scenario: The list is empty
    Node<T>* temp = new Node<T>();
    temp->data = data;
    first = temp;
    last = temp;
    count++;
  }
  else {
    Node<T>* temp = new Node<T>();
    temp->data = data;
    last->link = temp;
    last = temp;
    count++;
  }
}

template <typename T>
void LinkedListBase<T>::deleteFirst() {

  if (!first) {
    // Scenario: The list is empty
    cout << "The list was already empty" << endl;
    return;
  }
  else if (first == last) {
    // Scenario: One node list
    last = nullptr;
    delete first;
    first = nullptr;
    count--;
  }
  else {
    // Scenario: General, at least two or more nodes
    Node<T>* temp = nullptr;
    temp = first->link;
    delete first;
    first = temp;
    count--;
  }
}

template <typename T>
void LinkedListBase<T>::deleteLast() {
  if (!first) {
    // Scenario: The list is empty
    cout << "The list was already empty" << endl;
    return;
  }
  else if (first == last) {
    // Scenario: One node list
    last = nullptr;
    delete first;
    first = nullptr;
    count--;
  }
  else {
    // Scenario: General, at least two or more nodes
    Node<T>* temp = nullptr;
    temp = first;

    while (temp->link != last) {
      temp = temp->link; // This is like i++;
    }

    // temp is now at the second to last node
    delete last;
    last = temp;
    last->link = nullptr;
    count--;
  }
}


//**********************************
//Write your code below here
//**********************************

template <typename T>
class SinglyLinkedList : public LinkedListBase<T> {
public:
    void insertNewFifthElement(const T& data);
    T getFifthElement() const;
    void deleteFifthElement();
    void swapFourthAndFifthElement();
};

template<typename T>
void SinglyLinkedList<T>::insertNewFifthElement(const T& data) {

    Node<T>* ins = new Node<T>();
    ins->data = data;

    
    Node<T>* temp = nullptr;
    if (this->first) {
        temp = this->first;
    }
    else {
        //if this doesn't work, it's an empty list, so I don't need to do anything
        return;
    }

    //the flag is to make sure that temp made it to the fourth element
    bool flag = true;
    for (int i = 0; i < 3; i++) {
        if (temp->link) {
            temp = temp->link;
        }
        else {
            flag = false;
        }
        
    }
    if (flag) {
        if (temp->link) {
            ins->link = temp->link;
            temp->link = ins;
        }
        else {
            temp->link = ins;
            this->last = ins;
        }
        
    }
    

}

template<typename T>
T SinglyLinkedList<T>::getFifthElement() const{
    Node<T>* temp = nullptr;
    if (this->first) {
        temp = this->first;
    }
    else {
        //if this doesn't work, it's an empty list, so just throw an error
        throw 1;
    }

    for (int e = 0; e < 4; e++) {
        if (temp->link) {
            temp = temp->link;
        }
        else {
            throw 1;
        }
    }
    return temp->data;

}

template<typename T>
void SinglyLinkedList<T>::deleteFifthElement() {

    Node<T>* temp = nullptr;
    if (this->first) {
        temp = this->first;
    }
    else {
        //if this doesn't work, it's an empty list, so I don't need to do anything
        return;
    }

    bool flag = true;

    for (int i = 0; i < 3; i++) {
        if (temp->link) {
            temp = temp->link;
        }
        else {
            flag = false;
        }
    }
    
    //temp is now element 4, make sure that there's still a fifth element
    if (!temp->link) {
        flag = false;
    }

    //if there's at least 5 elements, so the flag hasn't been tripped
    if (flag) {
        //the element to be deleted
        Node<T>* rem = temp->link;

        // if there's a sixth element
        if (rem->link) {
            temp->link = rem->link;
            delete rem;
        }
        //if the fifth was the last element
        else {
            temp->link = nullptr;
            this->last = temp;
            delete rem;
        }
    }
}

template<typename T>
void SinglyLinkedList<T>::swapFourthAndFifthElement() {
    Node<T>* temp = nullptr;
    if (this->first) {
        temp = this->first;
    }
    else {
        //if this doesn't work, it's an empty list, so I don't need to do anything
        return;
    }

    //it's a bit odd to do a for loop that only runs twice, but for consistency's sake I'll use the same strategy to loop forward
    for (int i = 0; i < 2; i++) {
        if (temp->link) {
            temp = temp->link;
        }
        else {
            return;
        }
    }

    //temp is now element 3, make sure that there's a fifth element in the list
    if (!temp->link->link) {
        return;
    }

    //now that we've got temp to the fourth element, and ensured that a fifth element does exist, do the actual swap
    Node<T>* four = temp->link;
    Node<T>* five = four->link;

    if (this->last == five) {
        temp->link = five;
        five->link = four;
        four->link = nullptr;
        last = four;
    }
    else {
        Node<T>* six = five->link;

        //rearrange the pointers
        temp->link = five;
        five->link = four;
        four->link = six;
    }
    
    
    


}

//TODO: Define your methods here.

//**********************************
//Write your code above here
//**********************************


//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
  }
}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
    return false;
  }
}

//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "  You lost track of " << whatItIs << " bytes in memory!" << endl;
    return false;
  }
}

//This helps with testing, do not modify.
void testGetFifthElement() {
  SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->insertLast(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testGetFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test retrieving item. 
  int item = si->getFifthElement();
  checkTest("testGetFifthElement #2", 14, item);
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->insertLast(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testGetFifthElement #3", "10 11 12 13 14", si->getStringFromList());

  //Test retrieving item. 
  item = si->getFifthElement();
  checkTest("testGetFifthElement #4", 14, item);
  delete si;


  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 14; i++) {
    si->insertLast(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testGetFifthElement #5", "10 11 12 13", si->getStringFromList());

  //Try to access out of bounds.  
  string caughtError = "";
  try {
    item = si->getFifthElement();
  }
  catch (int) {
    caughtError = "caught";
  }
  checkTest("testGetFifthElement #6", "caught", caughtError);
  delete si;

  SinglyLinkedList<string>* ss = new SinglyLinkedList<string>;
  ss->insertLast("Multi Pass");
  ss->insertLast("Lelu Dallas");
  ss->insertLast("BIG BADA BOOM");
  ss->insertLast("Bruce Willis");
  ss->insertLast("Fried Chicken");
  ss->insertLast("EEEAAAAAAAeeeaaaaaEEeeAAAEEaaaaAA");
  checkTest("testGetFifthElement #7", "Fried Chicken", ss->getFifthElement());
  delete ss;

  SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
  for (int i = 0; i < 10; i++) {
    dt->insertLast(DestructorTester());
  }
  dt->getFifthElement();
  if (DestructorTester::getCount() == 10) {
    cout << "Passed testGetFifthElement #8" << endl;
  }
  else {
    cout << "***Failed test testGetFifthElement #8 *** " << endl << "   You have a memory leak. " << endl;
  }

  delete dt;
  if (DestructorTester::getCount() == 0) {
    cout << "Passed testGetFifthElement #9" << endl;
  }
  else {
    cout << "***Failed test testGetFifthElement #9 *** " << endl << "   You have a memory leak. " << endl;
  }
}

//This helps with testing, do not modify.
void testInsertNewFifthElement() {

  SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->insertLast(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testInsertNewFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test inserting an item
  si->insertNewFifthElement(97);
  checkTest("testInsertNewFifthElement #2", "10 11 12 13 97 14 15 16 17 18 19", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->insertLast(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testInsertNewFifthElement #3", "10 11 12 13 14", si->getStringFromList());

  //Test inserting an item
  si->insertNewFifthElement(97);
  checkTest("testInsertNewFifthElement #4", "10 11 12 13 97 14", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 14; i++) {
    si->insertLast(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testInsertNewFifthElement #5", "10 11 12 13", si->getStringFromList());

  //Test inserting an item
  si->insertNewFifthElement(97);
  checkTest("testInsertNewFifthElement #6", "10 11 12 13 97", si->getStringFromList());
  checkTest("testInsertNewFifthElement #7", 97, si->getLast());
  delete si;



  // Now test inserting an invalid option
  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 13; i++) {
    si->insertLast(i);
  }
  si->insertNewFifthElement(1000);
  //Test just to make sure the data didn't go in at all and didn't crash.
  checkTest("testInsertNewFifthElement #8", "10 11 12", si->getStringFromList());

  delete si;

  SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
  for (int i = 0; i < 10; i++) {
    dt->insertLast(DestructorTester());
  }
  dt->insertNewFifthElement(DestructorTester());
  if (DestructorTester::getCount() == 11) {
    cout << "Passed testInsertNewFifthElement #9" << endl;
  }
  else {
    cout << "***Failed test testInsertNewFifthElement #9 *** " << endl << "   You have a memory leak. " << endl;
  }

  delete dt;
  if (DestructorTester::getCount() == 0) {
    cout << "Passed testInsertNewFifthElement #10" << endl;
  }
  else {
    cout << "***Failed test testInsertNewFifthElement #10 *** " << endl << "   You have a memory leak. " << endl;
  }

}


//This helps with testing, do not modify.
void testDeleteFifthElement() {
  // Note from the instructor: Please do not delete the actual movie.  It's very good and shouldn't be removed.

  SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->insertLast(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testDeleteFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test deleting an item
  si->deleteFifthElement();
  checkTest("testDeleteFifthElement #2", "10 11 12 13 15 16 17 18 19", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 16; i++) {
    si->insertLast(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testDeleteFifthElement #3", "10 11 12 13 14 15", si->getStringFromList());

  //Test deleting an item
  si->deleteFifthElement();
  checkTest("testDeleteFifthElement #4", "10 11 12 13 15", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->insertLast(i);
  }
  //Test just to make sure the data went in the list. 
  checkTest("testDeleteFifthElement #5", "10 11 12 13 14", si->getStringFromList());
  checkTest("testDeleteFifthElement #6", 14, si->getLast());

  //Test deleting an item
  si->deleteFifthElement();
  checkTest("testDeleteFifthElement #7", "10 11 12 13", si->getStringFromList());
  checkTest("testDeleteFifthElement #8", 13, si->getLast());
  delete si;

  SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
  for (int i = 0; i < 10; i++) {
    dt->insertLast(DestructorTester());
  }
  dt->deleteFifthElement();
  if (DestructorTester::getCount() == 9) {
    cout << "Passed testDeleteFifthElement #9" << endl;
  }
  else {
    cout << "***Failed test testDeleteFifthElement #9 *** " << endl << "   You have a memory leak. " << endl;
  }

  delete dt;
  if (DestructorTester::getCount() == 0) {
    cout << "Passed testDeleteFifthElement #10" << endl;
  }
  else {
    cout << "***Failed test testDeleteFifthElement #10 *** " << endl << "   You have a memory leak. " << endl;
  }

}



//This helps with testing, do not modify.
void testSwapFourthAndFifthElement() {
  // Note from the instructor: Please do not delete the actual movie.  
  // It's very good and shouldn't be removed.

  SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->insertLast(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testSwapFourthAndFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test swapping an item
  si->swapFourthAndFifthElement();
  checkTest("testSwapFourthAndFifthElement #2", "10 11 12 14 13 15 16 17 18 19", si->getStringFromList());

  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->insertLast(i);
  }

  //Test just to make sure the data went in the list. 
  checkTest("testSwapFourthAndFifthElement #3", "10 11 12 13 14", si->getStringFromList());

  //Test swapping an item
  si->swapFourthAndFifthElement();
  checkTest("testSwapFourthAndFifthElement #4", "10 11 12 14 13", si->getStringFromList());
  checkTest("testSwapFourthAndFifthElement #5", 13, si->getLast());
  delete si;


  SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
  for (int i = 0; i < 10; i++) {
    dt->insertLast(DestructorTester());
  }
  unsigned int beforeTotalCopyCalls = DestructorTester::getTotalCopyCalls();
  dt->swapFourthAndFifthElement();
  unsigned int afterTotalCopyCalls = DestructorTester::getTotalCopyCalls();
  if (beforeTotalCopyCalls == afterTotalCopyCalls) {
    cout << "Passed testSwapFourthAndFifthElement #6" << endl;
  }
  else {
    cout << "***Failed test testSwapFourthAndFifthElement #6 *** " << endl << "   You didn't move the pointers around, you copied values " << (afterTotalCopyCalls - beforeTotalCopyCalls) << " times." << endl;
  }

  if (DestructorTester::getCount() == 10) {
    cout << "Passed testSwapFourthAndFifthElement #7" << endl;
  }
  else {
    cout << "***Failed test testSwapFourthAndFifthElement #7 *** " << endl << "   You have a memory leak. " << endl;
  }

  delete dt;
  if (DestructorTester::getCount() == 0) {
    cout << "Passed testSwapFourthAndFifthElement #8" << endl;
  }
  else {
    cout << "***Failed test testSwapFourthAndFifthElement #8 *** " << endl << "   You have a memory leak. " << endl;
  }

}


void pressAnyKeyToContinue() {
  cout << "Press enter to continue...";

  cin.get();

}


int main() {

  testGetFifthElement();

  testInsertNewFifthElement();

  pressAnyKeyToContinue();

  testDeleteFifthElement();

  testSwapFourthAndFifthElement();

  pressAnyKeyToContinue();

  return 0;
}