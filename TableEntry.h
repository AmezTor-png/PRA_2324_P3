#ifndef TABLEENTRT_H
#define TABLEENTRY_H

#include <stream>
#include <ostream>

template <typename V>
class TableEntry{
  public:
    TableEntry(std::string key, V value){
      this->key = key;
      this->value = value;
    }

    TableEntry(std::string key){
      this->key = key;
    }

    TableEntry(){
      key = "";
    }

    friend bool operator == (const TableEntry<V> &te1, const TableEntry<V> &te2){
      return te1.key == te2.key;
    }

    friend bool operator != (const TableEntry<V> &te1, const TableEntry<V> &te2){
      return te1.key != te2.key;
    }

    friend std::ostream& operator << (std::ostream &out, const TableEntry<V> &te){
      
    }




};

#endif
