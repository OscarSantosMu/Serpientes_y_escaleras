#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

///El contador es para el numero de jugador
int contador=0;
///auxiliar para verificar que sea mayor
int aux;
///Valor auxiliar para borrar booleano del jugador en casilla anterior
int casillaanterior;
///Auxiliares de cada dado y valor del dado global
int auxdado1,auxdado2,suma;
///Turno del jugador
int turnoJugador=1;
///Valor inicial para que se niegue el ingreso de jugadores menores a 2 y mayores a 4
int jugadores=1;


///Informacion del jugador
struct nodo
{
    int NumcasillaJugador;
    int NumJugador;
    string NombreJugador;
    nodo *sig;
};

nodo *inicio = NULL;

///Estructura para el tablero, para cada casilla
struct Nodo
{
    int Numcasilla;
    int x;
    int y;
    bool Jugador_en_casilla;
    bool colaSerpiente;
    bool cabezaSerpiente;
    bool inicioEscalera;
    bool finEscalera;
    Nodo *avanza;
    Nodo *especial;
};

Nodo *tablero = NULL;

Nodo *creaNodo(int cont)                ///Crea nuevos nodos
{
    Nodo *nuevo_nodo = new Nodo();      ///Reserva espacio para un nodo
    nuevo_nodo->Numcasilla = cont;
    nuevo_nodo->Jugador_en_casilla = NULL;
    nuevo_nodo->cabezaSerpiente = false;
    nuevo_nodo->colaSerpiente = false;
    nuevo_nodo->inicioEscalera = false;
    nuevo_nodo->finEscalera = false;
    nuevo_nodo->avanza = NULL;
    nuevo_nodo->especial = NULL;
    return nuevo_nodo;
}

Nodo *insertarNodo(Nodo *&tablero, int cont)    ///Va insertando y enlazando los nodos
{
    if(tablero==NULL)
    {
        Nodo *nuevo_nodo = creaNodo(cont);
        tablero = nuevo_nodo;
    }
    else
    {
        insertarNodo(tablero->avanza,cont);
    }
}

Nodo *busqueda(Nodo *tablero,int buscarCasilla)     ///Busqueda de alguna casilla del tablero
{
    if(tablero==NULL)
    {
        return false;
    }
    else
    {
        if(buscarCasilla==tablero->Numcasilla)
        {
            cout << "La casilla " << tablero->Numcasilla << " cambia su valor booleano" << endl;
            return tablero;
        }
        else
        {
            cout << "Esta buscando en la casilla " << tablero->Numcasilla << endl;
            return busqueda(tablero->avanza,buscarCasilla);
        }
    }
}

nodo *buscarElemento(nodo *inicio,int buscar)       ///Busqueda de algun jugador
{
    if(inicio==NULL)
    {
        return false;
    }
    else
    {
        if(buscar=inicio->NumJugador)
        {
            cout << "Numero de jugador " << inicio->NumJugador << " encontrado en la busqueda" << endl;
            return inicio;
        }
        else
        {
            cout << "Esta buscando en la casilla del jugador " << inicio->NumJugador << endl;
            return buscarElemento(inicio->sig,buscar);
        }
    }
}

int dado()
{
    int valor;
    valor = rand()%6 + 1;
    auxdado1 = valor;
    cout << "Dado1: " << valor;
    return valor;
}

int dado2()
{
    int valor;
    valor = rand()%6 + 1;
    auxdado2 = valor;
    cout << " + Dado2: " << valor << endl;
    return valor;
}

nodo *creaNodoJug(string Nombre)        ///Agrega jugadores
{
    nodo *nuevo_nodo = new nodo();      ///Reserva espacio para un nodo
    contador++;
    nuevo_nodo->NumcasillaJugador = 1;
    nuevo_nodo->NumJugador = contador;
    nuevo_nodo->NombreJugador = Nombre;
    nuevo_nodo->sig = NULL;
    return nuevo_nodo;
}

nodo *insertarNodoJug(nodo *&inicio, string Nombre)     ///Inserta y va enlazando los nodos
{
    if(inicio==NULL)
    {
        nodo *nuevo_nodo = creaNodoJug(Nombre);
        inicio = nuevo_nodo;
    }
    else
    {
        insertarNodoJug(inicio->sig,Nombre);
    }
}

