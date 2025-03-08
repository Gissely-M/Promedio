#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Materia {
    string nombre;
    string diaSemana;
    int horaInicio, horaFin;
    float nota1, nota2, nota3;

    double promedio() const {
        return (nota1 + nota2 + nota3) / 3;
    }

    void mostrar() const {
        cout << "Materia: " << nombre << " | Notas: " << nota1 << ", " << nota2 << ", " << nota3 << " | Promedio: " << promedio();
        if (promedio() < 3.0) {
            cout << " (Bajo desempeno)";
        } else if (promedio() > 4.0) {
            cout << " (Excelente)";
        }
        cout << endl;
        cout << "Horario: " << diaSemana << " " << (horaInicio <= 12 ? horaInicio : horaInicio - 12) << (horaInicio < 12 ? " AM" : (horaInicio == 12 ? " M" : " PM")) << " - " << (horaFin <= 12 ? horaFin : horaFin - 12) << (horaFin < 12 ? " AM" : (horaFin == 12 ? " M" : " PM")) << endl;
    }
};

// Mapeo de días de la semana para ordenarlos correctamente
vector<string> semana = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};

int obtenerIndiceDia(const string& dia) {
    auto it = find(semana.begin(), semana.end(), dia);
    return (it != semana.end()) ? distance(semana.begin(), it) : 7; // 7 si no se encuentra
}

// Función para mostrar el horario ordenado por día de la semana
void mostrarHorario(const vector<Materia>& materias) {
    if (materias.empty()) {
        cout << "No hay materias registradas.\n";
        return;
    }
	cout << "\n---------- HORARIO ----------" <<endl;
    // Ordenamos las materias por el índice del día de la semana
    vector<Materia> materiasOrdenadas = materias;
    sort(materiasOrdenadas.begin(), materiasOrdenadas.end(), [](const Materia& a, const Materia& b) {
        return obtenerIndiceDia(a.diaSemana) < obtenerIndiceDia(b.diaSemana);
    });

    string diaActual = "";
    for (const auto& materia : materiasOrdenadas) {
        if (materia.diaSemana != diaActual) {
            diaActual = materia.diaSemana;
            cout << "\n-------- " << diaActual << " --------" << endl;
        }
        materia.mostrar();
        cout << "----------------------------------\n";
    }
}

struct Acudiente {
	string nombre;
	string apellido;
	string numeroContacto;
	string direccion;
	string neighboorhood;
	
	void mostrar () const {
		cout << "\n---------- ACUDIENTE ----------\n" << endl;
		cout << "Nombre del acudiente: " << nombre << " " << apellido <<endl;
		cout << "Numero del contacto: " << numeroContacto <<endl;
		cout << "Direccion: " << direccion << " barrio " << neighboorhood <<endl;
	}
};

struct Estudiante {
    string nombre;
    string apellido;
    string carrera;
    vector <Materia> materias;
	Acudiente acudiente;
	
		//Este double permite mostrar el promedio del estudiante en general
    double promedioGeneral() const {
    	//Si el vector materias está vacío, mostrará 0 automaticamente
        if (materias.empty()) return 0.0;
        double suma = 0;
        //realiza el promedio de todas materias
        for (const auto& materia : materias) {
            suma += materia.promedio();
        }
        return suma / materias.size();
    }
    void mostrar() const {
    	cout << "\n---------- ESTUDIANTE ----------\n"<<endl;
        cout << "\nNombre: " << nombre << " " <<  apellido << endl;
        cout << "Programa universitario: " << carrera << endl;
        cout << "Materias cursadas (" << materias.size() << ")\n";
    	promedioGeneral ();
		acudiente.mostrar();
    	mostrarHorario (materias);
	}

};

// Vector global de estudiantes
vector<Estudiante> estudiantes;

//Agregar un nuevo estudiante
void agregarEstudiante() {
    Estudiante estudiante;
    cout << "\n---------- AGREGAR ESTUDIANTE ----------\n" << endl;
    cout << "Ingrese el nombre y apellido del estudiante: ";
	cin >> estudiante.nombre >> estudiante.apellido;
//Carrera del estudiante
	cout << "Ingrese el programa universitario del estudiante: ";
	cin.ignore();
	getline (cin, estudiante.carrera);
//Para el tamaño del vector dinámico
    int numMaterias;
    cout << "Ingrese la cantidad de materias: ";
    cin >> numMaterias;
    cin.ignore();
//For para mostrar la cantidad de materias matriculadas
    for (int i = 0; i < numMaterias; i++) {
        Materia materia;
        //Permite llevar el conteo de las materias añadidas
        cout << "Nombre de la materia #" << i + 1 << ": ";
        getline(cin, materia.nombre);
        //Horario
        cout << "Ingrese el dia de la semana en que cursa esta materia: ";
        cin >> materia.diaSemana;
		
		cout << "Ingrese la hora de inicio y la hora fin de la clase: "<<endl;
		cin >> materia.horaInicio >> materia.horaFin;
        
		cout << "Ingrese las 3 notas: ";
        cin >> materia.nota1 >> materia.nota2 >> materia.nota3;
        cin.ignore();
        
        estudiante.materias.push_back(materia);
    }
// Datos del acudiente
    cout << "\n---------- Informacion del Acudiente ----------\n";
    cout << "Nombre del acudiente: ";
    cin >> estudiante.acudiente.nombre >> estudiante.acudiente.apellido;
    cout << "Numero telefonico del acudiente: ";
    cin.ignore();
    getline(cin, estudiante.acudiente.numeroContacto);
    cout << "Direccion del acudiente: ";
    getline(cin, estudiante.acudiente.direccion);
    cout << "Barrio de residencia: ";
    getline (cin, estudiante.acudiente.neighboorhood);

    estudiantes.push_back(estudiante);
    cout << "Estudiante agregado exitosamente.\n";
}

