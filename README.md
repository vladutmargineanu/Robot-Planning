# Data-Structures
Homeworks for the Data Structures course @ ACS, UPB 2018.

# Robot-Planning
 Data inceperii temei: 19-03-2018
 Data finalizarii temei: 04-04-2018

 Problemele intampinate:
 - enunt ambiguu (neexplicit) sau greu de inteles
 - memory-leak-uri
 - transmiterea multor paramtrii in functii
 - erori de coding-style
 - solutie nefunctionala: retinerea ultimei comenzi procesate de un robot
   intr-o structura (la intalnirea a doua comenzii consecutive de UNDO,
   rezultatul era gresit)
   
# Algorithm

 In rezolvarea problemei, am folosit functii pentru fiecare comanda primita de robot. Astfel, am 8 functii care indeplinesc cate o sarcina in functie de comanda:
 - add_get_box; (este de tip void, adaug comanda de tip add-get in coada robotului respectiv, Robots[RobotsId], in functie de prioritate)
 - add_drop_box; (este de tip void, adaug comanda de tip add-drop in coada robotului respectiv, Robots[RobotsId], in functie de prioritate)
 - execute; (este de tip void, execut prima comanda din coada robotului respectiv, Robots[RobotsId] si modificam numarul cutiilor cu numarul real cu care se proceseaza comanda, din map sau din number_boxes,care retine numarul de cutii pentru fiecare robot in functie de tipul comenzii get sau drop)
 - print_commands; (este de tip void, afisez comenziile din coada Robotului respectiv, Robots[RobotsId])
 - last_executed_commands;(este de tip void, afisam ultima comanda executata retinuta in coada History_Exe)
 - undo; (este de tip void, anulez efectul ultimei comenzi de tipul ADD sau EXECUTE, retinute in coada OrderComm si stiva History)
 - how_much_time; (returneaza un întreg reprezentând cât timp a stat LAST_EXECUTED_COMMAND în coada robotului său, înainte să fie executată cu ajutorul cozi Time, care se actualizeaza in functiile execute si undo)
 - how_many_boxes. (returneaza un întreg reprezentând câte cutii cară în acel moment de timp robotul cu id-ul RobotId, care sunt memorate in vectorul number_boxes)
 
 Pentru retinerea datelor am folosit variabile de tip Deque si Stack, transmise prin referinta in functiile de mai sus dupa cum urmeaza:
- Robots => este un vector de cozi, fiecare coada reprezinta cate un robot in care retin comenzile adaugate pentru a le prelucra in functiile execute si undo.
- OrderComm => este o coada in care memorez comenziile de tip add-get si add-drop, adaugate in coada fiecarui robot in functiile add_get_box si add_drop_box. In functia execute, retin comanda executata pentru anularea efectului comenzii execute in functia undo, in cazul in care ultima comanda adaugata in coada robotului a fost executata.
- Time => este o coada in care memorez momentul cand se executa o comanda, pentru calcularea timpului cat stat ultima comanda executata in coada robotului in functia how_much_time. In cazul in care se face UNDO pe o comanda de tip execute, se serge timpul comenzii executate (actualizam timpul);
- Hostory_Exe =>  este o coada in care retin fiecare comanda executata pentru afisarea in functia last_executed_command. In cazul in care se face UNDO pe o comanda de tip EXECUTE, stergem ultima comanda stocata in variabila coada.
- History => este o stiva in care memorez tipul (numele) comenzii adaugate in coada robotului respectiv in functiile add_get_box sau add_drop_box, iar in functia execute retin tipul EXECUTE. Aceasta stiva ma ajuta in functia UNDO, deoarece stiu ce fel de comanda trebuie anulata.
 
 In functia main, prelucrez informatiile in instructiunea switch, pentru usurinta, citindu-se din fisier comenziile care trebuie procesate si apelandu-se functiile respecive. Am definit o functie pentru a returna o constanta de tip intreg, in functie de comanda procesata din fisier. Parametrii functiilor care se modifica, sunt transmise prin referinta. Dupa terminarea citirii din fisier, se fac dezalocarile necesare la datele alocate dinamic.
