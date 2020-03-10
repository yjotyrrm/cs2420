//Copyright 2020, Bradley Peterson, Weber State University, all rights reserved. (Feb 20202)

#include <iostream>
#include <unordered_map>
#include <forward_list>
#include <string>
#include <sstream>
#include <functional>  //For the C++11 hash
#include <chrono>      
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::stringstream;
using std::forward_list;
using std::pair;
using std::hash;


template <typename T> class HashTable;

//******************
//The Iterator class
//******************
template <typename T>
class Iterator : public std::iterator<std::forward_iterator_tag, T> {
  friend class HashTable<T>;
public:
  // TODO: Implement the following:
  //operator* (Note that this returns a pair, not a T.  The pair's first template parameter is a string, and the second template parameter is a T.
  //operator!=  You need to compare the arr pointer, the current bucket index, and the forward_list iterators
  //operator++ prefix This one is somewhat tricky.  Read the PDF.  It ends with return *this;

private:
  // TODO: Five data members are needed.  I gave you one, supply the other four

  // A pointer to the array of linked lists
  // The total number of buckets (the size of the array)
  // A past the end boolean
  // The current linked list/bucket index that this iterator is at

  // This one was a pain, so I just gave it to you.  It's a forward_list iterator.  The compiler has a hard time reading
  // the entire data type, so you have to help the compiler by telling it that it's data type name, and not some other kind of C++ code.
  typename std::forward_list< pair< string, T> >::iterator iter;
};


//****************************
//The HashTable class
//****************************

template <typename T>
class HashTable {
public:

  // TODO: Make a HashTable constructor which accepts a number of buckets.  The constructor
  // itself should create a new array, with this->arr holding the 0th index/address of the array
  // Also make sure to update buckets.

  HashTable(const unsigned int buckets) {
      arr = new forward_list< pair< string, T > >[buckets];
      this->buckets = buckets;
  }
  HashTable(HashTable<T>&& objToCopy) noexcept {
    this->buckets = objToCopy.buckets;
    this->arr = objToCopy.arr;
    objToCopy.buckets = 0;
    objToCopy.arr = nullptr;
  }
  ~HashTable() { delete[] arr; }
  HashTable(const HashTable<T>& objToMove) = delete;
  HashTable<T> operator=(const HashTable<T>& objToMove) = delete;
  HashTable<T> operator=(HashTable<T>&& objToMove) = delete;


  unsigned int getNumBuckets() { return buckets; }

  // TODO: Create the following methods
  void create(string key, const T& value);
  void create(string key, T&& value);
  // exists()
  bool exists(string key);
  // retrieve()
  T retrieve(string key);
  // operator[]()
  T operator[](string key);
  // there is no mention of whether this shoudl take an r or an L value, so I'll write it to take an L value
  void update(string key, const T& value);
  // remove()
  void remove(string key);
  // A begin() method which returns an iterator
  // An end() method which returns an iterator
private:
  unsigned int buckets{ 0 };
  forward_list< pair< string, T > >* arr{ nullptr };
};

template <typename T>
void HashTable<T>::create(string key, const T& value) {
    int index = (hash<string>{}(key)) % buckets;
    cout << "creation index " << index;
    //the actual linked list, or "bucket" we need to work with
    forward_list< pair< string, T > >* bucket = arr[index];

    //check to make sure the key isn't already in, and if it is just cout and return
    for (auto& item : bucket) {
        if (item.first == key) {
            cout << "the key " << key << " is already in the list" << endl;
            return;
        }
    }
    //push the key value page
    bucket.push_back(pair<string, T>(key, value));
}

template <typename T>
void HashTable<T>::create(string key, T&& value) {
    int index = (hash<string>{}(key)) % buckets;
    cout << "creation index " << index;
    //the actual linked list, or "bucket" we need to work with
    forward_list< pair< string, T > > bucket = arr[index];

    //check to make sure the key isn't already in, and if it is just cout and return
    for (auto& item : bucket) {
        if (item.first == key) {
            cout << "the key " << key << " is already in the list" << endl;
            return;
        }
    }

    //it says to use emplace_front, even though I push the L values to the back.  Regardless, I don't think it particularly matters how this linked list is ordered
    bucket.emplace_front(key, value);
}

template <typename T>
bool HashTable<T>::exists(string key) {
    int index = (hash<string>{}(key)) % buckets;

    //the actual linked list, or "bucket" we need to work with
    forward_list< pair< string, T > > bucket = arr[index];

    for (auto& item : bucket) {
        if (item.first == key) {
            //if we find the key, set return true
            return true;
        }
    }

    return false;
}

