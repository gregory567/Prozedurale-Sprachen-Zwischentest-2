#include <stdio.h>
#include <stdlib.h>

/*
ZWISCHENTEST 2

Aufgabe
Schreiben Sie ein Programm das es dem Benutzer erm�glicht einen Zug, Waggon f�r Waggon, zusammen zu stellen.
Dabei hat jeder Waggon einen von drei vordefinierten Typen (Passagierwagen, Schlafwagen und Speisewagen)
und eine Kapazit�t (von 20 bis 130 Pl�tze). Ein Zug besteht aus maximal 10 Waggons.
Jeder Waggon hat eine eindeutige Position innerhalb des Zuges.

Ihr Programm soll ein Men� ausgeben, um folgende Aktionen beliebig oft durchzuf�hren:

    1.) den Zug mit allen Waggons anzeigen (print train)
    2.) einen neuen Waggon erfassen und an einer bestimmten Position in den Zug einf�gen (new carriage)
    3.) eine Statistik zum Zug ausgeben (print stats)
    4.) das Programm beenden (exit)
*/

// Enumeration f�r Waggontypen
enum type{
    passenger, sleeper, diner
};

// Struktur f�r einen einzelnen Waggon
struct carriage {
    enum type typ;
    int capacity;
};

// Struktur f�r einen ganzen Zug (Kette von mehreren Waggons)
struct train {
    struct carriage carriages[10];
    int length;
};

/*
Die Funktion printCarriage() gibt den als Parameter �bergebenen Waggon in folgendem Format aus: "[<Typ>:<Kapazit�t>]".
Dabei soll der Typ Passagierwagen mit 'P', Schlafwagen mit 'S' und Speisewagen mit 'D' angezeigt werden.
Die Kapazit�t soll dreistellig und mit f�hrenden Nullen angezeigt werden. Die Funktion soll keinen Zeilenumbruch ausgeben.
*/

void printCarriage(struct carriage car){
    // Wenn ein Passagierwagen als Parameter �bergeben wird:
    if(car.typ == passenger){
        printf("[P:%03d]", car.capacity);
    }
    // Wenn ein Schlafwagen als Parameter �bergeben wird:
    if(car.typ == sleeper){
        printf("[S:%03d]", car.capacity);
    }
    // Wenn ein Speisewagen als Parameter �bergeben wird:
    if(car.typ == diner){
        printf("[D:%03d]", car.capacity);
    }
}

/*
Die Funktion printTrain() gibt den als Parameter �bergebenen Zug (Vorsicht: Zeiger) mit allen Waggons in folgendem Format aus:
"Train: <Position>:[<Typ>:<Kapazit�t>]-<Position>:[<Typ>:<Kapazit�t>]-... Length: <Zugl�nge>".
Die Position entspricht dabei dem Index des Waggons im Feld.
Verwenden Sie zur Ausgabe der Waggons die Funktion zur Ausgabe eines Waggons.
Train: 0:[P:020]-1:[S:020] Length: 2
Wenn der Zug keine Waggons hat, muss "Train: No Carriages!" ausgegeben werden.
Train: No Carriages!
*/

void printTrain(struct train* zug){
    // Die Zugl�nge in len speichern
    int len = zug->length;
    // Wenn der Zug mehr als 0 Waggons hat:
    if(len != 0){
        printf("\nTrain: ");
        for(int i = 0; i < len; i++){
            // Die Position entspricht dem Index des Waggons im Feld.
            printf("%d:", i);
            // Zur Ausgabe der Waggons wird die Funktion zur Ausgabe eines Waggons verwendet.
            printCarriage(zug->carriages[i]);
            // Bindestrich wird nur ausgegeben wenn der Zug mehr als einen Waggon hat.
            // Bindestrich wird nur bis nach dem vorletzten Waggon (vor dem letzten Waggon) ausgegeben.
            if(len > 1 && i < len - 1){
                printf("-");
            }
        }
        // Am Ende Zugl�nge ausgeben:
        printf(" Length: %d", len);
    }
    // Wenn der Zug keine Waggons hat, wird "Train: No Carriages!" ausgegeben.
    else{
        printf("\nTrain: No Carriages!");
    }
}

