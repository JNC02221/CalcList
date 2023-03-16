//This is the .hpp file that I included into this .cpp file
#include "CalcList.hpp"

//These are the libraries that we included for this project
#include <sstream>
#include <iomanip>


//This is the constructor function that sets headers next to trailer and trailers previous to header
CalcList::CalcList()
{
    curr = new Node;
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;

}


//Gives the total for all the operatins that have been called 
double CalcList::total() const
{
    return curr->elem->sum;
}

//This is the code that makes the function newOperation function as it it suposed too
void CalcList::newOperation(const FUNCTIONS func, const double operand) 
{
    Node* newCurr  = new Node;

    //Checks to see if the list is empty and if so justs put it in between the header and trailer
    //and if it is not empty then adds the operation to the back of the list
    if( header->next == trailer)
    {
        header->next = newCurr;
        newCurr->prev = header;
        newCurr->elem->count = 1;
        trailer->prev = newCurr;
        newCurr->next = trailer;
    }
    else
    {
         newCurr->prev = curr;
         curr->next = newCurr;
         newCurr->elem->count = 1 + curr->elem->count;
         trailer->prev = newCurr;
         newCurr->next = trailer;
    }

    //This is the switch statement that calculates the proper operation and changes the totals
    switch(func)
    {
        case 0: 
            newCurr->elem->sum = curr->elem->sum + operand;
            newCurr->elem->oper = '+';
            break;
        case 1:
            newCurr->elem->sum = curr->elem->sum - operand;
            newCurr->elem->oper = '-';
            break;
        case 2:
            newCurr->elem->sum = curr->elem->sum * operand;
            newCurr->elem->oper = '*';
            break;
        case 3:
            //This is the if statment for the exception throw if someone tries to divide by 0 in the calculator 
            if(operand == 0)
            {
                throw operand;
            }
            newCurr->elem->sum = curr->elem->sum / operand;
            newCurr->elem->oper = '/';
            break;
    }

    //here we simply set the num variable in elem to the number that was used in the operation to find the new total and we set curr to be the node
    newCurr->elem->num = operand;
    curr = newCurr;

}

//This is the function that will allow removeLastOperation to get rid of the last operation that was done in the link list and return the total to the previous amount
void CalcList::removeLastOperation()
{
    Node* temp = new Node;
    
    //This is the if statement for the exeption throw if the list is empty and you try to remove the last operation
    if((header->next == trailer))
    {
        throw 1;
    }

    //This is just the code that takes out the last node/operation and then deletes it 
    trailer->prev = curr->prev;
    temp = curr;
    curr = curr->prev;
    curr->next = trailer;
    delete temp;

}

//Prints out all of the operations and displays them in decending order
std::string CalcList::toString(unsigned short precision) const
{
    Node* n  = new Node;
    n = curr;
    double zero = 0;
    std::stringstream list;

    //This is the while loop that we used to help store all of the operations into one string to be returned 
    while(n->prev != NULL)
    {
        if(n->prev == header)
        {
            list << std::fixed << std::setprecision(precision) << n->elem->count << ": "  <<  zero <<  n->elem->oper << n->elem->num << "=" << n->elem->sum << "\n" ;
            break;
        }
        list << std::fixed  << std::setprecision(precision) << n->elem->count << ": " <<   n->prev->elem->sum <<  n->elem->oper  << n->elem->num << "=" << n->elem->sum <<  "\n" ;
        
        n = n->prev;
    }

    std::string s = list.str();
    list.clear();
    return s;
}