template <typename T>
T HashTable<T>::retrieve(string key) {
    int index = (hash<string>{}(key)) % buckets;
    cout << "retrieval index " << index;
    //the actual linked list, or "bucket" we need to work with
    forward_list< pair< string, T > > bucket = arr[index];
    
    for (auto& item : bucket) {
        cout << "gothere" << endl;
        cout << item.first << endl;
        if (item.first == key) {
            //if we find the key, return the data
            return item.second;
        }
    }
    throw 1;
}

template <typename T>
T HashTable<T>::operator[](string key) {
    return retrieve(key);
}

template <typename T>
void HashTable<T>::update(string key, const T& value) {
    int index = (hash<string>{}(key)) % buckets;

    //the actual linked list, or "bucket" we need to work with
    forward_list< pair< string, T > >* bucket = arr[index];

    for (auto& item : bucket) {
        if (item.first == key) {
            //if we find the key, overwrite
            item.second = value;
        }
    }
    cout << "the key " << key << " was not in the hastable" << endl;

}

template <typename T>
void HashTable<T>::remove(string key) {
    int index = (hash<string>{}(key)) % buckets;

    //the actual linked list, or "bucket" we need to work with
    forward_list< pair< string, T > > bucket = arr[index];

    bucket.remove_if([key](auto i) {
        //removeif iterates over the list, so i will be the data of each node
        return (i.first == key);
        });
}
//************************************************************************************
//A quick and simple class that simulates a Product object.  Do not modify
//************************************************************************************
class Product {
public:
  void setCost(int cost);
  void setName(const string&);
  string getName();
  int getCost();
  string getAllInfo();
private:
  string name;
  unsigned int cost{ 0 };
};

void Product::setCost(int cost) {
  this->cost = cost;
}
void Product::setName(const string& name) {
  this->name = name;
}
string Product::getName() {
  return name;
}
int Product::getCost() {
  return cost;
}
string Product::getAllInfo() {
  stringstream ss;
  ss << "Name: " << name << ", Cost: " << cost;
  return ss.str();
}


//This helps with testing, do not modify.
template <typename T>
string NumberToString(T Number)
{
  stringstream ss;
  ss << Number;
  return ss.str();
}

//This helps with testing, do not modify.
bool checkEmpty(string testName, string whatItIs) {

  if (whatItIs != "") {
    cout << "Passed " << testName << ", the data was " << whatItIs << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testName << " *** " << endl << "   No data was found! " << endl;
    return false;
  }
}

//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    cout << "Passed " << testName << endl;
    return true;
  }
  else if (whatItShouldBe == "") {
    cout << "****** Failed test " << testName << " ****** " << endl << "     Output was '" << whatItIs << endl << "'     Output should have been blank" << endl;
    return false;

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
    cout << "***Failed test " << testName << " *** " << endl << "  There are " << whatItIs << " bytes of memory yet to be reclaimed!" << endl;
    return false;
  }
}


//This helps with testing, do not modify.

