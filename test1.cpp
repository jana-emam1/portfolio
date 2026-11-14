
#include <iostream>
#include <stdexcept>
using namespace std;

// ==========================================
// Node Class
// ==========================================

template <typename T>
class Node {
public:
    T element;
    Node<T>* next;

    Node(T value) {
        element = value;
        next = nullptr;
    }
};

// ==========================================
// Singly Linked List Class
// ==========================================

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    // Constructor
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // Destructor
    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Prevent accidental shallow copying
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // Display all elements
    void display() const {
        Node<T>* current = head;

        while (current != nullptr) {
            cout << current->element << " -> ";
            current = current->next;
        }

        cout << "NULL" << endl;
    }

    // Return number of elements
    int count() const {
        return size;
    }

    // Search for an element
    bool search(T value) const {
        Node<T>* current = head;

        while (current != nullptr) {
            if (current->element == value) {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    // Insert at the beginning
    void insertFirst(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }

        size++;
    }

    // Insert at the end
    void append(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    // Insert at a specific index
    void add(int index, T value) {
        if (index < 0 || index > size) {
            throw out_of_range("Invalid index");
        }

        if (index == 0) {
            insertFirst(value);
            return;
        }

        if (index == size) {
            append(value);
            return;
        }

        Node<T>* current = head;

        for (int i = 1; i < index; i++) {
            current = current->next;
        }

        Node<T>* newNode = new Node<T>(value);

        newNode->next = current->next;
        current->next = newNode;

        size++;
    }

    // Find the middle element
    T findMiddle() const {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        Node<T>* slow = head;
        Node<T>* fast = head;

        while (fast != nullptr &&
               fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->element;
    }

    // Reverse the linked list
    void reverse() {
        tail = head;

        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }

        head = prev;
    }

    // Remove the first element
    T removeFirst() {
        if (size == 0) {
            throw runtime_error("List is empty");
        }

        Node<T>* temp = head;
        T value = temp->element;

        head = head->next;
        delete temp;

        size--;

        if (head == nullptr) {
            tail = nullptr;
        }

        return value;
    }

    // Remove the last element
    T removeLast() {
        if (size == 0) {
            throw runtime_error("List is empty");
        }

        if (size == 1) {
            return removeFirst();
        }

        Node<T>* current = head;

        while (current->next != tail) {
            current = current->next;
        }

        T value = tail->element;

        delete tail;

        tail = current;
        tail->next = nullptr;

        size--;

        return value;
    }

    // Remove an element at a specific index
    T removeAt(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }

        if (index == 0) {
            return removeFirst();
        }

        if (index == size - 1) {
            return removeLast();
        }

        Node<T>* prev = head;

        for (int i = 1; i < index; i++) {
            prev = prev->next;
        }

        Node<T>* current = prev->next;

        prev->next = current->next;

        T value = current->element;

        delete current;
        size--;

        return value;
    }
};

// ==========================================
// Main Function
// ==========================================

int main() {
    LinkedList<int> list;

    // Insert elements
    list.insertFirst(10);
    list.append(20);
    list.append(30);
    list.insertFirst(5);

    cout << "Original List: ";
    list.display();

    cout << "Count: " << list.count() << endl;

    // Search
    int value = 30;

    if (list.search(value)) {
        cout << value << " is found" << endl;
    }
    else {
        cout << value << " is NOT found" << endl;
    }

    // Insert at index 2
    list.add(2, 25);

    cout << "\nAfter Insertion: ";
    list.display();

    // Find middle
    cout << "Middle Element: "
         << list.findMiddle() << endl;

    // Reverse
    list.reverse();

    cout << "\nReversed List: ";
    list.display();

    // Remove first
    cout << "\nRemoved First: "
         << list.removeFirst() << endl;

    list.display();

    // Remove last
    cout << "\nRemoved Last: "
         << list.removeLast() << endl;

    list.display();

    // Remove at index
    cout << "\nRemoved at Index 1: "
         << list.removeAt(1) << endl;

    list.display();

    cout << "\nFinal Count: "
         << list.count() << endl;

    return 0;
}
