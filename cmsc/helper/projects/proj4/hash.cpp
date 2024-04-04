// CMSC 341 - Fall 2021 - Project 4
#include "hash.h"
#include "math.h"
HashTable::HashTable(unsigned size, hash_fn hash){
    if (isPrime(size)) {
        m_capacity1 = size;
    }
    else {
        m_capacity1 = findNextPrime(size);
    }

    m_capacity2 = 0;
    m_size1 = 0;
    m_size2 = 0;
    m_numDeleted1 = 0;
    m_numDeleted2 = 0;
    m_table1 = new File[m_capacity1];
    m_table2 = nullptr;
    m_newTable = TABLE1;
    m_hash = hash;
}

HashTable::~HashTable(){
    delete [] m_table1;
    delete [] m_table2;
}

File HashTable::getFile(string name, int diskBlock){
unsigned int p = 0; // counter for collisions
unsigned int p2 = 0;
unsigned int &s1 = (m_newTable == TABLE1) ? m_size1 : m_size2;
unsigned int &s2 = (m_newTable == TABLE1) ? m_size2 : m_size1;
unsigned int &cap1 = (m_newTable == TABLE1) ? m_capacity1 : m_capacity2;
unsigned int &cap2 = (m_newTable == TABLE1) ? m_capacity2 : m_capacity1;
unsigned int i = m_hash(name) % cap1; //used to calculate the index for the hash search
unsigned int i2 = m_hash(name) % cap2;
File* &hash1 = (m_newTable == TABLE1) ? m_table1 : m_table2;
File* &hash2 = (m_newTable == TABLE1) ? m_table2 : m_table1; 
// These variables are going to essential when finding and searching the tables
File r; //this is my return type

 while(hash1[i].diskBlock() != diskBlock && p <= s1){ // checks to make sure its not already there
    i = (m_hash(name) + (p * p)) % cap1;
    p++;
 }
 // looking into both tables for the file then return and if its not found also return
 if (hash1[i].diskBlock() == diskBlock) {
     r = hash1[i];
 }
 else if (hash2 != nullptr && r == EMPTY) {
     while (hash2[i2].diskBlock() != diskBlock && p2 <= s2){
         i2 = (m_hash(name) + (p2 * p2)) % cap2;
         p2++;
     }
 }
 else if (hash2[i2].diskBlock() == diskBlock) {
     r = hash2[i2];
 }

return r;
}

bool HashTable::insert(File file){
    unsigned int i = 1;
    unsigned int indexer = 0;
    unsigned int hash_indexer = 0;
   
// the quadratic probing
    if(m_newTable == TABLE1) {
        indexer = m_hash(file.key()) % m_capacity1;
        hash_indexer = indexer;
        while (m_table1[hash_indexer].diskBlock() != 0 && 
            m_table1[hash_indexer].diskBlock() != file.diskBlock() && i < numEntries(TABLE1)) {
            hash_indexer = (m_hash(file.key()) % m_capacity1 + (i * i)) % m_capacity1;
            i++;
        }// end while
        m_table1[hash_indexer] = file;
    }// end if
    //m_table1[hash_indexer] = file;
    else {
    indexer = m_hash(file.key()) % m_capacity2;
    hash_indexer = indexer;
        while (m_table2[hash_indexer].diskBlock() != 0 &&
            m_table2[hash_indexer].diskBlock() != file.diskBlock() && i < numEntries(TABLE2)) {
        hash_indexer = (m_hash(file.key()) % m_capacity2 + (i * i)) % m_capacity2;
        i++;
        }// end while
        m_table2[hash_indexer] = file;
    } // end else
    //m_table2[hash_indexer] = file;

    // These file pointer variables and make it easier for rehashing
    File* &hash1 = (m_newTable == TABLE1) ? m_table1 : m_table2;
    File* &hash2 = (m_newTable == TABLE1) ? m_table2 : m_table1; 
    TABLENAME active = (m_newTable == TABLE1) ? TABLE1 : TABLE2;
    TABLENAME inactive = (m_newTable == TABLE1) ? TABLE2 : TABLE1;
    unsigned int &cap1 = (m_newTable == TABLE1) ? m_capacity1 : m_capacity2;
    unsigned int &cap2 = (m_newTable == TABLE1) ? m_capacity2 : m_capacity1;
    unsigned int &s1 = (m_newTable == TABLE1) ? m_size1 : m_size2;
    unsigned int &s2 = (m_newTable == TABLE1) ? m_size2 : m_size1;
    if(lambda(m_newTable) > 0.5 && hash2 == nullptr) {
        m_newTable = (m_newTable == TABLE1) ? TABLE2 : TABLE1;
        cap2 = findNextPrime(4 * s1);
        rehash(active);
    }
    else if (s2 > 0) {
        rehash(inactive);
    }
    s1 = (m_newTable == TABLE1) ? m_size1 : m_size2; 
    s1++;

    return true;
}

