#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#include "time.h"
#include "Partidos.h"

int main() {
    system("color C0"); //para ponerle color a la consola
    srand(time(NULL));
    nodoEquipo* equipos=NULL;
    pasarEquiposArchiToLista(&equipos);
    Grupo selecciones[8];
    GrupoPartido partidos[8];
    Fases fases[4];

    while(1) {
        system("cls");
        int MenuInicio = 1;
        int MenuFin = 5;
        int LineaDeInicio = 7;
        int Menu; //Controla el menu seleccionado actualmente
        int flag = 0;

        gotoxy(25,2);
        printf("******************** FIXTURE QATAR 2022 ********************\n\n\n");
        printf("\t\t\tSeleccione una opcion\n\n\n");

        goy(LineaDeInicio);  // Ir a la linea de inicio, debe ir antes del menu seleccionable.

        printf("\t\t\t\t 1- Generar y mostrar grupos\n");
        printf("\t\t\t\t 2- Mostrar partidos de fase de grupos\n");
        printf("\t\t\t\t 3- Mostrar tabla de resultados de fase de grupos\n");
        printf("\t\t\t\t 4- Menu eliminatorias\n");
        printf("\t\t\t\t 5- Cerrar\n");

        Menu = 1;
        goy(LineaDeInicio);
        printf("\t\t---->");

        while(1) {

            Sleep(100); //Retrasar el ciclo

            if(GetAsyncKeyState(VK_UP)) { //Saber si la flecha para arriba fue pulsada

                Menu = Menu == MenuInicio ? MenuFin: --Menu; //Si menu == MenuInicio entonces Menu = MenuFin, sino Menu--.
                printf("\r\t\t     "); // Eliminar la flecha actual
                goy(LineaDeInicio + Menu-1); // Ir a la linea del proximo menu
                printf("\t\t---->"); // Colocar nueva flecha

                }
            else if (GetAsyncKeyState(VK_DOWN)) {

                Menu = Menu == MenuFin ? MenuInicio: ++Menu; // Si menu == MenuFin entonces Menu = Menu Inicio, sino Menu++.
                printf("\r\t\t     ");
                goy(LineaDeInicio + Menu - 1);
                printf("\t\t---->");

                }
            else if (GetAsyncKeyState(VK_RETURN) && flag == 1) {
                break;
                }

            flag = 1;

            }


        switch(Menu) {
            case 1:
                system("cls");

                seleccionarEquipo(&equipos);
                cargarGrupos(equipos,selecciones);
                mostrarGrupo(selecciones);
                jugarFaseDeGrupo(selecciones,partidos);

                pausa();
                break;

            case 2:
                system("cls");
                mostrarTodosLosPartidosGrupo(partidos);
                pausa();
                break;

            case 3:
                system("cls");
                mostrarTablaCompleta(selecciones);
                pausa();
                break;

            case 4:
                cargarFaseOctavos(selecciones, fases);
                cargarFaseCuartos(fases);
                cargarFaseSemi(fases);
                cargarFaseTercerPuesto(fases);
                cargarFaseFinal(fases);

                while(1) {
                    system("cls");
                    !GetAsyncKeyState(VK_RETURN);
                    int MenuInicioE = 1;
                    int MenuFinE = 6;
                    int LineaDeInicioE = 7;
                    int MenuE;

                    gotoxy(25,2);
                    printf("******************** MENU ELIMINATORIAS ********************\n\n\n");
                    printf("\t\t\tSeleccione una opcion\n\n\n");

                    goy(LineaDeInicioE);

                    printf("\t\t\t\t 1-Ver Octavos de Final\n");
                    printf("\t\t\t\t 2-Ver Cuartos de Final\n");
                    printf("\t\t\t\t 3-Ver Semi Final y Tercer Puesto\n");
                    printf("\t\t\t\t 4-Ver Final\n");
                    printf("\t\t\t\t 5-Ver Arbol\n");
                    printf("\t\t\t\t 6-Cerrar\n");

                    MenuE = 1;
                    goy(LineaDeInicioE);
                    printf("\t\t---->");

                    while(1) {

                        Sleep(100); //Retrasar el ciclo

                        if(GetAsyncKeyState(VK_UP)) { //Saber si la flecha para arriba fue pulsada

                            MenuE = MenuE == MenuInicioE ? MenuFinE: --MenuE; //Si menu == MenuInicio entonces Menu = MenuFin, sino Menu--.
                            printf("\r\t\t     "); // Eliminar la flecha actual
                            goy(LineaDeInicioE + MenuE-1); // Ir a la linea del proximo menu
                            printf("\t\t---->"); // Colocar nueva flecha

                            }
                        else if (GetAsyncKeyState(VK_DOWN)) {

                            MenuE = MenuE == MenuFinE ? MenuInicioE: ++MenuE; // Si menu == MenuFin entonces Menu = Menu Inicio, sino Menu++.
                            printf("\r\t\t     ");
                            goy(LineaDeInicioE + MenuE - 1);
                            printf("\t\t---->");

                            }
                        else if (GetAsyncKeyState(VK_RETURN) && flag == 1) {
                            break;
                            }

                        flag = 1;

                        }


                    switch(MenuE) {
                        case 1:
                            system("cls");
                            printf("\n\t PARTIDOS DE OCTAVOS\n");
                            mostrarListaPartidosFases(fases[0].partidos);
                            pausa();
                            break;

                        case 2:
                            system("cls");
                            printf("\n\tPARTIDOS DE CUARTOS\n");
                            mostrarListaPartidosFases(fases[1].partidos);
                            pausa();
                            break;

                        case 3:
                            system("cls");
                            printf("\n\t\tSEMIFINALES\n");
                            mostrarListaPartidosFases(fases[2].partidos);
                            printf("\n\t\tTercer Puesto\n");
                            mostrarListaPartidosFases(fases[3].partidos);
                            pausa();
                            break;

                        case 4:
                            system("cls");
                            printf("\n\t\tFINAL");
                            mostrarListaPartidosFases(fases[4].partidos);
                            pausa();
                            break;

                        case 5:
                            system("cls");
                            mostrarArbol(fases);
                            pausa();
                            break;

                        case 6:
                            break;

                        }
                    if(MenuE == 6) break;
                    }
                break;

            case 5:
                exit(1);
                break;
            }
        }
    return 0;
    }
