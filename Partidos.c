#include "Partidos.h"

int posFechas = 0;

void pausa () { //presiono enter para continuar

    printf("\n");
    system("Pause");
    system("cls");
    }

void gotoxy(int X,int Y) {    // cambia las coordenadas del cursor
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=X;
    dwPos.Y=Y;
    SetConsoleCursorPosition(hcon,dwPos);
    }

void goy(int y) {     //cambia las coordenadas pero solo en el eje y

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);

    }


///EQUIPOS
nodoEquipo* crearNodoEquipo(Equipo dato) {

    nodoEquipo* nuevo = (nodoEquipo*)malloc(sizeof(nodoEquipo));

    nuevo->equipo = dato;
    nuevo->siguiente =NULL;

    return nuevo;
    }

void insertarEquipo(nodoEquipo** lista, Equipo dato) {

    nodoEquipo* seg;
    nodoEquipo* nuevo = crearNodoEquipo(dato);
    if (*lista == NULL) {
        *lista = nuevo;
        }
    else {
        seg = *lista;

        while (seg->siguiente != NULL) {
            seg = seg->siguiente;
            }
        seg->siguiente = nuevo;
        }
    }

void pasarEquiposToArchivo() {

    FILE* fp = fopen("equipos.bin", "wb");
    char continuar = 's';
    Equipo aux;

    if(fp) {

        while(continuar == 's') {

            printf("\nIngrese el nombre del equipo :   ");
            fflush(stdin);
            gets(aux.nomEquipo);
            printf("Ingrese el tier del equipo :   ");
            scanf("%i", &aux.tier);

            aux.gd = 0;
            aux.clasifica = 0;
            aux.mp = 0;
            aux.gf = 0;
            aux.ga = 0;
            aux.win = 0;
            aux.loss = 0;
            aux.draw = 0;
            aux.pts = 0;

            fwrite(&aux, sizeof(Equipo), 1, fp);

            printf("Ingresar otro s/n");
            fflush(stdin);
            scanf("%c", &continuar);

            }
        fclose(fp);
        }

    }

void mostrarArchivoEquipos() {

    FILE* fp = fopen("equipos.bin", "rb");
    Equipo aux;

    if(fp) {

        while(fread(&aux, sizeof(Equipo), 1, fp) > 0) {

            printf("Nombre del equipo :   %s    Tier :   %i\n\n", aux.nomEquipo, aux.tier);

            }
        fclose(fp);
        }
    }

void pasarEquiposArchiToLista(nodoEquipo** lista) {

    FILE* fp = fopen("equipos.bin", "rb");
    Equipo aux;

    if(fp) {

        while(fread(&aux, sizeof(Equipo), 1, fp) > 0) {
            insertarEquipo(lista, aux);
            }
        fclose(fp);
        }
    }

void mostrarListaEquipos(nodoEquipo* lista) {

    nodoEquipo* seg = lista;

    while(seg != NULL) {

        printf("%s",seg->equipo.nomEquipo);
        seg = seg->siguiente;

        }
    }

void seleccionarEquipo(nodoEquipo** lista) {

    char seleccionado[30];
    int encontrado;
    int getAsynckey = 0;
    do {

        printf("\n Ingrese una seleccion valida que quiera:  ");
        fflush(stdin);
        gets(seleccionado);
        encontrado = buscarClasificarSeleccion2(*lista, seleccionado);

        if(encontrado == 0) {

            if(getAsynckey == 0)
                    {
                        system("cls");
                        getAsynckey = 1;
                    }else
                    {
                        printf("\n [!] No se encuentra la seleccion ingresada, intente de nuevo \n");
                        pausa();
                    }

            }

        }
    while (encontrado==0);

    }

int buscarClasificarSeleccion (nodoEquipo *lista,char seleccionado[]) {
    system("cls");
    nodoEquipo* seg = lista;

    while(seg != NULL && strcmpi(seleccionado, seg->equipo.nomEquipo) != 0) {
        seg = seg->siguiente;
        }
    if(seg == NULL) return 0 ;
    else {
        printf("\n\n [ Seleccion de %s ] \n", seleccionado);
        do {
            printf("\n Ingrese (1) si clasifica, (-1) si no clasifica o (0) si la clasificacion es aleatoria: ");
            fflush(stdin);
            scanf("%d",&seg->equipo.clasifica);
            if(seg->equipo.clasifica != 0 && seg->equipo.clasifica != 1 && seg->equipo.clasifica != -1 ) {
                printf(" [!] El valor ingresado debe ser alguna de las opciones mencionadas (1 / 0 / -1), intente de nuevo. \n\n");
                }
            }
        while(seg->equipo.clasifica < (-1) || seg->equipo.clasifica >1 );
        return 1;
        }
    }

