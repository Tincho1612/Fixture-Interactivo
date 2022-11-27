#ifndef PARTIDOS_H_INCLUDED
#define PARTIDOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#include "time.h"

//para gotoxy:
#include <conio.h>
#include<windows.h>

///ESTRUCTURAS

typedef struct
{

    char nomEquipo[40];
    int tier; ///1,2,3,4
    int clasifica; ///1, 0, -1
    int mp; ///partidos jugados
    int gf;   ///goles a favor
    int ga;  ///goles en contra
    int gd; ///diferencia de goles
    int win;  ///partidos ganados
    int loss;  ///partidos perdidos
    int draw;///partidos empatados
    int pts;  ///puntos totales

} Equipo;

typedef struct nodoEquipo
{
    Equipo equipo;
    struct nodoEquipo* siguiente;

} nodoEquipo;

typedef struct nodoGrupoEquipo
{
    Equipo* equipo;
    struct nodoGrupoEquipo* siguiente;
} nodoGrupoEquipo;

typedef struct
{
    char letra; ///'A','B'....
    struct nodoGrupoEquipo* equipos; ///siempre va a haber 4
} Grupo;

typedef struct
{
    int id; ///opcional
    int fecha; ///eligen ustedes el criterio, el tipo tambien
    Equipo* equipo1;
    Equipo* equipo2;
    int golesEq1;
    int golesEq2;
    int penales1; ///en la fase de grupos no hay penales
    int penales2; ///pueden setearlo en 1 y 0 (como un boolean)
} Partido;

typedef struct nodoPartido
{
    Partido partido;
    struct nodoPartido* siguiente;
} nodoPartido;

typedef struct
{
    char letra;
    nodoPartido* partidos;
} GrupoPartido;

typedef struct
{
    int idFase;
    nodoPartido* partidos;
}Fases;

///PROTOTIPADOS
void pausa ();
void gotoxy(int X,int Y);
void goy(int y);

///EQUIPOS
nodoEquipo* crearNodoEquipo(Equipo dato);
void insertarEquipo(nodoEquipo** lista, Equipo dato);
void pasarEquiposToArchivo();
void mostrarArchivoEquipos();
void pasarEquiposArchiToLista(nodoEquipo** lista);
void mostrarListaEquipos(nodoEquipo* lista);
int buscarClasificarSeleccion (nodoEquipo *lista,char seleccionado[]);
void seleccionarEquipo(nodoEquipo** lista);

///GRUPOS
nodoGrupoEquipo* crearNodoGrupo(Equipo* dato);
void insertarEquipoGrupo(nodoGrupoEquipo** grupo, Equipo* dato);
void cargarGrupos (nodoEquipo* lista,Grupo grupo[]);
void mostrarListaGrupos (nodoGrupoEquipo* lista);
void mostrarGrupo (Grupo grupos[]);

///PARTIDOS
void pasarFechasToArr(int fechas[]);
Partido inicializarPartido(Equipo* equipo1, Equipo* equipo2, Partido aux, int fechas[]);
void campoClasifica(Equipo* equipo1, Equipo* equipo2, Partido* aux);
int calcularProbEquipo(Equipo* equipo);
void calcularProbPartido(Equipo* equipo1, Equipo* equipo2, Partido* aux);
void asignarEstadisticas(Equipo* equipo1, Equipo* equipo2, Partido aux);
Partido partido(Equipo* equipo1, Equipo* equipo2);
void insertarPartidos (nodoPartido** lista,Partido dato);
void mostrarListaPartidos (nodoPartido* partidos);
void mostrarTodosLosPartidosGrupo(GrupoPartido grupos[]);
void jugarConLosSiguientes (nodoGrupoEquipo* lista,nodoPartido** partidos);
void jugarListaDePartidos (nodoGrupoEquipo* lista,nodoPartido** partidos);
void jugarFaseDeGrupo (Grupo selecciones[],GrupoPartido partidos[]);
void tablaGrupo(nodoGrupoEquipo* lista);
void tablaGrupo(nodoGrupoEquipo* lista);
Equipo* retornarPrimero (nodoGrupoEquipo* lista);
Equipo* retornarSegundo (nodoGrupoEquipo* lista);

///FASES
void penalesMS(Partido* aux, int prob1, int prob2);
void ganadorPenales(Equipo* equipo1, Equipo* equipo2, Partido* aux);
void asignarEstadisticasFases(Equipo* equipo1, Equipo* equipo2, Partido* aux);
Partido partidoFases(Equipo* equipo1, Equipo* equipo2) ;
Equipo* recibirGanador(Partido aux);
Equipo* recibirPerdedor(Partido aux);
void cargarFaseOctavos(Grupo selecciones[], Fases Octavos[]);
void cargarFaseCuartos(Fases fases[]);
void cargarFaseSemi(Fases fases[]);
void cargarFaseTercerPuesto(Fases fases[]);
void cargarFaseFinal(Fases fases[]);

void mostrarListaPartidosFases(nodoPartido* lista);
void mostrarArbolAuxOct(nodoPartido* lista);
void mostrarArbolAuxCrt(nodoPartido* lista);
void mostrarArbolAuxSemi(nodoPartido* lista);
void mostrarArbolAuxFinal(nodoPartido* lista);
void mostrarArbol(Fases fases[]);


#endif // PARTIDOS_H_INCLUDED
