#include <iostream>
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>
#include <locale.h>

using namespace std;
const char *nombre_archivo ="archivos.dat";
const char *temp_archivo ="temporal.dat";
#define Eliminado -1


struct Estudiante{
	int codigo;
	char nombres[50];
	char apellidos[50];
	char direccion[50];
	int telefono;

};

void crear();
void leer();
void actualizar();
void eliminar();
void eliminarfisico();


main(){
	leer();
	crear();
	actualizar();
	eliminar();
	eliminarfisico();
	
	system("PAUSE");
}
void leer(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	if(!archivo){
		archivo = fopen(nombre_archivo,"w+b");	
	}
	Estudiante estudiante;
	int id=0;
	do {
		cout<<"______________________________"<<endl;
		cout<<id<<" | "<<estudiante.codigo<<" | "<< estudiante.nombres<<" | "<<estudiante.apellidos<<" | "<<estudiante.direccion<<" | "<<estudiante.telefono<<endl;
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		id+=1;
	}while(feof(archivo)==0);
	fclose(archivo);
}

void crear(){
	FILE* archivo = fopen(nombre_archivo,"ab");
	Estudiante estudiante;
	char continuar;
	string nombre,apellido,direccion;
	do{
		
		fflush(stdin);
		cout<<"Ingrese Codigo:";
		cin>>estudiante.codigo;
		cin.ignore();
		
		cout<<"Ingrese nombres:";
		getline(cin,nombre);
		strcpy(estudiante.nombres,nombre.c_str());
		
		cout<<"Ingrese apellidos:";
		getline(cin,apellido);
		strcpy(estudiante.apellidos,apellido.c_str());
		
		cout<<"Ingrese direccion:";
		getline(cin,direccion);
		strcpy(estudiante.direccion,direccion.c_str());		
		
		cout<<"Ingrese telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
		
		fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		
		cout<<"Desea Ingresar Otro Registro (s/n):";
		cin>>continuar;
	}while(continuar=='s');
	fclose(archivo);
	leer ();
}
void actualizar(){
	FILE* archivo = fopen(nombre_archivo,"r+b");
	Estudiante estudiante;
	char continuar;
	string nombre,apellido,direccion;
	int id=0;
	cout<<"Ingrese el ID a modificar:";
	cin>>id;
	fseek(archivo,id * sizeof(Estudiante),SEEK_SET);
	
	cout<<"Ingrese Codigo:";
	cin>>estudiante.codigo;
	cin.ignore();
		
	cout<<"Ingrese nombres:";
	getline(cin,nombre);
	strcpy(estudiante.nombres,nombre.c_str());
		
	cout<<"Ingrese apellidos:";
	getline(cin,apellido);
	strcpy(estudiante.apellidos,apellido.c_str());
	
	cout<<"Ingrese direccion:";
	getline(cin,direccion);
	strcpy(estudiante.direccion,direccion.c_str());	
		
	cout<<"Ingrese telefono:";
	cin>>estudiante.telefono;
	cin.ignore();
	
	fwrite(&estudiante,sizeof(Estudiante),1,archivo);
	fclose(archivo);
	leer();
}

void eliminar(){
	
	FILE* archivo = fopen(nombre_archivo,"r+b");
	FILE* archivo1 = fopen(temp_archivo,"w+b");
	Estudiante estudiante;
	char continuar;
	char elimina;
	string nombre,apellido;
	int id,codigo;
	char repite = 1;
	char respuesta[50];
	cout<<"Ingrese el ID a eliminar:";
	cin>>id;
	fseek(archivo,id * sizeof(Estudiante),SEEK_SET);
	
	if (archivo == NULL) {
		elimina = 0;
 
	} else {
		elimina = 0;
		fread(&estudiante, sizeof(Estudiante), 1, archivo);
		while (!feof(archivo)) {
			if (codigo == id) {
				fseek(archivo, ftell(archivo) - sizeof(id), SEEK_SET);
				codigo = Eliminado;
				fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
				elimina = 1;
				break;
			}
			fread(&estudiante, sizeof(Estudiante), 1, archivo);
		}
	}
	
	do {
	
	if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
	
	} while (repite);
	
	fclose(archivo);
	leer();	
}

void eliminarfisico(){
	
	FILE *archivo;
	FILE *archivo1;
	Estudiante estudiante;
	char elimina = 0;
	int codigo;
 
	archivo = fopen("archivos.dat", "r+b");
	archivo1 = fopen("temporal.dat", "w+b");
 
	if (archivo == NULL || archivo1 == NULL) {
		elimina = 0;
	} else {

		fread(&estudiante, sizeof(Estudiante), 1, archivo);
		while (!feof(archivo)) {
			if (codigo != Eliminado) {
				fwrite(&estudiante, sizeof(Estudiante), 1, archivo1);
			}
			fread(&estudiante, sizeof(Estudiante), 1, archivo);
		}
		fclose(archivo);
		fclose(archivo1);
 
		remove("archivos.dat");
		rename("temporal.dat", "archivos.dat");
 
		elimina = 1;
	}
	leer();	
}

