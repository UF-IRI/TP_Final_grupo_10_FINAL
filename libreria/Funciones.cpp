#include "funciones.h"
#pragma warning(disable : 4996)
bool CompararFechas(consulta UltimaConsulta)
{
	time_t now = time(0); //inicializo la fecha actual
	tm* aux = localtime(&now); //obtengo fecha actual
	time_t fecha_actual = mktime(aux); //pasamos la fecha de la computadora a segundos para compararlas
	time_t fecha_consulta = mktime(&(UltimaConsulta.fecha_consulta)); //paso la fecha de la consulta a segundos
	int dif = 0;
	dif = difftime(fecha_actual, fecha_consulta) / 3600; //calculo la diferencia de tiempo en segundos, lo retorno y lo paso a horas
	int horas = dif / 8760; //un año tiene 8760 horas (asumiendo 365 días)
	if (horas > 10)
		return 1;
	else
		return 0;
}
tm Fecha_de_string_a_tm(string fecha)
{
	tm estructura;
	string dia = "";
	string mes = "";
	string anio = "";
	int i = 0;
	while (i < fecha.length())
	{

		while (fecha[i] != '/')
		{

			mes += fecha[i];
			i++;


		}
		i++;
		if (fecha[i] == '/')
			i++;
		while (fecha[i] != '/')
		{

			dia += fecha[i];
			i++;

		}
		i++;
		if (fecha[i] == '/')
			i++;
		while (fecha[i] != '/' && anio.length() < 4)
		{

			anio += fecha[i];
			i++;

		}
	}
	int mesi = stoi(mes);
	int diai = stoi(dia);
	int anioi = stoi(anio);
	estructura.tm_wday = diai;
	estructura.tm_mon = mesi;
	estructura.tm_year = anioi;

	return estructura;
}

#pragma region Leo Archivos
void Leo_Historia_Clinica(ifstream& file, pacientes*& Hist_clinicas, int*& N) // recibo una strutc y su tam inicial para guardar y hacer resize
{
	pacientes aux;
	//aux = Hist_clinicas;
	char coma = ',';
	string Header[7];
	int i = 0;
	if (!(file.is_open()))
	{
		cout << "Error al abrir el archivo de historias clinicas" << endl;
		//return; para no imprimir
	}
	else
	{
		string auxfecha1;
		file >> Header[0] >> coma >> Header[1] >> coma >> Header[2] >> coma >> Header[3] >> coma >> Header[4] >> coma >> Header[5] >> coma >> Header[6];
		while (file)
		{
			file >> aux.DNI >> coma >> aux.nombre >> coma >> aux.apellido >> coma >> aux.sexo >> coma >> auxfecha1 >> coma >> aux.estado >> coma >> aux.id_OS;
			aux.fecha_nacimiento = Fecha_de_string_a_tm(auxfecha1);
			agregarPacientes(Hist_clinicas, aux, N);

		}
	}
	file.close();
}
void Leo_Archivo_Medicos(ifstream& file, medicos*& archivo_medicos, int*& N) // recibo una strutc y su tam inicial para guardar y hacer resize
{
	medicos aux;
	char coma = ',';
	string Header[6];
	int i = 0;
	if (!(file.is_open()))
	{
		cout << "Error al abrir el archivo de medicos" << endl;
	}
	else
	{
		file >> Header[0] >> coma >> Header[1] >> coma >> Header[2] >> coma >> Header[3] >> coma >> Header[4] >> coma >> Header[5];
		while (!file.eof())
		{
			file >> aux.id_medico >> coma >> aux.nombre >> coma >> aux.apellido >> coma >> aux.telefono >> coma >> aux.especialidad >> coma >> aux.activo;
			agregarMedico(archivo_medicos, aux, N);
		}
	}
	file.close();
}
void Leo_Archivo_Contactos(ifstream& file, contacto*& archivo_contacto, int*& N) // recibo una strutc y su tam inicial para guardar y hacer resize
{
	contacto aux;
	char coma = ',';
	string Header[5];
	int i = 0;
	if (!(file.is_open()))
	{
		cout << "Error al abrir el archivo de contactos" << endl;
	}
	else
	{
		file >> Header[0] >> coma >> Header[1] >> coma >> Header[2] >> coma >> Header[3] >> coma >> Header[4];
		while (file)
		{
			file >> aux.DNI >> coma >> aux.telefono >> coma >> aux.numero_celular >> coma >> aux.direccion >> coma >> aux.mail;
			agregarContactos(archivo_contacto, aux, N);
		}
	}
	file.close();
}

