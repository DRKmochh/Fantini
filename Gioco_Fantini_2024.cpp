//Inizio dichiarazione librerie
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <string>
#include <stdlib.h>
#include <time.h>
//Fine dichiarazione librerie

using namespace std;

//inizio dichiarazione funzioni
void stampa_titolo(int riga);
void stampa_gioca(int riga);
void stampa_regole(int riga);
bool menu_iniziale(int righe, int colonne, COORD &gioca_coord, COORD &regole_coord);
void setup(int &righe, int &colonne);
void gotoXY(int x, int y);
void stampa_cursore(int x, int y);
void cancella_cursore(int x, int y);
bool selezione_iniziale(COORD gioca_coord, COORD regole_coord);
void ShowConsoleCursor(bool showFlag);
void setColor(int bg, int fg);
void stampa_numero_unsel(unsigned short int dado, unsigned short int riga);
short unsigned int selezione_giocatori(COORD gioca_coord);
void regole(COORD gioca_coord);
short unsigned int selezione_lunghezza(COORD gioca_coord);
void selezione_nomi(COORD gioca_coord, short unsigned int &n_giocatori, string nomi[]);
// Da qui finisce il menu' e inizia il gioco --------------------------------------
void stampa_fantini(unsigned short int fantini, unsigned short int riga);
void stampa_dado(unsigned short int dado, unsigned short int riga);
void setup_gioco(int colonne, short unsigned int n_giocatori, short unsigned int lunghezza);
void gioco(int colonne, short unsigned int n_giocatori, short unsigned int lunghezza, string nomi[]);

const unsigned short int colori[4] = {12, 1, 6, 14}; //I colori dei giocatori

//Fine dichiarazione funzioni

int main()
{//Inizio MAIN
    int n_righe_console, n_colonne_console; //86x317 nel mio caso
    COORD gioca_coord, regole_coord;

    setup(n_righe_console, n_colonne_console); //Cambia i colori, mette a schermo intero, e nei parametri mette il numero delle righe e colonne del terminale, utili per la grafica

    if(menu_iniziale(n_righe_console, n_colonne_console, gioca_coord, regole_coord)) //Le coord viene passato per riferimento
    {//Qui inizia il gioco ------------------------------------------------------------------------------------------------------------------------
        //Chiede i parametri all'utente
        short unsigned int n_giocatori = selezione_giocatori(gioca_coord);
        short unsigned int lunghezza = selezione_lunghezza(gioca_coord);

        string nomi[4];
        selezione_nomi(gioca_coord, n_giocatori, nomi);

        //Avvia il gioco
        system("cls");
        setup_gioco(n_colonne_console, n_giocatori, lunghezza);
        gioco(n_colonne_console, n_giocatori, lunghezza, nomi);

    }
    else
    {//Qui si indicano le regole ------------------------------------------------------------------------------------------------------------------
        regole(gioca_coord);
    }

    system("cls");

    return main();
}//Fine MAIN

void stampa_titolo(int riga)
{//Inizio funzione per stampare il titolo
    switch(riga)
    {//Inizio switch per stampare codice ascii del titolo
        case 0:
            cout << "  /$$$$$$                                         ";
            break;
        case 1:
            cout << " /$$$$$$$$                   /$$     /$$           /$$";
            break;
        case 2:
            cout << " /$$__  $$                                        ";
            break;
        case 3:
            cout << "| $$_____/                  | $$    |__/          |__/";
            break;
        case 4:
            cout << "| $$  \\__/  /$$$$$$   /$$$$$$   /$$$$$$$  /$$$$$$ ";
            break;
        case 5:
            cout << "| $$    /$$$$$$  /$$$$$$$  /$$$$$$   /$$ /$$$$$$$  /$$";
            break;
        case 6:
            cout << "| $$       /$$__  $$ /$$__  $$ /$$_____/ |____  $$";
            break;
        case 7:
            cout << "| $$$$$|____  $$| $$__  $$|_  $$_/  | $$| $$__  $$| $$";
            break;
        case 8:
            cout << "| $$      | $$  \\ $$| $$  \\__/|  $$$$$$   /$$$$$$$";
            break;
        case 9:
            cout << "| $$__/ /$$$$$$$| $$  \\ $$  | $$    | $$| $$  \\ $$| $$";
            break;
        case 10:
            cout << "| $$    $$| $$  | $$| $$       \\____  $$ /$$__  $$";
            break;
        case 11:
            cout << "| $$   /$$__  $$| $$  | $$  | $$ /$$| $$| $$  | $$| $$";
            break;
        case 12:
            cout << "|  $$$$$$/|  $$$$$$/| $$       /$$$$$$$/|  $$$$$$$";
            break;
        case 13:
            cout << "| $$  |  $$$$$$$| $$  | $$  |  $$$$/| $$| $$  | $$| $$";
            break;
        case 14:
            cout << " \\______/  \\______/ |__/      |_______/  \\_______/";
            break;
        case 15:
            cout << "|__/   \\_______/|__/  |__/   \\___/  |__/|__/  |__/|__/";
            break;
    }//Fine switch per stampare codice ascii del titolo
}//Fine funzione per stampare il titolo

void stampa_gioca(int riga)
{//Inizio funzione per stampare la scritta gioca
    switch(riga)
    {//Inizio switch per stampare la scritta gioca
        case 0:
            cout << "  ___ _              ";
            break;
        case 1:
            cout << " / __(_)___  __ __ _ ";
            break;
        case 2:
            cout << "| (_ | / _ \\/ _/ _` |";
            break;
        case 3:
            cout << " \\___|_\\___/\\__\\__,_|";
            break;
    }//Fine switch per stampare la scritta gioca
}//Fine funzione per stampare la scritta gioca

void stampa_regole(int riga)
{//Inizio funzione per stampare le regole
    switch(riga)
    {//Inizio switch per stampare le regole
        case 0:
            cout << " ___              _     ";
            break;
        case 1:
            cout << "| _ \\___ __ _ ___| |___ ";
            break;
        case 2:
            cout << "|   / -_) _` / _ \\ / -_)";
            break;
        case 3:
            cout << "|_|_\\___\\__, \\___/_\\___|";
            break;
        case 4:
            cout << "        |___/           ";
            break;
    }//Fine switch per stampare le regole
}//Fine funzione per stampare le regole

