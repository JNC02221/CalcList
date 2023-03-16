//This is the .hpp file that we included into this .hpp file
#include "CalcListInterface.hpp"

//This is the libraries that we included into this code
#include<iostream>

//This is the class for the variables that must be stored in the list 
class Elem
{
    public:
        double sum = 0.0; //Total at this node 
        int count;        //Number in the operation chain
        double num;       //Number used in the operation for the new total
        char oper;        //The symbol attatched to the operation used for the new total 
};

//This is the class for the node that will be the building blocks for the list
class Node
{ 
    private:
        Elem* elem = new Elem;
        Node* prev;
        Node* next;
        friend class CalcList;

};

//This is the class that we set so that is can be used to acces all of the functions and variables that are stored in the list
class CalcList : public CalcListInterface
{
    public:
        CalcList();  //constructor
        virtual double total() const;
        virtual void newOperation(const FUNCTIONS func, const double operand);
        virtual void removeLastOperation();
        virtual std::string toString(unsigned short precision) const;
        
    private:
        Node* header;
        Node* trailer;
        Node* curr;    //This is the current node that will be pointed at   
};



