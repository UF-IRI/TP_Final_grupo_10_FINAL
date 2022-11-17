#include "iri.cpp"
#include <iostream>
#include<string>
#include "Funciones.h"


int main()
{
    int p = 0;
    int* N = &p;
    pacientes* Hist_clinica = new pacientes[*N];
    ifstream file1;
    file1.open(HistoriasClinicas, ios::in);
    Leo_Historia_Clinica(file1, Hist_clinica, N);
    Elimino_Paciente_Repetido(Hist_clinica, N);

    int k = 0;
    int* P = &k;
    contacto* Datos_Contactos = new contacto[*P];
    ifstream file3;
    file3.open(Contacto, ios::in);
    Leo_Archivo_Contactos(file3, Datos_Contactos, P);
    Elimino_Contacto_Repetido(Datos_Contactos, P);

    int e = 0;
    int* W = &e;
    medicos* Datos_Medicos = new medicos[*W];
    ifstream file5;
    file5.open(Medicos, ios::in);
    Leo_Archivo_Medicos(file5, Datos_Medicos, W);
    Elimino_Medico_Repetido(Datos_Medicos, W);


    obra_social* OS = new obra_social[6];
    OS[0].id_obra_social = "1";
    OS[0].obra_social = "Medicus";
    OS[1].id_obra_social = "2";
    OS[1].obra_social = "OSDE";
    OS[2].id_obra_social = "3";
    OS[2].obra_social = "IOSFA";
    OS[3].id_obra_social = "4";
    OS[3].obra_social = "Italiano";
    OS[4].id_obra_social = "5";
    OS[4].obra_social = "Aleman";
    OS[5].id_obra_social = "6";
    OS[5].obra_social = "Espanyol";
   
    cout << "\nIngrese el DNI del paciente a buscar : " << endl;
    string clave;
    cin >> clave;

    pacientes Paciente = BuscarPaciente2(Hist_clinica, *N, clave);
    if (Paciente.DNI == "0")
    {
        cout << " Paciente no encontrado" << endl;
        return 0;
    }
    contacto Contacto_Del_Paciente = BuscarContactoPaciente2(Datos_Contactos, *P, clave);
    if (Contacto_Del_Paciente.DNI == "0")
    {
        cout << " no nos podremos comunicar con el paciente" << endl;
        return 0;
    }
    string Obra_Social_Del_Paciente = Buscar_obra_social(Paciente, OS);
    if (Obra_Social_Del_Paciente == "0")
    {
        cout << " no podremos llenar toda la informacion del paciente" << endl;
        return 0;
    }
    ifstream Consul;
    Consul.open(Consultas, ios::in);
    consulta UltimaConsulta_Del_Paciente = BuscarUltimaConsulta(Consul, clave);
    if (UltimaConsulta_Del_Paciente.DNI == "0")
    {
        cout << " No se encontraron consultas del paciente : " << clave << endl;
    }
    RecuperarPacientes2(Paciente, UltimaConsulta_Del_Paciente, Contacto_Del_Paciente, Obra_Social_Del_Paciente);


    delete[]Hist_clinica;
    delete[] OS;
    delete[]Datos_Contactos;
    delete[]Datos_Medicos;

    return 0;

}