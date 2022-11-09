#include <stdio.h>
#include <fstream>
#include "LinkedList.h"
#include <iostream>
#include <string.h>
using namespace std;
int vertices=0, aristas=0 ,tiempo = 0;
bool Direct = false;
LinkedList aristasList,verticesList,verticesColorPi,verticesComienzaTermina,ciclos;

void loadData(char *arg);
void ResetData();
void DFS_Visit(int u);
void DFS();
void BFS(int s);
void showDFS();
void showBFS();
void Order_Topologico();
void FindCiclos();
void PrintPath(int s, int v);
void printComponent(int u);
void ComponentConexo();

int main(int argc,char **arg){
    loadData(arg[1]);
    int opciones = 0;
    while(opciones!=4){
        ResetData();
        cout<<endl<<endl<<"1. Orden Topologico."<<endl<<"2. Detectar ciclos."<<endl<<"3. Componentes conexos."<<endl<<"4. Salir.";
        cout<<endl<<endl<<" #:";
        scanf("%d", &opciones); 
        cout<<endl;
        cout<<endl;
        switch(opciones){
            case 1:{
                Order_Topologico();
                break;
            }
            case 2:{
                FindCiclos();
                break;
            }
            case 3:{
                ComponentConexo();
                break;
            }
        }
    }
    
    return 0;
}


void loadData(char *arg){ // LOADS THE FILE INFORMATION 
    
    if(arg[strlen(arg)-6]=='D') // CHECK IF THE LIST IS DIRECTED OR NOT
        Direct = true;
    else
        Direct = false;
    ifstream infile;
    infile.open(arg);
    int x,y;
    int value;
    infile>>vertices;
    infile>>aristas;
    
    for(int i = 0 ; i < vertices;i++){
        verticesList.addElement(i,0);
        verticesColorPi.addElement(0,0);
        verticesComienzaTermina.addElement(0,0);
    }
    infile>>x;
    infile>>y;
     aristasList = LinkedList(x,y);
    for(int i = 0 ;i < aristas - 1;i++){
        infile>>x;
        infile>>y;
        aristasList.addElement(x,y);
    }
    infile.close();
}

void ResetData(){ // RESTORE ALL THE DEFAULT VALUES 
    for(int i = 0; i<vertices;i++){
        verticesList.updateElement(i,0,i);
        verticesColorPi.updateElement(0,0,i);
        verticesComienzaTermina.updateElement(0,0,i);
    }
    ciclos = LinkedList();
}

void DFS_Visit(int u){
    tiempo = tiempo + 1 ;
    
    verticesColorPi.updateElement(1,verticesColorPi.getElement(u).y,u); // UPDATE THE COLOR TO 1 = GRAY
    verticesComienzaTermina.updateElement(tiempo,verticesComienzaTermina.getElement(u).y,u); // UPDATE THE START TIME
    for(int i = 0 ;i <aristas;i++){
        if(aristasList.getElement(i).x == u){
            int v = aristasList.getElement(i).y;
            int  color = verticesColorPi.getElement(v).x;
            if(color==0){                                                           //  0 = WHITE
                verticesColorPi.updateElement(verticesColorPi.getElement(i).x,u,v); // UPDATE THE  PI OF THE VERTICE
                DFS_Visit(v);
            }
            else if(color == 1) //1 = GRAY  IF THE COLOR IS GRAY THAT MEANS IS A CICLES SINCE THE VERTICE IS NOT NEW AND HASN'T ENDED YET
                ciclos.addElement(aristasList.getElement(i).x ,v); // SAVES THE CICLES FOR LATER USE 
            
        }
    }
    verticesColorPi.updateElement(2,verticesColorPi.getElement(u).y,u); // MARK THE VERTICE AS ENDED 2 = BLACK
    
    tiempo=tiempo + 1 ;
    verticesComienzaTermina.updateElement(verticesComienzaTermina.getElement(u).x,tiempo,u); //UPDATE THE ENDING TIME 
}
void DFS(){
    ResetData();
    for(int i =0;i<vertices;i++){           
        verticesColorPi.updateElement(0,-1,i); // SET ALL THE VERTICES TO COLOR WHITE = 0 AND -1= nil
    }
    tiempo = 0 ;
    for(int i = 0; i < vertices;i++){
        
            int  color = verticesColorPi.getElement(i).x;
            if(color==0){ // 0 == WHITE
                DFS_Visit(i); // DO DFS VISIT AS i AS ROOT
            }
        
        
    }
}
void BFS(int s){
    
    for(int i = 0;i<vertices;i++){         //SET ALL THE VALUES TO WHITE , NIL, INFINITE AND ENDING TIME 0
        verticesColorPi.updateElement(0,-1,i);    
        verticesComienzaTermina.updateElement(-1,0,i);
    }
    verticesColorPi.updateElement(1,-1,s);     // UPDATE THE VALUES OF THE ROOT 
    verticesComienzaTermina.updateElement(1,0,s);
    LinkedList Q =  LinkedList();
    Q.addElement(s,0); // ADD THE FIRST ELEMENT (ROOT)
    int u=0;
    while(Q.getSize()!=0){   // REPEAT UNTIL THE Q  IS EMPTY 
        u = Q.getLast().x;
        Q.removeElement(); //DEQUEUE
        for(int i = 0;i<aristas;i++){  // GOES THROUGH ALL THE ARISTAS 
            
            struct Node value =  aristasList.getElement(i);
            if(value.x == u || !Direct && value.y == u){ // SEARCH THE ADJACENT VERTICES OF U AND IF IS NOT DIRECT CONECTION SEARCH BOTH WAYS
                
                int v =0;                       // GET THE VALUE OF THE ARISTA
                if(value.y == u)
                    v= value.x;
                else
                    v= value.y;
                    
                    
                int  color = verticesColorPi.getElement(v).x;
                if(color==0){   // 0 == WHITE
                    verticesColorPi.updateElement(1,u,v); // SET COLOR TO GRAY AND PI TO u
                    verticesComienzaTermina.updateElement(verticesComienzaTermina.getElement(u).x+1,0,v); // SET BEGINING TIME TO u.d + 1 
                    
                    Q.addElement(v,0); //ENQUEUE
                }
            }
        }
        verticesColorPi.updateElement(2,verticesColorPi.getElement(u).y,u); // SET COLOR BALCK
    }
    
}