bool menu_iniziale(int righe, int colonne, COORD &gioca_coord, COORD &regole_coord)
{//Inizio funzione per il menù
    int i_righe, i_colonne;

    // 16 + 4vuoto + 8testo + 4vuoto + 16 + 2vuoto + 1testo + 1vuoto + 1testo + 2vuoto + resto

    int laterali = (colonne - 141) / 2;//calcola quanti '#' laterali vanno stampati

    for(i_righe = 0; i_righe < (righe - 30) / 3; i_righe++)
    {//Inizio for per stampare la prima zona di soli #
        for(i_colonne = 0; i_colonne < colonne; i_colonne++)
            cout << "#";
        cout << endl;
    }//Fine for per stampare la prima zona di soli #

    for(i_righe = 0; i_righe < 4; i_righe++)
    {//Inizio for per stampare 4 linee vuote
        for(i_colonne = 0; i_colonne < laterali; i_colonne++)
            cout << "#";
        for(i_colonne = 0; i_colonne < 140; i_colonne++)
            cout << " ";
        for(i_colonne = 0; i_colonne < laterali+1; i_colonne++)
            cout << "#";
        cout << endl;
    }//Fine for per stampare 4 linee vuote

    for(i_righe = 0; i_righe < 8; i_righe++)   //stampa il titolo
    {
        for(i_colonne = 0; i_colonne < laterali; i_colonne++)
            cout << "#";
        cout << "               "; //10 spazi
        stampa_titolo(i_righe*2);
        cout << "      "; //6 spazi
        stampa_titolo((i_righe*2)+1);
        cout << "               "; //10 spazi
        for(i_colonne = 0; i_colonne < laterali+1; i_colonne++)
            cout << "#";
        cout << endl;
    }

    for(i_righe = 0; i_righe < 4; i_righe++) //4 linee vuote
    {
        for(i_colonne = 0; i_colonne < laterali; i_colonne++)
            cout << "#";
        for(i_colonne = 0; i_colonne < 140; i_colonne++)
            cout << " ";
        for(i_colonne = 0; i_colonne < laterali+1; i_colonne++)
            cout << "#";
        cout << endl;
    }

    for(i_righe = 0; i_righe < (righe - 30) / 3; i_righe++) //Seconda zona solo '#'
    {
        for(i_colonne = 0; i_colonne < colonne; i_colonne++)
            cout << "#";
        cout << endl;
    }

    for(i_righe = 0; i_righe < 2; i_righe++) //2 linee vuote
    {
        for(i_colonne = 0; i_colonne < laterali; i_colonne++)
            cout << "#";
        for(i_colonne = 0; i_colonne < 140; i_colonne++)
            cout << " ";
        for(i_colonne = 0; i_colonne < laterali+1; i_colonne++)
            cout << "#";
        cout << endl;
    }

    for(i_righe = 0; i_righe < 4; i_righe++)   //stampa "Gioca"
    {
        for(i_colonne = 0; i_colonne < laterali; i_colonne++)
            cout << "#";
        cout << "                                                            "; //40 spazi

        if(i_righe == 2)
        {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            gioca_coord = csbi.dwCursorPosition;
        }

        stampa_gioca(i_righe);
        cout << "                                                           "; //39 spazi
        for(i_colonne = 0; i_colonne < laterali+1; i_colonne++)
            cout << "#";
        cout << endl;
    }

    for(i_righe = 0; i_righe < 2; i_righe++) //2 linee vuote
    {
        for(i_colonne = 0; i_colonne < laterali; i_colonne++)
            cout << "#";
        for(i_colonne = 0; i_colonne < 140; i_colonne++)
            cout << " ";
        for(i_colonne = 0; i_colonne < laterali+1; i_colonne++)
            cout << "#";
        cout << endl;
    }

    for(i_righe = 0; i_righe < 5; i_righe++)   //stampa "Regole"
    {
        for(i_colonne = 0; i_colonne < laterali; i_colonne++)
            cout << "#";
        cout << "                                                           "; //39 spazi

        if(i_righe == 3)
        {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            regole_coord = csbi.dwCursorPosition;
        }

        stampa_regole(i_righe);
        cout << "                                                         "; //37 spazi
        for(i_colonne = 0; i_colonne < laterali+1; i_colonne++)
            cout << "#";
        cout << endl;
    }

    //1 linea vuota
    for(i_colonne = 0; i_colonne < laterali; i_colonne++)
        cout << "#";
    for(i_colonne = 0; i_colonne < 140; i_colonne++)
        cout << " ";
    for(i_colonne = 0; i_colonne < laterali+1; i_colonne++)
        cout << "#";
    cout << endl;

    for(i_righe = 0; i_righe < (righe - 30) / 3; i_righe++) //Terza zona solo '#'
    {
        for(i_colonne = 0; i_colonne < colonne; i_colonne++)
            cout << "#";
        cout << endl;
    }
    return selezione_iniziale(gioca_coord, regole_coord);
}//Fine funzione per il menu

void setup(int &righe, int &colonne)
{
    system("COLOR 0A");

    system("mode 650");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    ShowConsoleCursor(false);

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    colonne = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    righe = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void gotoXY(int x, int y)
{
    COORD CursorPos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, CursorPos);
}

void stampa_cursore(int x, int y)
{
    gotoXY(x-5,y-1);
    cout << "|\\";
    gotoXY(x-5,y);
    cout << "|/";
}

void cancella_cursore(int x, int y)
{
    gotoXY(x-5,y-1);
    cout << "  ";
    gotoXY(x-5,y);
    cout << "  ";
}

bool selezione_iniziale(COORD gioca_coord, COORD regole_coord)
{
    const unsigned int sleep_time = 100;
    bool b = true;
    char input;

    stampa_cursore(gioca_coord.X, gioca_coord.Y);
    do
    {
        input = getch();
        if (input == -32) { // if the first value is esc
            switch(getch()) { // the real value
                case 72:
                case 80:
                    // code for arrow up or down
                    b = !b;
                    if(b)
                    {
                        cancella_cursore(regole_coord.X, regole_coord.Y);
                        stampa_cursore(gioca_coord.X, gioca_coord.Y);
                    }
                    else
                    {
                        cancella_cursore(gioca_coord.X, gioca_coord.Y);
                        stampa_cursore(regole_coord.X, regole_coord.Y);
                    }
                    break;
            }
        }
    }while(input != 13);

    return b;
}

void ShowConsoleCursor(bool showFlag)
{
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); CONSOLE_CURSOR_INFO cursorInfo;
GetConsoleCursorInfo(out, &cursorInfo);
cursorInfo.bVisible = showFlag; // set the cursor visibility
SetConsoleCursorInfo(out, &cursorInfo);
}

void setColor(int bg, int fg)
{
    int val;
    if (bg<0)
        bg=0;
    if (fg>15)
        fg=15;
    val=bg*16+fg;
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        val);
}