int buscarClasificarSeleccion2(nodoEquipo* lista, char seleccionado[]) {

    int MenuInicio = 1;
    int MenuFin = 3;
    int LineaDeInicio = 2;
    nodoEquipo* seg = lista;
    int Menu; //Controla el menu seleccionado actualmente

    while(seg != NULL && strcmpi(seleccionado, seg->equipo.nomEquipo) != 0) {
        seg = seg->siguiente;
        }
    if(seg == NULL) return 0 ;
    else {
        system("cls");
        printf("Indique el resultado en fase de grupos de la seleccion de %s\n\n", seleccionado);

        goy(LineaDeInicio);  // Ir a la linea de inicio, debe ir antes del menu seleccionable.

        printf("\t\t1. Clasifica\n");
        printf("\t\t2. No clasifica\n");
        printf("\t\t3. Aleatorio\n");

        int flag = 0;
        Menu = 1;
        goy(LineaDeInicio);
        printf("---->");

        while(1) {

            Sleep(100); //Retrasar el ciclo

            if(GetAsyncKeyState(VK_UP)) { //Saber si la flecha para arriba fue pulsada

                Menu = Menu == MenuInicio ? MenuFin: --Menu; //Si menu == MenuInicio entonces Menu = MenuFin, sino Menu--.
                printf("\r     "); // Eliminar la flecha actual
                goy(LineaDeInicio + Menu-1); // Ir a la linea del proximo menu
                printf("---->"); // Colocar nueva flecha

                }
            else if (GetAsyncKeyState(VK_DOWN)) {

                Menu = Menu == MenuFin ? MenuInicio: ++Menu; // Si menu == MenuFin entonces Menu = Menu Inicio, sino Menu++.
                printf("\r     ");
                goy(LineaDeInicio + Menu - 1);
                printf("---->");

                }
            else if (GetAsyncKeyState(VK_RETURN) && flag == 1) {
                break;
                }
            flag = 1; //Necesario que no se presione automaticamente el "Enter" al entrar a la funcion.
            }
        printf("\n\n\n\n"); // Para que no se superponga en texto.

        switch(Menu) {

            case 1:
                seg->equipo.clasifica = 1;
                printf("\nEl equipo seleccionado va a pasar la fase de grupos\n");
                pausa();
                break;
            case 2:
                seg->equipo.clasifica = -1;
                printf("\nEl equipo seleccionado no va a pasar la fase de grupos\n");
                pausa();
                break;
            case 3:
                seg->equipo.clasifica = 0;
                printf("\nEl resultado en fase de grupos será aleatorio\n");
                pausa();
                break;

            }
            return 1;
        }
    }

///GRUPOS
nodoGrupoEquipo* crearNodoGrupo(Equipo* dato) {

    nodoGrupoEquipo* nuevo = (nodoGrupoEquipo*)malloc(sizeof(nodoGrupoEquipo));
    nuevo->equipo = dato;
    nuevo->siguiente = NULL;
    return nuevo;

    }

void insertarEquipoGrupo(nodoGrupoEquipo** grupo, Equipo* dato) {

    nodoGrupoEquipo* nuevo = crearNodoGrupo(dato);
    nuevo->siguiente = *grupo;
    *grupo = nuevo;

    }

void cargarGrupos (nodoEquipo* lista,Grupo grupo[]) {

    int letraGrupo = 65; //Codigo ascii

    nodoEquipo* seg = lista;

    for(int i = 0; i<8; i++) {

        grupo[i].letra = letraGrupo;
        nodoGrupoEquipo* aux = NULL;
        for(int j = 0; j<4; j++) {

            nodoGrupoEquipo* nuevo = (nodoGrupoEquipo*)malloc(sizeof(nodoGrupoEquipo));
            nuevo->equipo=&((seg)->equipo);
            nuevo->siguiente = aux;
            aux = nuevo;
            seg = seg->siguiente;

            }
        letraGrupo++;
        grupo[i].equipos = aux;
        }
    }