void imprimir(nodo *inicio)     ///Imprime la informacion de los jugadores
{
    int tamano = 0;
    while(inicio!=NULL)
    {
        cout << "\nNumero de jugador: " << inicio->NumJugador;
        cout << "\nNombre del jugador: " << inicio->NombreJugador;
        cout << "\nNumero de casilla: " << inicio->NumcasillaJugador;
        inicio = inicio->sig;
        tamano++;
        cout << "\n";
    }
    if(tamano==0)
    {
        cout << "Lista vacia, ingrese jugadores" << endl;
    }
    else
    {
        cout << "\nJugadores que se agregaron exitosamente" << endl;
    }
}

void mostrarNodo(Nodo *tablero)     ///Muestra toda la informacion de las casillas del tablero
{
    int contadorlista = 0;
    while(tablero->avanza!=NULL)
    {
        cout << "\n\nNumero de Casilla: " << tablero->Numcasilla << endl;
        cout << "Esta casilla tiene un booleano para colaserpiente de " << tablero->colaSerpiente << endl;
        cout << "Esta casilla tiene un booleano para cabezaserpiente de " << tablero->cabezaSerpiente << endl;
        cout << "Esta casilla tiene un booleano para inicioescalera de " << tablero->inicioEscalera << endl;
        cout << "Esta casilla tiene un booleano para finescalera de " << tablero->finEscalera << endl;
        cout << "Esta casilla tiene un booleano para Jugador_en_casilla de " << tablero->Jugador_en_casilla << endl;
        cout << "Su valor en x es " << tablero->x << endl;
        cout << "Su valor en y es " << tablero->y << endl;
        if(tablero->especial != NULL)
        {
            cout << "Su siguiente especial es : " << tablero->especial->Numcasilla << endl;
        }
        cout << "Su siguiente es " << tablero->avanza->Numcasilla << endl;
        tablero=tablero->avanza;
        contadorlista++;
    }
    if(contadorlista==0)
    {
        cout << "Lista vacia";
    }
}

void insertarSerpiente(Nodo *tablero, int serpientes)       ///Agrega booleanos a las casillas
{
    srand (time(NULL));
    for(int i=0;i<serpientes;i++)
    {
        ///Encuentra una casilla vacia para la cabeza (todos NULL)
        Nodo *cabeza;
        do
        {
        int valorrand = (rand()%69) +2;    ///Este rand asigna la casilla donde estaran las cabezas (entre 2 y 70)
        cout << "El valor del rand cabeza fue " << valorrand << endl;
        aux = valorrand;
        cabeza = busqueda(tablero,valorrand);
        }while(cabeza->colaSerpiente == true || cabeza->cabezaSerpiente == true || cabeza->inicioEscalera == true || cabeza->finEscalera == true);
        cabeza->cabezaSerpiente = true;
        cout << "Booleano de cabezaSerpiente es " << cabeza->cabezaSerpiente << endl;

        ///Encuentra una casilla vacia para la cola (todos NULL)
        Nodo *cola;
        do
        {
            int valorrand = 0;
            while(valorrand<aux)
            {
                valorrand = (rand()%77) +20;   ///Este rand asigna la casilla donde estaran las colas (entre 20 y 96)
            }
            cout << "El valor del rand cola fue " << valorrand << endl;
            cola = busqueda(tablero,valorrand);
        }while(cola->colaSerpiente == true || cola->cabezaSerpiente == true || cola->inicioEscalera == true || cola->finEscalera == true);
        cola->colaSerpiente = true;
        cout << "Valor de colaSerpiente es " << cola->colaSerpiente << endl;
        ///Enlazamos las direcciones de memoria
        cola->especial = cabeza;
    }
}

void insertarEscaleras(Nodo *tablero,int escaleras)         ///Agrega booleanos a las casillas
{
    srand (time(NULL));
    for(int i=0;i<escaleras;i++)
    {
        ///Encuentra una casilla vacia para el inicio de la escalera (todos NULL)
        Nodo *empieza;
        do
        {
        int valorrand = (rand()%69) +2;    ///Este rand asigna la casilla donde empieza la escalera (entre 2 y 70)
        cout << "El valor del rand empieza fue " << valorrand << endl;
        aux = valorrand;
        empieza = busqueda(tablero,valorrand);
        }while(empieza->colaSerpiente == true || empieza->cabezaSerpiente == true || empieza->inicioEscalera == true || empieza->finEscalera == true);
        empieza->inicioEscalera = true;
        cout << "Booleano de inicioEscalera es " << empieza->inicioEscalera << endl;

        ///Encuentra una casilla vacia para el fin de la escalera (todos NULL)
        Nodo *termina;
        do
        {
            int valorrand = 0;
            while(valorrand<aux)
            {
                valorrand = (rand()%77) +20;   ///Este rand asigna la casilla donde estara el fin de la escalera (entre 20 y 96)
            }
            cout << "El valor del rand termina fue " << valorrand << endl;
            termina = busqueda(tablero,valorrand);
        }while(termina->colaSerpiente == true || termina->cabezaSerpiente == true || termina->inicioEscalera == true || termina->finEscalera == true);
        termina->finEscalera = true;
        cout << "Valor de finEscalera es " << termina->finEscalera << endl;
        ///Enlazamos las direcciones de memoria
        empieza->especial = termina;
    }
}