void stampa_numero_unsel(unsigned short int numero, unsigned short int riga)
{
/*
.---------------------------------------------------------------------------------------------------.
|      ████                  ████████                  ████████                 █████ █████         |
|     ##███                 ███####███                ███####███               ##███ ##███          |
|      #███                ###    #███               ###    #███                #███  #███ █        |
|      #███                   ███████                   ██████#                 #███████████        |
|      #███                  ███####                   ######███                #######███#█        |
|      #███                 ███      █                ███   #███                      #███#         |
|      █████               #██████████               ##████████                       █████         |
|     #####                ##########                 ########                       #####          |
'---------------------------------------------------------------------------------------------------'
*/
    switch(numero)
    {
        case 1:

            switch(riga)
            {
                case 1:
                    cout << "      ";
                    setColor(2,2); //sfondo verde
                    cout << "    ";
                    setColor(0,2); //sfondo nero
                    cout << "     ";
                    break;
                case 2:
                    cout << "     ##";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "     ";
                    break;
                case 3:
                    cout << "      #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "     ";
                    break;
                case 4:
                    cout << "      #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "     ";
                    break;
                case 5:
                    cout << "      #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "     ";
                    break;
                case 6:
                    cout << "      #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "     ";
                    break;
                case 7:
                    cout << "      ";
                    setColor(2,2); //sfondo verde
                    cout << "     ";
                    setColor(0,2); //sfondo nero
                    cout << "    ";
                    break;
                case 8:
                    cout << "     #####     ";
                    break;
            }
            break;
        case 2:

            switch(riga)
            {
                case 1:
                    cout << "    ";
                    setColor(2,2); //sfondo verde
                    cout << "        ";
                    setColor(0,2); //sfondo nero
                    cout << "   ";
                    break;
                case 2:
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "####";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 3:
                    cout << "  ###    #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 4:
                    cout << "     ";
                    setColor(2,2); //sfondo verde
                    cout << "       ";
                    setColor(0,2); //sfondo nero
                    cout << "   ";
                    break;
                case 5:
                    cout << "    ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "####    ";
                    break;
                case 6:
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "      ";
                    setColor(2,2); //sfondo verde
                    cout << " ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 7:
                    cout << "  #";
                    setColor(2,2); //sfondo verde
                    cout << "          ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 8:
                    cout << "  ##########   ";
                    break;
            }
            break;
        case 3:

            switch(riga)
            {
                case 1:
                    cout << "    ";
                    setColor(2,2); //sfondo verde
                    cout << "        ";
                    setColor(0,2); //sfondo nero
                    cout << "   ";
                    break;
                case 2:
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "####";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 3:
                    cout << "  ###    #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 4:
                    cout << "     ";
                    setColor(2,2); //sfondo verde
                    cout << "      ";
                    setColor(0,2); //sfondo nero
                    cout << "#   ";
                    break;
                case 5:
                    cout << "    ######";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 6:
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "   #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 7:
                    cout << "  ##";
                    setColor(2,2); //sfondo verde
                    cout << "        ";
                    setColor(0,2); //sfondo nero
                    cout << "   ";
                    break;
                case 8:
                    cout << "   ########    ";
                    break;
            }
            break;
        case 4:

            switch(riga)
            {
                case 1:
                    cout << "  ";
                    setColor(2,2); //sfondo verde
                    cout << "     ";
                    setColor(0,2); //sfondo nero
                    cout << " ";
                    setColor(2,2); //sfondo verde
                    cout << "     ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 2:
                    cout << " ##";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << " ##";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "   ";
                    break;
                case 3:
                    cout << "  #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "  #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << " ";
                    setColor(2,2); //sfondo verde
                    cout << " ";
                    setColor(0,2); //sfondo nero
                    cout << " ";
                    break;
                case 4:
                    cout << "  #";
                    setColor(2,2); //sfondo verde
                    cout << "           ";
                    setColor(0,2); //sfondo nero
                    cout << " ";
                    break;
                case 5:
                    cout << "  #######";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "#";
                    setColor(2,2); //sfondo verde
                    cout << " ";
                    setColor(0,2); //sfondo nero
                    cout << " ";
                    break;
                case 6:
                    cout << "        #";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "#  ";
                    break;
                case 7:
                    cout << "        ";
                    setColor(2,2); //sfondo verde
                    cout << "     ";
                    setColor(0,2); //sfondo nero
                    cout << "  ";
                    break;
                case 8:
                    cout << "       #####   ";
                    break;
            }
            break;
    }
}

void stampa_numero_sel(unsigned short int numero, unsigned short int riga)
{
/*
.---------------------------------------------------------------------------------------------------.
|                                                                                                   |
|     ████                  ████████                  ████████                 █████ █████          |
|      ███                 ███    ███                ███    ███                 ███   ███           |
|      ███                        ███                       ███                 ███   ███ █         |
|      ███                   ██████                    ██████                   ███████████         |
|      ███                  ███                             ███                       ███ █         |
|      ███                 ███      █                ███    ███                       ███           |
|     █████                ██████████                 ████████                       █████          |
'---------------------------------------------------------------------------------------------------'
*/
    switch(numero)
    {
        case 1:

            switch(riga)
            {
                case 1:
                    cout << "               ";
                    break;
                case 2:
                    cout << "     ";
                    setColor(2,2); //sfondo verde
                    cout << "    ";
                    setColor(0,2); //sfondo nero
                    //cout << "      ";
                    break;
                case 3:
                    cout << "      ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "      ";
                    break;
                case 4:
                    cout << "      ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "      ";
                    break;
                case 5:
                    cout << "      ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "      ";
                    break;
                case 6:
                    cout << "      ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "      ";
                    break;
                case 7:
                    cout << "      ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "      ";
                    break;
                case 8:
                    cout << "     ";
                    setColor(2,2); //sfondo verde
                    cout << "     ";
                    setColor(0,2); //sfondo nero
                    //cout << "     ";
                    break;
            }
            break;
        case 2:

            switch(riga)
            {
                case 1:
                    cout << "               ";
                    break;
                case 2:
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "        ";
                    setColor(0,2); //sfondo nero
                    //cout << "         ";
                    break;
                case 3:
                    cout << "  ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "    ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "        ";
                    break;
                case 4:
                    cout << "         ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "        ";
                    break;
                case 5:
                    cout << "    ";
                    setColor(2,2); //sfondo verde
                    cout << "      ";
                    setColor(0,2); //sfondo nero
                    //cout << "          ";
                    break;
                case 6:
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "              ";
                    cout << "         ";
                    break;
                case 7:
                    cout << "  ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "      ";
                    setColor(2,2); //sfondo verde
                    cout << " ";
                    setColor(0,2); //sfondo nero
                    //cout << "        ";
                    break;
                case 8:
                    cout << "  ";
                    setColor(2,2); //sfondo verde
                    cout << "          ";
                    setColor(0,2); //sfondo nero
                    //cout << "        ";
                    break;
            }
            break;
        case 3:

            switch(riga)
            {
                case 1:
                    cout << "               ";
                    break;
                case 2:
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "        ";
                    setColor(0,2); //sfondo nero
                    //cout << "         ";
                    break;
                case 3:
                    cout << "  ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "    ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "        ";
                    break;
                case 4:
                    cout << "         ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "        ";
                    break;
                case 5:
                    cout << "    ";
                    setColor(2,2); //sfondo verde
                    cout << "      ";
                    setColor(0,2); //sfondo nero
                    //cout << "          ";
                    break;
                case 6:
                    cout << "         ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "        ";
                    break;
                case 7:
                    cout << "  ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "    ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "        ";
                    break;
                case 8:
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "        ";
                    setColor(0,2); //sfondo nero
                    //cout << "         ";
                    break;
            }
            break;
        case 4:

            switch(riga)
            {
                case 1:
                    cout << "               ";
                    break;
                case 2:
                    cout << " ";
                    setColor(2,2); //sfondo verde
                    cout << "     ";
                    setColor(0,2); //sfondo nero
                    cout << " ";
                    setColor(2,2); //sfondo verde
                    cout << "     ";
                    setColor(0,2); //sfondo nero
                    //cout << "  ";
                    break;
                case 3:
                    cout << "  ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "   ";
                    break;
                case 4:
                    cout << "  ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << "   ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << " ";
                    setColor(2,2); //sfondo verde
                    cout << " ";
                    setColor(0,2); //sfondo nero
                    //cout << " ";
                    break;
                case 5:
                    cout << "  ";
                    setColor(2,2); //sfondo verde
                    cout << "           ";
                    setColor(0,2); //sfondo nero
                    //cout << "  ";
                    break;
                case 6:
                    cout << "        ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    cout << " ";
                    setColor(2,2); //sfondo verde
                    cout << " ";
                    setColor(0,2); //sfondo nero
                    //cout << " ";
                    break;
                case 7:
                    cout << "        ";
                    setColor(2,2); //sfondo verde
                    cout << "   ";
                    setColor(0,2); //sfondo nero
                    //cout << "   ";
                    break;
                case 8:
                    cout << "       ";
                    setColor(2,2); //sfondo verde
                    cout << "     ";
                    setColor(0,2); //sfondo nero
                    //cout << "  ";
                    break;
            }
            break;
    }
}

