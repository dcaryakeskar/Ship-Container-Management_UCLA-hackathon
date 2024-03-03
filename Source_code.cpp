#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
using namespace std;

class queuenode {
    queuenode* next;

public:
    int info;
    queuenode* Create_node() {
        queuenode* temp;
        temp = new (queuenode);
        temp->next = NULL;
        return (temp);
    }

    void enqueue(int item) {
        queuenode* newnode, *temp;
        newnode = Create_node();
        newnode->info = item;
        newnode->next = NULL;
        if (rear == NULL && front == NULL) {
            rear = newnode;
            front = newnode;
        } else {
            rear->next = newnode;
            rear = newnode;
        }
    }

    void dequeue() {
        queuenode* temp = front;
        if (front == NULL && rear == NULL) {
            cout << "Queue is empty" << endl;
            return;
        } else if (front == rear) {
            front = NULL;
            rear = NULL;
        } else {
            front = front->next;
            cout << "Deleted element is: " << temp->info << endl;
            delete (temp);
        }
    }

    void display() {
        queuenode* temp = front;
        while (temp != NULL) {
            cout << temp->info << "-";
            temp = temp->next;
        }
        cout << endl;
    }

    queuenode* getFront() {
        return front;
    }

    queuenode* front = NULL;
    queuenode* rear = NULL;
};

class Container {
private:
    string clientName;
    string startLocation;
    string endLocation;
    string status;
    string dateFree;

public:
    Container(string clientName, string startLocation, string endLocation, string status, string dateFree) {
        this->clientName = clientName;
        this->startLocation = startLocation;
        this->endLocation = endLocation;
        this->status = status;
        this->dateFree = dateFree;
    }

    string getClientName() {
        return clientName;
    }

    string getStartLocation() {
        return startLocation;
    }

    string getEndLocation() {
        return endLocation;
    }

    string getStatus() {
        return status;
    }

    string getDateFree() {
        return dateFree;
    }

    void setCurrentTime() {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        dateFree = buf;
    }

    void estimateDateFree() {
        time_t now = time(0);
        time_t estimatedTime = now + 3 * 24 * 60 * 60;
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&estimatedTime);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        dateFree = buf;
    }
};

class ListNode {
public:
    Container* container;
    ListNode* next;

    ListNode(Container* container) {
        this->container = container;
        this->next = NULL;
    }
};

class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void insert(Container* container) {
        ListNode* newNode = new ListNode(container);

        if (!head) {
            head = newNode;
        } else {
            ListNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void display() {
        ListNode* current = head;
        while (current) {
            Container* container = current->container;
            cout << "Client: " << container->getClientName() << ", Location: " << container->getEndLocation()
                 << ", Status: " << container->getStatus() << ",Expected Date Free: " << container->getDateFree() << endl;
            current = current->next;
        }
    }
};

class ContainerManager {
private:
    LinkedList containers;
    queuenode queue;

public:
    void allocateContainer(string clientName, string startLocation, string endLocation, string status) {
        Container* container = new Container(clientName, startLocation, endLocation, status, "");

        if (status == "Damaged") {
            int containerNumber;
            cout << "Enter the damaged container number: ";
            cin >> containerNumber;
            cout << endl;
            enqueueDamagedContainer(containerNumber);
        } else {
            container->estimateDateFree();
            containers.insert(container);
        }
    }

    void displayContainers() {
        cout << "Containers:" << endl;
        containers.display();
    }

    void enqueueDamagedContainer(int item) {
        queue.enqueue(item);
    }

    void repairContainer() {
        queuenode* front = queue.getFront();
        if (front) {
            int repairedContainer = front->info;
            queue.dequeue();
            cout << "Repaired container " << repairedContainer << " is back in service." << endl;
        } else {
            cout << "No damaged containers to repair." << endl;
        }
    }
};

int main() {
    ContainerManager manager;
    int choice;

    while (true) {
        cout << "Enter 1 to allocate container, 2 to display containers, 3 to enqueue damaged container, 4 to repair container, 5 to exit: ";
        cin >> choice;

        try {
            if (choice == 1) {
                string clientName, startLocation, endLocation, status;
                cout << "Enter client name: ";
                cin >> clientName;
                cout << "Enter start location: ";
                cin >> startLocation;
                cout << "Enter end location: ";
                cin >> endLocation;
                cout << "Enter status (Damaged/Undamaged): ";
                cin >> status;

                manager.allocateContainer(clientName, startLocation, endLocation, status);
            } else if (choice == 2) {
                manager.displayContainers();
            } else if (choice == 3) {
                int damagedContainer;
                cout << "Enter damaged container number: ";
                cin >> damagedContainer;

                if (damagedContainer > 0) {
                    manager.enqueueDamagedContainer(damagedContainer);
                } else {
                    cout << "Invalid damaged container number." << endl;
                }
            } else if (choice == 4) {
                manager.repairContainer();
            } else if (choice == 5) {
                break;
            } else {
                cout << "Invalid choice. Please select a valid option." << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