void mostrarListaGrupos (nodoGrupoEquipo* lista) {

    nodoGrupoEquipo* seg = lista;

    while (seg !=NULL) {
        printf("\n Tier (%i) | %s \n", seg->equipo->tier, seg->equipo->nomEquipo);
        seg=seg->siguiente;
        }
    }

void mostrarGrupo (Grupo grupos[]) {
    int validos=8;
    int i=0;
    while (i < validos) {
        printf("\n____________________________\n");
        printf("          GRUPO %c", grupos[i].letra);
        printf("\n____________________________\n");
        mostrarListaGrupos(grupos[i].equipos);
        i++;
        }
    }


///PARTIDOS
void pasarFechasToArr(int fechas[]) {

    FILE* fp = fopen("Fechas.bin", "rb");
    int aux;
    int i = 0;

    if(fp) {

        while(fread(&aux, sizeof(int), 1, fp) > 0) {

            fechas[i] = aux;
            i++;
            }
        fclose(fp);
        }
    }

Partido inicializarPartido(Equipo* equipo1, Equipo* equipo2, Partido aux, int fechas[]) {

    aux.golesEq1=0;
    aux.golesEq2=0;
    aux.equipo1 = equipo1;
    aux.equipo2 = equipo2;
    aux.penales1 = 0;
    aux.penales2 = 0;
    aux.fecha = fechas[posFechas];
    posFechas++;

    return aux;
    }

void campoClasifica(Equipo* equipo1, Equipo* equipo2, Partido* aux) {

    if(equipo1->clasifica == -1) {
        aux->golesEq2++;
        equipo1->ga++;
        equipo2->gf++;
        }
    else if(equipo1->clasifica == 1) {
        aux->golesEq1++;
        equipo2->ga++;
        equipo1->gf++;
        }
    else if(equipo2->clasifica == -1) {
        aux->golesEq1++;
        equipo2->ga++;
        equipo1->gf++;
        }
    else if(equipo2->clasifica == 1) {
        aux->golesEq2++;
        equipo1->ga++;
        equipo2->gf++;
        }
    }

int calcularProbEquipo(Equipo* equipo) {

    if(equipo->tier == 1) {

        return 40;
        }
    else if(equipo->tier == 2) {
        return 25;
        }
    else if(equipo->tier == 3) {
        return 15;
        }
    else if(equipo->tier ==4) {
        return 5;
        }
    }

void calcularProbPartido(Equipo* equipo1, Equipo* equipo2, Partido* aux) {

    int i = 0;
    int probEquipo1 = calcularProbEquipo(equipo1);
    int probEquipo2 = calcularProbEquipo(equipo2);

    int probSum = probEquipo1+probEquipo2;
    int probSg = 100 - probSum;

    int probAux1 = probSg + probEquipo1;
    int probAux2 = probSg + probEquipo1 + probEquipo2;

    while(i < 6) {
        int prob = rand() % 100;
        if(prob > probSg && prob < probAux1) {
            aux->golesEq1++;
            equipo1->gf++;
            equipo1->gd++;
            equipo2->ga++;
            equipo2->gd--;
            }
        else if(prob > probAux1 && prob < probAux2) {
            aux->golesEq2++;
            equipo2->gf++;
            equipo2->gd++;
            equipo1->ga++;
            equipo1->gd--;
            }
        i++;
        }
    }

void asignarEstadisticas(Equipo* equipo1, Equipo* equipo2, Partido aux) {

    equipo1->mp++;
    equipo2->mp++;
    if(aux.golesEq1 == aux.golesEq2) {
        equipo1->pts++;
        equipo2->pts++;
        equipo1->draw++;
        equipo2->draw++;
        }
    else if(aux.golesEq1 > aux.golesEq2) {
        equipo1->win++;
        equipo1->pts+=3;
        equipo2->loss++;
        }
    else if(aux.golesEq1 < aux.golesEq2) {
        equipo2->win++;
        equipo2->pts+=3;
        equipo1->loss++;
        }
    }

