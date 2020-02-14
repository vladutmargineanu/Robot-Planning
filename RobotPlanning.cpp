/* Copyright 2018 Margineanu Nicolae-Vladut */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "Stack.h"
#include "Deque.h"

std::ifstream in("robots.in");
std::ofstream out("robots.out");

/* definesc o structura pentru a retine 
   caracteristiciile fiecarei comenzi */
struct  Command {
    std::string CommandType;
    int x, y, NrBoxes, Boxes, Priority, time, RobotId;
};

enum string_commands {
        ADD_GET_BOX,
        ADD_DROP_BOX,
        UNDO,
        EXECUTE,
        PRINT_COMMANDS,
        HOW_MUCH_TIME,
        HOW_MANY_BOXES,
        LAST_EXECUTED_COMMAND
};

/* definesc o functie care ne returneaza constante de tip intreg
  pentru citirea fiecarei comenzi in instructiunea switch din main */
string_commands command(std::string const& CommandType) {
        if (CommandType == "ADD_GET_BOX") return ADD_GET_BOX;
        if (CommandType == "ADD_DROP_BOX") return ADD_DROP_BOX;
        if (CommandType == "UNDO") return UNDO;
        if (CommandType == "EXECUTE") return EXECUTE;
        if (CommandType == "PRINT_COMMANDS") return PRINT_COMMANDS;
        if (CommandType == "HOW_MUCH_TIME") return HOW_MUCH_TIME;
        if (CommandType == "HOW_MANY_BOXES") return HOW_MANY_BOXES;
        return LAST_EXECUTED_COMMAND;
}

/* adaug comanda de tip add-get in coada robotului
   respectiv in functie de prioritate */
void add_get_box(int total_time, Deque<Command> *Robots,
                  Stack<std::string, 40> &History, Deque<Command> &OrderComm) {
  int RobotId, x, y, NrBoxes, Priority;
  Command last_command;   // retin caracteristiciile comenzii
  in >> RobotId >> x >> y >> NrBoxes >> Priority;
  last_command.CommandType = "ADD_GET_BOX";
  last_command.x = x;
  last_command.y = y;
  last_command.NrBoxes = NrBoxes;
  last_command.Priority = Priority;
  // retin momentul adaugarii comenzii in coada robotului
  last_command.time = total_time;
  // voi retine in campul Boxes numarul real de cutii prelucrate
  last_command.Boxes = NrBoxes;
  last_command.RobotId = RobotId;
  if (Priority == 0) {
    Robots[RobotId].push_front(last_command);
  } else {
    Robots[RobotId].push_back(last_command);
  }
  // retin comanda in coada OrderComm
  OrderComm.push_front(last_command);
  // retin numele comenzii in stiva History
  History.push(last_command.CommandType);
}

/* adaug comanda de tip add-drop in coada robotului
   respectiv in functie de prioritate */
void add_drop_box(int total_time, Deque<Command> *Robots,
                   Stack<std::string, 40> &History, Deque<Command> &OrderComm) {
  int RobotId, x, y, NrBoxes, Priority;
  Command last_command;  // retinem caracteristiciile comenzii
  in >> RobotId >> x >> y >> NrBoxes >> Priority;
  last_command.CommandType = "ADD_DROP_BOX";
  last_command.x = x;
  last_command.y = y;
  last_command.NrBoxes = NrBoxes;
  last_command.Priority = Priority;
  // retin momentul adaugarii comenzii in coada robotului
  last_command.time = total_time;
  // voi retine in campul Boxes numarul real de cutii prelucrate
  last_command.Boxes = NrBoxes;
  last_command.RobotId = RobotId;

  if (Priority == 0) {
    Robots[RobotId].push_front(last_command);
  } else {
    Robots[RobotId].push_back(last_command);
  }
  // retin comanda in coada OrderComm
  OrderComm.push_front(last_command);
  // retin numele comenzii in stiva History
  History.push(last_command.CommandType);
}

/* execut prima comanda din coada robotului respectiv si modific
   numarul cutiilor in functie de tipul comenzii get sau drop */
