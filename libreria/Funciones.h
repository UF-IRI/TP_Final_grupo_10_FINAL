#pragma once
#include "Globales.h"

#pragma region Busqueda
string Buscar_obra_social(pacientes Paciente, obra_social* OS);
consulta BuscarUltimaConsulta(ifstream& Consul, string clave);
pacientes BuscarPaciente(ifstream& file, string clave);
contacto BuscarContactoPaciente(ifstream& file, string clave);
bool CompararFechas(consulta UltimaConsulta);
tm Fecha_de_string_a_tm(string fecha);
#pragma endregion Busqueda

#pragma region Leo Archivos
void Leo_Historia_Clinica(ifstream& file, pacientes*& Hist_clinicas, int*& N);
void Leo_Archivo_Contactos(ifstream& file, contacto*& archivo_contacto, int*& N);
void Leo_Archivo_Medicos(ifstream& file, medicos*& archivo_medicos, int*& N);
#pragma endregion Leo Archivos

#pragma region  Agregar 
void agregarPacientes(pacientes*& lista, pacientes nuevo, int*& tamactual);
void agregarMedico(medicos*& lista, medicos nuevo, int*& tamactual);
void agregarContactos(contacto*& lista, contacto nuevo, int*& tamactual);
void agregarConsultas(consulta*& lista, consulta nuevo, int*& tamactual);
#pragma endregion Agregar 


#pragma region Eliminar repetidos
void Elimino_Paciente_Repetido(pacientes*& Hist_clinicas, int*& N);
void Elimino_Medico_Repetido(medicos*& datos_medicos, int*& N);
void Elimino_Contacto_Repetido(contacto*& Contactos, int*& N);
#pragma endregion Eliminar repetidos

#pragma region Copiar sin repetidos
void Copio_Hist_Clinicas_Sin_Repetidos(ofstream& file, pacientes* Hist_clinicas, int*& N);
void Copio_Medicos_Sin_Repetidos(ofstream& file, medicos* archivo_medico, int*& N);
void Copio_Contactos_Sin_Repetidos(ofstream& file, contacto* archivo_contacto, int*& N);
#pragma endregion Copiar sin repetidos

#pragma region Resize
void Resize_Medicos(int cuantos_agregar, int*& N, medicos*& datos);
void Resize_Contactos(int cuantos_agregar, int*& N, contacto*& datos);
void Resize_Consultas(int cuantos_agregar, int*& N, consulta*& consul);
void Resize_Pacientes(int cuantos_agregar, int*& N, pacientes*& pac);
#pragma endregion Resize

void RecuperarPacientes(ifstream& Archivo_Contacto, pacientes Paciente, consulta UltimaConsulta, contacto ContactoDelPaciente, string os);
void Guardar(string NombreDelArchivo, pacientes Paciente, consulta UltimaConsulta, contacto Contac, string os);
void SecretariaPacientes(pacientes Paciente, consulta UltimaConsulta, contacto Contac, string os);

void RecuperarPacientes2(pacientes Paciente, consulta UltimaConsulta, contacto ContactoDelPaciente, string os);
contacto BuscarContactoPaciente2(contacto* estructura, int N, string clave);
pacientes BuscarPaciente2(pacientes* estructura, int N, string clave);