/*
Allgemein zu Eingaben:
Leerzeichen und Zeilenumbr�che sollen ignoriert werden.
Wenn etwas Ung�ltiges eingegeben wurde, muss "Input invalid! Try again: " ausgegeben und erneut eingelesen werden.
Sie k�nnen sich aber darauf verlassen, dass Zeichen eingegeben werden, wenn Zeichen erwartet werden und Zahlen eingegeben werden, wenn Zahlen erwartet werden.
*/

/*
Die Funktion getMenu() erfragt welche Aktion ausgef�hrt werden soll und liefert ein entsprechendes Zeichen zur�ck.
*/

char getMenu(){
    char action;
    printf("\nChoose Action: print train (p), new carriage (n), print stats (s) or exit (x):");
    do{
        scanf("%c", &action);
        // Leerzeichen und Zeilenumbr�che sollen ignoriert werden:
        if (action == ' ' || action == '\n'){
            continue;
        }
        // Wenn etwas Ung�ltiges eingegeben wurde, wird "Input invalid! Try again: " ausgegeben.
        if(action != 'p' && action != 'n' && action != 's' && action != 'x'){
            printf("\nInput invalid! Try again:");
        }
    // Wenn etwas G�ltiges eingegeben wurde, bricht die Schleife ab.
    }while(action != 'p' && action != 'n' && action != 's' && action != 'x');
    // Die Funktion gibt das letzte g�ltige eingelese Zeichen zur�ck.
    return action;
}

/*
Die Funktion getCarriage() erfragt den Waggontyp und die Kapazit�t des Waggons und liefert einen Waggon mit entsprechenden Werten zur�ck.
*/

struct carriage getCarriage(){
    char waggontyp;
    int capacity;
    struct carriage car;

    printf("\nChoose type of carriage: passenger (p), sleeper (s) or diner (d):");
    do{
        scanf("%c", &waggontyp);
        // Leerzeichen und Zeilenumbr�che sollen ignoriert werden:
        if (waggontyp == ' ' || waggontyp == '\n'){
            continue;
        }
        // Wenn etwas Ung�ltiges eingegeben wurde, wird "Input invalid! Try again: " ausgegeben.
        if (waggontyp != 'p' && waggontyp != 's' && waggontyp != 'd'){
            printf("\nInput invalid! Try again:");
        }
    // Wenn etwas G�ltiges eingegeben wurde, bricht die Schleife ab.
    }while(waggontyp != 'p' && waggontyp != 's' && waggontyp != 'd');

    printf("\nChoose capacity (20 - 130):");
    do{
        scanf("%d", &capacity);
        // Wenn etwas Ung�ltiges eingegeben wurde, wird "Input invalid! Try again: " ausgegeben.
        if(capacity < 20 || capacity > 130){
            printf("\nInput invalid! Try again:");
        }
    // Wenn etwas G�ltiges eingegeben wurde, bricht die Schleife ab.
    }while(capacity < 20 || capacity > 130);

    if(waggontyp == 'p'){
        //car = (struct carriage){passenger, capacity}; funktioniert hier auch
        car.typ = passenger;
        car.capacity = capacity;
    }
    else if(waggontyp == 's'){
        //car = (struct carriage){sleeper, capacity}; funktioniert hier auch
        car.typ = sleeper;
        car.capacity = capacity;
    }
    else if(waggontyp == 'd'){
        //car = (struct carriage){diner, capacity}; funktioniert hier auch
        car.typ = diner;
        car.capacity = capacity;
    }
    // Die Funktion gibt eine Waggon-Struktur zur�ck.
    return car;
}

/*
Die Funktion getPosition() erh�lt die Zugl�nge als Parameter, erfragt die Position f�r einen neu einzuh�ngenden Wagon und liefert diese zur�ck.
Beispiel: Bei Zugl�nge 2 gibt es daher 3 g�ltige Positionen: 0, 1, 2.
*/

