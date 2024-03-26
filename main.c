#include <stdio.h>
#include <stdlib.h>

/*
ZWISCHENTEST 2

Aufgabe
Schreiben Sie ein Programm das es dem Benutzer ermöglicht einen Zug, Waggon für Waggon, zusammen zu stellen.
Dabei hat jeder Waggon einen von drei vordefinierten Typen (Passagierwagen, Schlafwagen und Speisewagen)
und eine Kapazität (von 20 bis 130 Plätze). Ein Zug besteht aus maximal 10 Waggons.
Jeder Waggon hat eine eindeutige Position innerhalb des Zuges.

Ihr Programm soll ein Menü ausgeben, um folgende Aktionen beliebig oft durchzuführen:

    1.) den Zug mit allen Waggons anzeigen (print train)
    2.) einen neuen Waggon erfassen und an einer bestimmten Position in den Zug einfügen (new carriage)
    3.) eine Statistik zum Zug ausgeben (print stats)
    4.) das Programm beenden (exit)
*/

// Enumeration für Waggontypen
enum type{
    passenger, sleeper, diner
};

// Struktur für einen einzelnen Waggon
struct carriage {
    enum type typ;
    int capacity;
};

// Struktur für einen ganzen Zug (Kette von mehreren Waggons)
struct train {
    struct carriage carriages[10];
    int length;
};

/*
Die Funktion printCarriage() gibt den als Parameter übergebenen Waggon in folgendem Format aus: "[<Typ>:<Kapazität>]".
Dabei soll der Typ Passagierwagen mit 'P', Schlafwagen mit 'S' und Speisewagen mit 'D' angezeigt werden.
Die Kapazität soll dreistellig und mit führenden Nullen angezeigt werden. Die Funktion soll keinen Zeilenumbruch ausgeben.
*/

void printCarriage(struct carriage car){
    // Wenn ein Passagierwagen als Parameter übergeben wird:
    if(car.typ == passenger){
        printf("[P:%03d]", car.capacity);
    }
    // Wenn ein Schlafwagen als Parameter übergeben wird:
    if(car.typ == sleeper){
        printf("[S:%03d]", car.capacity);
    }
    // Wenn ein Speisewagen als Parameter übergeben wird:
    if(car.typ == diner){
        printf("[D:%03d]", car.capacity);
    }
}

/*
Die Funktion printTrain() gibt den als Parameter übergebenen Zug (Vorsicht: Zeiger) mit allen Waggons in folgendem Format aus:
"Train: <Position>:[<Typ>:<Kapazität>]-<Position>:[<Typ>:<Kapazität>]-... Length: <Zuglänge>".
Die Position entspricht dabei dem Index des Waggons im Feld.
Verwenden Sie zur Ausgabe der Waggons die Funktion zur Ausgabe eines Waggons.
Train: 0:[P:020]-1:[S:020] Length: 2
Wenn der Zug keine Waggons hat, muss "Train: No Carriages!" ausgegeben werden.
Train: No Carriages!
*/

void printTrain(struct train* zug){
    // Die Zuglänge in len speichern
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
        // Am Ende Zuglänge ausgeben:
        printf(" Length: %d", len);
    }
    // Wenn der Zug keine Waggons hat, wird "Train: No Carriages!" ausgegeben.
    else{
        printf("\nTrain: No Carriages!");
    }
}

/*
Allgemein zu Eingaben:
Leerzeichen und Zeilenumbrüche sollen ignoriert werden.
Wenn etwas Ungültiges eingegeben wurde, muss "Input invalid! Try again: " ausgegeben und erneut eingelesen werden.
Sie können sich aber darauf verlassen, dass Zeichen eingegeben werden, wenn Zeichen erwartet werden und Zahlen eingegeben werden, wenn Zahlen erwartet werden.
*/

/*
Die Funktion getMenu() erfragt welche Aktion ausgeführt werden soll und liefert ein entsprechendes Zeichen zurück.
*/

char getMenu(){
    char action;
    printf("\nChoose Action: print train (p), new carriage (n), print stats (s) or exit (x):");
    do{
        scanf("%c", &action);
        // Leerzeichen und Zeilenumbrüche sollen ignoriert werden:
        if (action == ' ' || action == '\n'){
            continue;
        }
        // Wenn etwas Ungültiges eingegeben wurde, wird "Input invalid! Try again: " ausgegeben.
        if(action != 'p' && action != 'n' && action != 's' && action != 'x'){
            printf("\nInput invalid! Try again:");
        }
    // Wenn etwas Gültiges eingegeben wurde, bricht die Schleife ab.
    }while(action != 'p' && action != 'n' && action != 's' && action != 'x');
    // Die Funktion gibt das letzte gültige eingelese Zeichen zurück.
    return action;
}