short unsigned int selezione_giocatori(COORD gioca_coord)
{
    const int OFFSET[4] = {0, 20, 40, 59};

    //Corregge le variabili
    gioca_coord.X -= 26;
    gioca_coord.Y += 6;


    gotoXY(gioca_coord.X, gioca_coord.Y);

    for(int i = 1; i < 9; i++) //Stampa i numeri
    {
        for(int j = 1; j < 5; j++)
        {
            stampa_numero_unsel(j, 9-i);
            cout << "     ";
        }
        gotoXY(gioca_coord.X, gioca_coord.Y - i);
    }
    //Rimuove i caratteri rimasti "Gioca" e "Regole"
    gotoXY(gioca_coord.X, gioca_coord.Y + 1);
    cout << "                                                          ";
    gotoXY(gioca_coord.X, gioca_coord.Y + 2);
    cout << "                                                          ";
    gotoXY(gioca_coord.X, gioca_coord.Y - 8);
    cout << "                                                          ";

    //Stampa scritta
    gotoXY(gioca_coord.X + 26 , gioca_coord.Y - 9);
    cout << "Quante persone giocano?";

    char input;
    short unsigned int selezione = 1;
    for(int i = 1; i< 9; i++)
    {
        gotoXY(gioca_coord.X + OFFSET[selezione-1] , gioca_coord.Y - i + 1);
        stampa_numero_sel(1, 9-i);
        cout << "     ";
    }

    do
    {
        input = getch();
        if (input == -32) { // if the first value is esc
            switch(getch()) { // the real value
                case 77:
                    // code for arrow right

                    for(int i = 1; i< 9; i++)
                    {
                        gotoXY(gioca_coord.X + OFFSET[selezione-1] , gioca_coord.Y - i + 1);
                        stampa_numero_unsel(selezione, 9-i);
                        cout << "     ";
                    }

                    if(selezione == 4)
                        selezione = 1;
                    else
                        selezione++;

                    for(int i = 1; i< 9; i++)
                    {
                        gotoXY(gioca_coord.X + OFFSET[selezione-1] , gioca_coord.Y - i + 1);
                        stampa_numero_sel(selezione, 9-i);
                        cout << "     ";
                    }
                    break;
                case 75:
                    // code for arrow left

                    for(int i = 1; i< 9; i++)
                    {
                        gotoXY(gioca_coord.X + OFFSET[selezione-1] , gioca_coord.Y - i + 1);
                        stampa_numero_unsel(selezione, 9-i);
                        cout << "     ";
                    }

                    if(selezione == 1)
                        selezione = 4;
                    else
                        selezione--;

                    for(int i = 1; i< 9; i++)
                    {
                        gotoXY(gioca_coord.X + OFFSET[selezione-1] , gioca_coord.Y - i + 1);
                        stampa_numero_sel(selezione, 9-i);
                        cout << "     ";
                    }
                    break;
            }
        }
    }while(input != 13);
    return selezione;
}

void regole(COORD gioca_coord)
{
    gotoXY(gioca_coord.X - 50, gioca_coord.Y - 2);
    cout << "Il gioco si svolge a turno partendo da un fantino a caso.                                  ";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y - 1);
    cout << "Questi lancia 2 dadi (numero tra 2 e 12) e avanza di tanti quadratini quanto il numero uscito dal lancio";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y);
    cout << "ma nel caso che entrambi i dadi abbiano lo stesso valore allora l'avanzamento              ";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y + 1);
    cout << "e' aumentato del 30% approssimato all'intero superiore.                                    ";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y + 2);
    cout << "Se i quadratini raggiunti oltrepassano la lunghezza del percorso allora il fantino ha vinto";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y + 3);
    cout << "e la corsa degli altri fantini prosegue per determinare l'ordine d'arrivo finale.          ";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y + 4);
    cout << "Se i quadratini sono un multiplo di 5 allora il fantino indietreggia di 6                  ";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y + 5);
    cout << "ma non puo' indietreggiare sotto lo zero.                                                  ";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y + 6);
    cout << "                                                                                           ";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y + 7);
    cout << "                                                                                           ";
    gotoXY(gioca_coord.X - 50, gioca_coord.Y + 8);
    cout << "                                                ";
    system("pause");
}

