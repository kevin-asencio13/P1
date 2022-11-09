#include <iostream>
#include "LinkedList.h"
using namespace std;


LinkedList :: LinkedList(){ //CONSTRUCTOR
    size = 0;
}

LinkedList :: LinkedList(int element1,int element2){ //COSNTRUCTOR
    
    size=0;
    addElement(element1,element2);
}

void LinkedList ::  addElement(int element1,int element2){ //ADD NEW ELEMENT TO THE LIST
    if(size==0){
        
        struct Node *newNode  = new Node;
        newNode->x = element1;
        newNode->y = element2;
        newNode->next = NULL;
        last =  newNode;
        current =  newNode;
        head =  newNode;
        
    }
    else{
        
        struct Node *newNode  = new Node;
        newNode->x = element1;
        newNode->y = element2;
        newNode->next = NULL;
        last->next= newNode;
        last = newNode;
    }
    size++;
}
void LinkedList :: addElementByPos(int element1 , int element2 , int index){ //ADD NEW ELEMENT TO THE LIST AT THE POSITION INDEX
    if(index==0){
            
        struct Node *newNode  = new Node;
        newNode->x = element1;
        newNode->y = element2;
        newNode->next = head;
        head = newNode;
        size++;
        }
    else if(index>=0&&index<size){
        
        int i = 0;
        struct Node *CNode = head;
        struct Node *LNode =CNode;
        
        while(i<size&&i<index){
            LNode =CNode;
            CNode = CNode->next;
            i++;
            }
            
        struct Node *newNode  = new Node;
        newNode->x = element1;
        newNode->y = element2;
        
        newNode->next = CNode;
        
        LNode->next = newNode;
            
        size++;
        }
    else 
        addElement(element1,element2);
}

void LinkedList :: removeElementByPos(int index){ //REMOVE AN ELEMENT AT THE POSITION INDEX
        if(size!=0&&index<size){
            struct Node *NewCurrent  = head;
            for(int i = 0;i<index-1;i++){
                NewCurrent = NewCurrent->next;
            }if(index==0){
                if(head->next!=NULL)
                    head=head->next;    
                else{
                head=NULL;
                last=NULL;
                current=NULL;
                }
            }
            else if(NewCurrent->next!=NULL){ 
                struct Node *Remove = NewCurrent->next;
                NewCurrent->next = Remove->next;
                last= NewCurrent;
                }
            else{
                NewCurrent->next=NULL;
                last= NewCurrent;
            }
            size--;
        }
        
}
void LinkedList :: removeElement(){ // REMOVE THE LAST ELEMENT IN THE LIST
        removeElementByPos(size-1);
}
Node LinkedList :: getNext(){ // GET THE NEXT ELEMENT OF THE LIST
    if(size>0&&current->next!=NULL){
        struct Node nextNode = *(current->next);
        current = current->next;
        return nextNode;

    }
    else return *head;
    
}
Node LinkedList ::getLast(){return *last;}  //RETURN THE LAST ELEMENT OF THE LIST
Node LinkedList :: getHead(){return *head;} // RETURN THE FIRST ELEMENT OF THE LIST
void LinkedList :: Reset(){current=head;}   // RESET THE CURRENT ITERRATOR(USED FOR GETNEXT)
Node LinkedList :: getCurrent(){return *current;} // RETURN THE CURRENT ELEMENT IN THE ITERRATOR(USED FOR GETNEXT)
int LinkedList :: getSize(){return size;}    // GET THE SIZE OF THE LIST

Node LinkedList :: updateElement(int element1, int element2, int index){ //CHANGE THE VALUES OF THE ELEMENT AT INDEX
    struct Node *NewCurrent  = head;
    if(size!=0&&index<size){
            
        for(int i = 0;i<index;i++){
            NewCurrent = NewCurrent->next;
        }
        NewCurrent->x=element1;
        NewCurrent->y=element2;
    }
    return *(NewCurrent); 
}
Node LinkedList :: getElement(int index){  // RETURN THE ELEMENT AT THE POSITION INDEX
    struct Node *NewCurrent  = head;
    if(size!=0&&index<size){
            
        for(int i = 0;i<index;i++){
            NewCurrent = NewCurrent->next;
        }
    }
    return *(NewCurrent); 
}

void LinkedList :: printElement(){ //PRINT THE ENTIRE LIST 
    struct Node *newCurrent = head;
    cout<<"Elements: "<<endl;
    for(int i=0;i<size;i++){
        cout<<i<<" [ "<< newCurrent->x <<", "<< newCurrent->y<<" ]"<<endl;
        if(newCurrent->next!=NULL)
            newCurrent = newCurrent->next;
    }
}