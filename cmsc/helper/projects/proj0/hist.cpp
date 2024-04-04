#include "hist.h"

Data::Data():m_arraySize(DATAARRAYSIZE){
    m_data = new int[DATAARRAYSIZE]();
}
Data::~Data(){
    delete [] m_data;
}
void Data::simulateData(int students){
    Random *r = new Random(MINGRADE,MAXGRADE);
    for ( int i=0; i < students; i++){

    switch (r->getNormRand()) {
        case 0 ... 9:
            m_data[0]+=1;
            break;
        case 10 ... 19:
            m_data[1]+=1;
            break;
        case 20 ... 29:
            m_data[2]+=1;
            break;
        case 30 ... 39:
            m_data[3]+=1;
            break;
        case 40 ... 49:
            m_data[4]+=1;
            break;
        case 50 ... 59:
            m_data[5]+=1;
            break;
        case 60 ... 69:
            m_data[6]+=1;
            break;
        case 70 ... 79:
            m_data[7]+=1;
            break;
        case 80 ... 89:
            m_data[8]+=1;
            break;
        case 90 ... 100:
            m_data[9]+=1;
            break;

     }

    }
}

void Data::dump(int item) {
 cout << "Histogram for item " << + item << endl;
    for (int x = 0; x < m_arraySize; x++){
        int num = 10 * (x+1);
        cout << num << + " ";
        cout.width(m_data[x]);
        cout.fill('*');
        cout << "" << endl;

    }
    
}

int Data::getData(int index){
    return m_data[index];
}
int Data::getArraySize(){
    return m_arraySize;
}
// Overloaded equality operator. It returns true if two objects are the same.
// The "same objects" means they are the same pointers and carry the same value  
// in every correpsonding cell.
// For testing inequality we can simply negate the return value of this operator.
bool operator==(const Data& lhs, const Data& rhs){
    if (&lhs == &rhs)
    {
        for (int i=0;i<lhs.m_arraySize;i++){
            if (lhs.m_data[i] != rhs.m_data[i])
                return false;
        }
        return true;
    }
    else return false;
}

Hist::Hist(int items){
        if (items < 1) {
            m_items = 0;
        }
        else {
            m_items = items;
        }
       m_table = new Data [m_items]();
}

Hist::~Hist(){
    delete[] m_table;
}

void Hist::dump(){
    for (int i=0;i<m_items;i++){
        m_table[i].dump(i);
        cout << endl;
    }
}

void Hist::simulateData(int students){
    try
    {
        if (m_items < 1) {
            throw std::out_of_range("Out of range");
        }
        for (int i = 0; i < m_items; i++) {
            m_table[i].simulateData(students);
        }

    }
    catch (const std::out_of_range& e) 
    {
        cout << "Error at simulate: number of items is out of range!" << endl;
    } 
}

Hist::Hist(const Hist & rhs){
    this-> m_table = new Data[rhs.m_items]();
    this-> m_items = rhs.m_items;

    for(int i=0; i < rhs.m_items; i++) {
        
        for (int j = 0; j < rhs.m_table[i].m_arraySize; j++) {
               this-> m_table[i].m_data[j] = rhs.m_table[i].m_data[j];
        }

    }
}

const Hist & Hist::operator=(const Hist & rhs){
    if (this != &rhs) {
    delete[] this->m_table;
    this-> m_table = new Data[rhs.m_items]();
    this-> m_items = rhs.m_items;

    for(int i=0; i < rhs.m_items; i++) {
        
        for (int j = 0; j < rhs.m_table[i].m_arraySize; j++) {
               this-> m_table[i].m_data[j] = rhs.m_table[i].m_data[j];
            }

        }
    }
    return *this;

}