#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>

using namespace std;

void gotoxy(int x, int y);
void cuadro(int x1, int y1, int x2, int y2);
void textoConColor(int color, const string &texto);

struct Viajero {
    int id;
    string nombre;
    string direccion;
    string nacionalidad;
    string fechaNacimiento;
    string genero;
};

struct Ingreso {
    int idViajero;
    string fechaIngreso;
    string lugarIngreso;
};

struct Salida {
    int idViajero;
    string fechaSalida;
    string lugarSalida;
};

struct Visa {
    int idViajero;
    bool esValida;
    string fechaExpiracion;
    string tipoVisa;
};

struct Pais {
    string nombre;
    bool requiereVisa;
};

struct TipoVisa {
    string nombre;
    string descripcion;
};

string intToStringAlternative(int num) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d", num);
    return string(buffer);
}

const int MAX_VIAJEROS = 100;
Viajero viajeros[MAX_VIAJEROS];
Ingreso ingresos[MAX_VIAJEROS];
Salida salidas[MAX_VIAJEROS];
Visa visas[MAX_VIAJEROS];
Pais paises[10];
TipoVisa tiposVisa[10];

int contadorViajeros = 0;
int contadorIngresos = 0;
int contadorSalidas = 0;
int contadorVisas = 0;
int contadorPaises = 0;
int contadorTiposVisa = 0;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void cuadro(int x1, int y1, int x2, int y2) {
    int i;
    for (i = x1; i <= x2; i++) {
        gotoxy(i, y1); printf("%c", 205);
        gotoxy(i, y2); printf("%c", 205);
    }
    for (i = y1; i <= y2; i++) {
        gotoxy(x1, i); printf("%c", 186);
        gotoxy(x2, i); printf("%c", 186);
    }
    gotoxy(x1, y1); printf("%c", 201);
    gotoxy(x1, y2); printf("%c", 200);
    gotoxy(x2, y1); printf("%c", 187);
    gotoxy(x2, y2); printf("%c", 188);
}

void textoConColor(int color, const string &texto) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << texto;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void inicializarCatalogos() {
    paises[0] = {"Mexico", false};
    paises[1] = {"Estados Unidos", true};
    paises[2] = {"Canada", true};
    paises[3] = {"Brasil", false};
    paises[4] = {"Argentina", false};
    contadorPaises = 5;

    tiposVisa[0] = {"Turismo", "Visa para turismo"};
    tiposVisa[1] = {"Trabajo", "Visa para trabajar"};
    tiposVisa[2] = {"Estudiante", "Visa para estudiar"};
    contadorTiposVisa = 3;
}

void mostrarMenu() {
    system("cls");
    cuadro(1, 1, 60, 20);

    gotoxy(3, 3); textoConColor(11, "1. Agregar Viajero");
    gotoxy(3, 5); textoConColor(11, "2. Registrar Ingreso");
    gotoxy(3, 7); textoConColor(11, "3. Registrar Salida");
    gotoxy(3, 9); textoConColor(11, "4. Consultar Informacion de Viajero");
    gotoxy(3, 11); textoConColor(11, "5. Borrar Registros");
    gotoxy(3, 13); textoConColor(11, "6. Generar Reportes");
    gotoxy(3, 15); textoConColor(11, "7. Salir");
    gotoxy(3, 17); textoConColor(14, "Selecciona una opcion: ");
}

void mostrarOpcionesVisa() {
    system("cls");
    cuadro(1, 1, 60, 14);
    textoConColor(14, "Seleccione el tipo de visa:\n");

    for (int i = 0; i < contadorTiposVisa; i++) {
        gotoxy(3, 3 + i); textoConColor(11, intToStringAlternative(i + 1) + ". " + tiposVisa[i].nombre + " - " + tiposVisa[i].descripcion);
    }
    gotoxy(3, 3 + contadorTiposVisa + 1); textoConColor(14, "Selecciona una opcion: ");
}