void movimiento(nodo *inicio, Nodo *tablero, int turno)         ///Va moviendo los jugadores segun el turno que toque
{
    int suma,i,bandera=0;
    nodo *aux = inicio;
    Nodo *aux2 = tablero;
    Nodo *aux3 = tablero;
    Nodo *aux4 = tablero;
    while(aux!=NULL)
    {
        if(aux->NumJugador==turno)
        {
            cout << "Le toca a " << aux->NombreJugador << endl;
            suma = dado() + dado2();
            cout << "El valor del dado es " << suma << endl;
            casillaanterior = aux->NumcasillaJugador;
            cout << "Su casilla anterior es " <<casillaanterior << endl;
            aux->NumcasillaJugador += suma;
            ///Si se pasa de 100 entonces retrocede
            if(aux->NumcasillaJugador>100)
                aux->NumcasillaJugador = 200-aux->NumcasillaJugador;
            ///Busca casilla del tablero
            aux2 = busqueda(tablero,aux->NumcasillaJugador);
            ///Enlaza NumCasillaJugador de estructura nodo con NumCasilla de estructura Nodo
            aux2->Numcasilla = aux->NumcasillaJugador;

//            if(aux2->Jugador_en_casilla==true)
//            {
//                cout << "Si entre al if de la casilla" << endl;
//                aux3 = busqueda(tablero,casillaanterior);
//                cout << "La casilla a regresar es " << aux3->Numcasilla << endl;
//                aux = buscarElemento(inicio,!aux->NumJugador);
//                cout << "El jugador a mover es " << aux->NombreJugador << endl;
//                aux->NumcasillaJugador = aux3->Numcasilla;
//
//                bandera=1;
////                aux2->Numcasilla = aux->NumcasillaJugador;
////                switch(turno)
////                {
////                case 1:
////                    setcolor(1);
////                    circle(aux2->x-10,aux2->y-10,16);
////                    delay(500);
////                    setcolor(0);
////                    circle(aux2->x-10,aux2->y-10,16);
////                    delay(500);
////                    setcolor(1);
////                    circle(aux3->x-10,aux3->y-10,16);
////                    break;
////                case 2:
////                    setcolor(3);
////                    circle(aux2->x-10,aux2->y-10,16);
////                    delay(500);
////                    setcolor(0);
////                    circle(aux2->x-10,aux2->y-10,16);
////                    delay(500);
////                    setcolor(3);
////                    circle(aux3->x-10,aux3->y-10,16);
////                    break;
////
////                }
//
//            }
            if(bandera==0)
            {
                cout << "Casilla del tablero donde se puso jugador " << aux2->Numcasilla << endl;
                cout << "Valor booleano de la casilla " << aux2->Numcasilla << " antes de poner true es " << aux2->Jugador_en_casilla << endl;
                aux2->Jugador_en_casilla = true;
                cout << "Valor booleano de la casilla " << aux2->Numcasilla << " es " << aux2->Jugador_en_casilla << endl;
                cout << "Casilla del jugador " << aux->NumJugador << " es " << aux->NumcasillaJugador << endl;

                ///Buscamos casilla del tablero de la casilla anterior
                aux3 = busqueda(tablero,casillaanterior);
                cout << "Valor booleano de la casilla " << aux3->Numcasilla << " antes de poner false es " << aux3->Jugador_en_casilla << endl;
                aux3->Jugador_en_casilla = false;
                cout << "Valor booleano de la casilla " << aux3->Numcasilla << " es " << aux3->Jugador_en_casilla << endl;
            }

            if((aux2->colaSerpiente)==true || (aux2->inicioEscalera)==true)
            {
                cout << "Si entre al if especial" << endl;
                aux4 = aux3;
                casillaanterior = aux2->Numcasilla;
                aux2 = aux2->especial;
                ///Enlazamos casilla del tablero nueva y casilla del jugador
                aux->NumcasillaJugador = aux2->Numcasilla;
                cout << "Casilla del tablero donde se puso jugador " << aux2->Numcasilla << endl;
                cout << "Valor booleano de la casilla " << aux2->Numcasilla << " antes de poner true es " << aux2->Jugador_en_casilla << endl;
                aux2->Jugador_en_casilla = true;
                cout << "Valor booleano de la casilla " << aux2->Numcasilla << " es " << aux2->Jugador_en_casilla << endl;
                cout << "Casilla del jugador " << aux->NumJugador << " es " << aux->NumcasillaJugador << endl;

                ///Buscamos casilla del tablero de la casilla anterior
                aux3 = busqueda(tablero,casillaanterior);
                cout << "Valor booleano de la casilla " << aux3->Numcasilla << " antes de poner false es " << aux3->Jugador_en_casilla << endl;
                aux3->Jugador_en_casilla = false;
                cout << "Valor booleano de la casilla " << aux3->Numcasilla << " es " << aux3->Jugador_en_casilla << endl;
            }
            ///Se hace el movimiento grafico
//            aux3 = busqueda(tablero,casillaanterior);
            cout << "Las coordenadas de x son: " << aux3->x << " hasta " << aux2->x << endl;
            cout << "Las coordenadas de y son: " << aux3->y << " hasta " << aux2->y << endl;
//            for(i=aux3->x;i>=aux2->x;i--)
//            {
                switch(turno)
                {
                case 1:
                    setcolor(1);
                    circle(aux3->x-10,aux3->y-10,16);
                    delay(500);
                    setcolor(0);
                    circle(aux3->x-10,aux3->y-10,16);
                    circle(aux4->x-10,aux4->y-10,16);
                    delay(500);
                    setcolor(1);
                    circle(aux2->x-10,aux2->y-10,16);
                    break;
                case 2:
                    setcolor(3);
                    circle(aux3->x+10,aux3->y-10,16);
                    delay(500);
                    setcolor(0);
                    circle(aux3->x+10,aux3->y-10,16);
                    circle(aux4->x+10,aux4->y-10,16);
                    delay(500);
                    setcolor(3);
                    circle(aux2->x+10,aux2->y-10,16);
                    break;
                case 3:
                    setcolor(5);
                    circle(aux3->x-3,aux3->y-10,16);
                    delay(500);
                    setcolor(0);
                    circle(aux3->x-3,aux3->y-10,16);
                    circle(aux4->x-3,aux4->y-10,16);
                    delay(500);
                    setcolor(5);
                    circle(aux2->x-3,aux2->y-10,16);
                    break;
                case 4:
                    setcolor(6);
                    circle(aux3->x+3,aux3->y-10,16);
                    delay(500);
                    setcolor(0);
                    circle(aux3->x+3,aux3->y-10,16);
                    circle(aux4->x+3,aux4->y-10,16);
                    delay(500);
                    setcolor(6);
                    circle(aux2->x+3,aux2->y-10,16);
                    break;
                }
            if(bandera==1)
                return;
//            }
        }
        aux = aux->sig;
    }
}