/*
Die Funktion getCarriage() erfragt den Waggontyp und die Kapazität des Waggons und liefert einen Waggon mit entsprechenden Werten zurück.
*/

struct carriage getCarriage(){
    char waggontyp;
    int capacity;
    struct carriage car;

    printf("\nChoose type of carriage: passenger (p), sleeper (s) or diner (d):");
    do{
        scanf("%c", &waggontyp);
        // Leerzeichen und Zeilenumbrüche sollen ignoriert werden:
        if (waggontyp == ' ' || waggontyp == '\n'){
            continue;
        }
        // Wenn etwas Ungültiges eingegeben wurde, wird "Input invalid! Try again: " ausgegeben.
        if (waggontyp != 'p' && waggontyp != 's' && waggontyp != 'd'){
            printf("\nInput invalid! Try again:");
        }
    // Wenn etwas Gültiges eingegeben wurde, bricht die Schleife ab.
    }while(waggontyp != 'p' && waggontyp != 's' && waggontyp != 'd');

    printf("\nChoose capacity (20 - 130):");
    do{
        scanf("%d", &capacity);
        // Wenn etwas Ungültiges eingegeben wurde, wird "Input invalid! Try again: " ausgegeben.
        if(capacity < 20 || capacity > 130){
            printf("\nInput invalid! Try again:");
        }
    // Wenn etwas Gültiges eingegeben wurde, bricht die Schleife ab.
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
    // Die Funktion gibt eine Waggon-Struktur zurück.
    return car;
}

/*
Die Funktion getPosition() erhält die Zuglänge als Parameter, erfragt die Position für einen neu einzuhängenden Wagon und liefert diese zurück.
Beispiel: Bei Zuglänge 2 gibt es daher 3 gültige Positionen: 0, 1, 2.
*/

int getPosition(int train_length){
    int position;
    printf("\nChoose position for the new carriage (0-%d):", train_length);
    do{
        scanf("%d", &position);
        // Wenn etwas Ungültiges eingegeben wurde, wird "Input invalid! Try again: " ausgegeben.
        if(position < 0 || position > train_length){
            printf("\nInput invalid! Try again:");
        }
    // Wenn etwas Gültiges eingegeben wurde, bricht die Schleife ab.
    }while(position < 0 || position > train_length);
    // Die Funktion gibt die Position zurück, an der der neue Waggon eingefügt werden soll.
    return position;
}


/*
Die Funktion insertCarriage() erhält einen Zeiger auf den Zug, eine Position an welcher der neue Waggon eingefügt werden soll und den einzufügenden Waggon.
Wenn 0 als Position übergeben wird, soll der Waggon am Anfang eingefügt werden.
Die Funktion muss bei Erfolg 0 und bei Fehler einen negativen Fehlercode zurückliefern:
-1 wenn der Zug bereits voll ist und -2 wenn die Position nicht gültig ist.
Ein Schlafwagen darf nur unmittelbar vor zwei aufeinanderfolgenden Passagierwagen eingefügt werden.
Falls diese Bedingung nicht erfüllt ist, muss -3 als Fehlercode zurückgeliefert werden.

Mögliches Vorgehen beim Einfügen:
Um einen neuen Waggon einzufügen, kann das Feld vom Ende bis zur übergebenen Position durchlaufen werden.
Dabei wird zuerst der letzte Waggon um eins nach rechts verschoben, danach der Vorletzte, usw. bis die Position erreicht ist,
an der der neue Waggon eingefügt werden soll.
Nachdem auch dieser Waggon verschoben wurde und die Position nun frei ist, kann der neue Waggon eingefügt werden.
*/

int insertCarriage(struct train* zug, int position, struct carriage car){
    // Fehlercode ist automatisch auf 0 gestellt:
    int code = 0;
    // Wenn der übergebene Zug bereits 10 Waggons hat, Fehlercode -1 ausgeben:
    if(zug->length == 10){
        code = -1;
    }
    // Wenn die Position an welcher der neue Waggon eingefügt werden soll nicht gültig ist, Fehlercode -2 ausgeben:
    else if(position < 0 || position > zug->length){
        code = -2;
    }
    // Wenn der neue Waggon am Ende des Zuges eingefügt werden soll:
    else if(position == zug->length){
        // Wenn es sich dabei um einen Schlafwagen handelt:
        if(car.typ == sleeper){
            code = -3;
        }
        // Wenn es sich dabei um einen Passagierwagen oder Speisewagen handelt, Waggon am Ende einfügen:
        else{
            zug->carriages[position] = car;
            zug->length = (zug->length) + 1;
        }
    }
    // Wenn der neue Waggon auf der vorletzten Stelle des Zuges eingefügt werden soll:
    else if(position == (zug->length)-1){
        // Wenn es sich dabei um einen Schlafwagen handelt:
        if(car.typ == sleeper){
            code = -3;
        }
        // Wenn es sich dabei um einen Passagierwagen oder Speisewagen handelt:
        else{
            // Alle Waggons vom Ende bis zur übergebenen (vorletzten) Position um eins nach Rechts verschieben:
            zug->carriages[position+1] = zug->carriages[position];
            // Waggon einfügen:
            zug->carriages[position] = car;
            zug->length = (zug->length) + 1;
        }
    }
    // Wenn der neue Waggon zwischen der ersten Stelle und 2 Stellen vor dem Ende des Zuges eingefügt werden soll:
    else if(position >= 0 && position < (zug->length)-1){
        // Wenn es sich dabei um einen Schlafwagen handelt:
        if(car.typ == sleeper){
            // Überprüfen, ob die folgenden zwei Waggons Passagierwagen sind:
            if(zug->carriages[position].typ == passenger && zug->carriages[position+1].typ == passenger){
                // Alle Waggons vom Ende bis zur übergebenen Position um eins nach Rechts verschieben:
                for(int i = (zug->length) - 1; i >= position; i--){
                    zug->carriages[i+1] = zug->carriages[i];
                }
                // Waggon einfügen:
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
            // Alle Waggons vom Ende bis zur übergebenen Position um eins nach Rechts verschieben:
            for(int i = (zug->length) - 1; i >= position; i--){
                zug->carriages[i+1] = zug->carriages[i];
            }
            // Waggon einfügen:
            zug->carriages[position] = car;
            zug->length = (zug->length) + 1;
        }
    }
    // Die Funktion gibt einen (Fehler-)Code zurück:
    return code;
}

/*
Die Funktion sumCapacity() erhält einen Zeiger auf den Zug und den Typ eines Waggons
und liefert die Summe der Kapazitäten aller Waggons des Zuges die diesen Typ haben zurück.
*/

int sumCapacity(struct train* zug, enum type waggontyp){
    // Kapazitätensumme mit 0 initialisieren:
    int capacity_sum = 0;
    // Über alle Waggons im übergebenen Zug iterieren:
    for(int i = 0; i <= (zug->length) - 1; ++i){
        // Wenn der Typ des Waggons mit dem übergebenen Typ übereinstimmt, Summe der Kapazitäten um Kapazität des Waggons erweitern:
        if(zug->carriages[i].typ == waggontyp){
            capacity_sum = capacity_sum + zug->carriages[i].capacity;
        }
    }
    // Die Funktion gibt die Summe der Kapazitäten aller Waggons des Zuges die den übergebenen Typ haben zurück:
    return capacity_sum;
}

/*
Die Funktion erhält einen Zeiger auf den Zug und gibt den Zug und eine Statistik zu den Kapazitäten der drei Waggontypen formatiert aus.
Zur Ausgabe des Zuges und zur Ermittlung der Kapazitätssummen nutzen Sie die Funktionen printTrain und sumCapacity.
Nach der Ausgabe des Zuges folgt eine Zeile mit "Capacities:" und dann eine Zeile pro Waggontyp (Einrückung 2 Leerzeichen):
für Passagierwagen: "  Passenger: <Summe>"
für Schlafwagen: "  Sleeper: <Summe>"
für Speisewagen: "  Diner: <Summe>"
Falls die Kapazität von Plätzen in den Passagierwagen kleiner als 65 ist, soll hinter der entsprechenden Summe " - invalid" ausgegeben werden.
*/

void printTrainStats(struct train* zug){
    // Den übergebenen Zug ausgeben:
    printTrain(zug);

    printf("\nCapacities:");
    // Wenn die Kapazität von Plätzen in den Passagierwagen kleiner als 65 ist, wird hinter der entsprechenden Summe " - invalid" ausgegeben.
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






