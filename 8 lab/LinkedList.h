#include <string>

using namespace std;

int main();
struct Node {

    double data;
    Node *prev;
    Node *next;

    Node(double data, Node *next, Node *prev) {
        this->data = data;
        this->prev = prev;
        this->next = next;
    }
};
struct LinkedList {
private:

    Node *head = NULL, *end = NULL;
    int size = 0;
public:
    void add(double value);

    void checkIndex(int index);

    bool isEmpty();

    void checkSize();

    void add(int index, double value);

    double set(int index, double value);

    double remove();

    double remove(int index);

    double get(int index);

    int sizeOfList();

    double arithmeticMean();

    void replace(double oldData, double newData);

    void makeFileWithData(string pathToNewFile);

    void replaceEnds();

    void addElementsFromConsole();

private:
    void checkCharArray(char data[], int arraySize);

    int searchForQuoteMarks(char line[256], int counter);

    void unlink(Node *node);
};