void HashTable::rehash(TABLENAME table){
//if(lambda(m_newTable) > 0.5 || deletedRatio(table) > 0.8) {
    if (table == TABLE1) {
        if (m_table2 == nullptr) {
            m_capacity2 = findNextPrime((m_size2 - m_numDeleted2)*4);
            m_table2 = new File [m_capacity2];
            m_size2 = 0;
            m_numDeleted2 = 0;
        }

    int counter = 0;
    if (m_table1 == nullptr){
        return;
    }
    for (unsigned int i = 0; i < m_capacity1; i++) {
            if(counter >= m_capacity1 * .25) {
                return;
            }// end if
        m_table2[m_size2] = m_table1[i];
        m_table1[i] = EMPTY;
        m_size2++;
        m_size1--; 
        counter++;
    } // end for
    delete m_table1;
    m_table1 = nullptr;
    }// end if

     if (table == TABLE2) {
        if (m_table1 == nullptr) {
            m_capacity1 = findNextPrime((m_size1 - m_numDeleted1)*4);
            m_table1 = new File [m_capacity1];
            m_size1 = 0;
            m_numDeleted1 = 0;
        }
    int counter = 0;
    if (m_table2 == nullptr){
        return;
    }
    for (unsigned int i = 0; i < m_capacity2; i++) {
            if(counter >= m_capacity2 * .25) {
                return;
            }// end if
        m_table1[m_size1] = m_table2[i];
        m_table2[i] = EMPTY;
        m_size1++;
        m_size2--; 
        counter++;
    } // end for
    delete m_table2;
    m_table2 = nullptr;
    }// end if
//} // end biggest if
    
}// end function


bool HashTable::remove(File file){
    unsigned int p = 0; // counter for collisions
    unsigned int p2 = 0;
    File* &hash1 = (m_newTable == TABLE1) ? m_table1 : m_table2;
    File* &hash2 = (m_newTable == TABLE1) ? m_table2 : m_table1;
    TABLENAME active = (m_newTable == TABLE1) ? TABLE1 : TABLE2;
    TABLENAME inactive = (m_newTable == TABLE1) ? TABLE2 : TABLE1;
    unsigned int &cap1 = (m_newTable == TABLE1) ? m_capacity1 : m_capacity2;
    unsigned int &cap2 = (m_newTable == TABLE1) ? m_capacity2 : m_capacity1;
    unsigned int &s1 = (m_newTable == TABLE1) ? m_size1 : m_size2;
    unsigned int &s2 = (m_newTable == TABLE1) ? m_size2 : m_size1;
    unsigned int i = m_hash(file.key()) % cap1; //used to calculate the index for the hash search
    unsigned int i2 = 0; 
    if (cap2 > 0){
        i2 = m_hash(file.key()) % cap2;
    }
    
    bool r; //this is my return type

        while(hash1[i].diskBlock() != file.diskBlock() && p <= s1){ // checks to make sure its not already there
            i = (m_hash(file.key()) + (p * p)) % cap1;
            p++;
        }
        // looking into both tables for the file then return and if its not found also return
        if (hash1[i].diskBlock() == file.diskBlock()) {
            hash1[i]= DELETED;
            r = true;
        }
        else if (hash2 != nullptr && r == false) {
            while (hash2[i2].diskBlock() != file.diskBlock() && p2 <= s2){
                i2 = (m_hash(file.key()) + (p2 * p2)) % cap2;
                p2++;
            }
        }
        else if (hash2[i2].diskBlock() == file.diskBlock()) {
             hash2[i2] = DELETED;
        }

        if(deletedRatio(m_newTable) > 0.8 && hash2 == nullptr) {
        m_newTable = (m_newTable == TABLE1) ? TABLE2 : TABLE1;
        cap2 = findNextPrime(4 * s1);
        rehash(active);
    }
    else if (s2 > 0) {
        rehash(inactive);
    }
    return true;
}

float HashTable::lambda(TABLENAME tablename) const {
    unsigned int space = (tablename == TABLE1) ? m_size1 : m_size2;
    unsigned int cap = (tablename == TABLE1) ? m_capacity1 : m_capacity2;
    // the varaiable make calculating the load factors for the tables easier
    if (cap == 0){
        return 0;
    }
    return (float(space) / float(cap));
}// end lambda

float HashTable::deletedRatio(TABLENAME tableName) const {
    unsigned int fill = (tableName == TABLE1) ? m_capacity1 : m_capacity2;
    unsigned int del = (tableName == TABLE1) ? m_numDeleted1 : m_numDeleted2;
    return (float(del / fill));
}// end deletedRatio

void HashTable::dump() const {
    cout << "Dump for table 1: " << endl;
    if (m_table1 != nullptr)
        for (int i = 0; i < m_capacity1; i++) {
            cout << "[" << i << "] : " << m_table1[i] << endl;
        }
    cout << "Dump for table 2: " << endl;
    if (m_table2 != nullptr)
        for (int i = 0; i < m_capacity2; i++) {
            cout << "[" << i << "] : " << m_table2[i] << endl;
        }
}

bool HashTable::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int HashTable::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}
