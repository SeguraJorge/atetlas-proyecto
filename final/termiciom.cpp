#include <iostream>
#include <malloc.h>
#include <cstdlib>
using namespace std;

struct paciente{
    float vuelta =0.0;
    int ronda =0;
    float ultima =0.0;
    int val=0;
    float tiempo=0.0;
    float tiempo_total =0.0;
    float promedio=0.0;
    char nombre[30];
    paciente *sig;
    paciente *izq;
    paciente *der;
    
};

struct promedio {
    float prom;
    promedio *sig;
    paciente *apunta;
    
    char name [30];
};
promedio *cabp, *auxp, *aux2p;

paciente *cab, *aux, *aux2, *raiz;
int d,per;
float tiempo_total =0.0;





int registrar(){
   
     cout<<"REGISTRADOR DE ATLETAS"<<endl;
     cout<<"--------------------------"<<endl;

    if(cab==NULL){
         cab=(struct paciente*)malloc(sizeof(struct paciente));
         cout<<"Introduzca el documento de atleta: ";  
         cin>>cab->val;
         cout<<"Introduzca el nombre del atleta: ";
         cin>>cab->nombre;
      /*  cout<<endl;
         cout<<"REGISTRADOR DE VUELTAS"<<endl;
         cout<<"--------------------------"<<endl;
         cout<<"esciba cuantas vueltas son: ";
         cin>>d;
         for(int i = 0; i < d; i++) {
         cout << "Ingresa el tiempo de la vuelta " << i+1 << ": ";
         cin>>tiempo_vuelta;
         cab->tiempo += (tiempo_vuelta)/d; 
         }
         cab->vuelta = tiempo_vuelta;     
      */
         cab->sig = NULL;
    }
    else
        {
            aux = (struct paciente*)malloc(sizeof(struct paciente));
            cout<<"introduzca el documento del atleta: ";
            cin>>aux->val;
            cout<<"Introduzca el nombre de atleta: ";
            cin>>aux->nombre;
         /*   cout<<endl;
            cout<<"REGISTRADOR DE VUELTAS"<<endl;
            cout<<"--------------------------"<<endl;
              for(int i = 0; i < d; i++) {
              cout << "Ingresa el tiempo de la vuelta " << i+1 << ": ";
              cin>>tiempo_vuelta;
              aux->tiempo += (tiempo_vuelta)/d;
              }
              aux->vuelta = tiempo_vuelta;
           */
            aux->sig=NULL;
            aux2=cab; 
            while (aux2->sig!=NULL)
            {
                aux2 = aux2->sig;
            }
            aux2->sig =aux;
            aux2=aux=NULL;
            free(aux);
            free(aux2);                    
        }
        per++;
        cout<<endl;
    cout<<"Regitro exitoso (-_-)";
      cout<<endl;
    return 0;
    
}
int mostrarp(){

     cout<<"ATLETAS REGISTRADOS"<<endl;
     cout<<"-----------------------"<<endl;
    for(aux=cab; aux!=NULL; aux=aux->sig){
    cout<<"Documento: "<<aux->val<<endl;
    cout<<"Nombre: "<<aux->nombre<<endl;
    cout<<"ultima vuelta: "<<aux->tiempo<<endl;
    cout<<"-----------------------"<<endl;
    }
}
int mostar(){
    
     cout<<"ATLETAS REGISTRADOS"<<endl;
     cout<<"-----------------------"<<endl;
    for(aux=cab; aux!=NULL; aux=aux->sig){
    cout<<"Documento: "<<aux->val<<endl;
    cout<<"Nombre: "<<aux->nombre<<endl;
    cout<<"ultima vuelta: "<<aux->tiempo<<endl;
    cout<<"vueltas corridas: "<<aux->vuelta<<endl;
    cout<<"Promedio de vueltas: "<<aux->promedio<<endl;
    cout<<"-----------------------"<<endl;
  
    
    }
    
    cout<<"-----------------------"<<endl;
    cout<<" Numero de atletas: "<<per<<endl;
    cout<<"-----------------------"<<endl;
    return 0;
}
int posicionar (){
if(aux->promedio< aux2->promedio){
        if(aux2->izq!=NULL){
            aux2 = aux2->izq;
           posicionar ();
            
        }
        else{
             aux2->izq = aux;
        }
    }
    else if(aux->promedio > aux2->promedio){
        if(aux2->der!=NULL){
            aux2 = aux2->der;
           posicionar ();
            
        }
        else{
             aux2->der = aux;
        }

    }
    return 0;
}
 