void agregarViajero() {
    if (contadorViajeros < MAX_VIAJEROS) {
        system("cls");
        cuadro(1, 1, 60, 24);
        textoConColor(14, "Ingrese la información del viajero:\n");

        gotoxy(3, 3); textoConColor(11, "ID del viajero: ");
        cin >> viajeros[contadorViajeros].id;
        gotoxy(3, 5); textoConColor(11, "Nombre del viajero: ");
        cin.ignore();
        getline(cin, viajeros[contadorViajeros].nombre);
        gotoxy(3, 7); textoConColor(11, "Direccion: ");
        getline(cin, viajeros[contadorViajeros].direccion);
        gotoxy(3, 9); textoConColor(11, "Nacionalidad: ");
        getline(cin, viajeros[contadorViajeros].nacionalidad);
        gotoxy(3, 11); textoConColor(11, "Fecha de nacimiento (DD/MM/AAAA): ");
        getline(cin, viajeros[contadorViajeros].fechaNacimiento);
        gotoxy(3, 13); textoConColor(11, "Genero: ");
        getline(cin, viajeros[contadorViajeros].genero);

        visas[contadorVisas].idViajero = viajeros[contadorViajeros].id;
        gotoxy(3, 15); textoConColor(11, "¿Tiene visa válida? (1: Si, 0: No): ");
        cin >> visas[contadorVisas].esValida;
        if (visas[contadorVisas].esValida) {
            gotoxy(3, 17); textoConColor(11, "Ingrese la fecha de expiracion de la visa (DD/MM/AAAA): ");
            cin.ignore();
            getline(cin, visas[contadorVisas].fechaExpiracion);

            mostrarOpcionesVisa();
            int opcionVisa;
            cin >> opcionVisa;
            visas[contadorVisas].tipoVisa = tiposVisa[opcionVisa - 1].nombre;
        }
        contadorVisas++;
        contadorViajeros++;
    } else {
        gotoxy(3, 19); textoConColor(12, "No se pueden agregar mas viajeros.");
    }
}

void registrarIngreso() {
    if (contadorIngresos < MAX_VIAJEROS) {
        system("cls");
        cuadro(1, 1, 60, 16);
        textoConColor(14, "Registrar Ingreso:\n");

        gotoxy(3, 3); textoConColor(11, "Ingrese ID del viajero: ");
        cin >> ingresos[contadorIngresos].idViajero;
        gotoxy(3, 5); textoConColor(11, "Ingrese fecha de ingreso (DD/MM/AAAA): ");
        cin.ignore();
        getline(cin, ingresos[contadorIngresos].fechaIngreso);
        gotoxy(3, 7); textoConColor(11, "Ingrese lugar de ingreso: ");
        getline(cin, ingresos[contadorIngresos].lugarIngreso);
        contadorIngresos++;
    } else {
        gotoxy(3, 9); textoConColor(12, "No se pueden registrar mas ingresos.");
    }
}

void registrarSalida() {
    if (contadorSalidas < MAX_VIAJEROS) {
        system("cls");
        cuadro(1, 1, 60, 16);
        textoConColor(14, "Registrar Salida:\n");

        gotoxy(3, 3); textoConColor(11, "Ingrese ID del viajero: ");
        cin >> salidas[contadorSalidas].idViajero;
        gotoxy(3, 5); textoConColor(11, "Ingrese fecha de salida (DD/MM/AAAA): ");
        cin.ignore();
        getline(cin, salidas[contadorSalidas].fechaSalida);
        gotoxy(3, 7); textoConColor(11, "Ingrese lugar de salida: ");
        getline(cin, salidas[contadorSalidas].lugarSalida);
        contadorSalidas++;
    } else {
        gotoxy(3, 9); textoConColor(12, "No se pueden registrar mas salidas.");
    }
}

void consultarInformacion() {
    system("cls");
    cuadro(1, 1, 60, 16);
    textoConColor(14, "Consultar Informacion de Viajero:\n");

    int id;
    gotoxy(3, 3); textoConColor(11, "Ingrese ID del viajero: ");
    cin >> id;

    bool encontrado = false;
    for (int i = 0; i < contadorViajeros; i++) {
        if (viajeros[i].id == id) {
            encontrado = true;
            gotoxy(3, 5); textoConColor(11, "Nombre: " + viajeros[i].nombre);
            gotoxy(3, 7); textoConColor(11, "Direccion: " + viajeros[i].direccion);
            gotoxy(3, 9); textoConColor(11, "Nacionalidad: " + viajeros[i].nacionalidad);
            gotoxy(3, 11); textoConColor(11, "Fecha de Nacimiento: " + viajeros[i].fechaNacimiento);
            gotoxy(3, 13); textoConColor(11, "Genero: " + viajeros[i].genero);
            break;
        }
    }
    if (!encontrado) {
        gotoxy(3, 15); textoConColor(12, "Viajero no encontrado.");
    }

    gotoxy(3, 17); textoConColor(14, "Presione Enter para volver al menú...");
    cin.ignore(); 
    cin.get(); 
}


