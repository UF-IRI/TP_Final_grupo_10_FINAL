#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>


#define Archivados "Archivados.csv" // va a ser un nuevo archivo, en el cual guardamos los pacientes que no retornaran
#define HistoriasClinicas ".../data_files/input/IRI_Pacientes.csv" // todos los que alguna vez se atendieron en el sanatorio
#define Contacto ".../data_files/input/IRI_Contactos.csv" // datos para ccontactar cada paciente
#define Consultas ".../data_files/input/IRI_Consultas.csv" //toda las ultimas consultas de todos los pacientes
#define Medicos  ".../data_files/input/IRI_Medicos.csv" // archivo  con todos los medicos
#define Actuales "Actuales.csv" // donde guardaremos los pacientes que se seguiran atendiendo en el hospital
using namespace std;
typedef struct
{
	string DNI;
	string nombre;
	string apellido;
	string sexo;
	tm fecha_nacimiento;
	string estado;
	string id_OS;//id de obra social, solo tiene una obra social perteneciente a su ultima consulta
}pacientes;
typedef struct contacto
{
	string DNI;
	string telefono;
	string numero_celular;
	string direccion;
	string mail;

};
typedef struct consulta
{
	string DNI;
	tm fecha_pedido;//Cuando pidieron el turno
	tm fecha_consulta;
	bool Presento;
	string id_medico;
};

typedef struct medicos
{
	string id_medico;
	string nombre;
	string apellido;
	string telefono;
	string especialidad;
	bool activo;

};
typedef struct obra_social
{
	string id_obra_social;
	string obra_social;
};