void actualizarNotas(Estudiante &estudiante) {
    cout << "\n---------- ACTUALIZAR NOTAS ----------\n"<<endl;
	cout << "Ingrese el nombre de la materia a actualizar: ";
    string materiaBuscada;
    cin.ignore();
    getline(cin, materiaBuscada);

    bool encontrada = false;
    for (auto &materia : estudiante.materias) {
        if (materia.nombre == materiaBuscada) {
            cout << "Ingrese las nuevas 3 notas: ";
            cin >> materia.nota1 >> materia.nota2 >> materia.nota3;
            cin.ignore();
            cout << "Notas actualizadas correctamente.\n";
            encontrada = true;
            break;
        }
    }
    if (!encontrada) {
        cout << "Materia no encontrada.\n";
    }
}

void buscarEstudianteNombre() {
	cout << "\n---------- BUSCAR ESTUDIANTE ----------\n" <<endl;
    cout << "Ingrese el nombre del estudiante a buscar: ";
    cin.ignore();
    string nombreBuscado;
    getline(cin, nombreBuscado);

    bool encontrado = false;
    for (auto& estudiante : estudiantes) {
        if (estudiante.nombre == nombreBuscado) {
            estudiante.mostrar();
            cout << "Promedio general: " << estudiante.promedioGeneral() << "\n";

            int opcion;
            cout << "Desea actualizar notas de una materia? (1: Sí, 2: No): ";
            cin >> opcion;
            if (opcion == 1) {
                actualizarNotas(estudiante);
            }

            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "Estudiante no encontrado.\n";
    }
}

void buscarEstudianteApellido() {
	cout << "\n---------- BUSCAR ESTUDIANTE ----------\n"<<endl;
    cout << "Ingrese el apellido del estudiante a buscar: ";
    cin.ignore();
    string apellidoBuscado;
    getline(cin, apellidoBuscado);

    bool encontrado = false;
    for (auto& estudiante : estudiantes) {
        if (estudiante.apellido == apellidoBuscado) {
            estudiante.mostrar();
            cout << "Promedio general: " << estudiante.promedioGeneral() << "\n";

            int opcion;
            cout << "Desea actualizar notas de una materia? (1: Sí, 2: No): ";
            cin >> opcion;
            if (opcion == 1) {
                actualizarNotas(estudiante);
            }

            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "Estudiante no encontrado.\n";
    }
}
//Orden Alfabético
void mostrarEstudiantesOrdenados() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    sort(estudiantes.begin(), estudiantes.end(), [](const Estudiante& a, const Estudiante& b) {
        return a.nombre < b.nombre;
    });

    cout << "\n---------- LISTADO DE ESTUDIANTES ----------\n";
    for (const auto& estudiante : estudiantes) {
        cout << "Nombre: " << estudiante.nombre << " " << estudiante.apellido << " (" << estudiante.materias.size() << ")" <<endl;
		cout << "Promedio general: " << estudiante.promedioGeneral() << "\n";
        cout << "----------------------------------\n";
    }
}


int main() {
    int opcion;
    int opcion2;
    //Para que no se cierre
    do {
        cout << "\n---------- MENU ----------\n";
        cout << "1. Agregar estudiante.\n";
        cout << "2. Buscar estudiante.\n";
        cout << "3. Lista de los estudiantes.\n";
        cout << "4. Salir.\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarEstudiante();
                break;
            case 2:
            	cout << "\nDesea buscar el estudiante por nombre o apellido? (1: Nombre, 2: Apellido): ";
            	cin >> opcion2;
            	
                switch (opcion2){
                	case 1:
                		buscarEstudianteNombre();
                		break;
                	case 2:
                		buscarEstudianteApellido();
                		break;
				}
				
                break;
            case 3:
                mostrarEstudiantesOrdenados();
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida, intente nuevamente.\n";
        }
    } while (opcion != 4);

    return 0;
}