#pragma endregion Leo Archivos

#pragma region agregar
void agregarPacientes(pacientes*& lista, pacientes nuevo, int*& tamactual) {
	*tamactual = *tamactual + 1;
	int i = 0;
	pacientes* aux = new pacientes[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = lista[i];
		i++;
	}
	aux[i] = nuevo;

	delete[] lista;
	lista = aux;

	return;
}
void agregarContactos(contacto*& lista, contacto nuevo, int*& tamactual) {
	*tamactual = *tamactual + 1;
	int i = 0;
	contacto* aux = new contacto[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = lista[i];
		i++;
	}
	aux[i] = nuevo;

	delete[] lista;
	lista = aux;

	return;
}
void agregarConsultas(consulta*& lista, consulta nuevo, int*& tamactual)
{
	*tamactual = *tamactual + 1;
	int i = 0;
	consulta* aux = new consulta[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = lista[i];
		i++;
	}
	aux[i] = nuevo;

	delete[] lista;
	lista = aux;

	return;
}
void agregarMedico(medicos*& lista, medicos nuevo, int*& tamactual) {
	*tamactual = *tamactual + 1;
	int i = 0;
	medicos* aux = new medicos[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = lista[i];
		i++;
	}
	aux[i] = nuevo;

	delete[] lista;
	lista = aux;

	return;
}
#pragma  endregion agregar

#pragma region Eliminar repetidos
void Elimino_Paciente_Repetido(pacientes*& Hist_clinicas, int*& N)
{
	int contador = 0;
	int o = 0;
	int* p = &o;
	pacientes  aux;
	int contador_nulos = 0;
	int j = 0;
	for (int i = 0; i < *N - 1; i++)
	{
		for (j = i; j < *N - 1; j++)
		{
			if (Hist_clinicas[i].DNI == Hist_clinicas[j + 1].DNI)
			{
				Hist_clinicas[j + 1].DNI = "0";

			}
		}
	}
	for (int i = 0; i < *N; i++)
	{
		for (int j = 0; j < *N - 1; j++)
		{
			if (Hist_clinicas[j].DNI == "0")
			{
				aux = Hist_clinicas[j];
				Hist_clinicas[j] = Hist_clinicas[j + 1];
				Hist_clinicas[j + 1] = aux; // muevo los nulos al final
				contador_nulos++;
			}
		}
	}
	*N = *N - contador_nulos;
	// reduzco el tamaño de mi lista, entonces ya me queda sin los nulos
}
void Elimino_Medico_Repetido(medicos*& datos_medicos, int*& N)
{
	int contador = 0;
	int o = 0;
	int* p = &o;
	medicos aux;
	int contador_nulos = 0;
	int j = 0;
	for (int i = 0; i < *N - 1; i++)
	{
		for (j = i; j < *N - 1; j++)
		{
			if (datos_medicos[i].id_medico == datos_medicos[j + 1].id_medico)
			{
				datos_medicos[j + 1].id_medico = "0";

			}
		}
	}
	for (int i = 0; i < *N; i++)
	{
		for (int j = 0; j < *N - 1; j++)
		{
			if (datos_medicos[j].id_medico == "0")
			{
				aux = datos_medicos[j];
				datos_medicos[j] = datos_medicos[j + 1];
				datos_medicos[j + 1] = aux; // muevo los nulos al final
				contador_nulos++;
			}
		}
	}
	*N = *N - contador_nulos;
	// reduzco el tamaño de mi lista, entonces ya me queda sin los nulos
}
void Elimino_Contacto_Repetido(contacto*& Contactos, int*& N)
{
	int contador = 0;
	int o = 0;
	int* p = &o;
	contacto  aux;
	int contador_nulos = 0;
	int j = 0;
	for (int i = 0; i < *N - 1; i++)
	{
		for (j = i; j < *N - 1; j++)
		{
			if (Contactos[i].DNI == Contactos[j + 1].DNI)
			{
				Contactos[j + 1].DNI = "0";

			}
		}
	}
	for (int i = 0; i < *N; i++)
	{
		for (int j = 0; j < *N - 1; j++)
		{
			if (Contactos[j].DNI == "0")
			{
				aux = Contactos[j];
				Contactos[j] = Contactos[j + 1];
				Contactos[j + 1] = aux; // muevo los nulos al final
				contador_nulos++;
			}
		}
	}
	*N = *N - contador_nulos;
	// reduzco el tamaño de mi lista, entonces ya me queda sin los nulos
}
#pragma endregion Eliminar repetidos

