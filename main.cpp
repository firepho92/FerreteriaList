/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: alex
 *
 * Created on 5 de septiembre de 2018, 10:43 PM
 */
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <chrono>
#include <ctime>
#include <sstream>
#include "Producto.h"
#include "ProductNode.h"

using namespace std;
using json = nlohmann::json;

/*
 *
 */
 /*Lists definitions*/

 float validateNumber(string prompt){
     float number;
     string str;
     while(true){
         cout << prompt;
         getline(cin, str);
         stringstream convert(str);
         if(convert >> number && !(convert >> str)) return number;
         cout << "Ingrese un número válido \n";
     }
 }

/*struct nodeP{
  Producto *producto;
  int cantidad;
  struct nodeP *next;
}*/

/*struct node{
  Producto *producto;
  struct node *next;
};*/

typedef struct ProductNode *Productos;
//typedef struct nodeP *Productos;

/*void addProduct(Productos &list, Producto *producto){
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
}*/

/*void readProducts(Productos list){
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
}*/

void updateProductos(Productos list, string str){
  bool flag= false;
  string nombre = "";
  float precioVenta = 0, precioCompra = 0;
  int cantidad = 0;
  while(list != NULL){
    if(list != NULL){
      if(list->producto->getNombre() == str){
        cout << "Ingresa nombre: \n";
        cin >> nombre;
        cin.get();
        precioVenta = validateNumber("Ingresa precio de venta:\n");
        precioCompra = validateNumber("Ingresa precio de compra: \n");
        cantidad = validateNumber("Ingresa la cantidad de unidades en stock: \n");
        list->producto->setNombre(nombre);
        list->producto->setPrecio(precioVenta);
        list->producto->setPrecioCompra(precioCompra);
        list->producto->setUnidades(cantidad);
        flag = true;
        cout << "Presione enter para continuar...";
        return;
      }
      list = list->next;
    }
  }
  if(flag == false)
    cout << "Producto no encontrado. \n";
}

void deleteProduct(Productos &list){
  Productos prev, lista;
  lista = list;
  string nombre;
  cout << "Ingresa el nombre del producto a borrar: \n";
  getline(cin, nombre);
  if(lista != NULL){
    while(lista != NULL){
      if(lista->producto->getNombre() == nombre){
        cout << lista->producto->getNombre() << endl;
        if(lista == list)
          list = list->next;
        else
          prev->next = lista->next;
        delete(lista);
        cout << "Producto removido \nPresione enter para continuar...";
        return;
      }
      prev = lista;
      lista = lista->next;
    }
  }
  else
    cout << "No hay productos en el inventario.";

    cout << "Presione enter para continuar...";
}

int getProductosSize(Productos list){
  int size = 0;
  if(list != NULL){
    while(list != NULL){
      size++;
      list = list->next;
    }
  }else{
    return 0;
  }
  return size;
}
/*functions*/
void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #endif
    #ifdef linux
        system("clear");
    #endif
}

/*Main*/