void showDFS(){
    verticesColorPi.printElement(); 
    verticesComienzaTermina.printElement();
}
void showBFS(){
    verticesColorPi.printElement(); 
    verticesComienzaTermina.printElement();
}

void Order_Topologico(){
    DFS(); //CALLS DFS TO SAVE THE RESULTS
    LinkedList Order = LinkedList();
    Order.addElement(0,verticesComienzaTermina.getElement(0).y);
   
    for(int i = 1; i < vertices ;i++){  //GOES THROUGH ALL THE VERTICES TO SORT THEM IN ACENDING ORDER
         
        int t = verticesComienzaTermina.getElement(i).y;  // GET THE ENDING TIME OF THE VERTICE
        int j = 0;
        while(j<Order.getSize()&&t>Order.getElement(j).y){  // REPEAT UNTIL THE CORRECT INDEX IS FOUND TO INSERT THE ELEMENT IN ACENDING ORDER
          j++;  
        }
        
        Order.addElementByPos(i,verticesComienzaTermina.getElement(i).y,j); //INSER THE ELEMENT AT THE FOUND INDEX
        
    }
    cout<<endl<<"[vertice, tiempo f]"<<endl;
    Order.printElement(); // PRINT ALL THE ELEMENTS IN THE CORRECT ORDER OF ENDING TIME 
}

void FindCiclos(){
    DFS(); // CALLS DFS TO SAVE THE RESULTS
    cout<<endl<<"[vertice, vertice]"<<endl;
    ciclos.printElement(); // PRINT ALL THE FOUND CICLES
}

void PrintPath(int s, int v){
    if(v==s){
        cout<< s <<" ";
    }
    else if(verticesColorPi.getElement(v).y==-1){
        cout<<" No path from "<<s<<" to "<<v<<" exist "<<endl;
    }
    else { 
        PrintPath(s,verticesColorPi.getElement(v).y);
        cout<< v<<" ";
    }
}

void printComponent(int u){
    LinkedList comp;
    comp.addElement(u,-1);
    for(int i = 0; i < vertices ; i++){      //GOES THROUGH  ALL THE ARISTAS 
        struct Node V = verticesColorPi.getElement(i);
        if(V.y!=-1){        //CHECK IF THE VERTICE IS PART OF THE COMPONENT  -1 = INFINITE TIME
            comp.addElement(i,V.y); //ADD THE VERTICE TO THE COMPONENT LIST
            verticesList.updateElement(i,1,i); // SET THE VERTICE AS DISCOVERED
            
        }
    }
    cout<<endl<<"[vertice , vertice pi ] #-1 = NIL"<<endl;
    comp.printElement(); //PRINT ALL THE ELEMENTS OF THE COMPONENT
}

void ComponentConexo(){
    int c = 0;
    
    for(int i = 0; i < vertices;i++){      // GOES THROUGH ALL THE VERTICES
        if(verticesList.getElement(i).y==0){ //CHECK IF THE VERTICE HAS BEEN DISCOVERED
            c++;
            cout<<endl<< "Component "<<c<<": "<<endl;
            
            BFS(i);                     //CALLS BFS USING i AS THE ROOT  
            printComponent(i);          // PRINTS ALL THE COMPONENTS FOUND USING BFS
        }
    }
}