// las siguientes funciones no las usamos, para evitar abrir tantas veces el archivo
#pragma region Copiar sin repetidos
void Copio_Hist_Clinicas_Sin_Repetidos(ofstream& file, pacientes* Hist_clinicas, int*& N)
{

	char coma = ',';
	string Header[7];
	int i = 0;
	if (!(file.is_open()))
	{
		cout << "Error al abrir el archivo de historias clinicas";
	}
	else
	{
		file << Header[0] << coma << Header[1] << coma << Header[2] << coma << Header[3] << coma << Header[4] << coma << Header[5] << coma << Header[6];
		while (!file.eof() && i < *N)
		{
			file << Hist_clinicas[i].DNI << coma << Hist_clinicas[i].nombre << coma << Hist_clinicas[i].apellido << coma << Hist_clinicas[i].sexo << coma << Hist_clinicas[i].fecha_nacimiento.tm_mday << coma << Hist_clinicas[i].fecha_nacimiento.tm_mon << coma << Hist_clinicas[i].fecha_nacimiento.tm_year << coma << Hist_clinicas[i].id_OS << coma << Hist_clinicas[i].estado;
			i++;
		}
	}
	file.close();
}
void Copio_Medicos_Sin_Repetidos(ofstream& file, medicos* archivo_medico, int*& N)
{
	char coma = ',';
	string Header[6];
	int i = 0;
	if (!(file.is_open()))
	{
		cout << "Error al abrir el archivo de medicos";
	}
	else
	{
		file << Header[0] << coma << Header[1] << coma << Header[2] << coma << Header[3] << coma << Header[4] << coma << Header[5];
		while (!file.eof() && i < *N)
		{
			file << archivo_medico[i].id_medico << coma << archivo_medico[i].nombre << coma << archivo_medico[i].apellido << coma << archivo_medico[i].telefono << coma << archivo_medico[i].especialidad << coma << archivo_medico[i].activo;
			i++;
		}
	}
	file.close();
}
void Copio_Contactos_Sin_Repetidos(ofstream& file, contacto* archivo_contacto, int*& N)
{
	char coma = ',';
	string Header[5];
	int i = 0;
	if (!(file.is_open()))
	{
		cout << "Error al abrir el archivo de contactos";
	}
	else
	{
		file << Header[0] << coma << Header[1] << coma << Header[2] << coma << Header[3] << coma << Header[4];
		while (!file.eof() && i < *N)
		{
			file << archivo_contacto[i].DNI << coma << archivo_contacto[i].telefono << coma << archivo_contacto[i].numero_celular << coma << archivo_contacto[i].direccion << coma << archivo_contacto[i].mail;
			i++;
		}
	}
	file.close();
}
#pragma endregion Copiar sin repetidos
#pragma region Busqueda
pacientes BuscarPaciente(ifstream& file, string clave)
{
	char coma = ',';
	int i = 0;
	string Header[7];
	pacientes Hist_clinicas; // struct axuliar que usamos para leer el archivo, no la vamos a retornar, la vamos pisando porque no nos interesa
	pacientes Paciente_Encontrado; // son los datos del paciente que buscamos
	if (!(file.is_open()))
	{
		cout << "Error al abrir el archivo";
	}
	else
	{
		file >> Header[0] >> coma >> Header[1] >> coma >> Header[2] >> coma >> Header[3] >> coma >> Header[4] >> coma >> Header[5] >> coma >> Header[6];
		while (!file.eof())
		{
			//mientras el archivo este abierto,el paciente.
			string fecha1;
			file >> Hist_clinicas.DNI >> coma >> Hist_clinicas.nombre >> coma >> Hist_clinicas.apellido >> coma >> Hist_clinicas.sexo >> coma >> fecha1 >> coma >> Hist_clinicas.id_OS >> coma >> Hist_clinicas.estado;
			Hist_clinicas.fecha_nacimiento = Fecha_de_string_a_tm(fecha1);
			if (clave == Hist_clinicas.DNI)
			{
				Paciente_Encontrado = Hist_clinicas;
			}
		};
	}
	// cierro el archivo
	if (Paciente_Encontrado.DNI != clave)
	{
		cout << " paciente no encontrado" << endl;
	}
	file.close();
	return Paciente_Encontrado;//retorno el paciente y sus datos
}
contacto BuscarContactoPaciente(ifstream& file, string clave)
{
	char coma = ',';
	int i = 0;
	string Header[5];
	contacto aux;
	contacto Todos; // struct axuliar que usamos para leer el archivo, no la vamos a retornar, la vamos pisando porque no nos interesa
	contacto contacto_del_paciente; // son los datos del paciente que buscamos
	if (!(file.is_open()))
	{
		cout << "Error al abrir el archivo de contacto";
		return aux;
	}
	else
	{
		file >> Header[0] >> coma >> Header[1] >> coma >> Header[2] >> coma >> Header[3] >> coma >> Header[4];
		while (!file.eof())
		{
			//mientras el archivo este abierto,el paciente.
			file >> Todos.DNI >> coma >> Todos.telefono >> coma >> Todos.numero_celular >> coma >> Todos.direccion >> coma >> Todos.mail;
			if (clave == Todos.DNI)
			{
				contacto_del_paciente = Todos;
			}
		};
	}
	if (contacto_del_paciente.DNI != clave)
	{
		cout << " paciente no encontrado" << endl;
	}
	// cierro el archivo
	file.close();
	return contacto_del_paciente;//retorno el contacto del paciente
}
void RecuperarPacientes(ifstream& Archivo_Contacto, pacientes Paciente, consulta UltimaConsulta, contacto ContactoDelPaciente, string os)//recibe los datos del paciente por referencia para poder ser modificados
{
	contacto ContactoPaciente;

	if (Paciente.estado == "fallecido") // el paciente esta muerto
	{
		cout << " El paciente ha fallecido " << endl;

	}
	else
	{
		if (CompararFechas(UltimaConsulta) == 1)
		{
			//pasaron mas de 10 años
			// el paciente es irrecuperable, mandamos su historia clínica al archivo Archivados
			ContactoPaciente = BuscarContactoPaciente(Archivo_Contacto, Paciente.DNI);
			Guardar(Archivados, Paciente, UltimaConsulta, ContactoPaciente, os);
		}
		else // pasaron menos de 10 años
		{
			if (UltimaConsulta.Presento == false && Paciente.estado == "nc")
				// si no se presento ni reprogramo
			{
				cout << " El paciente podria volver" << endl;
				SecretariaPacientes(Paciente, UltimaConsulta, ContactoDelPaciente, os);
				Guardar(Actuales, Paciente, UltimaConsulta, ContactoDelPaciente, os);
			}
			else
			{
				cout << "El paciente reprogramo o asistio a su ultima consulta" << endl;
			}
		}
	}

}
#pragma endregion Busqueda