void execute(int total_time, int **map, int *number_boxes,
              Deque<Command> *Robots, Stack<std::string, 40> &History,
              Deque<Command> &OrderComm, Deque<Command> &History_Exe,
              Deque<int> &Time) {
  int RobotId = -1, x = -1, y = -1, NrBoxes = -1;
  std::string CommandType;
  in >> RobotId;
  if (Robots[RobotId].isEmpty()) {
    out << "EXECUTE: No command to execute\n";
  } else {
    Time.push_front(total_time);  // retinem momentul executarii
    CommandType = Robots[RobotId].front().CommandType;
    x = Robots[RobotId].front().x;
    y = Robots[RobotId].front().y;
    NrBoxes = Robots[RobotId].front().NrBoxes;
    if (CommandType == "ADD_GET_BOX") {
      // comanda este de tipul get
      if (map[x][y] < NrBoxes) {
        NrBoxes = map[x][y];
      }
      map[x][y] -= NrBoxes;
      number_boxes[RobotId] += NrBoxes;
    } else {
      // comanda este de tipul drop
      if (number_boxes[RobotId] < NrBoxes) {
        NrBoxes = number_boxes[RobotId];
      }
      number_boxes[RobotId] -= NrBoxes;
      map[x][y] += NrBoxes;
    }
    // retin comanda executata
    History_Exe.push_front(Robots[RobotId].front());
    History_Exe.front().Boxes = NrBoxes;  // memoram numarul real de cutii
    // daca se executa, se adauga in coada OrderComm
    OrderComm.push_front(Robots[RobotId].front());
    OrderComm.front().Boxes = NrBoxes;  // modificam numarul real de cutii
    // sterg comanda din coada Robotului respectiv
    Robots[RobotId].pop_front();
    // retin tipul comenzii
    History.push("EXECUTE");
  }
}

// afisez comenziile din coada Robotului respectiv
void print_commands(Deque<Command> *Robots) {
  int RobotId;
  in >> RobotId;
    if (Robots[RobotId].isEmpty()) {
        out << "PRINT_COMMANDS: No command found\n";
    } else {
      out << "PRINT_COMMANDS: "<< RobotId << ": ";
      out << Robots[RobotId] << "\n";
    }
}

// afisez ultima comanda executata retinuta in coada History_Exe
void last_executed_commands(Deque<Command> &History_Exe) {
  if ( History_Exe.isEmpty() ) {
    out << "LAST_EXECUTED_COMMAND: No command executed\n";
  } else {
    out << "LAST_EXECUTED_COMMAND: " << History_Exe.front().RobotId << ": ";
    if (History_Exe.front().CommandType == "ADD_GET_BOX") {
          out << "GET ";
      } else {
        out << "DROP ";
      }
    out << History_Exe.front().x << ' ' << History_Exe.front().y
        << ' ' << History_Exe.front().Boxes << "\n";
    }
}

/* Anulez efectul ultimei comenzi de tipul ADD sau EXECUTE */
void undo(int total_time, int **map, int *number_boxes,
           Deque<Command> *Robots, Stack<std::string, 40> &History,
           Deque<Command> &OrderComm, Deque<Command> &History_Exe,
           Deque<int> &Time) {
  if ( History.isEmpty() ) {
    out << "UNDO: No History\n";
  } else if (History.peek() == "ADD_DROP_BOX"
             || History.peek() == "ADD_GET_BOX") {
          // ultima comanda este de tip ADD sau GET
           int level = OrderComm.front().RobotId;
          // sterg comanda din coada robotului in functie de prioritate
           if (OrderComm.front().Priority == 1) {
             Robots[level].pop_back();
           } else {
             Robots[level].pop_front();
           }
           // sterg comanda din OrderComm
           OrderComm.pop_front();
           // sterg tipul comenzii din stiva History
           History.pop();

  } else {
           // capul stivei History.peek() are valoarea EXECUTE
          History.pop();
          int level = OrderComm.front().RobotId;

          OrderComm.front().time = total_time;
          Robots[level].push_front(OrderComm.front());
          Robots[level].front().NrBoxes = OrderComm.front().Boxes;

          if (OrderComm.front().CommandType == "ADD_GET_BOX") {
            // comanda este de tipul get
            number_boxes[level] -= OrderComm.front().Boxes;
            map[OrderComm.front().x][OrderComm.front().y]
             += OrderComm.front().Boxes;
          } else {
            // comanda este de tipul drop
            number_boxes[level] += OrderComm.front().Boxes;
            map[OrderComm.front().x][OrderComm.front().y] -=
             OrderComm.front().Boxes;
          }
          // sterg ultima comanda executata din coada History_Exe
          History_Exe.pop_front();
          // sterg comanda din OrderComm
          OrderComm.pop_front();
          // sterg momentul executarii din coada Time
          Time.pop_front();
  }
}

