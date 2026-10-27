#include<iostream>
#include "Person.h"
using std::cout;

Person::Person():id(""), name(""){
}

Person::Person(const string &id, const string &name): id(id), name(name){
}

Person::~Person(){
}

void Person::setId(const string &id){
    this->id = id;
}

string Person::getId() const{
    return id;
}

void Person::setName(const string &name){
    this->name = name;
}

string Person::getName() const{
    return name;
}

void Person::displayInfo() const{
    cout << "ID: " << id << " ,Name: " << name;
}