void menu()
{
    string Nombre;
    int Op, escaleras, serpientes, flag=0;
    srand (time(NULL));
    do
    {
        cout << "\nElija una opcion:\n";
        cout << "1. Numero de jugadores.\n";
        cout << "2. Numero de serpientes.\n";
        cout << "3. Numero de escaleras.\n";
        cout << "4. Mostrar informacion de los jugadores.\n";
        cout << "5. Empezar a jugar.\n";
        cout << "6. Salir del juego.\n";
        cin >> Op;
        switch(Op)
        {
        case 1:
            do
            {
                cout << "Ingrese la cantidad de jugadores (2-4 jugadores): ";
                cin >> jugadores;
                if(jugadores>=2 && jugadores<=4)
                    break;
                if(flag==0)
                    {
                        cout << "Ingrese un numero de jugadores valido" << endl;
                        system("pause");
                        system("cls");
                        menu();
                    }
            }while(jugadores<2 || jugadores>4);
            for(int i=1;i<=jugadores;i++)
            {
                cout << "Ingrese nombre del jugador " << i << " : ";
                cin >> Nombre;
                insertarNodoJug(inicio,Nombre);
            }
            imprimir(inicio);
            system("pause");
            system("cls");
            break;
        case 2:
            cout << "Ingrese el numero de serpientes que tendra el juego: ";
            cin >> serpientes;
            insertarSerpiente(tablero,serpientes);
            mostrarNodo(tablero);
            system("pause");
            break;
        case 3:
            cout << "Ingrese el numero de escaleras que tendra el juego: ";
            cin >> escaleras;
            insertarEscaleras(tablero,escaleras);
            mostrarNodo(tablero);
            system("pause");
            break;
        case 4:
            imprimir(inicio);
            system("pause");
            system("cls");
            break;
        case 5:
            if(inicio==NULL)
            {
                cout << "Primero ingrese jugadores" << endl;
                system("pause");
                system("cls");
                menu();
            }
            system("cls");
            Op=6;
            break;
        case 6:
            exit(0);
            break;
        }
        system("cls");
    }while(Op!=6);
}

