#include <iostream> // Includes the standard input/output stream library
#include <fstream>
using namespace std; // Standard namespace will be used throughout the code

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList // Declares the DoublyLinkedList class
{
    private:
        struct Node
        {
            string data; // The data in a Node
            Node* prev; // The pointer to the previous Node
            Node* next; // The pointer to the next Node
            // Parametrized constructor that initializes the members using an initializer list
            Node(string val, Node* p = nullptr, Node* n = nullptr) : data(val), prev(p), next(n) {}
        };

        Node* head; // The pointer to the first Node struct in the linked-list
        Node* tail; // The pointer to the last Node struct in the linked-list

    public:
        // Default constructor to initialize an empty linked list
        DoublyLinkedList() : head(nullptr), tail(nullptr) {}

        Node* getHead() const { return head; }
        Node* getTail() const { return tail; }

        // A class method to insert a new Node struct after a given position
        void insert_after(string value, int position)
        {
            if (position < 0) // First check if the position given is valid
            {
                cout << "Position must be >= 0." << endl;
                return;
            }

            Node* newNode = new Node(value); // Dynamically create a new Node struct
            if (!head) // Evaluates to true if the list is empty
            {
                head = tail = newNode;
                return;
            }

            // Traversing until the desired position is reached
            Node* temp = head;
            for (int i = 0; i < position && temp; ++i)
                temp = temp->next;

            if (!temp) // If temp is a nullptr, then the position is out of bounds
            {
                cout << "Position exceeds list size. Node not inserted.\n";
                delete newNode; // Free up the dynamically allocated memory
                return;
            }

            newNode->next = temp->next; // Link the new node with the next node
            newNode->prev = temp; // Link the new node with the previous node
            if (temp->next) // if not inserting at the end
                temp->next->prev = newNode;
            else // if so, the newNode becomes the tail
                tail = newNode;
            temp->next = newNode; // Insert new node after 'temp'
        }

        // A class method that deletes a node by its value
        void delete_val(string value)
        {
            if (!head) return; // Nothing to delete if the list is empty

            // Traverse through the list until the node with the desired value is reached
            Node* temp = head;
            while (temp && temp->data != value)
                temp = temp->next;

            if (!temp) return; // Out of bounds

            // Check if the head is being deleted
            if (temp->prev)
                temp->prev->next = temp->next;
            else
                head = temp->next;

            // Check if the tail is being deleted
            if (temp->next)
                temp->next->prev = temp->prev;
            else
                tail = temp->prev;

            delete temp;
        }

        void delete_pos(int pos)
        {
            if (!head) // Nothing to delete if the list is empty
            {
                cout << "List is empty." << endl;
                return;
            }

            if (pos == 1) // If deleting the head, call 'pop_front()' function to pop the head
            {
                pop_front();
                return;
            }

            Node* temp = head;
            for (int i = 1; i < pos; i++)
            {
                if (!temp) // Out of bounds or the list is empty
                {
                    cout << "Position does not exist." << endl;
                    return;
                }
                else
                    temp = temp->next; // Otherwise keep traversing
            }
            if (!temp) // Out of bounds
            {
                cout << "Position does not exist." << endl;
                return;
            }

            // Deleting the tail
            if (!temp->next)
            {
                pop_back();
                return;
            }

            // Rerouting the pointers
            Node* tempPrev = temp->prev;
            tempPrev->next = temp->next; // the current pointer's prev now points to its next node
            temp->next->prev = tempPrev; // the current pointer's next now points to its previous node
            delete temp;
        }

        void push_back(string v)
        {
            Node* newNode = new Node(v); // instantiate a new node to be inserted to the end of the list
            if (!tail) // When the list is empty
                head = tail = newNode;
            else
            {
                tail->next = newNode; // the current tail now points to the new node
                newNode->prev = tail; // the current tail now becomes the prev to the new node
                tail = newNode; // make this new node tail
            }
        }

        void push_front(string v)
        {
            Node* newNode = new Node(v); // instantiate a new node to be added to the front of the list
            if (!head) // When the list is empty
                head = tail = newNode;
            else {
                newNode->next = head; // the head now becomes the next
                head->prev = newNode; // the newNode now becomes the prev to the current head
                head = newNode; // make this new node head
            }
        }

        void pop_front()
        {
            if (!head) // Nothing to pop if the list is empty
            {
                cout << "List is empty." << endl;
                return;
            }

            Node* temp = head;
            if (head->next)
            {
                // Make the new head be the next of the current head
                head = head->next;
                head->prev = nullptr;
            }
            else
                head = tail = nullptr;
            delete temp;
        }

        void pop_back()
        {
            if (!tail) // Nothing to pop if the list is empty
            {
                cout << "List is empty." << endl;
                return;
            }

            Node* temp = tail;
            if (tail->prev)
            {
                // Make the new tail be the prev of the current tail
                tail = tail->prev;
                tail->next = nullptr;
            }
            delete temp;
        }

        ~DoublyLinkedList()
        {
            // Delete every single node
            while (head)
            {
                // Keep updating the head to be its next
                Node*temp = head;
                head = head->next;
                delete temp;
            }
        }

        // A class method to print out the data of all nodes in the list
        void print()
        {
            Node* current = head;
            if (!current) { // Nothing to print if the list is empty
                cout << "List is empty." << endl;
                return;
            }
            // Iterate through each node until the end is reached
            while (current) {
                cout << current->data << "\n";
                current = current->next;
            }
            cout << endl;
        }
        // A class method to print all nodes in the list from tail to head, same logic as above
        void print_reverse()
        {
            Node* current = tail;
            if (!current) {
                cout << "List is empty." << endl;
                return;
            }
            while (current) {
                cout << current->data << " ";
                current = current->prev;
            }
            cout << endl;
        }

        void every_other_element()
        {
            Node* current = head;
            bool output = true; // Set a flag that will be true every other time
            while (current)
            {
                if (output)
                    cout << current->data << " ";
                output = !output;
                current = current->next;
            }
            cout << endl;
        }
};

