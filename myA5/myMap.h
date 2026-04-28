#ifndef MYMAP_H_
#define MYMAP_H_
#include <iostream>
#include <vector>
#include <utility>

template <typename K, typename V>

class Map{
private:
    std::vector<std::pair<K, V>> data;

    int findIndex(const K& key) const {
        int i = 0;
        int size = data.size() - 1;
        while(i <= size) {
            int mid = (i + size)/2;
            if(!(data[mid].first < key) && !(key < data[mid].first)){
                return mid;
            } else if(key < data[mid].first) {
                size = mid - 1;
            } else {
                i = mid + 1;
            }
        }
        return -1;
    }

    int insertPos(const K& key) const {
        int i = 0;
        int size = data.size();
        while(i < size) {
            int mid = (i + size)/2;
            if(data[mid].first < key) {
                i = mid + 1;
            } else {
                size = mid;
            }
        }
        return i;
    }

public:
    Map() = default;
    ~Map() = default;
    Map(const Map& other) = default;
    Map(Map&& other) = default;
    Map& operator=(const Map& other) = default;
    Map& operator=(Map&& other) = default;

    V& operator[](const K& key) {
        int i = findIndex(key);
        if(i != -1) {
            return data[i].second;
        }
        int j = insertPos(key);
        data.insert(data.begin() + j, {key, V()});
        return data[j].second;
    }

    V operator()(const K& key) const {
        int i = findIndex(key);
        if(i != -1) {
            return data[i].second;
        }
        return V();
    }

    class Iterator{
    private:
        typename std::vector<std::pair<K, V>>::iterator iter;
    public:
        Iterator(typename std::vector<std::pair<K, V>>::iterator i) : iter(i) {}

        K operator*() {
            return iter->first;
        }

        Iterator& operator++() {
            iter++;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return iter != other.iter;
        }
    };

    Iterator begin() {
        return Iterator(data.begin());
    }

    Iterator end() {
        return Iterator(data.end());   
    }
};

#endif