void indicaciones()
{
    cout<<"INSTRUCCIONES"<<endl;
    cout<<"SERPIENTES Y ESCALERAS C++"<<endl<<endl;
    cout<<"Serpientes y Escaleras es un didactico juego semejante al juego en ingles de Chutes and Ladders. Se piensa que su origen se da en la India aunque no se sabe con certeza cuando."<<endl<<endl;
    cout<<"Este juego de etica fue creado, presumiblemente por hindues para enseñar a los niños sobre religion. Aunque en la actualidad se utiliza con fines didacticos; en algunos casos para enseñar a contar o para enseñar a identificar palabras."<<endl<<endl;
    cout<<"El juego de Serpientes y Escaleras se juega en un tablero,  las escaleras estan dibujadas al pie de cuadros que permiten al jugador ascender mas alto, por otro lado se encuentran en mayor cantidad los cuadros con serpientes, que al caer en estas casillas el jugador debera retroceder."<<endl<<endl;

    system("pause");
    system("cls");
}

void crearBoton(nodo *inicio)           ///Crea un boton con la funcion de movimiento y pone las caras del dado
{
    inicio = buscarElemento(inicio,turnoJugador);
    int flag=1,valor_dado, valor_dado2,valor,desplazar;
    char auxchar[15];
    int x,y;
    setcolor(RED);
    circle(1170,480,60);
    setfillstyle(SOLID_FILL,RED);
    floodfill(1180,490,RED);
    setcolor(WHITE);
    settextstyle(3,0,2);
    outtextxy(1140,545,"Lanzar");
    outtextxy(1148,570,"dado");
    outtextxy(1050,600,"Jugador ");
    outtextxy(1050,625,"Lanzo el dado");
//    sprintf(auxchar,"%s",(inicio->NombreJugador).c_str());
//    outtextxy(1100,625,auxchar);
    ///Muestra turno con numero
//    sprintf(auxchar,"%d",turnoJugador);
//    outtextxy(1100,625,auxchar);
//    inicio = buscarElemento(inicio,turnoJugador);
    srand (time(NULL));
    while(flag==1)
    {
        while(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if((x>1110 && x<1230)&&(y>420 && y<540))
            {
                if(turnoJugador==jugadores+1)
                    turnoJugador=1;
                cout << turnoJugador << " lanzo el dado" << endl;
                ///Borra texto anterior
//                sprintf(auxchar,"%s",(inicio->NombreJugador).c_str());
//                setcolor(0);
//                outtextxy(1125,625,auxchar);
                sprintf(auxchar,"%d",turnoJugador);
                setcolor(0);
                outtextxy(1125,600,auxchar);
                sprintf(auxchar,"%d",turnoJugador);
                setcolor(15);
                outtextxy(1135,600,auxchar);
                ///Escribe nuevo texto
//                sprintf(auxchar,"%s",(inicio->sig->NombreJugador).c_str());
//                setcolor(15);
//                outtextxy(1125,625,auxchar);
                ///Realiza movimiento de casilla
                movimiento(inicio,tablero,turnoJugador);
                turnoJugador++;
                valor_dado = auxdado1;
                valor_dado2= auxdado2;

//                sprintf(auxchar,"%d",turnoJugador);
//                setcolor(15);
//                outtextxy(1100,625,auxchar);
                flag=0;
                break;
            }
        }
        delay(200);
    }
///el valor de desplazar en esta seccion servirá para imprimir el valor en el primer dado cuando i=1 y en el segundo cuando i=2
    for(int i=1; i<=2;i++)
    {
        if(i==1)
        {
            valor=valor_dado;
            desplazar=0;
        }
        if(i==2)
        {
            valor=valor_dado2;
            desplazar=160;
        }
            setcolor(BLACK);
            setfillstyle(SOLID_FILL,BLACK);
        switch (valor)
        {
            ///    fillellipse(x,y,distancia_a_x,distancia_a_y
            case 1:
                    setcolor(DARKGRAY);
                    rectangle(1120,120+desplazar,1220,220+desplazar);
                    setfillstyle(SOLID_FILL,WHITE);
                    floodfill(1170,170+desplazar,DARKGRAY);
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL,BLACK);
                    fillellipse(1170,170+desplazar,7,7);
    //                system("pause");
                    break;
            case 2:
                    setcolor(DARKGRAY);
                    rectangle(1120,120+desplazar,1220,220+desplazar);
                    setfillstyle(SOLID_FILL,WHITE);
                    floodfill(1170,170+desplazar,DARKGRAY);
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL,BLACK);
                    fillellipse(1145,195+desplazar,7,7);
                    fillellipse(1195,145+desplazar,7,7);
    //                system("pause");
                    break;

            case 3:
                    setcolor(DARKGRAY);
                    rectangle(1120,120+desplazar,1220,220+desplazar);
                    setfillstyle(SOLID_FILL,WHITE);
                    floodfill(1170,170+desplazar,DARKGRAY);
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL,BLACK);
                    fillellipse(1145,195+desplazar,7,7);
                    fillellipse(1195,145+desplazar,7,7);
                    fillellipse(1171,170+desplazar,7,7);
    //                system("pause");
                    break;

            case 4:
                    setcolor(DARKGRAY);
                    rectangle(1120,120+desplazar,1220,220+desplazar);
                    setfillstyle(SOLID_FILL,WHITE);
                    floodfill(1170,170+desplazar,DARKGRAY);
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL,BLACK);
                    fillellipse(1145,145+desplazar,7,7);
                    fillellipse(1145,195+desplazar,7,7);
                    fillellipse(1195,145+desplazar,7,7);
                    fillellipse(1195,195+desplazar,7,7);
    //                system("pause");
                    break;

            case 5:
                    setcolor(DARKGRAY);
                    rectangle(1120,120+desplazar,1220,220+desplazar);
                    setfillstyle(SOLID_FILL,WHITE);
                    floodfill(1170,170+desplazar,DARKGRAY);
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL,BLACK);
                    fillellipse(1145,145+desplazar,7,7);
                    fillellipse(1145,195+desplazar,7,7);
                    fillellipse(1195,145+desplazar,7,7);
                    fillellipse(1195,195+desplazar,7,7);
                    fillellipse(1170,170+desplazar,7,7);
    //                system("pause");
                    break;

            case 6:
                    setcolor(DARKGRAY);
                    rectangle(1120,120+desplazar,1220,220+desplazar);
                    setfillstyle(SOLID_FILL,WHITE);
                    floodfill(1170,170+desplazar,DARKGRAY);
                    setcolor(BLACK);
                    setfillstyle(SOLID_FILL,BLACK);
                    fillellipse(1145,145+desplazar,7,7);
                    fillellipse(1145,170+desplazar,7,7);
                    fillellipse(1145,195+desplazar,7,7);
                    fillellipse(1195,145+desplazar,7,7);
                    fillellipse(1195,170+desplazar,7,7);
                    fillellipse(1195,195+desplazar,7,7);
    //                system("pause");
                    break;
        }
    }
}