int main(int argc, char** argv) {
  Productos list = NULL;
  list->addProduct(list, new Producto("1", "Martillo", 50, 25, 100));
    //vector<Producto*> productos;
    //json carrito, ventas;
    int menuPrincipalOpcion = 0, menuInventarioOpcion = 0, menuVentasOpcion = 0;


    while(menuPrincipalOpcion != 3){
        menuInventarioOpcion = 0;
        menuVentasOpcion = 0;
        clearScreen();
        cout << "Selecciona una opción del menú: \n";
        cout << "1. Inventario \n";
        cout << "2. Ventas \n";
        cout << "3. Salir \n";
        cin >> menuPrincipalOpcion;
        if(menuPrincipalOpcion == 1){
            while(menuInventarioOpcion != 5){
                string clave = "", nombre = "", str = "", stop = "";
                float precioCompra = 0, precioVenta = 0;
                int cantidad = 0, index = 3;
                clearScreen();
                cout << "Selecciona una opción: \n";
                cout << "1. Agregar un producto.\n";
                cout << "2. Actualizar producto. \n";
                cout << "3. Ver productos. \n";
                cout << "4. Eliminar producto. \n";
                cout << "5. Volver al menu principal. \n";
                cin >> menuInventarioOpcion;
                cin.get();
                switch(menuInventarioOpcion){
                    case 1:
                        clearScreen();
                        cout << "Agregar nuevo producto:\n";
                        cout << "Ingresa nombre: \n";
                        cin >> nombre;
                        cin.get();
                        precioVenta = validateNumber("Ingresa precio de venta:\n");
                        precioCompra = validateNumber("Ingresa precio de compra: \n");
                        cantidad = validateNumber("Ingresa la cantidad de unidades en stock: \n");
                        clave = to_string(index + 1);
                        list->addProduct(list, new Producto(clave, nombre, precioVenta, precioCompra, cantidad));
                        cout << "Preiona enter para continuar...";
                        cin.get();
                        break;
                    case 2:
                        clearScreen();
                        cout << "Ingresa el nombre del producto a editar: " << endl;
                        getline(cin, nombre);
                        updateProductos(list, nombre);
                        cin.get();
                        break;
                    case 3:
                        clearScreen();
                        cout << getProductosSize(list) << endl;
                        list->readProducts(list);
                        cin.get();
                        break;
                    case 4:
                        clearScreen();
                        deleteProduct(list);
                        cin.get();
                        break;
                }
            }
        }
        if(menuPrincipalOpcion == 2){
            while(menuVentasOpcion != 6){
                auto time_now = chrono::system_clock::now();
                time_t time_now_t = chrono::system_clock::to_time_t(time_now);
                json objeto, elemento, elementos, venta;
                string clave, date = "", finalizarVenta;
                int cantidad;
                bool sellingFlag = false;
                float total = 0;
                clearScreen();
                cout << "Selecciona una opción: \n";
                cout << "1. Agregar un producto al carrito.\n";
                cout << "2. Eliminar un producto del carrito.\n";
                cout << "3. Ver carrito. \n";
                cout << "4. Finalizar venta. \n";
                cout << "5. Ver historial de ventas.\n";
                cout << "6. Regresar al menu principal.\n";
                cin >> menuVentasOpcion;
                cin.get();
                switch(menuVentasOpcion){
                    case 1:
                        clearScreen();

                        /*for(int i = 0; i < productos.size(); i++){
                            cout << "Clave: " << productos[i]->getClave() << ", Nombre: " <<productos[i]->getNombre() << ", Precio de venta: " << productos[i]->getPrecio() << ", Precio de compra: " << productos[i]->getPrecioCompra() << ", Unidades: " << productos[i]->getUnidades() << endl ;
                        }
                        cout << "Ingrese la clave del producto a comprar: \n";
                        cin >> clave;
                        cout << "Ingrese la cantidad a comprar:\n";
                        cin >> cantidad;
                        for(int i = 0; i < productos.size(); i++){
                            if(clave == productos[i]->getClave()){
                                objeto["clave"] = clave;
                                objeto["nombre"] = productos[i]->getNombre();
                                objeto["precioVenta"] = productos[i]->getPrecio();
                                objeto["cantidad"] = cantidad;
                            }
                        }
                        carrito["productos"].push_back(objeto);*/
                        cin.get();
                        break;
                    case 2:
                        /*clave = "";
                        clearScreen();
                        if(carrito.size() > 0){
                            cout << carrito["productos"] << endl;
                            cout << "Ingresa clave del producto a borrar:\n";
                            getline(cin, clave);
                            for(int i = 0; i < carrito["productos"].size(); i++){
                                if(clave == carrito["productos"][i]["clave"]){
                                    carrito["productos"].erase(i);
                                    break;
                                }
                            }
                            cout << "Producto removido \n";
                        }else{
                            cout << "Carrito de compras vacio\n";
                        }
                        cout << "Presione enter para regresar...";
                        cin.get();*/
                        break;
                    case 3:
                        clearScreen();
                        /*if(carrito["productos"].size() > 0){
                            cout << carrito["productos"] << endl << endl;
                        }else{
                            cout << "Carrito de compras vacio\n";
                        }
                        cout << "Presione enter para regresar...";
                        cin.get();*/
                        break;
                    case 4:
                        clearScreen();
                        /*date = ctime(&time_now_t);
                        cout << date << endl;
                        for(int i = 0; i < carrito["productos"].size(); i++){
                            float pV, c, sT;
                            pV = carrito["productos"][i]["precioVenta"];
                            c = carrito["productos"][i]["cantidad"];
                            sT = pV * c;
                            elemento["clave"] = carrito["productos"][i]["clave"];
                            elemento["nombre"] = carrito["productos"][i]["nombre"];
                            elemento["precioVenta"] = carrito["productos"][i]["precioVenta"];
                            elemento["cantidad"] = carrito["productos"][i]["cantidad"];
                            elemento["subtotal"] = sT;
                            elementos.push_back(elemento);
                            total += sT;
                            cout << "nombre: " << carrito["productos"][i]["nombre"] << ", precio unitario: " << carrito["productos"][i]["precioVenta"] << ", cantidad: " << carrito["productos"][i]["cantidad"] << ", subtotal: "<< sT << endl;
                        }
                        cout << endl << "Total: " << total << endl;
                        cout << "Presione S para aceptar o N para cancelar:\n";
                        getline(cin, finalizarVenta);
                        if(finalizarVenta == "s"){
                            for(int i = 0; i < elementos.size(); i++){
                                for(int j = 0; j < productos.size(); j++){
                                    if(elementos[i]["clave"] == productos[j]->getClave()){
                                        if(productos[j]->vender(elementos[i]["cantidad"])){
                                            sellingFlag = true;
                                        }else{
                                            sellingFlag = false;
                                        }
                                    }
                                }
                            }
                            if(sellingFlag){
                                venta["ticket"] = ventas.size() + 1;
                                venta["fecha"] = date;
                                venta["productos"] = elementos;
                                cout << "Venta exitosa\n";
                                ventas.push_back(venta);
                            }else{
                                cout << "No se puede finalizar la venta";
                            }
                        }else{
                            cout << "Venta cancelada\n";
                        }
                        cout << ventas << endl;
                        carrito.clear();
                        elementos.clear();
                        elemento.clear();
                        cout << "Presione enter para continuar...";*/
                        cin.get();
                        break;
                    case 5:
                        clearScreen();
                        /*cout << "Ventas:\n";
                        cout << ventas << endl;
                        cout << "Presione enter para volver...";*/
                        cin.get();
                        break;
                }
            }
        }
    }
    return 0;
}
