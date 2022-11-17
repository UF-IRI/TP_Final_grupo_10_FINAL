#include "gmock/gmock.h"
#include "Funciones.h"

namespace foobar::tests 
{
	TEST(Test_BuscarPaciente_en_estructura, Test_Caso1)
	{
		int o = 4;
		int* P = &o;
		pacientes* prueba3 = new pacientes[*P];
		prueba3[0].DNI = "10242582";
		prueba3[0].nombre = " Cersty";
		prueba3[0].apellido = "Thurston";
		prueba3[0].sexo = "F";
		prueba3[0].fecha_nacimiento.tm_year = 1970;
		prueba3[0].fecha_nacimiento.tm_mon = 6;
		prueba3[0].fecha_nacimiento.tm_wday = 9;
		prueba3[0].estado = "n/c";
		prueba3[0].id_OS = "Medicus";

		prueba3[1].DNI = "78512";
		prueba3[1].nombre = " Matias";
		prueba3[1].apellido = "Lopez";
		prueba3[1].sexo = "M";
		prueba3[1].fecha_nacimiento.tm_year = 1970;
		prueba3[1].fecha_nacimiento.tm_mon = 8;
		prueba3[1].fecha_nacimiento.tm_wday = 7;
		prueba3[1].estado = "internado";
		prueba3[1].id_OS = "Italiano";

		prueba3[2].DNI = "523032";
		prueba3[2].nombre = " Camila";
		prueba3[2].apellido = "Ramat";
		prueba3[2].sexo = "F";
		prueba3[2].fecha_nacimiento.tm_year = 2022;
		prueba3[2].fecha_nacimiento.tm_mon = 6;
		prueba3[2].fecha_nacimiento.tm_wday = 9;
		prueba3[2].estado = "fallecido";
		prueba3[2].id_OS = "OSDE";

		prueba3[3].DNI = "78512";
		prueba3[3].nombre = " Matias";
		prueba3[3].apellido = "Lopez";
		prueba3[3].sexo = "M";
		prueba3[3].fecha_nacimiento.tm_year = 1970;
		prueba3[3].fecha_nacimiento.tm_mon = 8;
		prueba3[3].fecha_nacimiento.tm_wday = 7;
		prueba3[3].estado = "internado";
		prueba3[3].id_OS = "Italiano";

		pacientes Retorno = BuscarPaciente2(prueba3, *P, prueba3[2].DNI);

		ASSERT_THAT(prueba3[2].DNI, Retorno.DNI);

	}
	TEST(TestEliminar, Test_Caso2)
	{
		int o = 4;
		int* P = &o;
		pacientes* prueba = new pacientes[*P];
		prueba[0].DNI = "10242582";
		prueba[0].nombre = " Cersty";
		prueba[0].apellido = "Thurston";
		prueba[0].sexo = "F";
		prueba[0].fecha_nacimiento.tm_year = 1970;
		prueba[0].fecha_nacimiento.tm_mon = 6;
		prueba[0].fecha_nacimiento.tm_wday = 9;
		prueba[0].estado = "n/c";
		prueba[0].id_OS = "Medicus";

		prueba[1].DNI = "78512";
		prueba[1].nombre = " Matias";
		prueba[1].apellido = "Lopez";
		prueba[1].sexo = "M";
		prueba[1].fecha_nacimiento.tm_year = 1970;
		prueba[1].fecha_nacimiento.tm_mon = 8;
		prueba[1].fecha_nacimiento.tm_wday = 7;
		prueba[1].estado = "internado";
		prueba[1].id_OS = "Italiano";

		prueba[2].DNI = "523032";
		prueba[2].nombre = " Camila";
		prueba[2].apellido = "Ramat";
		prueba[2].sexo = "F";
		prueba[2].fecha_nacimiento.tm_year = 2022;
		prueba[2].fecha_nacimiento.tm_mon = 6;
		prueba[2].fecha_nacimiento.tm_wday = 9;
		prueba[2].estado = "fallecido";
		prueba[2].id_OS = "OSDE";

		prueba[3].DNI = "78512";
		prueba[3].nombre = " Matias";
		prueba[3].apellido = "Lopez";
		prueba[3].sexo = "M";
		prueba[3].fecha_nacimiento.tm_year = 1970;
		prueba[3].fecha_nacimiento.tm_mon = 8;
		prueba[3].fecha_nacimiento.tm_wday = 7;
		prueba[3].estado = "internado";
		prueba[3].id_OS = "Italiano";


		pacientes* prueba2 = new pacientes[3];
		prueba2[0].DNI = "10242582";
		prueba2[0].nombre = " Cersty";
		prueba2[0].apellido = "Thurston";
		prueba2[0].sexo = "F";
		prueba2[0].fecha_nacimiento.tm_year = 1970;
		prueba2[0].fecha_nacimiento.tm_mon = 6;
		prueba2[0].fecha_nacimiento.tm_wday = 9;
		prueba2[0].estado = "n/c";
		prueba2[0].id_OS = "Medicus";

		prueba2[1].DNI = "78512";
		prueba2[1].nombre = " Matias";
		prueba2[1].apellido = "Lopez";
		prueba2[1].sexo = "M";
		prueba2[1].fecha_nacimiento.tm_year = 1970;
		prueba2[1].fecha_nacimiento.tm_mon = 8;
		prueba2[1].fecha_nacimiento.tm_wday = 7;
		prueba2[1].estado = "internado";
		prueba2[1].id_OS = "Italiano";

		prueba2[2].DNI = "523032";
		prueba2[2].nombre = " Camila";
		prueba2[2].apellido = "Ramat";
		prueba2[2].sexo = "F";
		prueba2[2].fecha_nacimiento.tm_year = 2022;
		prueba2[2].fecha_nacimiento.tm_mon = 6;
		prueba2[2].fecha_nacimiento.tm_wday = 9;
		prueba2[2].estado = "fallecido";
		prueba2[2].id_OS = "OSDE";

		Elimino_Paciente_Repetido(prueba, P);

		for (int i = 0; i < 3; i++)
		{
			ASSERT_THAT(prueba2[i].DNI, prueba[i].DNI);
		}
	}

	TEST(BuscarObraSocial, Test_Caso3)
	{
		pacientes* prueba = new pacientes();
		prueba[0].DNI = "10242582";
		prueba[0].nombre = " Cersty";
		prueba[0].apellido = "Thurston";
		prueba[0].sexo = "F";
		prueba[0].fecha_nacimiento.tm_year = 1970;
		prueba[0].fecha_nacimiento.tm_mon = 6;
		prueba[0].fecha_nacimiento.tm_wday = 9;
		prueba[0].estado = "n/c";
		prueba[0].id_OS = "Medicus";

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
		string ob = Buscar_obra_social(*prueba, OS);

		ASSERT_THAT(prueba[0].id_OS, ob);
	}
}