void stampa_numero_lun(unsigned short int numero, unsigned short int riga)
{
    switch(numero)
    {
        case 1:
            switch(riga)
            {
                case 1:
                    cout << "      _ ";
                    break;

                case 2:
                    cout << "     / |";
                    break;

                case 3:
                    cout << "     | |";
                    break;

                case 4:
                    cout << "     | |";
                    break;

                case 5:
                    cout << "     |_|";
                    break;
            }
            break;
        case 2:
            switch(riga)
            {
                case 1:
                    cout << "  ____  ";
                    break;

                case 2:
                    cout << " |___ \\ ";
                    break;

                case 3:
                    cout << "   __) |";
                    break;

                case 4:
                    cout << "  / __/ ";
                    break;

                case 5:
                    cout << " |_____|";
                    break;
            }
            break;
        case 3:
            switch(riga)
            {
                case 1:
                    cout << "  _____ ";
                    break;

                case 2:
                    cout << " |___ / ";
                    break;

                case 3:
                    cout << "   |_ \\ ";
                    break;

                case 4:
                    cout << "  ___) |";
                    break;

                case 5:
                    cout << " |____/ ";
                    break;
            }
            break;
        case 4:
            switch(riga)
            {
                case 1:
                    cout << " _  _   ";
                    break;

                case 2:
                    cout << "| || |  ";
                    break;

                case 3:
                    cout << "| || |_ ";
                    break;

                case 4:
                    cout << "|__   _|";
                    break;

                case 5:
                    cout << "   |_|  ";
                    break;
            }
            break;
        case 5:
            switch(riga)
            {
                case 1:
                    cout << "  ____  ";
                    break;

                case 2:
                    cout << " | ___| ";
                    break;

                case 3:
                    cout << " |___ \\ ";
                    break;

                case 4:
                    cout << "  ___) |";
                    break;

                case 5:
                    cout << " |____/ ";
                    break;
            }
            break;
        case 6:
            switch(riga)
            {
                case 1:
                    cout << "   __   ";
                    break;

                case 2:
                    cout << "  / /_  ";
                    break;

                case 3:
                    cout << " | '_ \\ ";
                    break;

                case 4:
                    cout << " | (_) |";
                    break;

                case 5:
                    cout << "  \\___/ ";
                    break;
            }
            break;
        case 7:
            switch(riga)
            {
                case 1:
                    cout << "  _____ ";
                    break;

                case 2:
                    cout << " |___  |";
                    break;

                case 3:
                    cout << "    / / ";
                    break;

                case 4:
                    cout << "   / /  ";
                    break;

                case 5:
                    cout << "  /_/   ";
                    break;
            }
            break;
        case 8:
            switch(riga)
            {
                case 1:
                    cout << "   ___  ";
                    break;

                case 2:
                    cout << "  ( _ ) ";
                    break;

                case 3:
                    cout << "  / _ \\ ";
                    break;

                case 4:
                    cout << " | (_) |";
                    break;

                case 5:
                    cout << "  \\___/ ";
                    break;
            }
            break;
        case 9:
            switch(riga)
            {
                case 1:
                    cout << "   ___  ";
                    break;

                case 2:
                    cout << "  / _ \\ ";
                    break;

                case 3:
                    cout << " | (_) |";
                    break;

                case 4:
                    cout << "  \\__, |";
                    break;

                case 5:
                    cout << "    /_/ ";
                    break;
            }
            break;
        case 0:
            switch(riga)
            {
                case 1:
                    cout << "   ___  ";
                    break;

                case 2:
                    cout << "  / _ \\ ";
                    break;

                case 3:
                    cout << " | | | |";
                    break;

                case 4:
                    cout << " | |_| |";
                    break;

                case 5:
                    cout << "  \\___/ ";
                    break;
            }
            break;
    }
}

short unsigned int selezione_lunghezza(COORD gioca_coord)
{

    //Corregge le variabili
    gioca_coord.X -= 26;
    gioca_coord.Y += 6;

    //Rimuove i caratteri rimasti
    for(int i = 0; i < 9; i++)
    {
        gotoXY(gioca_coord.X, gioca_coord.Y - i);
        cout << "                                                                            ";
    }

    //Stampa i numeri
    for(int i = 1; i < 6; i++)
    {
        gotoXY(gioca_coord.X + 28, gioca_coord.Y - i);
        stampa_numero_lun(2, 6-i);
        stampa_numero_lun(5, 6-i);
    }

    //Stampa scritta
    gotoXY(gioca_coord.X + 16 , gioca_coord.Y - 9);
    cout << "      Quanto e' lungo il tracciato?        ";

    //Stampa frecce
    gotoXY(gioca_coord.X + 50,gioca_coord.Y - 3);
    cout << "|\\";
    gotoXY(gioca_coord.X + 50,gioca_coord.Y - 2);
    cout << "|/";
    gotoXY(gioca_coord.X + 20,gioca_coord.Y - 3);
    cout << "/|";
    gotoXY(gioca_coord.X + 20,gioca_coord.Y - 2);
    cout << "\\|";

    char input;
    short unsigned int selezione = 25;

    do
    {
        input = getch();
        if (input == -32) { // if the first value is esc
            switch(getch()) { // the real value
                case 77:
                    // code for arrow right

                    for(int i = 0; i < 6; i++)
                    {
                        gotoXY(gioca_coord.X + 28, gioca_coord.Y - i + 1);
                        cout << "                 ";
                    }

                    if(selezione != 65)
                        selezione++;

                    for(int i = 1; i < 6; i++)
                    {
                        gotoXY(gioca_coord.X + 28, gioca_coord.Y - i);
                        stampa_numero_lun(selezione/10, 6-i);
                        stampa_numero_lun(selezione%10, 6-i);
                    }
                    break;
                case 75:
                    // code for arrow left

                    for(int i = 0; i < 6; i++)
                    {
                        gotoXY(gioca_coord.X + 28, gioca_coord.Y - i + 1);
                        cout << "                 ";
                    }

                    if(selezione != 25)
                        selezione--;

                    for(int i = 1; i< 6; i++)
                    {
                        gotoXY(gioca_coord.X + 28, gioca_coord.Y - i);
                        stampa_numero_lun(selezione/10, 6-i);
                        stampa_numero_lun(selezione%10, 6-i);
                    }
                    break;
            }
        }
    }while(input != 13);
    return selezione;
}

void selezione_nomi(COORD gioca_coord, short unsigned int &n_giocatori, string nomi[])
{
    //Corregge le variabili
    gioca_coord.X -= 26;
    gioca_coord.Y += 6;

    //Rimuove i caratteri rimasti
    for(int i = 0; i < 9; i++)
    {
        gotoXY(gioca_coord.X, gioca_coord.Y - i);
        cout << "                                                                            ";
    }

    for(int i = 1; i <= n_giocatori; i++)
    {
        //Stampa scritta
        gotoXY(gioca_coord.X + 16 , gioca_coord.Y - 9);
        cout << "Inserisci il nome del giocatore " << i << " --> ";
        getline(cin, nomi[i-1]);
        gotoXY(gioca_coord.X + 16 , gioca_coord.Y - 9);
        cout << "                                                                                   ";
    }

    if(n_giocatori == 1)
    {
        nomi[1] = "CPU";
        n_giocatori++;
    }
}

// Da qui finisce il menu' e inizia il gioco ----------------------------------------------------------------------------

