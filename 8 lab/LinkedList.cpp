#include <iostream>
#include <fstream>
#include "LinkedList.h"

/**
     * Appends the specified value to the end of this list.
     * @param value - value that appends
     */
void  LinkedList::add(double value) {
    Node *node = new Node(value, NULL, end);
    if (size == 0) {
        head = node;
        end = head;
    } else {
        end->next = node;;
        end = node;
    }
    size++;
}

/**
 * Checks index (if it correct)
 * @param index - current index
 */
void LinkedList::checkIndex(int index) {
    if (index < 0 && index > size) {
        cout << "Element index in list is invalid";
        throw exception();
    }
}

/**
 * Whether or not list is found
 * @return - (true) - isEmpty/(false) - filled with element(s)
 */
bool LinkedList::isEmpty() {
    return size == 0;
}

/**
 * Checks size (if it is correct)
 * @return - (true) correct / (false) incorrect
 */
void LinkedList::checkSize() {
    if (isEmpty()) {
        cout << "List is Empty";
        throw exception();
    }
}

/**
* Adds new node to the end of the list
* @param index - index of the specified element
* @param value - value that inserts
*/
void LinkedList::add(int index, double value) {
    checkSize();
    checkIndex(index);
    Node *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    Node *node = new Node(value, current, current->prev);
    if (index == 0) head = node;
    else current->prev->next = node;
    current->prev = node;
    size++;
}

/**
 * Replaces the element at the specified
 * position in this list with the specified element.
 * @param index   - index of the specified element
 * @param element - element to what we want to change
 * @return - element data that was in it
 */
double LinkedList::set(int index, double value) {
    checkSize();
    checkIndex(index);
    Node *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = value;
}

/**
 * Removes the element from the end of the list
 * @return  - element data that was in it
 */
double LinkedList::remove() {
    checkSize();
    int oldValue = end->data;
    Node *prev = end->prev;
    prev->next = NULL;
    unlink(end);
    delete (end);
    end = prev;
    size--;
    return oldValue;
}

/**
 * Removes the element at the specified position in this list.
 * @param index - index of specified element
 * @return - element data that was in it
 */
double LinkedList::remove(int index) {
    checkSize();
    checkIndex(index);
    if (index == size - 1) {
        return remove();
    } else if (index == 0) {
        Node *current = head;
        int oldValue = current->data;
        head = head->next;
        head->prev = NULL;
        unlink(current);
        delete (current);
        size--;
        return oldValue;
    } else {
        Node *current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        double oldValue = current->data;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        unlink(current);
        delete (current);
        size--;
        return oldValue;
    }
}

/**
* Returns the element at the specified position in this list.
* @param index - index of element
* @return - element data at the specified position
*/
double LinkedList::get(int index) {
    checkSize();
    checkIndex(index);
    Node *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}


/**
 * Returns the number of elements in this list.
 * @return - LinkedList size
 */
int LinkedList::sizeOfList() {
    return size;
}

/**
 * Returns the average of all list elements
 * @return - average of all list elements
 */
double LinkedList::arithmeticMean() {
    checkSize();
    double sum = 0;
    Node *current = head;
    for (int i = 0; i < sizeOfList(); i++) {
        sum = sum + current->data;
        current = current->next;
    }
    return sum / sizeOfList();
}

/**
 * Searching for ald data in list, then replacing it to the new one
 * @param oldData - old element data
 * @param newData - new element data
 */
void LinkedList::replace(double oldData, double newData) {
    Node *current = head;
    for (int i = 0; i < sizeOfList(); i++) {
        if (current->data == oldData) {
            current->data = newData;
        }
        current = current->next;
    }
}

/**
 * Makes file that contain all list elements
 * @param pathToNewFile - path to the new file that will be created
 */
void LinkedList::makeFileWithData(string pathToNewFile) {
    ofstream fileOutput(pathToNewFile);
    Node *current = head;
    fileOutput << "[";
    for (int i = 0; i < sizeOfList(); i++) {
        fileOutput << ((i == 0) ? (to_string(current->data)) : (", " + to_string(current->data)));
        current = current->next;
    }
    fileOutput << "]";
    fileOutput.close();
}

/**
 * Replaces list beginning and ending
 */
void LinkedList::replaceEnds() {
    double temporaryArr = head->data;
    head->data = end->data;
    end->data = temporaryArr;
}

/**
 * Adds elements from console to the list
 */
void LinkedList::addElementsFromConsole() {
    char userLine[256] = "";
    int wordBeginning = 0, wordEnding = 0;
    cout << endl << "Enter data of the list in this way: '0.785','78542.0100489','1234.'" << endl
         << "Line also mustn't contain quote marks inside word/line that will be added in the list" << endl;

    cin.getline(userLine, 256);
    for (int i = 0; userLine[i] != '\000'; i++) {
        i = searchForQuoteMarks(userLine, i);
        wordBeginning = ++i;
        i = searchForQuoteMarks(userLine, i);
        wordEnding = i++;

        char newData[wordEnding - wordBeginning];
        for (int counter = 0; wordBeginning < wordEnding; wordBeginning++, counter++) {
            newData[counter] = userLine[wordBeginning];
        }
        checkCharArray(newData, wordEnding - wordBeginning);
        cout << stod(newData) << endl;
        add(stod(newData));
    }
}

/**
 * Checks array for invalid input
 * @param data - user data(number)
 * @param arraySize - user data size
 */
void LinkedList::checkCharArray(char data[], int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        if (!((data[i] >= '0' && data[i] <= '9') || data[i] == '.')) {
            cout << "Incorrect input. Check the line you entered.";
            throw exception();
        }
    }
}

/**
 * Searching for quote marks in user input from console
 * @param line - console input
 * @param counter - counter where program end elements processing
 * @return
 */
int LinkedList::searchForQuoteMarks(char line[256], int counter) {
    for (; line[counter] != '\000'; counter++) {
        if (line[counter] == 39) { //39 = '
            return counter;
        }
    }
    cout << "Incorrect input. Check the line you entered.";
    throw exception();
}

/**
 * Unlinks one node for deleting it
 * @param node - node that have to be deleted
 */
void LinkedList::unlink(Node *node) {
    node->prev = NULL;
    node->next = NULL;
}


