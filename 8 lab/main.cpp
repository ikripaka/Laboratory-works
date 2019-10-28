#include <iostream>
#include "LinkedList.h"


using namespace std;

int main() {
    LinkedList *list = new LinkedList;
    for (int i = 0; i < 10; i++) {
        list->add(i);
    }
    cout << list->get(5);
    list->add(9, 19);
    list->add(4, 10);

    list->add(0, 11);
    list->set(0, 12);
    list->set(5, 13);

    std::cout << list->get(0) << endl;

    std::cout << list->get(list->sizeOfList() - 1) << endl;
    std::cout << list->remove() << endl;
    std::cout << list->get(5) << endl;
    std::cout << list->remove(5) << endl;

    list->remove();
    list->remove(5);
    list->remove(0);
    cout << "Average value: " << list->arithmeticMean() << endl;
    list->replace(5, 1);
    list->replace(1, 3);
    list->replaceEnds();
    list->addElementsFromConsole();
    list->makeFileWithData("G:/Visual Studio/output.txt");
    cout << "Is list empty: " << ((list->isEmpty()) ? "yes" : "no") << endl;
    cout << "size: " << list->get(list->sizeOfList() - 1);
    return 0;
}