void crearDado(int k)       ///Crea el dado grafico
{
    setcolor(DARKGRAY);
    rectangle(1120,120+k,1220,220+k);
    ///Linea horizontal superior
    line(1145,95+k,1245,95+k);
    ///Linea vertical derecha
    line(1245,95+k,1245,195+k);
    ///Linea diagonal derecha superior
    line(1220,120+k,1245,95+k);
    ///Linea diagonal izquierda
    line(1120,120+k,1145,95+k);
    ///Linea diagonal derecha inferior
    line(1220,220+k,1245,195+k);
    ///rellenar
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(1170,170+k,DARKGRAY);
    floodfill(1183,108+k,DARKGRAY);
    floodfill(1233,158+k,DARKGRAY);
}

void crearTablero(Nodo *tablero)        ///Crea el tablero virtual y asigna coordenadas
{
    Nodo *Posiciones = tablero;
    Posiciones = busqueda(tablero,1);                       ///es un auxiliar tipo nodo
    int contadortablero=0;                         ///este contador es el numero de las casillas
    int par=1;
    char casilla[4];
    for(int y=635; y>=117; y=y-74)
    {
        if(par%2==0)
        {
            for(int x=67; x<=955; x=x+74)
            {
                Posiciones->y = y;  ///Guardamos coordenadas de las casillas
                Posiciones->x = x;
                cout << Posiciones->Numcasilla << endl;
                cout << "Valor de x = " << Posiciones->x << " Valor de y " << Posiciones->y << endl;
                circle(x,y,37);
                contadortablero++;
                settextstyle(3,0,1);
                sprintf(casilla,"%d",contadortablero);
                outtextxy(x,y,casilla);
                if(Posiciones->Numcasilla != 100)
                    Posiciones = Posiciones->avanza;
                if(contadortablero==100)
                {
                    circle(x,y,37);
                    setfillstyle(SOLID_FILL,RED);
                    floodfill(x,y,WHITE);
                    Posiciones->y = y;
                    Posiciones->x = x;
                    y=116;
                    break;
                }
            }
        }
        else
        {
            for(int x=955; x>=67; x=x-74)
            {
                Posiciones->y = y;      ///Guardamos coordenadas de las casillas
                Posiciones->x = x;
                cout << Posiciones->Numcasilla << endl;
                cout << "Valor de x = " << Posiciones->x << " Valor de y " << Posiciones->y << endl;
                circle(x,y,37);
                contadortablero++;
                settextstyle(3,0,1);
                sprintf(casilla,"%d",contadortablero);
                outtextxy(x,y,casilla);
                Posiciones = Posiciones->avanza;
            }
        }
        par++;
    }
    cout << "Sale del for" << endl;
}

