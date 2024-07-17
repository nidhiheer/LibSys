#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book {
private:
    string title;
    string author;
    bool isAvailable;

public:
    Book(string title, string author) {
        this->title = title;
        this->author = author;
        this->isAvailable = true;
    }

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    bool getAvailability() {
        return isAvailable;
    }

    void setAvailability(bool availability) {
        this->isAvailable = availability;
    }
};

class Patron {
private:
    string name;
    vector<Book*> borrowedBooks;

public:
    Patron(string name) {
        this->name = name;
    }

    string getName() {
        return name;
    }

    void borrowBook(Book* book) {
        borrowedBooks.push_back(book);
        book->setAvailability(false);
    }

    void returnBook(Book* book) {
        for (int i = 0; i < borrowedBooks.size(); i++) {
            if (borrowedBooks[i] == book) {
                borrowedBooks.erase(borrowedBooks.begin() + i);
                book->setAvailability(true);
                return;
            }
        }
    }
};

class Library {
private:
    vector<Book*> books;
    vector<Patron*> patrons;

public:
    void addBook(Book* book) {
        books.push_back(book);
    }

    void displayBooks() {
        for (Book* book : books) {
            cout << "Title: " << book->getTitle() << ", Author: " << book->getAuthor() << ", Availability: " << (book->getAvailability() ? "Yes" : "No") << endl;
        }
    }

    void addPatron(Patron* patron) {
        patrons.push_back(patron);
    }

    void checkOutBook(string patronName, string bookTitle) {
        Patron* patron = getPatron(patronName);
        Book* book = getBook(bookTitle);

        if (patron != nullptr && book != nullptr && book->getAvailability()) {
            patron->borrowBook(book);
            cout << "Book checked out successfully." << endl;
        } else {
            cout << "Book not available or patron not found." << endl;
        }
    }

    void returnBook(string patronName, string bookTitle) {
        Patron* patron = getPatron(patronName);
        Book* book = getBook(bookTitle);

        if (patron != nullptr && book != nullptr) {
            patron->returnBook(book);
            cout << "Book returned successfully." << endl;
        } else {
            cout << "Book not found or patron not found." << endl;
        }
    }

private:
    Patron* getPatron(string name) {
        for (Patron* patron : patrons) {
            if (patron->getName() == name) {
                return patron;
            }
        }
        return nullptr;
    }

    Book* getBook(string title) {
        for (Book* book : books) {
            if (book->getTitle() == title) {
                return book;
            }
        }
        return nullptr;
    }
};

int main() {
    Library library;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add book" << endl;
        cout << "2. Display books" << endl;
        cout << "3. Add patron" << endl;
        cout << "4. Check out book" << endl;
        cout << "5. Return book" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                cout << "Enter book title: ";
                cin >> title;
                cout << "Enter book author: ";
                cin >> author;
                library.addBook(new Book(title, author));
                break;
            }
            case 2:
                library.displayBooks();
                break;
            case 3: {
                string name;
                cout << "Enter patron name: ";
                cin >> name;
                library.addPatron(new Patron(name));
                break;
            }
            case 4: {
                string patronName, bookTitle;
                cout << "Enter patron name: ";
                cin >> patronName;
                cout << "Enter book title: ";
                cin >> bookTitle;
                library.checkOutBook(patronName, bookTitle);
                break;
            }
            case 5: {
                string patronName, bookTitle;
                cout << "Enter patron name: ";
                cin >> patronName;
                cout << "Enter book title: ";
                cin >> bookTitle;
                library.returnBook(patronName, bookTitle);
                break;
            }
        }
    }
}