int guardar (){
    aux->promedio =  aux->tiempo_total/aux->vuelta;
    aux = (struct paciente *) malloc (sizeof(struct paciente));
    aux->izq = aux->der = NULL;
    
    if(raiz==NULL){
        raiz = aux;
        aux = NULL;
        free(aux);
    
    }
    else {
        aux2 = raiz;
        posicionar();
    }
    return 0;
}

int preorden(paciente *recursivo){
     cout<<"Año "<<recursivo->promedio<<endl;
    if(recursivo->izq!=NULL)
        preorden(recursivo->izq);
    if(recursivo->der!=NULL)
        preorden(recursivo->der);
    return 0;
}
int recorrer(){
    aux = raiz;
    if(aux!=NULL){
        preorden(aux);
    }
  return 0;
}
int calcularpromedio(){
    float prom;
    int bandera = 0;
    aux->promedio =  aux->tiempo_total/aux->vuelta;
    if(cabp==NULL){
        cabp = (struct promedio*) malloc (sizeof(struct promedio));
        cabp->prom = aux->promedio;
        cabp->sig = NULL;
        
        cabp->apunta = aux;
    } else {
      
        aux2p = cabp;
        while(aux2p!=NULL){            
            
            if(aux2p->apunta==aux) {
                aux2p->prom = aux->promedio;
                bandera = 1;
            }
            aux2p=aux2p->sig;
        }
        if(bandera==0){
            auxp = (struct promedio*) malloc (sizeof(struct promedio));
            auxp->prom = aux->promedio;  

            auxp->apunta = aux;
            auxp->sig = cabp;
            cabp = auxp;
            auxp = NULL;
            free(auxp);
        }


    }

}

int registrarvuelta(){
    int documento;
    int bandera = 0;    
    mostrarp();
    cout<<"Ingrese el numero del corredor"<<endl;
    cin>>documento;
    aux = cab;
    while(aux!=NULL){        
        if(aux->val == documento){            
            bandera = 1; 
            aux->vuelta++;
            cout<<"Es el corredor: " <<aux->nombre<< " ("<<aux->vuelta<<") :: "<<aux->tiempo<<endl;
            cout<<endl;
            cout<<"Ingrese el tiempo de la ultima vuelta "<<endl;
            cin>>aux->tiempo;
            aux->tiempo_total = aux->tiempo_total + aux->tiempo;
            if(aux->vuelta>=2){
                
                calcularpromedio();
                guardar();
            }
        }
        aux = aux->sig;
    }
    if(bandera==0){
        cout<<"El corredor no existe"<<endl;
    }
        
}


int main(){
    raiz = (struct paciente *) malloc (sizeof(struct paciente));
    raiz->izq = raiz->der = NULL;
    
    int opc=0;
     
    do{
        cout<<" BIENVENIDO AL MENU "<<endl;
        cout<<"----------------------"<<endl;
        cout<<" (1) registrar atletas"<<endl;
        cout<<" (2) ver atletas"<<endl;
        cout<<" (3) vueltas "<<endl;
        cout<<" (4) orden "<<endl;
        cout<<" (5) salir"<<endl;
        cout<<"--> ";
        cin>>opc;
        switch(opc){
            case 1: registrar();
            break;
            case 2: mostar();
            break;
            case 3: registrarvuelta();
            break;
            case 4: recorrer();
            break;
            case 5:
                   cout<<"SU SECION A ACABADO";
                   break;
            
            default:
            cout<<"opcion no validad";
            break;       
        }
        
    }while(opc != 5);
    {   
      
    }

    {
    
    }

    return 0;
}