// de aca en adelante si las usamos
#pragma region Resize
void Resize_Medicos(int cuantos_agregar, int*& N, medicos*& datos)
{
	*N = *N + cuantos_agregar;
	int i = 0;
	medicos* aux = new medicos[*N];
	while (i < *N)
	{
		if (i < *N - cuantos_agregar)
		{
			aux[i] = datos[i];
		}
		i++;
	}
	delete[]datos;
	datos = aux;

}
void Resize_Consultas(int cuantos_agregar, int*& N, consulta*& consul)
{
	*N = *N + cuantos_agregar;
	int i = 0;
	consulta* aux = new consulta[*N];
	while (i < *N)
	{
		if (i < *N - cuantos_agregar)
		{
			aux[i] = consul[i];
		}
		i++;
	}
	delete[]consul;
	consul = aux;

}
void Resize_Pacientes(int cuantos_agregar, int*& N, pacientes*& pac)
{
	*N = *N + cuantos_agregar;
	int i = 0;
	pacientes* aux = new pacientes[*N];
	while (i < *N)
	{
		if (i < *N - cuantos_agregar)
		{
			aux[i] = pac[i];
		}
		i++;
	}
	delete[]pac;
	pac = aux;

}
void Resize_Contactos(int cuantos_agregar, int*& N, contacto*& datos)
{
	*N = *N + cuantos_agregar;
	int i = 0;
	contacto* aux = new contacto[*N];
	while (i < *N)
	{
		if (i < *N - cuantos_agregar)
		{
			aux[i] = datos[i];
		}
		i++;
	}
	delete[]datos;
	datos = aux;

}
#pragma endregion Resize