void borrarRegistros() {
    system("cls");
    cuadro(1, 1, 60, 14);
    textoConColor(14, "Borrar Registros:\n");

    int id;
    gotoxy(3, 3); textoConColor(11, "Ingrese ID del viajero a borrar: ");
    cin >> id;

    bool encontrado = false;
    for (int i = 0; i < contadorViajeros; i++) {
        if (viajeros[i].id == id) {
            encontrado = true;

            for (int j = i; j < contadorViajeros - 1; j++) {
                viajeros[j] = viajeros[j + 1];
            }
            contadorViajeros--;

            for (int j = 0; j < contadorIngresos; j++) {
                if (ingresos[j].idViajero == id) {
                    for (int k = j; k < contadorIngresos - 1; k++) {
                        ingresos[k] = ingresos[k + 1];
                    }
                    contadorIngresos--;
                    j--; 
                }
            }

            for (int j = 0; j < contadorSalidas; j++) {
                if (salidas[j].idViajero == id) {
                    for (int k = j; k < contadorSalidas - 1; k++) {
                        salidas[k] = salidas[k + 1];
                    }
                    contadorSalidas--;
                    j--; 
                }
            }

            for (int j = 0; j < contadorVisas; j++) {
                if (visas[j].idViajero == id) {
                    for (int k = j; k < contadorVisas - 1; k++) {
                        visas[k] = visas[k + 1];
                    }
                    contadorVisas--;
                    j--; 
                }
            }
            gotoxy(3, 5); textoConColor(11, "Registros borrados exitosamente.");
            break;
        }
    }
    if (!encontrado) {
        gotoxy(3, 7); textoConColor(12, "Viajero no encontrado.");
    }
}

void generarReportes() {
    system("cls");
    cuadro(1, 1, 60, 24);
    int fila = 3;

    gotoxy(3, fila); textoConColor(14, "=== Reporte de Viajeros ===");
    fila += 2;
    for (int i = 0; i < contadorViajeros; i++) {
        gotoxy(3, fila); textoConColor(11, "ID: " + intToStringAlternative(viajeros[i].id));
        fila++;
        gotoxy(3, fila); textoConColor(11, "Nombre: " + viajeros[i].nombre);
        fila++;
        gotoxy(3, fila); textoConColor(11, "Direccion: " + viajeros[i].direccion);
        fila++;
        gotoxy(3, fila); textoConColor(11, "Nacionalidad: " + viajeros[i].nacionalidad);
        fila++;
        gotoxy(3, fila); textoConColor(11, "Fecha de Nacimiento: " + viajeros[i].fechaNacimiento);
        fila++;
        gotoxy(3, fila); textoConColor(11, "Genero: " + viajeros[i].genero);
        fila++;
        gotoxy(3, fila); textoConColor(11, "---------------------------");
        fila++;
    }

    gotoxy(3, fila); textoConColor(14, "=== Reporte de Ingresos ===");
    fila += 2;
    for (int i = 0; i < contadorIngresos; i++) {
        gotoxy(3, fila); textoConColor(11, "ID Viajero: " + intToStringAlternative(ingresos[i].idViajero));
        fila++;
        gotoxy(3, fila); textoConColor(11, "Fecha de Ingreso: " + ingresos[i].fechaIngreso);
        fila++;
        gotoxy(3, fila); textoConColor(11, "Lugar de Ingreso: " + ingresos[i].lugarIngreso);
        fila++;
        gotoxy(3, fila); textoConColor(11, "---------------------------");
        fila++;
    }

    gotoxy(3, fila); textoConColor(14, "=== Reporte de Salidas ===");
    fila += 2;
    for (int i = 0; i < contadorSalidas; i++) {
        gotoxy(3, fila); textoConColor(11, "ID Viajero: " + intToStringAlternative(salidas[i].idViajero));
        fila++;
        gotoxy(3, fila); textoConColor(11, "Fecha de Salida: " + salidas[i].fechaSalida);
        fila++;
        gotoxy(3, fila); textoConColor(11, "Lugar de Salida: " + salidas[i].lugarSalida);
        fila++;
        gotoxy(3, fila); textoConColor(11, "---------------------------");
        fila++;
    }

    gotoxy(3, fila); textoConColor(14, "Presione una tecla para volver al menu");
    cin.ignore(); 
    cin.get();   
}


int main() {
    inicializarCatalogos();
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1:
                agregarViajero();
                break;
            case 2:
                registrarIngreso();
                break;
            case 3:
                registrarSalida();
                break;
            case 4:
                consultarInformacion();
                break;
            case 5:
                borrarRegistros();
                break;
            case 6:
                generarReportes();
                break;
            case 7:
                textoConColor(14, "Saliendo del sistema...");
                Sleep(1000);
                break;
            default:
                textoConColor(12, "Opción no válida. Intente nuevamente.");
                Sleep(1000);
                break;
        }
    } while (opcion != 7);

    return 0;
}




