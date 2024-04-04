#include <iostream>
#include <string>
using namespace std;

class Data {
   public:
      friend class HashTable;
      Data(){_key="";_value="";};
      Data(string k, string v): _key(k), _value(v) {}
   private:
      string _key;
      string _value;
};
class HashTable {
   private:
      Data* _buckets;
      int _tableLength;
      int _num;
   public:
      HashTable(int size) {
          _tableLength = size;
         _buckets = new Data[_tableLength];
         _num = 0;
      }
      ~HashTable() {
         delete [] _buckets;
      }
      int HashFunc(string key) {
         //This hash function adds all ASCII codes
         //and divide the results by array size
        int value = 0;
        for ( int i = 0; i < key.length(); i++ )
            value += key[i];
        return value % _tableLength;

      }
      void insert(string k, string v) {
        int h = HashFunc(k);
        while(!_buckets[h]._key.empty() &&
               _buckets[h]._key != k && 
               _buckets[h]._key != "DELETED"){
           h = (h+1)%_tableLength;
        }
        if (_buckets[h]._key.empty() || _buckets[h]._key == "DELETED")
         _buckets[h] = Data(k,v);
      else
         cout << "Not inserted!" << endl;
       }
      string find(string k) {
        int h = HashFunc(k);
        int counter =0;
        while(counter <= _num && !_buckets[h]._key.empty() &&
               _buckets[h]._key != k && 
               _buckets[h]._key != "DELETED"){
           h = (h+1)%_tableLength;
           counter++;
        }
        if (_buckets[h]._key == k)
         return _buckets[h]._value;
      else
         return "";
      }
      bool remove(string k){
         int h = HashFunc(k);
         int counter = 0;
         while(counter <= _num &&
               _buckets[h]._key != k /*&& 
               _buckets[h]._key != "DELETED"*/){
           h = (h+1)%_tableLength;
           counter++;
        }
        if (_buckets[h]._key == k){
           _buckets[h]._key = "DELETED";
           return true;
        }
        else
         return false;
      }
      void dump(){
         for (int i=0;i<_tableLength;i++)
            cout << i << " => " << _buckets[i]._key << "(" << _buckets[i]._value << ")" << endl;
      }
};

int main(){
   HashTable aTable(10);
   aTable.insert("pumpkin", "halloween");
   //cout << aTable.HashFunc("pumpkin") << "\t => " << aTable.find("pumpkin") << endl;
   //In the following example we can see that the hash result for keys stop and spot
   //is the same, because they have the same characters, therefore the value is
   //overwritten in the array
   aTable.insert("stop", "stop");
   //cout << "Index " << aTable.HashFunc("stop") << "\t => " << aTable.find("stop") << endl;
   aTable.insert("spot", "spot");
   //cout << "Index " << aTable.HashFunc("spot") << "\t => " << aTable.find("spot") << endl;
   
   aTable.insert("pots", "pots");
   aTable.remove("stop");
   aTable.remove("pots");
   aTable.insert("stop", "second stop");
   cout << "Dumping the hash table: " << endl;
   aTable.dump();
   cout << aTable.find("stop") << endl;
   cout << aTable.find("stst") << endl;

   return 0;
}
