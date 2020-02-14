/* Copyright 2018 Margineanu Nicolae-Vladut */
#ifndef DEQUE_H__
#define DEQUE_H__

template <typename T>

struct Node {
    T data;
    Node<T> *next;
    Node<T> *prev;

    // Constructor
    explicit Node(T data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class Deque {
 private:
    Node<T> *head;
    Node<T> *tail;
    int numElements;

 public:
    // Conctructor
    Deque() {
        head = nullptr;
        tail = nullptr;
        numElements = 0;
    }
    // Copy-constructor
    // Coada mea nu trebuie sa copieze o alta coada
    Deque(const Deque &object) {}

     // Destructor
    ~Deque() {
        if (!this->isEmpty()) {
            Node<T> *aux = head;
            while (head) {
                head = head->next;
                delete aux;
                aux = head;
            }
        }
    }

    // Copy-assignment
    // Coada mea nu trebuie sa i se atribuie unei alte cozii
    Deque& operator=(const Deque& obj) {}

    // adaugare element la sfarsit
    void push_back(T data) {
       if (isEmpty()) {
        head = new Node<T>(data);
        tail = head;
        } else {
         Node<T> *aux = new Node<T>(data);
         aux->prev = tail;
         tail->next = aux;
         tail = aux;
        }
        ++numElements;
    }

    // adaugare element la inceput
    void push_front(T data) {
        if (isEmpty()) {
            head = new Node<T>(data);
            tail = head;
        } else {
            Node<T> *aux = new Node<T>(data);
            aux -> next = head;
            head -> prev = aux;
	        head = aux;
        }
        ++numElements;
    }

    // stergere element la sfarsit
    void pop_back() {
        if (!isEmpty()) {
            if (head == tail) {
             // deque are un singur nod
              delete head;
              head = tail = nullptr;
            } else {
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
            }
            --numElements;
        }
    }

    // stergere element la inceput
    void pop_front() {
        if (!isEmpty()) {
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            } else {
                head = head->next;
                delete head->prev;
                head->prev = nullptr;
            }
            --numElements;
        }
    }

    // afisare ultimul element
    T& back() {
        return tail->data;
    }

    // afisare primul element
    T& front() {
        return head->data;
    }

    bool isEmpty() {
        return (!numElements) ? true : false;
    }

    int size() {
        return numElements;
    }

    Node<T> *getHead() {
        return head;
    }

    // supraincarcarea operatorului ostream <<
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, Deque<U>& list);
};

/* Operatorul << (ostream) este prieten cu clasa Deque, deci ii poate
   accesa membrii, chiar daca acestia sunt private. */
template <typename T>
std::ostream& operator<<(std::ostream& out, Deque<T>& list) {
    Node<T> *curr = list.getHead();

    if (list.size() > 0) {
        while (curr->next != nullptr) {
          if (curr->data.CommandType == "ADD_GET_BOX") {
                out << "GET ";
      } else {
       out << "DROP ";
      }
            out << curr->data.x << ' ' <<curr->data.y
                << ' ' <<curr->data.NrBoxes << "; ";
            curr = curr->next;
        }
        if (curr->data.CommandType == "ADD_GET_BOX") {
                out << "GET ";
      } else {
       out << "DROP ";
      }
        out << curr->data.x << ' ' <<curr->data.y
                << ' ' <<curr->data.NrBoxes;
    }
    return out;
}
#endif  // DEQUE_H__
