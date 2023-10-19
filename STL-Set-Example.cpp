// STLSetExample.cpp
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// ================================================================================
class Person
{
private:
    string ID;
    string name;


public:
    void setID(string idVal) { ID = idVal; }
    void setName(string nameVal) { name = nameVal; };


    string getID() const { return ID; }
    string getName() const { return name; }

    Person(string idVal = "na", string nameVal = "na")
    {
        setID(idVal);
        setName(nameVal);

    }

    string toString() const
    {
        stringstream sout;
        sout << this << " Person[ID: " << getID() << ", Name: " << getName()
            << "]";
        return sout.str();
    }

    bool operator< (const Person& other) const {
        return (this->getID() < other.getID());
        //return (this->getName() < other.getName());
    }
};

// ================================================================================


template <typename T> void showVector(vector<T>& v, string caption = "");
template <typename T> void showSet(set<T>& v, string caption = "");
void experiment01();
void testPersonRemoval(set<Person> people);

int main()
{
    experiment01();     //set of Person objects
}

//------------------------------------------------------
void experiment01() {
    // Play with this idea. Overload the Person's operator< using
    // a) ID  b)  name.
    // When using ID the set will have five persons, when using Name
    // the set is reduced to four (second Marge is rejected!)
    // -------------------------------------------------------------
    set<Person> people{
            Person("111", "Homer"),
            Person("222", "Marge"),
            Person("333", "Marge"),
            Person("555", "Lisa"),
            Person("444", "Bart"),
    };

    showSet(people, "Original Data Set");


    //----------------------------------------------------------------------------------
    // Try to add this person to the set - Observe that ID key 444 is already in the set
    // Caution - When the operator< uses ID to induce 'natural order' IDs similar to an
    // existing one will be rejected. If the operator< is based on the name, then
    // duplicate names will not be accepted.
    //----------------------------------------------------------------------------------
    people.insert(Person("444", "Bart"));
    cout << "SET people count is " << people.size() << endl;

    testPersonRemoval(people);  //Overve we pass set by value!


    // Algorithms & Lambda Expressions ---------------------------------------------
    // To be continued....

    //Copy the set to a vector - Sets cannot be sorted!
    vector<Person> people2(people.begin(), people.end());

    //Sort the vector using the default operator< for Person objects (ID natural-order)
    sort(people2.begin(), people2.end());  
    showVector(people2, "After sorting by default natural-order (ID)");

    //Compare person objects using ID
    auto lambda1 = [](Person p1, Person p2) {  return (p1.getID() < p2.getID()); };

    //Compare person objects using name first then id numbers
    auto lambda2 = [](Person p1, Person p2)
    {
        if (p1.getName() == p2.getName())
        {
            //return (p1.getID() < p2.getID());
            return (p2.getID() < p1.getID());   //Reversed ID order
        }
        else
        {
            return (p1.getName() < p2.getName());
        }
    };

    //Sort the vector using the lambda1 expression enforcing NAME order
    sort(people2.begin(), people2.end(), lambda1);
    showVector(people2, "After sorting by NAME (lambda1)");

    //Sort the vector using the lambda2 expression enforcing NAME then ID order
    sort(people2.begin(), people2.end(), lambda2);
    showVector(people2, "After sorting by NAME then ID (lambda2)");



}//experiment01

//----------------------------------------------------------------------
template <typename T>
void showVector(vector<T>& v, string caption) {
    cout << "\n" << caption << " Size: " << v.size() << "\n";
    auto it = v.begin();
    while (it != v.end()) {
        cout << it->toString() << endl;
        it++;
    }
}
//------------------------------------------------------------------------

// Remove a person from the set
void testPersonRemoval(set<Person> people)
{
    // Remove people whose name begins with 'M'
    vector<Person> personsToBeRemoved;
    // Identify those people whose name begins with 'M',
    // put a copy of the objects in the vector personsToBeRemoved.
    auto itr = people.begin();
    while (itr != people.end()) {
        char letter = itr->getName()[0];
        if (letter == 'M') {
            //people.erase(it);  //This SHOULD NOT be done - It corrupts the set
                                // Do not add/delete entries while traversing.
            personsToBeRemoved.push_back(*itr);
        }
        itr++;
    }

    showVector(personsToBeRemoved, "Persons to be removed from the set");
    for (Person p : personsToBeRemoved) {
        people.erase(p);
    }
    //showSet(people, "After removing all persons whose name begins with 'M'");
    showSet(people, "Set after removing all persons whose name begins with 'M'");

}
//------------------------------------------------------------------------
template <typename T>
void showSet(set<T>& s, string caption) {
    cout << "\n" << caption << " Size: " << s.size() << "\n";
    auto it = s.begin();
    while (it != s.end()) {
        cout << it->toString() << endl;
        it++;
    }
}