void dibujar_serpientes_escaleras(Nodo *tablero)        ///Crea el grafico para serpientes y escaleras
{
    Nodo *verificar = tablero;
        while(verificar!=NULL)
        {
//          verificar=busqueda(tablero,aux_numcasilla);
            if(verificar->colaSerpiente==true)
            {
                setcolor(GREEN);
                cout<<endl;
                cout<<"El valor de colaserpiente x= "<<verificar->x<<endl;
                cout<<"El valor de colaserpiente y= "<<verificar->y<<endl;
                cout<<"El valor de cabezaserpiente x= "<<verificar->especial->x<<endl;
                cout<<"El valor de cabezaserpiente y= "<<verificar->especial->y<<endl;
                cout<<endl;
                line(verificar->x,verificar->y,verificar->especial->x, verificar->especial->y);
            }
            if(verificar->inicioEscalera==true)
            {
                setcolor(YELLOW);
                cout<<endl;
                cout<<"El valor de colaserpiente x= "<<verificar->x<<endl;
                cout<<"El valor de colaserpiente y= "<<verificar->y<<endl;
                cout<<"El valor de cabezaserpiente x= "<<verificar->especial->x<<endl;
                cout<<"El valor de cabezaserpiente y= "<<verificar->especial->y<<endl;
                cout<<endl;
                line(verificar->x,verificar->y,verificar->especial->x, verificar->especial->y);
            }
            verificar = verificar->avanza;
        }
}

void jugar_o_Salir()
{
    int flag=1,x,y;
    ///Primer rectangulo
    setcolor(LIGHTGREEN);
    rectangle(289,339,511,413);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    floodfill(400,376,LIGHTGREEN);
    rectangle(215,265,955,487);
    ///Segundo rectangulo
    setcolor(LIGHTGREEN);
    rectangle(659,339,881,413);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    floodfill(770,376,LIGHTGREEN);
    setcolor(15);
    settextstyle(4,0,2);
    outtextxy(363,376,"Regresar al menu");
    outtextxy(733,376,"Salir del juego");
    while(flag==1)
    {
        while(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if((x>289 && x<511)&&(y>339 && y<413))
            {
                closegraph();
                system("cls");
                fflush(stdin);
                menu();
                flag=0;
                break;
            }
        }
        delay(250);
        while(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if((x>659 && x<881)&&(y>339 && y<413))
            {
                closegraph();
                system("cls");
                exit(0);
                flag=0;
                break;
            }
        }
        delay(250);
    }
    getch();
}