void stampa_fantini(unsigned short int fantini, unsigned short int riga)
{
    switch(fantini)
    {
        case 1: //Fantino 1

            switch(riga)
            {
                case 1:
                    cout << "                    ..::::.   ";
                    break;
                case 2:
                    cout << "                   ;$&&&&&$:  ";
                    break;
                case 3:
                    cout << "      ....;X&&$XX$&&&&&$::X$. ";
                    break;
                case 4:
                    cout << " ..:;;xXx;&&&&&&&&&&&&&:. ... ";
                    break;
                case 5:
                    cout << " ...:....$&&&Xx$&&&&$$&x++    ";
                    break;
                case 6:
                    cout << "      .xX:x$;. .......:X.+.   ";
                    break;
                case 7:
                    cout << "    .;x...x.           .+;.   ";
                    break;
                case 8:
                    cout << "     .    :x:.          ..:.  ";
                    break;
                case 9:
                    cout << "          ...";
                    break;

            }
            break;
        case 2: //Fantino 2

            switch(riga)
            {
                case 1:
                    cout << "                     ..:.:.   ";
                    break;
                case 2:
                    cout << "                 ..x$&&&&&&:  ";
                    break;
                case 3:
                    cout << "      ...:x&&&&XX&&&&&&X::x$+ ";
                    break;;
                case 4:
                    cout << " .:;;+Xx;x&&&&&&&&&&&&$:      ";
                    break;
                case 5:
                    cout << ".......;x$&$;:+X$&&$$&XXx:.   ";
                    break;
                case 6:
                    cout << ".......;x$&$;:+X$&&$$&XXx:.   ";
                    break;;
                case 7:
                    cout << "   ..+x:$x:.      ..:$...:X.  ";
                    break;
                case 8:
                    cout << "   ::..X.           .X.   .:  ";
                    break;
                case 9:
                    cout << "       . ";
                    break;

            }
            break;
        case 3: //Fantino 3

            switch(riga)
            {
                case 1:
                    cout << "                   .:;;....   ";
                    break;
                case 2:
                    cout << "         ..      .:$&&&&&$.   ";
                    break;
                case 3:
                    cout << "   ...:xX&&&&&$$&&&&&&&Xx$&x  ";
                    break;
                case 4:
                    cout << ".:;xxX+.x&&&&&&&&&&&&&.    .  ";
                    break;
                case 5:
                    cout << "  ....x$&&x;:+X$&&&$&$:       ";
                    break;
                case 6:
                    cout << "   ..x$;...   ...$;...;x:.    ";
                    break;
                case 7:
                    cout << "  .;X;.        .x:     .:xx.  ";
                    break;
                case 8:
                    cout << "               .+:.           ";
                    break;
                case 9:
                    cout << " ";
                    break;
            }
            break;

        case 4: //Fantino 4

            switch(riga)
            {
                case 1:
                    cout << "                 ..++;+.      ";
                    break;
                case 2:
                    cout << "     .. ..... ..+$&&&&&&x.    ";
                    break;
                case 3:
                    cout << ".. .;$$&&&&&&&&&&&&&$:..;;.   ";
                    break;
                case 4:
                    cout << ".+xXx:;&&&&&&&&&&&&X..        ";
                    break;
                case 5:
                    cout << "   .x$$x+:..;+x$$X&;          ";
                    break;
                case 6:
                    cout << ".:x;.+:      .++...X.         ";
                    break;
                case 7:
                    cout << "    ..    ..++..   .+..       ";
                    break;
                case 8:
                    cout << "          ...      ..+.       ";
                    break;
                case 9:
                    cout << " ";
                    break;
            }
            break;

        case 5: //Fantino 5

            switch(riga)
            {
                case 1:
                    cout << "                      ..      ";
                    break;
                case 2:
                    cout << "                 ..;$&&&;..   ";
                    break;
                case 3:
                    cout << "    ..:;+X$$Xx++X$&&&&XXXX:.  ";
                    break;
                case 4:
                    cout << ".....X$;&&&&&&&&&&&&&+. ...   ";
                    break;
                case 5:
                    cout << " ..:;:+x$&&xx&&&&&&$:.        ";
                    break;
                case 6:
                    cout << "     :+:x..   ..X&+.          ";
                    break;
                case 7:
                    cout << "    .;:.+: .;;;++$.           ";
                    break;
                case 8:
                    cout << "       ..      ..x.           ";
                    break;
                case 9:
                    cout << "               .... ";
                    break;
                }
            break;
        case 6: //Fantino 6

            switch(riga)
            {
                case 1:
                    cout << "                   ...        ";
                    break;
                case 2:
                    cout << "         ....   ...x&&&$:.    ";
                    break;
                case 3:
                    cout << "    ..:;X&&&&Xxx$&&&&$;;x;    ";
                    break;
                case 4:
                    cout << "   .x&X;$&&&&&&&&&&&x..       ";
                    break;
                case 5:
                    cout << " .;X+..x$&&x;$&&&&&:.         ";
                    break;
                case 6:
                    cout << "      .+xX:. ..x&x.           ";
                    break;
                case 7:
                    cout << "      .:+.;x.:Xxx;.           ";
                    break;
                case 8:
                    cout << "      ... ...x.               ";
                    break;
                case 9:
                    cout << "           .... ";
                    break;
                }
            break;

        case 7://Fantino 7
            switch(riga)
            {
                case 1:
                    cout << "                 .:x+.        ";
                    break;
                case 2:
                    cout << "      ..........+&&&&&+.      ";
                    break;
                case 3:
                    cout << "  ..:;x&&&&&&&&&&&&+..:.      ";
                    break;
                case 4:
                    cout << " .x$x.X&&&&&&&&&&$;.          ";
                    break;
                case 5:
                    cout << ".+x.. .X&&:+$&&&$:.           ";
                    break;
                case 6:
                    cout << "..    .x$x...:$:x+.           ";
                    break;
                case 7:
                    cout << "        ;;XX+x;+:.            ";
                    break;
                case 8:
                    cout << "        .. ..                 ";
                    break;
                case 9:
                    cout << " ";
                    break;
                }
            break;

        case 8://Fantino 8
            switch(riga)
            {
                case 1:
                    cout << "                 .x$X:.       ";
                    break;
                case 2:
                    cout << "     ..........:$&&&&&X.      ";
                    break;
                case 3:
                    cout << "   .:;x&&&&&&&&&&&&+ .: .     ";
                    break;
                case 4:
                    cout << " .+$X;;&&&&&&&&&&&;           ";
                    break;
                case 5:
                    cout << ".;x:.. .+&$;x$&&&$:           ";
                    break;
                case 6:
                    cout << "....   .X$$++.:x:.X.          ";
                    break;
                case 7:
                    cout << "         ..+x;;;:;.           ";
                    break;
                case 8:
                    cout << "             ...              ";
                    break;
                case 9:
                    cout << "        .. .. ";
                    break;
                }
            break;

        case 9://Fantino 9
            switch(riga)
            {
                case 1:
                    cout << "                ....          ";
                    break;
                case 2:
                    cout << "              .:X&&&;.        ";
                    break;
                case 3:
                    cout << "     .:+++;::;X&&&$x$X.       ";
                    break;
                case 4:
                    cout << " ..;XX&&&&&&&&&&&$.....       ";
                    break;
                case 5:
                    cout << ":$$;.;&&&&&&&&&&&;.           ";
                    break;
                case 6:
                    cout << "x+.   .;&&:+xxX&X+$.          ";
                    break;
                case 7:
                    cout << "..     .X&++:.+++:X.          ";
                    break;
                case 8:
                    cout << "        .:x:..   .:.          ";
                    break;
                case 9:
                    cout << "          .:.. ";
                    break;
                }
            break;

        case 10://Fantino 10
            switch(riga)
            {
                case 1:
                    cout << "                  .....       ";
                    break;
                case 2:
                    cout << "               ..;X&&&+.      ";
                    break;
                case 3:
                    cout << "      ..:;++;;;+$&&&$xX$.     ";
                    break;
                case 4:
                    cout << " ....+XX&&&&&&&&&&&$....      ";
                    break;
                case 5:
                    cout << " :X$x..x&&&&&&&&&&&;...       ";
                    break;
                case 6:
                    cout << ":+.    .$&+$x;++;++X$x.       ";
                    break;
                case 7:
                    cout << "..    .+X..:x+:..:;;..+:      ";
                    break;
                case 8:
                    cout << "      .:+.  ...;:     ..      ";
                    break;
                case 9:
                    cout << "        .;: ";
                    break;
                }
            break;

        case 11://Fantino 11
            switch(riga)
            {
                case 1:
                    cout << "                    ....      ";
                    break;
                case 2:
                    cout << "                 .:+X$XX:.    ";
                    break;
                case 3:
                    cout << "         ..::...;X&&&&$&&;.   ";
                    break;
                case 4:
                    cout << "     .:+$&&&&&&&&&&&&:..:..   ";
                    break;
                case 5:
                    cout << " .:$&X::&&&&&&&&&&&&X;.       ";
                    break;
                case 6:
                    cout << ".x+.. .+&XX&x;+x++;;x$+.      ";
                    break;
                case 7:
                    cout << "...  :X+...$+       .x;+;..   ";
                    break;
                case 8:
                    cout << "    .+:.   .X:.     .. ....   ";
                    break;
                case 9:
                    cout << "     :;.     :;. ";
                    break;
                }
            break;

        case 12://Fantino 12
            switch(riga)
            {
                case 1:
                    cout << "                 .:+XXxX:     ";
                    break;
                case 2:
                    cout << "        ........+$&&&&&&$;.   ";
                    break;
                case 3:
                    cout << "   ..;X$&&&&&&&&&&&&$:..:;.   ";
                    break;
                case 4:
                    cout << ";XX$x;.X&&&&&&&&&&&&$;..      ";
                    break;
                case 5:
                    cout << "    .:xXX&$::+xxx+;+X:+:      ";
                    break;
                case 6:
                    cout << "   .+x:+$;.        .:+;x      ";
                    break;
                case 7:
                    cout << " .;+.. .x           ..;x.     ";
                    break;
                case 8:
                    cout << "        .;:.                  ";
                    break;
                case 9:
                    cout << " ";
                    break;
                }
            break;
    }
}