Partido partido(Equipo* equipo1, Equipo* equipo2) {

    Partido aux;

    int fechas[64];
    pasarFechasToArr(fechas);

    aux = inicializarPartido(equipo1, equipo2, aux, fechas);

    if(equipo1->clasifica != 0 || equipo2->clasifica != 0) {
        campoClasifica(equipo1, equipo2, &aux);
        }
    else {
        calcularProbPartido(equipo1, equipo2, &aux);
        }

    asignarEstadisticas(equipo1, equipo2, aux);

    return aux;
    }

void insertarPartidos (nodoPartido** lista,Partido dato) {

    nodoPartido* nuevo = (nodoPartido*)malloc(sizeof(nodoPartido));
    nuevo->partido=dato;
    nuevo->siguiente=NULL;

    if (*lista == NULL) {
        *lista=nuevo;
        }
    else {
        nodoPartido* seg=*lista;
        while (seg->siguiente !=NULL) {
            seg=seg->siguiente;
            }
        seg->siguiente=nuevo;
        }
    }

void mostrarListaPartidos (nodoPartido* partidos) {

    nodoPartido* seg = partidos;
    while (seg!=NULL) {

        printf(".......................................%i................\n",seg->partido.fecha);
        printf("  [%i] \t\t%s\n",seg->partido.golesEq1, seg->partido.equipo1);
        printf("  [%i] \t\t%s\n",seg->partido.golesEq2, seg->partido.equipo2);

        seg=seg->siguiente;
        }
    }

void mostrarTodosLosPartidosGrupo(GrupoPartido grupos[]) {

    int i = 0;

    printf("\n\t\t   [PARTIDOS FASE DE GRUPO]\n");
    while(i < 8) {
        printf("\n______________________________________________________________");
        printf("\n Goles     |    Equipos          |     Fecha     |  GRUPO %c", grupos[i].letra);
        printf("\n______________________________________________________________\n");

        mostrarListaPartidos(grupos[i].partidos);
        i++;
        }
    }

void jugarConLosSiguientes (nodoGrupoEquipo* lista,nodoPartido** partidos) {
    Partido aux;
    nodoGrupoEquipo* seg=lista->siguiente;
    while (seg != NULL) {
        aux=partido(lista->equipo,seg->equipo);
        insertarPartidos(partidos,aux);
        seg=seg->siguiente;
        }
    }

void jugarListaDePartidos (nodoGrupoEquipo* lista,nodoPartido** partidos) {
    nodoGrupoEquipo* seg=lista;
    for (int i=0; i<4; i++) {
        jugarConLosSiguientes(seg,partidos);
        seg=seg->siguiente;
        }

    }

void jugarFaseDeGrupo (Grupo selecciones[],GrupoPartido partidos[]) {

    for (int i=0; i<8; i++) {
        partidos[i].partidos=NULL;
        partidos[i].letra=selecciones[i].letra;
        jugarListaDePartidos(selecciones[i].equipos,&(partidos[i].partidos));
        }
    }

void tablaGrupo(nodoGrupoEquipo* lista) {

    nodoGrupoEquipo* seg = lista;

    while (seg !=NULL) {

        printf("\n  [%i]\t   [%i]\t [%i]\t[%i]\t[%i]\t[%i]\t[%i]\t%s", seg->equipo->pts, seg->equipo->gf, seg->equipo->ga, seg->equipo->gd, seg->equipo->win,seg->equipo->loss, seg->equipo->draw, seg->equipo->nomEquipo);

        seg=seg->siguiente;
        }
    }

void mostrarTablaCompleta (Grupo grupos[]) {

    int validos=8;
    int i=0;

    printf("\n\t\t   [RESULTADOS FASE DE GRUPOS]\n");

    while (i < validos) {
        printf("\n____________________________________________________________________\n");
        printf("\n\t\t\t   GRUPO   %c", grupos[i].letra);
        printf("\n____________________________________________________________________\n");
        printf(" Puntos     GF    GA    GD       W       L       D      Equipo");
        printf("\n....................................................................\n");
        tablaGrupo(grupos[i].equipos);
        printf("\n \n");
        i++;
        }
    }