void how_much_time(Deque<int> &Time, Deque<Command> &History_Exe) {
  if ( History_Exe.isEmpty() ) {
    out << "HOW_MUCH_TIME: No command was executed\n";
  } else {
    out << "HOW_MUCH_TIME: " << Time.front() - History_Exe.front().time << "\n";
  }
}

void how_many_boxes(int *number_boxes) {
  int RobotId;
  in >> RobotId;
  out << "HOW_MANY_BOXES: " << number_boxes[RobotId] << "\n";
}

int main() {
  int N, LIN, COL, **map, i, j;
  int total_time = 0;
  in >> N >> LIN >> COL;
  /* Robots este un vector de cozi care reprezinta fiecare robot si 
    retin comenzile adaugate intr-o coada pentru fiecare robot */
  Deque<Command> *Robots = new Deque<Command>[N];
  /* Time este o coada in care memorez momentul
     cand se executa o comanda */
  Deque<int> Time;
  /* OrderComm este o coada in care memorez comenziile de tip add,
   adaugate in coada fiecarui robot si la executia fiecarei comenzi */
  Deque<Command> OrderComm;
  /* History este o stiva in care memorez tipul comenzii 
    adaugate in coada robotului respectiv sau tipul EXECUTE */
  Stack<std::string, 40> History;
  // History_Exe este o coada in care retin fiecare comanda executata
  Deque<Command> History_Exe;
  // inmagazinez numarul de cutii ale fiecarui robot intr-un vector dinamic
  int* number_boxes = new int[N];
  // initializez vectorul cu elemente nule
  for (i = 0; i < N; i++) {
    number_boxes[i] = 0;
  }
  // aloc memorie dinamica pntru matricea map
  map = new int*[LIN];

  for (i = 0; i < LIN; i++) {
    map[i] = new int[COL];
  }

  for (i = 0; i < LIN; i++) {
    for (j = 0; j < COL; j++) {
      in >> map[i][j];
    }
  }

  std::string inComm;
  while (in >> inComm) {
    // in total_time retin numarul de comenzi citite
    ++total_time;
    switch (command(inComm)) {
      case ADD_GET_BOX:
        add_get_box(total_time, Robots, History, OrderComm);
        break;
      case ADD_DROP_BOX:
        add_drop_box(total_time, Robots, History, OrderComm);
        break;
      case UNDO:
        undo(total_time, map, number_boxes, Robots,
            History, OrderComm, History_Exe, Time);
        break;
      case EXECUTE:
        execute(total_time, map, number_boxes, Robots,
                History, OrderComm, History_Exe, Time);
        break;
      case PRINT_COMMANDS:
        print_commands(Robots);
        break;
      case LAST_EXECUTED_COMMAND:
        last_executed_commands(History_Exe);
        break;
      case HOW_MUCH_TIME:
        how_much_time(Time, History_Exe);
        break;
      case HOW_MANY_BOXES:
        how_many_boxes(number_boxes);
        break;
    }
  }
// sterg alocarile dinamice
  for (i = 0; i < LIN; i++) {
    delete[] map[i];
  }
  delete[] number_boxes;
  delete[] map;
  delete[] Robots;
  return 0;
}