int getPosition(int train_length){
    int position;
    printf("\nChoose position for the new carriage (0-%d):", train_length);
    do{
        scanf("%d", &position);
        // Wenn etwas Ung�ltiges eingegeben wurde, wird "Input invalid! Try again: " ausgegeben.
        if(position < 0 || position > train_length){
            printf("\nInput invalid! Try again:");
        }
    // Wenn etwas G�ltiges eingegeben wurde, bricht die Schleife ab.
    }while(position < 0 || position > train_length);
    // Die Funktion gibt die Position zur�ck, an der der neue Waggon eingef�gt werden soll.
    return position;
}


/*
Die Funktion insertCarriage() erh�lt einen Zeiger auf den Zug, eine Position an welcher der neue Waggon eingef�gt werden soll und den einzuf�genden Waggon.
Wenn 0 als Position �bergeben wird, soll der Waggon am Anfang eingef�gt werden.
Die Funktion muss bei Erfolg 0 und bei Fehler einen negativen Fehlercode zur�ckliefern:
-1 wenn der Zug bereits voll ist und -2 wenn die Position nicht g�ltig ist.
Ein Schlafwagen darf nur unmittelbar vor zwei aufeinanderfolgenden Passagierwagen eingef�gt werden.
Falls diese Bedingung nicht erf�llt ist, muss -3 als Fehlercode zur�ckgeliefert werden.

M�gliches Vorgehen beim Einf�gen:
Um einen neuen Waggon einzuf�gen, kann das Feld vom Ende bis zur �bergebenen Position durchlaufen werden.
Dabei wird zuerst der letzte Waggon um eins nach rechts verschoben, danach der Vorletzte, usw. bis die Position erreicht ist,
an der der neue Waggon eingef�gt werden soll.
Nachdem auch dieser Waggon verschoben wurde und die Position nun frei ist, kann der neue Waggon eingef�gt werden.
*/

int insertCarriage(struct train* zug, int position, struct carriage car){
    // Fehlercode ist automatisch auf 0 gestellt:
    int code = 0;
    // Wenn der �bergebene Zug bereits 10 Waggons hat, Fehlercode -1 ausgeben:
    if(zug->length == 10){
        code = -1;
    }
    // Wenn die Position an welcher der neue Waggon eingef�gt werden soll nicht g�ltig ist, Fehlercode -2 ausgeben:
    else if(position < 0 || position > zug->length){
        code = -2;
    }
    // Wenn der neue Waggon am Ende des Zuges eingef�gt werden soll:
    else if(position == zug->length){
        // Wenn es sich dabei um einen Schlafwagen handelt:
        if(car.typ == sleeper){
            code = -3;
        }
        // Wenn es sich dabei um einen Passagierwagen oder Speisewagen handelt, Waggon am Ende einf�gen:
        else{
            zug->carriages[position] = car;
            zug->length = (zug->length) + 1;
        }
    }
    // Wenn der neue Waggon auf der vorletzten Stelle des Zuges eingef�gt werden soll:
    else if(position == (zug->length)-1){
        // Wenn es sich dabei um einen Schlafwagen handelt:
        if(car.typ == sleeper){
            code = -3;
        }
        // Wenn es sich dabei um einen Passagierwagen oder Speisewagen handelt:
        else{
            // Alle Waggons vom Ende bis zur �bergebenen (vorletzten) Position um eins nach Rechts verschieben:
            zug->carriages[position+1] = zug->carriages[position];
            // Waggon einf�gen:
            zug->carriages[position] = car;
            zug->length = (zug->length) + 1;
        }
    }
    // Wenn der neue Waggon zwischen der ersten Stelle und 2 Stellen vor dem Ende des Zuges eingef�gt werden soll:
    else if(position >= 0 && position < (zug->length)-1){
        // Wenn es sich dabei um einen Schlafwagen handelt:
        if(car.typ == sleeper){
            // �berpr�fen, ob die folgenden zwei Waggons Passagierwagen sind:
            if(zug->carriages[position].typ == passenger && zug->carriages[position+1].typ == passenger){
                // Alle Waggons vom Ende bis zur �bergebenen Position um eins nach Rechts verschieben:
                for(int i = (zug->length) - 1; i >= position; i--){
                    zug->carriages[i+1] = zug->carriages[i];
                }
                // Waggon einf�gen:
                zug->carriages[position] = car;
                zug->length = (zug->length) + 1;
            }
            // Wenn nur einer der folgenden zwei Waggons oder keiner von den beiden ein Passagierwagen sind, Fehlercode -3 ausgeben:
            else{
                code = -3;
            }
        }
        // Wenn es sich dabei um einen Passagierwagen oder Speisewagen handelt:
        else{
            // Alle Waggons vom Ende bis zur �bergebenen Position um eins nach Rechts verschieben:
            for(int i = (zug->length) - 1; i >= position; i--){
                zug->carriages[i+1] = zug->carriages[i];
            }
            // Waggon einf�gen:
            zug->carriages[position] = car;
            zug->length = (zug->length) + 1;
        }
    }
    // Die Funktion gibt einen (Fehler-)Code zur�ck:
    return code;
}