void stampa_dado(unsigned short int dado, unsigned short int riga)
{
    switch(dado)
    {
        case 1: //Dado 1

            switch(riga)
            {
                case 1:
                    cout << " _______   ";
                    break;
                case 2:
                    cout << "|\\   /\\ \\  ";
                    break;
                case 3:
                    cout << "|0\\ _\\/__\\ ";
                    break;
                case 4:
                    cout << "|00|()  ()|";
                    break;
                case 5:
                    cout << " \\0|  ()  |";
                    break;
                case 6:
                    cout << "  \\|()__()|";
                    break;
            }
            break;
        case 2: //Dado 2

            switch(riga)
            {
                case 1:
                    cout << " _______   ";
                    break;
                case 2:
                    cout << "|\\()    \\  ";
                    break;
                case 3:
                    cout << "| \\ ___()\\ ";
                    break;
                case 4:
                    cout << "|0 |()    |";
                    break;
                case 5:
                    cout << " \\ |  ()  |";
                    break;
                case 6:
                    cout << "  \\|____()|";
                    break;
            }
            break;
        case 3: //Dado 3

            switch(riga)
            {
                case 1:
                    cout << " _______   ";
                    break;
                case 2:
                    cout << "|\\() /\\ \\  ";
                    break;
                case 3:
                    cout << "| \\ _\\/()\\ ";
                    break;
                case 4:
                    cout << "|0 |()  ()|";
                    break;
                case 5:
                    cout << " \\ |  ()  |";
                    break;
                case 6:
                    cout << "  \\|()__()|";
                    break;
            }
            break;
        case 4: //Dado 4

            switch(riga)
            {
                case 1:
                    cout << " _______   ";
                    break;
                case 2:
                    cout << "|\\()  ()\\  ";
                    break;
                case 3:
                    cout << "| \\()__()\\ ";
                    break;
                case 4:
                    cout << "|0 |()    |";
                    break;
                case 5:
                    cout << " \\ |      |";
                    break;
                case 6:
                    cout << "  \\|____()|";
                    break;
            }
            break;
        case 5: //Dado 5

            switch(riga)
            {
                case 1:
                    cout << " _______   ";
                    break;
                case 2:
                    cout << "|\\()()()\\  ";
                    break;
                case 3:
                    cout << "|0\\()__()\\ ";
                    break;
                case 4:
                    cout << "|0 |      |";
                    break;
                case 5:
                    cout << " \\0|  ()  |";
                    break;
                case 6:
                    cout << "  \\|______|";
                    break;
            }
            break;
        case 6: //Dado 6

            switch(riga)
            {
                case 1:
                    cout << " _______   ";
                    break;
                case 2:
                    cout << "|\\()()()\\  ";
                    break;
                case 3:
                    cout << "|0\\()()()\\ ";
                    break;
                case 4:
                    cout << "|00|    ()|";
                    break;
                case 5:
                    cout << " \\0|      |";
                    break;
                case 6:
                    cout << "  \\|()____|";
                    break;
            }

            break;
    }
}

