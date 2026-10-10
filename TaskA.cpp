#include <iostream>
#include <string>
using namespace std;

struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void Add(BookRequestNode* request)
    {
        request->next = nullptr;

        if (front == nullptr)
        {
            front = request;
            rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            BookRequestNode* current = front;

            while (current->next != nullptr &&
                   current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == nullptr)
                rear = request;
        }

        count++;
    }

    BookRequestNode* Remove()
    {
        if (front == nullptr)
            return nullptr;

        BookRequestNode* request = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        request->next = nullptr;
        count--;

        return request;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    void PrintQueue()
    {
        BookRequestNode* current = front;

        if (current == nullptr)
        {
            cout << "Queue is empty.\n";
            return;
        }

        while (current != nullptr)
        {
            cout << "\nStudent ID: " << current->studentID;
            cout << "\nStudent Name: " << current->studentName;
            cout << "\nBook ID: " << current->bookID;
            cout << "\nBook Title: " << current->bookTitle;
            cout << "\nPriority: " << current->priority;
            cout << "\n----------------------\n";

            current = current->next;
        }
    }

    PriorityQueue(const PriorityQueue& other)
    {
        front = nullptr;
        rear = nullptr;
        count = 0;

        BookRequestNode* current = other.front;

        while (current != nullptr)
        {
            BookRequestNode* node = new BookRequestNode;

            node->studentID = current->studentID;
            node->studentName = current->studentName;
            node->bookID = current->bookID;
            node->bookTitle = current->bookTitle;
            node->priority = current->priority;
            node->next = nullptr;

            Add(node);
            current = current->next;
        }
    }

    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this == &other)
            return *this;

        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
        count = 0;

        BookRequestNode* current = other.front;

        while (current != nullptr)
        {
            BookRequestNode* node = new BookRequestNode;

            node->studentID = current->studentID;
            node->studentName = current->studentName;
            node->bookID = current->bookID;
            node->bookTitle = current->bookTitle;
            node->priority = current->priority;
            node->next = nullptr;

            Add(node);
            current = current->next;
        }

        return *this;
    }

    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }
};

BookRequestNode* CreateRequest(int sid, string name,
                              int bid, string title, int priority)
{
    BookRequestNode* request = new BookRequestNode;

    request->studentID = sid;
    request->studentName = name;
    request->bookID = bid;
    request->bookTitle = title;
    request->priority = priority;
    request->next = nullptr;

    return request;
}

int main()
{
    PriorityQueue requests;
    int choice;

    do
    {
        cout << "\n===== Library Book Request System =====\n";
        cout << "1. Add Book Request\n";
        cout << "2. Process Highest Priority Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int sid, bid, priority;
            string name, title;

            cout << "Enter Student ID: ";
            cin >> sid;

            cout << "Enter Student Name: ";
            getline(cin >> ws, name);

            cout << "Enter Book ID: ";
            cin >> bid;

            cout << "Enter Book Title: ";
            getline(cin >> ws, title);

            cout << "Enter Priority (1-3): ";
            cin >> priority;

            if (priority < 1 || priority > 3)
            {
                cout << "Invalid priority!\n";
            }
            else
            {
                requests.Add(CreateRequest(
                    sid, name, bid, title, priority));

                cout << "Request added successfully.\n";
            }
        }
        else if (choice == 2)
        {
            BookRequestNode* request = requests.Remove();

            if (request == nullptr)
                cout << "No requests to process.\n";
            else
            {
                cout << "Processed Student: "
                     << request->studentName << endl;
                cout << "Book: " << request->bookTitle << endl;
                cout << "Priority: " << request->priority << endl;

                delete request;
            }
        }
        else if (choice == 3)
        {
            requests.PrintQueue();
        }
        else if (choice == 4)
        {
            if (requests.IsEmpty())
                cout << "Queue is empty.\n";
            else if (requests.IsNotEmpty())
                cout << "Queue has pending requests.\n";
        }
        else if (choice == 5)
        {
            cout << "Exiting program.\n";
        }
        else
        {
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