Equipo* retornarPrimero (nodoGrupoEquipo* lista) {

    nodoGrupoEquipo* seg = lista;
    Equipo* primero=seg->equipo;
    seg = seg->siguiente;

    while (seg != NULL) {
        if (primero->pts < seg->equipo->pts) {
            primero=seg->equipo;
            }
        else if (primero->pts == seg->equipo->pts) {
            if (primero->gd < seg->equipo->gd) {
                primero=seg->equipo;
                }
            else if (primero->gf < seg->equipo->gf) {
                primero=seg->equipo;
                }
            }
        seg=seg->siguiente;
        }
    return primero;
    }

Equipo* retornarSegundo (nodoGrupoEquipo* lista) {

    nodoGrupoEquipo* seg = lista;
    Equipo* primero = retornarPrimero(seg);
    Equipo* segundo = seg->equipo;
    int puntosMax = 0;

    while (seg != NULL) {
        if(strcmp(seg->equipo->nomEquipo, primero->nomEquipo) ==0) {
            seg = seg->siguiente;
            }
        else {
            if(strcmp(seg->equipo->nomEquipo, primero->nomEquipo) !=0) {
                if (puntosMax < seg->equipo->pts) {
                    puntosMax = seg->equipo->pts;
                    segundo=seg->equipo;
                    }
                else if (segundo->pts == seg->equipo->pts) {
                    if (segundo->gd < seg->equipo->gd) {
                        segundo=seg->equipo;
                        }
                    else if (segundo->gf < seg->equipo->gf) {
                        segundo=seg->equipo;
                        }
                    }
                }
            seg=seg->siguiente;
            }
        }
    return segundo;
    }


///FASES
void penalesMS(Partido* aux, int prob1, int prob2) {
    int i = 0;
    int probTotal = prob1 + prob2;
    while(1) {
        i = 0;
        while(i < 1) {
            int prob = rand() % probTotal;
            if(prob < prob1) aux ->penales1++;
            i++;
            }
        i=0;
        while(i < 1) {
            int prob = rand() % probTotal;
            if(prob > prob1 && prob < probTotal) aux ->penales2++;
            i++;
            }
        if(aux->penales1 > aux->penales2 || aux->penales1 < aux->penales2) {
            break;
            }
        }
    }

void ganadorPenales(Equipo* equipo1, Equipo* equipo2, Partido* aux) {

    int prob1 = calcularProbEquipo(equipo1);
    int prob2 = calcularProbEquipo(equipo2);
    int i = 0;
    int probTotal = prob1 + prob2;

    while(i < 5) {
        int prob = rand() % probTotal;

        if(prob < prob1) {
            aux->penales1++;
            }
        i++;
        }
    i = 0;
    while(i < 5) {
        int prob = rand() % probTotal;

        if(prob > prob1 && prob < probTotal) {
            aux->penales2++;
            }
        i++;
        }
    if(aux->penales1 == aux->penales2) {
        penalesMS(aux, prob1, prob2);
        }
    }

void asignarEstadisticasFases(Equipo* equipo1, Equipo* equipo2, Partido* aux) {

    equipo1->mp++;
    equipo2->mp++;
    if(aux->golesEq1 == aux->golesEq2) {
        ganadorPenales(equipo1, equipo2, aux);

        if(aux->penales1 > aux->penales2) {
            equipo1->win++;
            equipo2->loss++;
            }
        else {
            equipo2->win++;
            equipo1->loss++;
            }
        }
    else if(aux->golesEq1 > aux->golesEq2) {
        equipo1->win++;
        equipo2->loss++;
        }
    else if(aux->golesEq1 < aux->golesEq2) {
        equipo2->win++;
        equipo1->loss++;
        }
    }

Partido partidoFases(Equipo* equipo1, Equipo* equipo2) {

    Partido aux;

    int fechas[64];
    pasarFechasToArr(fechas);

    aux = inicializarPartido(equipo1, equipo2, aux, fechas);

    calcularProbPartido(equipo1, equipo2, &aux);

    asignarEstadisticasFases(equipo1, equipo2, &aux);

    return aux;
    }

Equipo* recibirGanador(Partido aux) {
    if(aux.golesEq1 == aux.golesEq2) {
        if(aux.penales1 > aux.penales2) return aux.equipo1;
        else return aux.equipo2;
        }
    else if(aux.golesEq1 > aux.golesEq2) return aux.equipo1;
    else if(aux.golesEq1 < aux.golesEq2) return aux.equipo2;
    }

