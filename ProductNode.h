#ifndef PRODUCTNODE_H
#define PRODUCTNODE_H
#include "Producto.h"

using namespace std;
typedef struct ProductNode *Productos;

struct ProductNode{
  Producto * producto;
  struct ProductNode *next;

  void readProducts(Productos list){
    int i = 0;
    if(list != NULL){
      while(list != NULL){
        cout << " " << i + 1 << ") " << "Clave: " << list->producto->getClave() << ", Nombre: " << list->producto->getNombre() << ", Precio venta: $" << list->producto->getPrecio() << ", Precio compra: $" << list->producto->getPrecioCompra() << ", Cantidad en stock: " << list->producto->getUnidades() << endl;
        list = list->next;
        i++;
      }
    }else
      cout << "No hay productos en stock.";

    cout << "\n Presiona enter para continuar...";
  }

  void addProduct(Productos &list, Producto *producto){
    Productos t, q = new(struct ProductNode);
    q->producto = producto;
    q->next = NULL;

    if(list == NULL){
      list = q;
    }else{
      t = list;
      while(t->next != NULL){
        t = t->next;
      }
      t->next = q;
    }
  }
};

#endif
