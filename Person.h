#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <string>
using std::string;

//base class for anyone identified by an id and a name
class Person{
    protected:
        string id;
        string name;
    public:
        Person();
        Person(const string &id, const string &name);

        //virtual makes deleting through a Person* still runs Student's destructor
        virtual ~Person();


        void setId(const string &id);
        string getId() const;
        void setName(const string &name);
        string getName() const;

        //Student class can override this with its own version
        virtual void displayInfo() const;
};

#endif // PERSON_H_INCLUDED
