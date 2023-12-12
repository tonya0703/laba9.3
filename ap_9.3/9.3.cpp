#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Note {
    string lastName;
    string firstName;
    string phoneNumber;
    int birthDate[3];
};

void inputPersonData(Note& person);
void displayPersonData(const Note& person);
void displayAllData(const Note* array, int size);
bool compareBirthDates(const Note& a, const Note& b);
void sortArrayByBirthDates(Note* array, int size);
void searchByPhoneNumber(const Note* array, int size);
void saveDataToFile(const Note* array, int size, const std::string& fileName);
void loadDataFromFile(Note*& array, int& size, const std::string& fileName);
void displayMenu(); 

void inputPersonData(Note& person) {
    cout << "Enter last name: ";
    cin >> person.lastName;

    cout << "Enter first name: ";
    cin >> person.firstName;

    cout << "Enter phone number: ";
    cin >> person.phoneNumber;

    cout << "Enter birth date (day month year): ";
    for (int i = 0; i < 3; ++i) {
        cin >> person.birthDate[i];
    }
}

void displayPersonData(const Note& person) {
    cout << "Last name: " << person.lastName << "\n";
    cout << "First name: " << person.firstName << "\n";
    cout << "Phone number: " << person.phoneNumber << "\n";
    cout << "Birth date: " << person.birthDate[0] << "/" << person.birthDate[1] << "/" << person.birthDate[2] << "\n";
}

void displayAllData(const Note* array, int size) {
    for (int i = 0; i < size; ++i) {
        cout << "\nPerson " << i + 1 << ":\n";
        displayPersonData(array[i]);
    }
}

bool compareBirthDates(const Note& a, const Note& b) {
    for (int i = 2; i >= 0; --i) {
        if (a.birthDate[i] != b.birthDate[i]) {
            return a.birthDate[i] < b.birthDate[i];
        }
    }
    return false;
}

void sortArrayByBirthDates(Note* array, int size) {
    sort(array, array + size, compareBirthDates);
}

void searchByPhoneNumber(const Note* array, int size) {
    string searchNumber;
    cout << "Enter phone number to search: ";
    cin >> searchNumber;

    bool found = false;

    for (int i = 0; i < size; ++i) {
        if (array[i].phoneNumber == searchNumber) {
            cout << "Person found!\n";
            displayPersonData(array[i]);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Person not found with the given phone number.\n";
    }
}

void saveDataToFile(const Note* array, int size, const std::string& fileName) {
    ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        cout << "Error opening the file for writing.\n";
        return;
    }

    for (int i = 0; i < size; ++i) {
        outputFile << array[i].lastName << " " << array[i].firstName << " " << array[i].phoneNumber << " ";
        for (int j = 0; j < 3; ++j) {
            outputFile << array[i].birthDate[j] << " ";
        }
        outputFile << "\n";
    }

    cout << "Data successfully saved to file.\n";
    outputFile.close();
}

void loadDataFromFile(Note*& array, int& size, const std::string& fileName) {
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error opening the file for reading.\n";
        return;
    }


    int count = std::count(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>(), '\n');
    inputFile.seekg(0, std::ios::beg);


    array = new Note[count];
    size = count;

    for (int i = 0; i < count; ++i) {
        inputFile >> array[i].lastName >> array[i].firstName >> array[i].phoneNumber;
        for (int j = 0; j < 3; ++j) {
            inputFile >> array[i].birthDate[j];
        }
    }

    cout << "Data successfully loaded from file.\n";
    inputFile.close();
}

void displayMenu() {
    cout << "Menu:\n"
        << "1. Enter data for people\n"
        << "2. Display all people sorted by birth date\n"
        << "3. Search by phone number\n"
        << "4. Save data to a file\n"
        << "5. Load data from a file\n"
        << "6. Display all people after loading from file\n"
        << "7. Exit\n"
        << "Enter your choice: ";
}

int main() {
    int size;
    Note* array = nullptr;
    string fileName;

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter the number of people: ";
            cin >> size;

            if (size <= 0) {
                cout << "Invalid input. The number of people must be a positive integer.\n";
                break;
            }

            array = new Note[size];

            for (int i = 0; i < size; ++i) {
                cout << "\nEnter data for person " << i + 1 << ":\n";
                inputPersonData(array[i]);
            }

            sortArrayByBirthDates(array, size);
            break;
        }
        case 2: {
            cout << "\nAll People:\n";
            if (array != nullptr) {
                displayAllData(array, size);
            }
            else {
                cout << "No data entered yet!\n";
            }
            break;
        }
        case 3: {
            if (array != nullptr) {
                searchByPhoneNumber(array, size);
            }
            else {
                cout << "No data entered yet!\n";
            }
            break;
        }
        case 4: {
            if (array != nullptr) {
                cout << "\nEnter the file name to save data: ";
                cin >> fileName;
                saveDataToFile(array, size, fileName);
            }
            else {
                cout << "No data entered yet!\n";
            }
            break;
        }
        case 5: {
            cout << "\nEnter the file name to load data: ";
            cin >> fileName;
            loadDataFromFile(array, size, fileName);
            break;
        }
        case 6: {
            cout << "\nAll People After Loading from File:\n";
            if (array != nullptr) {
                displayAllData(array, size);
            }
            else {
                cout << "No data loaded from file!\n";
            }
            break;
        }
        case 7: {
            if (array != nullptr) {
                delete[] array;
            }
            cout << "Exiting...\n";
            break;
        }
        default: {
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
        }
    } while (choice != 7);

    return 0;
}