#pragma region BusquedaDesdeLasEstructuras
consulta BuscarUltimaConsulta(ifstream& Consul, string clave)
{
	char coma = ',';
	string Header[5];
	int i = 0, j = 0;
	consulta  UltimaConsulta; // es la ultima consulta, la cual retornamos
	if (!(Consul.is_open()))
	{
		cout << "Error al abrir el archivo de Consultas";
	}
	else
	{
		Consul >> Header[0] >> coma >> Header[1] >> coma >> Header[2] >> coma >> Header[3] >> coma >> Header[4];
		string auxfecha1;
		string auxfecha2;
		consulta aux;
		while (Consul)
		{
			//mientras el archivo este abierto, busco la ultima consulta.
			Consul >> aux.DNI >> coma >> auxfecha1 >> coma >> auxfecha2 >> coma >> aux.Presento >> coma >> aux.id_medico;
			aux.fecha_consulta = Fecha_de_string_a_tm(auxfecha1);
			aux.fecha_pedido = Fecha_de_string_a_tm(auxfecha2);
			if (clave == aux.DNI)
			{
				UltimaConsulta = aux;
			}
			i++;
		};
	}
	// cierro el archivo
	Consul.close();
	//libero memoria
	return UltimaConsulta;//retorno la ultima consulta del paciente, con sus datos
}
string Buscar_obra_social(pacientes Paciente, obra_social* OS)
{
	for (int i = 0; i < 6; i++)
	{
		if (Paciente.id_OS == OS[i].obra_social)
		{
			return OS[i].obra_social;
		}
	}
	cout << " no hay coincidencias en la obra social, con las cargadas en el sistema" << endl;
	return "0";
}
pacientes BuscarPaciente2(pacientes* estructura, int N, string clave)
{
	int contador_guardado = 0;
	pacientes PacienteEncontrado;
	for (int i = 0; i < N; i++)
	{
		if (estructura[i].DNI == clave) // si el dni del paciente coinicide con alguno de mis historias clinicas
		{
			PacienteEncontrado = estructura[i]; // lo guardo en un auxiliar
			contador_guardado++; // es para condicionar si lo hemos encontrado o no
		}
	}
	if (contador_guardado != 0)
	{
		return PacienteEncontrado; // lo retorno
	}
	else
		cout << " Los datos no coinciden con los cargados en el archivo" << endl;
}
contacto BuscarContactoPaciente2(contacto* estructura, int N, string clave)
{
	for (int i = 0; i < N; i++)
	{
		if (estructura[i].DNI == clave) // si encontramos el contacto del paciente
		{
			return estructura[i]; // lo retornamos
		}//10242584
	}
	cout << "Contacto del paciente:" << clave << " no fue encontrado" << endl;
}
void RecuperarPacientes2(pacientes Paciente, consulta UltimaConsulta, contacto ContactoDelPaciente, string os)//recibe los datos del paciente por referencia para poder ser modificados
{
	contacto ContactoPaciente;

	if (Paciente.estado == "fallecido") // el paciente esta muerto
	{
		cout << " El paciente ha fallecido " << endl;

	}
	else
	{
		if (CompararFechas(UltimaConsulta) == 1)
		{
			//pasaron mas de 10 años
			// el paciente es irrecuperable, mandamos su historia clínica al archivo Archivados
			//ContactoPaciente = BuscarContactoPaciente2(estructura, tamanio, Paciente.DNI);
			Guardar(Archivados, Paciente, UltimaConsulta, ContactoDelPaciente, os);
		}
		else // pasaron menos de 10 años
		{
			if (UltimaConsulta.Presento == false && Paciente.estado == "n/c")
				// si no se presento ni reprogramo
			{
				cout << " El paciente podria volver" << endl;
				SecretariaPacientes(Paciente, UltimaConsulta, ContactoDelPaciente, os);
				Guardar(Actuales, Paciente, UltimaConsulta, ContactoDelPaciente, os);
			}
			else
			{
				cout << "El paciente reprogramo o asistio a su ultima consulta" << endl;
			}
		}
	}

}
#pragma endregion BusquedaDesdeLasEstructuras