string getRandomName(const vector<string>& NAMES);
vector<string> readNamesFile(string fileName);

int main()
{
    srand(time(0));

    DoublyLinkedList line;
    vector<string> NAMES = readNamesFile("names.txt");

    cout << "Store opens:\n"; // Add five customers to the list
    for (int i = 0; i < 5; i++)
    {
        string aName = getRandomName(NAMES);
        line.push_back(aName);
        cout << "\t" << aName << " joins the line\n";
    }
    cout << "Resulting line:\n";
    line.print();

    for (int time = 2; time <= 20; time++)
    {
        cout << "Time step #" << time << ":\n";
        int prob;

        // 10% chance a VIP customer arrives
        prob = rand() % 100 + 1;
        if (prob <= 10)
        {
            string aVip = getRandomName(NAMES);
            line.push_front(aVip);
            cout << "\t" << aVip << " (VIP) joins the front of the line\n";
        }

        // 40% chance the customer at the front is served
        prob = rand() % 100 + 1;
        if (prob <= 40)
        {
            cout << "\t" << line.getHead()->data << " is served\n";
            line.pop_front();
        }

        // 20% chance the customer at the end leaves
        prob = rand() % 100 + 1;
        if (prob <= 20)
        {
            cout << "\t" << line.getTail()->data << " exits the rear of the line\n";
            line.pop_back();
        }

        // 10% chance any particular customer leaves



        // 60% chance a new customer joins at the end
        prob = rand() % 100 + 1;
        if (prob <= 60)
        {
            string aName = getRandomName(NAMES);
            cout << "\t" << aName << " joins the line\n";
            line.push_back(aName);
        }

        cout << "Resulting line:\n";
        line.print();
    }

    return 0;
}

vector<string> readNamesFile(string fileName)
{
    vector<string> NAMES {};
    ifstream fin(fileName);
    string aName;
    while (getline(fin, aName))
        NAMES.push_back(aName);
    fin.close();

    return NAMES;
}

string getRandomName(const vector<string>& NAMES)
{
    int index = rand() % 99;
    return NAMES[index];
}