//This helps with testing, do not modify.
void testSimpleIntHash() {

  cout << "######---  Uncomment your tests one-by-one to test ---######" << endl;
  HashTable<string> myHash(200000);

  //Test #1, add "Nuggets" into our hash with a key of 6.  Try to get it.
  myHash.create("6", "Nuggets");
  checkTest("testSimpleIntHash #1", "Nuggets", myHash.retrieve("6"));

  //Test #2, attempt to get the Nuggets using the operator[] code.
  checkTest("testSimpleIntHash #2", "Nuggets", myHash["6"]);

  //Test #3, attempt to change the value at this location:
  myHash["6"] = "Jazz";

  checkTest("testSimpleIntHash #3", "Jazz", myHash["6"]);

  //Test #4,
  //See if we can find it
  if (myHash.exists("6")) {
    checkTest("testSimpleIntHash #4", "", "");
  }
  else {
    checkTest("testSimpleIntHash #4", "This test should have found an item with key \"6\"", "This test did NOT find an item with key \"6\"");
  }

  //Test #5, see if we can find something that doesn't exist yet.
  if (myHash.exists("1234")) {
    checkTest("testSimpleIntHash #5", "This test should NOT have found an item with key \"1234\".", "This test found an item with key \"1234\"");
  }
  else {
    checkTest("testSimpleIntHash #5", "", "");
  }

  myHash.create("666", "Rockets");
  myHash.remove("666");

  if (myHash.exists("666")) {
    checkTest("testSimpleIntHash #6", "This test should NOT have found an item with key \"666\".", "This test found an item with key \"666\"");
  }
  else {
    checkTest("testSimpleIntHash #6", "", "");
  }

  //Add more into the hash
  myHash.create("13", "Lakers");
  myHash.create("25", "Bulls");
  myHash.create("101", "Pelicans");
  myHash.create("77", "Bucks");
  myHash.create("12", "Thunder");
  myHash.create("42", "Nets");
  myHash.create("97", "Timberwolves");
  myHash.create("123", "Hornets");
  myHash.create("500", "Mavericks");

  //Attempt to get them back
  checkTest("testSimpleIntHash #7", "Thunder", myHash.retrieve("12"));
  checkTest("testSimpleIntHash #8", "Bucks", myHash.retrieve("77"));
  checkTest("testSimpleIntHash #9", "Pelicans", myHash.retrieve("101"));
  checkTest("testSimpleIntHash #10", "Bulls", myHash.retrieve("25"));
  checkTest("testSimpleIntHash #11", "Lakers", myHash.retrieve("13"));
  checkTest("testSimpleIntHash #12", "Mavericks", myHash.retrieve("500"));
  checkTest("testSimpleIntHash #13", "Hornets", myHash.retrieve("123"));
  checkTest("testSimpleIntHash #14", "Timberwolves", myHash.retrieve("97"));
  checkTest("testSimpleIntHash #15", "Nets", myHash.retrieve("42"));

  // Start by preparing 200000 keys
  int key = 0;
  string* keys = new string[200000];
  stringstream out;
  cout << "Preparing to insert many items...be patient" << endl;
  for (unsigned int i = 0; i < 200000; i++) {

    //this next part just helps create some variation in generated W#s...
    if (i % 2 == 0) {
      key += 17;
    }
    else if (i % 3 == 0) {
      key += 23;
    }
    else if (i % 5 == 0) {
      key += 51;
    }
    else if (i % 7 == 0) {
      key += 13;
    }
    else {
      key += 71;
    }
    //convert an int to a string via help from the stringstream class
    out.str("");
    out << key;
    keys[i] = out.str();
  }

  cout << "Inserting 100000 items..." << endl;
  //Now add in 100000 keys and time it
  for (unsigned int i = 0; i < 100000; i++) {
    myHash.create(keys[i], "a"); //Just add a bunch of letter a's
  }

  //Test retrieving two of the items
  checkTest("testSimpleIntHash #16", "a", myHash.retrieve(keys[500]));
  checkTest("testSimpleIntHash #17", "a", myHash.retrieve(keys[999]));

  //Now time how long it takes to get 100000 items
  cout << "Verifying 100000 items...this definitely shouldn't take more than 5 seconds" << endl;
  bool missing = false;
  auto start = std::chrono::high_resolution_clock::now();
  for (unsigned int i = 0; i < 100000; i++) {
    if (!myHash.exists(keys[i])) {
      cout << "*** ERROR! Key #" << i << " was not found!" << endl;
      missing = true;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> diff = end - start;
  double benchmarkTime = diff.count() / 1000.0;
  cout << "Retrieving 100000 items took " << benchmarkTime << " milliseconds" << endl;


  //Now add in the next 100000 keys
  for (unsigned int i = 100000; i < 200000; i++) {
    myHash.create(keys[i], "a"); //Just add a bunch of letter a's
  }
  start = std::chrono::high_resolution_clock::now();
  for (unsigned int i = 100000; i < 200000; i++) {
    if (!myHash.exists(keys[i])) {
      cout << "*** ERROR! Key #" << i << " was not found!" << endl;
      missing = true;
    }
  }
  end = std::chrono::high_resolution_clock::now();
  diff = end - start;
  double benchmarkTime2 = diff.count() / 1000.0;
  cout << "Retrieving 100000 more items took " << benchmarkTime2 << " milliseconds" << endl;

  if (missing) {
    cout << "*** Failed testSimpleIntHash #18, one or more keys were not found" << endl;
  }
  else {
    cout << "Passed testSimpleIntHash #18, one or more keys were not found" << endl;
  }

  if (benchmarkTime < 5000 && benchmarkTime2 < (benchmarkTime * 2 * 1.5)) { //The 1.5 gives an extra 50% wiggle room
    cout << "Passed testSimpleIntHash #19, completed removeAllInstances in " << benchmarkTime2 << " milliseconds." << endl;

  }
  else {
    cout << "*** Failed testSimpleIntHash #19, removeAllInstances took " << benchmarkTime2 << " milliseconds." << endl;

    if (benchmarkTime > 5000) {
      cout << "*** The insertion time took too long.  It hould have been a 5000 milliseconds or less" << endl;
    }
    if (benchmarkTime2 < (benchmarkTime * 2 * 1.5)) {
      cout << "*** The two times should have been relatively similar" << endl;
    }
  }
  delete[] keys;

}


void testHashOfObjects() {

  //Create a HashTable. We want this to be a hash table with int keys, string object values,
  //And we also supply the hash function we want to use for integers..

  cout << "######---  Uncomment your tests one-by-one to test ---######" << endl;

  //HashTable<Product> myHash(2000);

  ////Test #1, add in a studentObject.  Try to retrive it.
  //Product tempProduct;
  //tempProduct.setCost(5);
  //tempProduct.setName("Silly string");
  //myHash.create("12341-51231", tempProduct);
  //checkTest("testHashOfObjects #1", "Silly string", myHash.retrieve("12341-51231").getName());

  ////Test #2, attempt to get the Product using its ID code
  //checkTest("testHashOfObjects #2", "Silly string", myHash["12341-51231"].getName());

  ////Test #3, see what happens if two Products have the same ID code.  This should overwrite the former.
  //tempProduct.setCost(18);
  //tempProduct.setName("Novelty foam hat");
  //myHash["12341-51231"] = tempProduct;
  //checkTest("testHashOfObjects #3", "Novelty foam hat", myHash["12341-51231"].getName());

  ////Test #4,
  ////See if we can find it
  //if (myHash.exists("12341-51231")) {
  //  checkTest("testHashOfObjects #4", "", "");
  //}
  //else {
  //  checkTest("testHashOfObjects #4", "This test should have found an item with key 12341-51231", "This test did NOT find an item with key 12341-51231");
  //}

  ////Test #5, see if we can find something that doesn't exist yet.
  //if (myHash.exists("56756-75675")) {
  //  checkTest("testHashOfObjects #5", "This test should NOT have found an item with key 56756-75675.", "This test found an item with key56756-75675");
  //}
  //else {
  //  checkTest("testHashOfObjects #5", "", "");
  //}

  ////Now throw in many more items.
  //int value = 0;
  //string key;
  //stringstream out;
  //for (unsigned int i = 0; i < 2000; i++) {
  //  //this next part just helps create some variation for our produce ID codes.
  //  if (i % 2 == 0) {
  //    value += 107;
  //  }
  //  else if (i % 3 == 0) {
  //    value += 83;
  //  }
  //  else if (i % 5 == 0) {
  //    value += 47;
  //  }
  //  else if (i % 7 == 0) {
  //    value += 131;
  //  }
  //  else {
  //    value += 53;
  //  }
  //  key = "12345-";
  //  out.str("");
  //  if (value < 100000)
  //    key = key + "0";
  //  if (value < 10000)
  //    key = key + "0";
  //  if (value < 1000)
  //    key = key + "0";
  //  if (value < 100)
  //    key = key + "0";
  //  if (value < 10)
  //    key = key + "0";
  //  out << value;
  //  string temp = out.str();
  //  if (temp.length() > 8) {
  //    temp = temp.substr(0, 8);
  //  }
  //  key = key + temp;
  //  //Whew, that took a while, but the W# is in key, and is ready to go

  //  //Create the student record, and load in values.
  //  tempProduct.setName("Acme Product");
  //  tempProduct.setCost(rand() % 41);

  //  //Testing the hash table "add" method
  //  myHash.create(key, tempProduct);
  //}

  ////Make sure one went in correctly.  get it.
  //checkEmpty("testHashOfObjects #6", myHash["12345-002112"].getAllInfo());


}



//This helps with testing, do not modify.
void testIteration() {

  cout << "######---  Uncomment your tests one-by-one to test ---######" << endl;

  //HashTable<int> someHash(5);
  //someHash.create("1", 1);
  //someHash.create("2", 4);
  //someHash.create("3", 9);
  //someHash.create("4", 16);
  //someHash.create("5", 25);
  //someHash.create("6", 36);
  //someHash.create("7", 49);

  ////Iterator<int> = someHash.begin();
  //forward_list<int> myList;
  //myList.push_front(1);
  //Iterator<int> iter = someHash.begin();

  //cout << "The first item.  key: " << (*iter).first << " value " << (*iter).second << endl;

  //// Now test operator!=
  //auto anotherIter = someHash.begin();

  //if (iter != anotherIter) {
  //  cout << "****** Failed testIteration #1 ****** " << endl << "   The two iteraters held the same data." << endl;
  //}
  //else {
  //  cout << "Passed testIteration #1" << endl;
  //}
  //++iter; //move it to the second item

  //if (iter != anotherIter) {
  //  cout << "Passed testIteration #2" << endl;
  //}
  //else {
  //  cout << "****** Failed testIteration #2 ****** " << endl << "     The two iteraters held different data." << endl;
  //}

  //cout << "The second item.  key: " << (*iter).first << " value " << (*iter).second << endl;

  //for (int i = 2; i < 7; i++) {
  //  ++iter;
  //}

  //// Display the last item
  //cout << "The last item.  key: " << (*iter).first << " value " << (*iter).second << endl;

  //// Go to the "past the end"
  //++iter;

  //auto endIter = someHash.end();
  //if (iter != endIter) {
  //  cout << "****** Failed testIteration #3 ****** " << endl << "   The two iteraters are the same, and != should have returned false." << endl;
  //}
  //else {
  //  cout << "Passed testIteration #3" << endl;
  //}

  //int arr[7];
  //int i = 0;
  //for (pair<string, int>& somePair : someHash) {
  //  cout << "key: " << somePair.first << " value " << somePair.second << " ";
  //  arr[i] = somePair.second;
  //  i++;
  //}
  //cout << endl;
  //std::sort(&arr[0], &arr[7]);
  //if (arr[0] == 1 && arr[1] == 4 && arr[2] == 9 && arr[3] == 16 && arr[4] == 25 && arr[5] == 36 && arr[6] == 49) {
  //  cout << "Passed testIteration #4" << endl;
  //}
  //else {
  //  cout << "****** Failed testIteration #4 ****** " << endl << "   The hashtable iteration didn't find all values." << endl;
  //}
  //cout << endl;


}

//This helps with testing, do not modify.
void testHashOfHashes() {

  cout << "######---  Uncomment your tests one-by-one to test ---######" << endl;

  //HashTable< HashTable<int> > studentAssignments(2000);
  //studentAssignments.create("Alice", HashTable<int>(1000));

  //HashTable<int> tempHash2(1000);
  //studentAssignments.create("Bob", HashTable<int>(1000));

  //HashTable<int> tempHash3(1000);
  //studentAssignments.create("Karl", HashTable<int>(1000));

  ////Give Alice some assignment scores
  //studentAssignments["Alice"].create("1", 73);
  //studentAssignments["Alice"].create("2", 65);
  //studentAssignments["Alice"].create("4", 91);
  ////Ensure it went in
  //checkTest("testHashofHashes #1", 65, studentAssignments["Alice"]["2"]);

  ////And Bob
  //studentAssignments["Bob"].create("1", 90);
  //studentAssignments["Bob"].create("3", 84);
  //studentAssignments["Bob"].create("4", 99);

  ////And Karl
  //studentAssignments["Karl"].create("1", 92);
  //studentAssignments["Karl"].create("2", 92);
  //studentAssignments["Karl"].create("3", 87);
  //studentAssignments["Karl"].create("4", 10);

  ////Now find the average of assignment 4 scores
  //int average = (studentAssignments["Alice"]["4"] + studentAssignments["Bob"]["4"] + studentAssignments["Karl"]["4"]) / 3;
  //checkTest("testHashofHashes #2", 66, average);

  //int scores = 0;
  //for (auto& studentAssignmentPair : studentAssignments) {
  //  for (auto& nameScorePair : studentAssignmentPair.second) {
  //    scores += nameScorePair.second;
  //    cout << nameScorePair.second << " ";
  //  }
  //}
  //cout << endl;
  //if (scores != 783) {
  //  cout << "Failed testHashofHashes #3!  Tried iterating and counting all the scores of all values.  Got " << scores << " instead of 783" << endl;
  //}
  //else {
  //  cout << "Passed testHashofHashes #3." << endl;
  //}
}


void pressAnyKeyToContinue() {
  cout << "Press Enter to continue...";
  cin.get();
}

int main() {

  testSimpleIntHash();
  pressAnyKeyToContinue();

  testHashOfObjects();
  pressAnyKeyToContinue();

  testIteration();
  pressAnyKeyToContinue();

  testHashOfHashes();
  pressAnyKeyToContinue();

  return 0;
}