void Guardar(string NombreDelArchivo, pacientes Paciente, consulta UltimaConsulta, contacto Contac, string os)
{
	fstream fp;
	fp.open(Actuales, ios::app);
	string* Header = new string[14];
	char coma = ',';
	int i = 0;
	if (!(fp.is_open()))
		cout << "error al abrir el nuevo archivo" << endl;
	else
	{
		fp >> Header[0] >> coma >> Header[1] >> coma >> Header[2] >> coma >> Header[3] >> coma >> Header[4] >> coma >> Header[5] >> coma >> Header[6] >> coma >> Header[7] >> coma >> Header[8] >> coma >> Header[9] >> coma >> Header[10] >> coma >> Header[11] >> coma >> Header[12] >> coma >> Header[13];
		//escribimos el header 
		fp << "DNI " << coma << " NOMBRE " << coma << " APELLIDO " << " F.NACIMIENTO " << coma << "ESTADO " << coma << " MEDICO " << coma << " ASISTENCIA " << coma << " F. ULTIMA CONSULTA " << coma << " OBRA SOCIAL" << coma << " TELEFONO" << coma << " CELULAR " << coma << "DIRECCION " << coma << "MAIL";
		//fp >> Header[0] >> coma >> Header[1] >> coma >> Header[2] >> coma >> Header[3] >> coma >> Header[4] >> coma >> Header[5] >> coma >> Header[6] >> coma >> Header[7] >> coma >> Header[8] >> coma >> Header[9] >> coma >> Header[10] >> coma >> Header[11] >> coma >> Header[12] >> coma >> Header[13];
		// DNI, nombre, apellido, sexo, fecha de nacimiento, estado, matricula medico, asistencia, fecha ultima consulta, obra social, telefono, numero de celular, direccion, mail
		while (!fp.eof()) //mientras el archivo este abierto, guardamos los datos del paciente, en la ultima posición que se encuentra vacia
		{
			fp << Paciente.DNI << coma << Paciente.nombre << coma << Paciente.apellido << coma << Paciente.sexo << coma << Paciente.fecha_nacimiento.tm_mday << coma << Paciente.fecha_nacimiento.tm_mon << coma << Paciente.fecha_nacimiento.tm_year << coma << Paciente.estado << coma << UltimaConsulta.id_medico << coma << UltimaConsulta.Presento << coma << UltimaConsulta.fecha_consulta.tm_mday << coma << UltimaConsulta.fecha_consulta.tm_mon << coma << UltimaConsulta.fecha_consulta.tm_year << coma << os << coma << Contac.telefono << coma << Contac.numero_celular << coma << Contac.direccion << coma << Contac.mail;
		}

	}
	fp.close();
}
void SecretariaPacientes(pacientes Paciente, consulta UltimaConsulta, contacto Contac, string os)
{
	int respuesta = rand() % 2; //hace un random entre 0 y 1 para que la respuesta del paciente sea aleatoria
	string aux;
	cout << "Contactandose con el numero " << Contac.numero_celular << "..." << endl;
	if (respuesta == 1)
	{
		cout << " Retorna " << endl;
		cout << " ¿Cual es su obra social? " << endl;
		cin >> aux;
		if (os != aux)
		{
			if (os == "Medicus")
			{
				Paciente.id_OS = 1;
			}
			if (os == "OSDE")
			{
				Paciente.id_OS = 2;
			}
			if (os == " IOSFA")
			{
				Paciente.id_OS = 3;
			}
			if (os == " Italiano")
			{
				Paciente.id_OS = 4;
			}
			if (os == "Aleman ")
			{
				Paciente.id_OS = 5;
			}
			if (os == "Espanyol")
			{
				Paciente.id_OS = 6;
			}
		}
		else
		{
			cout << "El paciente conserva la obra social que tenia en su ultima Consulta" << endl;
		}
	}

}