Equipo* recibirPerdedor(Partido aux) {
    if(aux.golesEq1 == aux.golesEq2) {
        if(aux.penales1 < aux.penales2) return aux.equipo1;
        else return aux.equipo2;
        }
    else if(aux.golesEq1 < aux.golesEq2) return aux.equipo1;
    else if(aux.golesEq1 > aux.golesEq2) return aux.equipo2;
    }

void cargarFaseOctavos(Grupo selecciones[], Fases Octavos[]) { //cargarFaseOctavos(selecciones, fases[0]); call

    Octavos[0].idFase = 8;
    Octavos[0].partidos = NULL;
    Equipo* primeroA=retornarPrimero(selecciones[0].equipos);
    Equipo* segundoA= retornarSegundo(selecciones[0].equipos);
    Equipo* primeroB = retornarPrimero(selecciones[1].equipos);
    Equipo* segundoB = retornarSegundo(selecciones[1].equipos);
    Equipo* primeroC= retornarPrimero(selecciones[2].equipos);
    Equipo* segundoC= retornarSegundo(selecciones[2].equipos);
    Equipo* primeroD = retornarPrimero(selecciones[3].equipos);
    Equipo* segundoD = retornarSegundo (selecciones[3].equipos);
    Equipo* primeroE = retornarPrimero(selecciones[4].equipos);
    Equipo* segundoE = retornarSegundo(selecciones[4].equipos);
    Equipo* primeroF = retornarPrimero(selecciones[5].equipos);
    Equipo* segundoF = retornarSegundo(selecciones[5].equipos);
    Equipo* primeroG = retornarPrimero(selecciones[6].equipos);
    Equipo* segundoG = retornarSegundo(selecciones[6].equipos);
    Equipo* primeroH = retornarPrimero(selecciones[7].equipos);
    Equipo* segundoH = retornarSegundo(selecciones[7].equipos);
    Partido primerPartido = partidoFases(primeroA,segundoB);
    insertarPartidos(&(Octavos[0].partidos), primerPartido);
    Partido segundoPartido = partidoFases(primeroC,segundoD);
    insertarPartidos(&(Octavos[0].partidos), segundoPartido);
    Partido tercerPartido = partidoFases(primeroE,segundoF);
    insertarPartidos(&(Octavos[0].partidos), tercerPartido);
    Partido cuartoPartido = partidoFases(primeroG,segundoH);
    insertarPartidos(&(Octavos[0].partidos), cuartoPartido);
    Partido quintoPartido = partidoFases(primeroB,segundoA);
    insertarPartidos(&(Octavos[0].partidos), quintoPartido);
    Partido sextoPartido = partidoFases(primeroD,segundoC);
    insertarPartidos(&(Octavos[0].partidos), sextoPartido);
    Partido septimoPartido = partidoFases(primeroF,segundoE);
    insertarPartidos(&(Octavos[0].partidos), septimoPartido);
    Partido octavoPartido = partidoFases(primeroH,segundoG);
    insertarPartidos(&(Octavos[0].partidos), octavoPartido);
    }

void cargarFaseCuartos(Fases fases[]) {

    fases[1].idFase = 4;
    fases[1].partidos = NULL;

    nodoPartido* seg = fases[0].partidos;

    while(seg != NULL) {
        Equipo* equipo1 = recibirGanador(seg->partido);
        seg = seg->siguiente;
        Equipo* equipo2 = recibirGanador(seg->partido);
        Partido partido = partidoFases(equipo1, equipo2);

        insertarPartidos(&(fases[1].partidos), partido);

        seg = seg->siguiente;
        }
    }

void cargarFaseSemi(Fases fases[]) {

    fases[2].idFase = 2;
    fases[2].partidos = NULL;

    nodoPartido* seg = fases[1].partidos;

    while(seg != NULL) {

        Equipo* equipo1 = recibirGanador(seg->partido);
        seg = seg->siguiente;
        Equipo* equipo2 = recibirGanador(seg->partido);
        Partido partido = partidoFases(equipo1, equipo2);

        insertarPartidos(&(fases[2].partidos), partido);

        seg = seg->siguiente;
        }
    }