void ciclo(nodo *inicio)        ///Permite la jugabilidad, no termina hasta que acaba el juego
{
    char ganador[15];
    int k=0;
    crearDado(k);
    k=160;
    crearDado(k);
    switch(jugadores)
    {
    case 1:
        break;
    case 2:
        while((inicio->NumcasillaJugador!=100) && (inicio->sig->NumcasillaJugador!=100))
        ///Crea los dos dados y verifica si algun jugador ya llego a 100
        {
            crearBoton(inicio);
            cout << inicio->NumcasillaJugador << endl;
            cout << inicio->sig->NumcasillaJugador << endl;
    //        mostrarNodo(tablero);
        }
        if(inicio->NumcasillaJugador==100)
            inicio = inicio;
        else if(inicio->sig->NumcasillaJugador==100)
            inicio = inicio->sig;
        break;
    case 3:
        while((inicio->NumcasillaJugador!=100) && (inicio->sig->NumcasillaJugador!=100) && (inicio->sig->sig->NumcasillaJugador!=100))
        ///Crea los dos dados y verifica si algun jugador ya llego a 100
        {
            crearBoton(inicio);
            cout << inicio->NumcasillaJugador << endl;
            cout << inicio->sig->NumcasillaJugador << endl;
            cout << inicio->sig->sig->NumcasillaJugador << endl;
    //        mostrarNodo(tablero);
        }
        if(inicio->NumcasillaJugador==100)
            inicio = inicio;
        else if(inicio->sig->NumcasillaJugador==100)
            inicio = inicio->sig;
        else if(inicio->sig->sig->NumcasillaJugador==100)
            inicio = inicio->sig->sig;
        break;
    case 4:
        while((inicio->NumcasillaJugador!=100) && (inicio->sig->NumcasillaJugador!=100) && (inicio->sig->sig->NumcasillaJugador!=100) && (inicio->sig->sig->sig->NumcasillaJugador!=100))
        ///Crea los dos dados y verifica si algun jugador ya llego a 100
        {
            crearBoton(inicio);
            cout << inicio->NumcasillaJugador << endl;
            cout << inicio->sig->NumcasillaJugador << endl;
            cout << inicio->sig->sig->NumcasillaJugador << endl;
            cout << inicio->sig->sig->sig->NumcasillaJugador << endl;
    //        mostrarNodo(tablero);
        }
        if(inicio->NumcasillaJugador==100)
            inicio = inicio;
        else if(inicio->sig->NumcasillaJugador==100)
            inicio = inicio->sig;
        else if(inicio->sig->sig->NumcasillaJugador==100)
            inicio = inicio->sig->sig;
        else if(inicio->sig->sig->sig->NumcasillaJugador==100)
            inicio = inicio->sig->sig->sig;
        break;
    }
    setcolor(9);
    rectangle(215,265,955,487);
    setfillstyle(SOLID_FILL,9);
    floodfill(511,376,9);
    settextstyle(4,0,6);
    sprintf(ganador,"%s",(inicio->NombreJugador).c_str());
    outtextxy(230,280,ganador);
    outtextxy(230,400," ha ganado el juego");
    cout << "Jugador " <<inicio->NumJugador << " ha ganado el juego";
    delay(5000);
    setcolor(0);
    rectangle(215,265,955,487);
    setfillstyle(SOLID_FILL,0);
    floodfill(511,376,0);
    setcolor(0);
    outtextxy(230,280,ganador);
    outtextxy(230,400," ha ganado el juego");
    jugar_o_Salir();
}

void inicia_grafico()
{
    int gd = DETECT, gm;
    ///initgraph(&gd, &gm, "C:\\TC\\BGI");
    initwindow(1400,700);
    delay(100);
}

int main()
{
    int i;
    for(i=1;i<=100;i++)
    {
        insertarNodo(tablero,i);
    }
//    mostrarNodo(tablero);
    indicaciones();
    menu();
    inicia_grafico();
    setlinestyle(SOLID_LINE,0,THICK_WIDTH);         ///Se establece linea solida y de grueso = 3 (thick)
    settextstyle(4,0,6);
    outtextxy(100,10, "Serpientes y escaleras");
    crearTablero(tablero);
    dibujar_serpientes_escaleras(tablero);
    mostrarNodo(tablero);
    ciclo(inicio);

    getch();
    closegraph();
    return 0;
}