/*
Die Funktion sumCapacity() erh�lt einen Zeiger auf den Zug und den Typ eines Waggons
und liefert die Summe der Kapazit�ten aller Waggons des Zuges die diesen Typ haben zur�ck.
*/

int sumCapacity(struct train* zug, enum type waggontyp){
    // Kapazit�tensumme mit 0 initialisieren:
    int capacity_sum = 0;
    // �ber alle Waggons im �bergebenen Zug iterieren:
    for(int i = 0; i <= (zug->length) - 1; ++i){
        // Wenn der Typ des Waggons mit dem �bergebenen Typ �bereinstimmt, Summe der Kapazit�ten um Kapazit�t des Waggons erweitern:
        if(zug->carriages[i].typ == waggontyp){
            capacity_sum = capacity_sum + zug->carriages[i].capacity;
        }
    }
    // Die Funktion gibt die Summe der Kapazit�ten aller Waggons des Zuges die den �bergebenen Typ haben zur�ck:
    return capacity_sum;
}

/*
Die Funktion erh�lt einen Zeiger auf den Zug und gibt den Zug und eine Statistik zu den Kapazit�ten der drei Waggontypen formatiert aus.
Zur Ausgabe des Zuges und zur Ermittlung der Kapazit�tssummen nutzen Sie die Funktionen printTrain und sumCapacity.
Nach der Ausgabe des Zuges folgt eine Zeile mit "Capacities:" und dann eine Zeile pro Waggontyp (Einr�ckung 2 Leerzeichen):
f�r Passagierwagen: "  Passenger: <Summe>"
f�r Schlafwagen: "  Sleeper: <Summe>"
f�r Speisewagen: "  Diner: <Summe>"
Falls die Kapazit�t von Pl�tzen in den Passagierwagen kleiner als 65 ist, soll hinter der entsprechenden Summe " - invalid" ausgegeben werden.
*/

void printTrainStats(struct train* zug){
    // Den �bergebenen Zug ausgeben:
    printTrain(zug);

    printf("\nCapacities:");
    // Wenn die Kapazit�t von Pl�tzen in den Passagierwagen kleiner als 65 ist, wird hinter der entsprechenden Summe " - invalid" ausgegeben.
    if(sumCapacity(zug, passenger) < 65){
        printf("\n  Passenger: %d - invalid", sumCapacity(zug, passenger));
    }
    else{
        printf("\n  Passenger: %d", sumCapacity(zug, passenger));
    }
    printf("\n  Sleeper: %d", sumCapacity(zug, sleeper));
    printf("\n  Diner: %d", sumCapacity(zug, diner));
}


int main() {

    char menu_input;
    int fehler_code;
    struct train zug = {.length = 0};
    int car_cnt = 0;

    do{
        menu_input = getMenu();
        if(menu_input == 'p'){
            printTrain(&zug);
        }
        else if(menu_input == 'n'){
            fehler_code = insertCarriage(&zug, getPosition(car_cnt), getCarriage());
            if(fehler_code == -1){
                printf("\nError: Train too long!");
            }
            else if(fehler_code == -2){
                printf("\nError: Position not possible!");
            }
            else if(fehler_code == -3){
                printf("\nError: Sleeper only possible directly before two passenger carriages!");
            }
            else{
                car_cnt = car_cnt + 1;
            }
        }
        else if(menu_input == 's'){
            printTrainStats(&zug);
        }
    }while(menu_input != 'x');

    return 0;
}