void cargarFaseTercerPuesto(Fases fases[]) {

    fases[3].idFase = 3;
    fases[3].partidos = NULL;

    nodoPartido* seg = fases[2].partidos;

    Equipo* equipo1 = recibirPerdedor(seg->partido);
    seg = seg->siguiente;
    Equipo* equipo2 = recibirPerdedor(seg->partido);

    Partido partido = partidoFases(equipo1, equipo2);

    insertarPartidos(&(fases[3].partidos), partido);
    }

void cargarFaseFinal(Fases fases[]) {

    fases[4].idFase = 1;
    fases[4].partidos = NULL;

    nodoPartido* seg = fases[2].partidos;

    Equipo* equipo1 = recibirGanador(seg->partido);
    seg = seg->siguiente;
    Equipo* equipo2 = recibirGanador(seg->partido);

    Partido partido = partidoFases(equipo1, equipo2);

    insertarPartidos(&(fases[4].partidos), partido);

    }

void mostrarListaPartidosFases(nodoPartido* lista) {

    nodoPartido* seg = lista;
    while(seg != NULL) {
        printf("\n___________________________________________");
        printf("\n Goles   |   Penales    |   Equipos ");
        printf("\n___________________________________________");
        printf("\n [%i]\t \t(%i)\t     %s",  seg->partido.golesEq1,  seg->partido.penales1, seg->partido.equipo1->nomEquipo);
        printf("\n [%i]\t \t(%i)\t     %s \n\n",  seg->partido.golesEq2,  seg->partido.penales2, seg->partido.equipo2->nomEquipo);

        seg = seg->siguiente;
        }
    }

void mostrarArbolAuxOct(nodoPartido* lista) {//es la mas extensa
    nodoPartido* seg = lista;

    if(seg!=NULL) {
        gotoxy(1, 2);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(1, 3);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(1, 6);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(1, 7);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(1, 11);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(1, 12);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(1, 15);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(1, 16);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(1, 20);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(1, 21);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(1, 24);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(1, 25);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(1, 29);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(1, 30);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(1, 33);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(1, 34);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);

        gotoxy(26, 4);
        printf("|_________");
        gotoxy(26, 5);
        printf("|");
        gotoxy(26, 13);
        printf("|__________");
        gotoxy(26, 14);
        printf("|");
        gotoxy(26, 22);
        printf("|__________");
        gotoxy(26, 23);
        printf("|");
        gotoxy(26, 31);
        printf("|__________");
        gotoxy(26, 32);
        printf("|");
        }
    }

void mostrarArbolAuxCrt(nodoPartido* lista) {

    nodoPartido* seg = lista;

    if(seg!=NULL) {
        gotoxy(35, 4);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(35, 5);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(35, 13);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(35, 14);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(35, 22);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(35, 23);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(35, 31);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(35, 32);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);

        gotoxy(58, 9);
        printf("__________");
        gotoxy(58, 27);
        printf("__________");

        for (int i=6; i<13; i++) {
            gotoxy(58, i);
            printf("|");
            }
        for(int j=24; j<31; j++) {
            gotoxy(58, j);
            printf("|");
            }

        }
    }

void mostrarArbolAuxSemi(nodoPartido* lista) {

    nodoPartido* seg = lista;

    if(seg!=NULL) {
        gotoxy(67, 9);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(67, 10);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);
        seg=seg->siguiente;

        gotoxy(67, 27);
        printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
        gotoxy(67, 28);
        printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);

        gotoxy(87, 17);
        printf("__________");

        for (int i=11; i<27; i++) {
            gotoxy(87, i);
            printf("|");
            }
        }
    }

void mostrarArbolAuxFinal(nodoPartido* lista) {

    nodoPartido* seg = lista;

    gotoxy(98, 17);
    printf("[%i   %s  (%i)", seg->partido.golesEq1, seg->partido.equipo1->nomEquipo, seg->partido.penales1);
    gotoxy(98, 18);
    printf("[%i   %s  (%i)", seg->partido.golesEq2, seg->partido.equipo2->nomEquipo, seg->partido.penales2);

    }

void mostrarArbol(Fases fases[]) {

    mostrarArbolAuxOct(fases[0].partidos);
    mostrarArbolAuxCrt(fases[1].partidos);
    mostrarArbolAuxSemi(fases[2].partidos);
    mostrarArbolAuxFinal(fases[4].partidos);
    gotoxy(1, 35);
    }

