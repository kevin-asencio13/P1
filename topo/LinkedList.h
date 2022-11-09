struct Node
{
    int x,y;
    Node *next;
};

class LinkedList{

    private:
        Node* head, *last, *current;
        int size;
        
    public:
        LinkedList();
        LinkedList(int element1,int element2);
        void removeElement();
        void addElement(int element1,int element2);
        void addElementByPos(int element1 , int element2 , int index);
        void removeElementByPos(int index);
        void Reset();
        Node getElement(int index);
        Node updateElement(int element1 , int element2 , int index);
        Node getNext();
        Node getHead();
        Node getLast();
        Node getCurrent();
        int getSize();
        void printElement();
        
};