void setup_gioco(int colonne, short unsigned int n_giocatori, short unsigned int lunghezza)
{
    srand(time(NULL));

    // Stampa i fantini
    for(int i = 0; i < n_giocatori; i++)
    {
        setColor(0, colori[i]);
        for(int j = 1; j < 10; j++)
        {
            gotoXY(2, j + i * 10);
            stampa_fantini(1, j);

        }
        for(int k = 0; k < lunghezza; k++)
            cout << "_";
    }

    setColor(0,2);

    short unsigned int random1 = rand() % 6 + 1;
    short unsigned int random2 = rand() % 6 + 1;
    // Stampa dadi
    for(int i = 0; i < 6; i++)
    {
        gotoXY(colonne - 30, i+1);
        stampa_dado(random1, i+1);
        cout << " ";
        stampa_dado(random2, i+1);
    }

    // Stampa box
    gotoXY(colonne - 30, 8);
    cout << " _________________________ ";
    gotoXY(colonne - 30, 9);
    cout << "/                         \\";
    gotoXY(colonne - 30, 10);
    cout << "|                         |";
    gotoXY(colonne - 30, 11);
    cout << "|                         |";
    gotoXY(colonne - 30, 12);
    cout << "|                         |";
    gotoXY(colonne - 30, 13);
    cout << "\\_________________________/";
}

void gioco(int colonne, short unsigned int n_giocatori, short unsigned int lunghezza, string nomi[])
{
    srand(time(NULL));
    //Inizializza le variabili
    const short unsigned int sleep_time = 100;
    short unsigned int turno = rand() % n_giocatori + 1;
    short unsigned int progressi[4] = {0};
    short unsigned int random1;
    short unsigned int random2;
    short unsigned int vincitore = 0;
    short unsigned int sum;

    do
    {
        // Scrive nella box ----------------
        gotoXY(colonne - 29, 9);
        cout << "                         ";
        gotoXY(colonne - 29, 9);
        cout << " E' il turno di";
        gotoXY(colonne - 29, 10);
        cout << "                         ";
        gotoXY(colonne - 29, 10);
        cout << " " << nomi[turno-1] << ".";
        gotoXY(colonne - 29, 11);
        cout << "                         ";
        gotoXY(colonne - 29, 11);
        cout << " Premi un tasto per";
        gotoXY(colonne - 29, 12);
        cout << "                         ";
        gotoXY(colonne - 29, 12);
        cout << " lanciare i dadi. ";
        if(nomi[turno-1] != "CPU")
            getch();

        // Genera e stampa i dadi ----------
        random1 = rand() % 6 + 1;
        random2 = rand() % 6 + 1;
        // Stampa dadi
        for(int i = 0; i < 6; i++)
        {
            gotoXY(colonne - 30, i+1);
            stampa_dado(random1, i+1);
            cout << " ";
            stampa_dado(random2, i+1);
        }
        sum = random1 + random2;
        if(random1 == random2)
                    sum += 1 + (float)sum*0.30;

        // Scrive nella box ----------------
        gotoXY(colonne - 29, 9);
        cout << "                         ";
        gotoXY(colonne - 29, 9);
        cout << " E' uscito " << sum;
        gotoXY(colonne - 29, 10);
        cout << "                         ";
        gotoXY(colonne - 29, 10);
        cout << " " << nomi[turno-1] << " avanza";
        gotoXY(colonne - 29, 11);
        cout << "                         ";
        gotoXY(colonne - 29, 11);
        cout << " di " << sum << " caselle.";
        gotoXY(colonne - 29, 12);
        cout << "                         ";
        gotoXY(colonne - 29, 12);
        cout << " Premi un tasto. ";

        // Animazione corsa -----------------
        setColor(0, colori[turno-1]);
        for(int i = progressi[turno-1], frame = 1; i < progressi[turno-1] + sum && i < lunghezza; i++)
        {
            Sleep(sleep_time);
            for(int j = 1; j < 10; j++)
            {
                gotoXY(i, j + (turno-1) * 10);
                cout <<"  ";
                stampa_fantini(frame, j);
            }
            frame++;
            if(frame == 13)
                frame = 1;
            Sleep(sleep_time);
            for(int j = 1; j < 10; j++)
            {
                gotoXY(i, j + (turno-1) * 10);
                cout <<"  ";
                stampa_fantini(frame, j);
            }
            frame++;
            if(frame == 13)
                frame = 1;
        }

        // Stabilizzazione post-animazione
        progressi[turno-1] += sum;
        Sleep(sleep_time);
        for(int j = 1; j < 10; j++)
        {
            gotoXY(progressi[turno-1], j + (turno-1) * 10);
            stampa_fantini(1, j);
        }
        for(int k = 0; k < lunghezza - progressi[turno-1]; k++)
                cout << "_";
        setColor(0,2);
        getch();

        // Torna indietro se multiplo di 5
        if(sum%5 == 0)
        {
            if(progressi[turno-1] >= 6)
                progressi[turno-1] -= 5;
            else
                progressi[turno-1] = 0;

            setColor(0, colori[turno-1]);
            for(int j = 1; j < 10; j++)
            {
                gotoXY(progressi[turno-1], j + (turno-1) * 10);
                stampa_fantini(1, j);
                if(j!=9)
                    cout << "             ";
            }
            for(int k = 0; k < lunghezza - progressi[turno-1]; k++)
                cout << "_";
            setColor(0,2);

            // Scrive nella box ----------------
            gotoXY(colonne - 29, 9);
            cout << "                         ";
            gotoXY(colonne - 29, 9);
            cout << " Oh no! Il cavallo di ";
            gotoXY(colonne - 29, 10);
            cout << "                         ";
            gotoXY(colonne - 29, 10);
            cout << " " << nomi[turno-1];
            gotoXY(colonne - 29, 11);
            cout << "                         ";
            gotoXY(colonne - 29, 11);
            cout << " e' inciampato!";
            gotoXY(colonne - 29, 12);
            cout << "                         ";
            gotoXY(colonne - 29, 12);
            cout << " Premi un tasto. ";
            getch();
        }

        // Controllo vincita e cambio turno
        if(progressi[turno-1] >= lunghezza)
            vincitore = turno;
        else
            if(turno != n_giocatori)
                turno++;
            else
                turno = 1;


    }while(vincitore == 0);

    // Annuncia il vincitore nella box ------------------------------------------
    gotoXY(colonne - 29, 9);
    cout << "                         ";
    gotoXY(colonne - 29, 9);
    cout << " Abbiamo un vincitore!" << sum;
    gotoXY(colonne - 29, 10);
    cout << "                         ";
    gotoXY(colonne - 29, 10);
    cout << " Ottimo lavoro";
    gotoXY(colonne - 29, 11);
    cout << "                         ";
    gotoXY(colonne - 29, 11);
    cout << " " << nomi[vincitore-1] << "!";
    gotoXY(colonne - 29, 12);
    cout << "                         ";
    gotoXY(colonne - 29, 12);
    cout << " Premi un tasto. ";
    getch();
}
