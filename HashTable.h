#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>

#include "Dict.h"
#include "TableEntry.h"
#include "ListLinked.h"

template <typename V>
class HashTable : public Dict<V>
{
    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>* table;

        int h(std::string key)
        {
            int suma = 0;

            for(size_t i = 0; i < key.size(); i++)
            {
                suma += int(key.at(i));
            }

            return suma % max;
        }

    public:
        HashTable(int size)
        {
            max = size;
            n = 0;
        }

        ~HashTable()
        {
            delete[] table;
        }

        int capacity()
        {
            return max;
        }

        void insert(std::string key, V value) override
        {
            int pos = h(key);
            TableEntry<V> entry(key, value);

            if (table[pos].search(entry) != -1)
            {
                throw std::runtime_error("insert: clave ya existente");
            }

            table[pos].prepend(entry);
            n++;
        }

        V search(std::string key) override
        {
            int pos = h(key);
            TableEntry<V> target(key);

            int idx = table[pos].search(target);

            if (idx == -1)
            {
                throw std::runtime_error("search: clave no encontrada");
            }

            return table[pos].get(idx).value;
        }

        V remove(std::string key) override
        {
            int pos = h(key);
            TableEntry<V> target(key);

            int idx = table[pos].search(target);

            if (idx == -1)
            {
                throw std::runtime_error("remove: clave no encontrada");
            }

            TableEntry<V> removed = table[pos].remove(idx);
            n--;
            
            return removed.value;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th)
        {
            for(int i = 0; i < th.max; i++)
            {
                if(th.table[i] == V()) out << " ";
                else out << th.table[i] << "\n";
            }

            return out;
        }

        V operator[](std::string key)
        {
            return search(key);
        }
};

#endif