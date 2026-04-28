#include <iostream>
#include "intSet.h"

void intSet::swap(intSet& other){
    int *tmpData = data;
    data = other.data;
    other.data = tmpData;

    int tmpSize = size;
    size = other.size;
    other.size = tmpSize;

    int tmpCapacity = capacity;
    capacity = other.capacity;
    other.capacity = tmpCapacity;
}

intSet::intSet() : data{new int[4]}, size{0}, capacity{4} {}

intSet::intSet(const intSet& is) : data{new int[is.capacity]}, size{is.size}, capacity{is.capacity}{
    for(int i = 0; i < size; i++){
        data[i] = is.data[i];
    }
}

intSet::intSet(intSet&& is) : data{is.data}, size{is.size}, capacity{is.capacity} {
    is.data = nullptr;
    is.size = 0;
    is.capacity = 0;
}

intSet& intSet::operator=(const intSet& is){
    if (this != &is){
        intSet temp{is};
        swap(temp);
    }
    return *this;
}

intSet& intSet::operator=(intSet&& is){
    if (this != &is){
        swap(is);
    }
    return *this;
}

intSet::~intSet() {
    delete[] data;
}

bool intSet::contains(int e) const {
    for(int i = 0; i < size; i++){
        if(data[i] == e){
            return true;
        }
    }
    return false;
}

void intSet::add(int e){
    if(contains(e)){
        return;
    }
    if(size == capacity){
        int *newData = new int[capacity * 2];

        for(int i = 0; i < size; i++){
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity *= 2;
    }
    data[size] = e;
    size++;
}

void intSet::remove(int e){
    for(int i = 0; i < size; i++){
        if(data[i] == e){
            for(int j = 0; j < size - 1; j++){
                data[j] = data[j + 1];
            }
            size--;
            return;
        }
    }
}

intSet intSet::operator|(const intSet& other) const {
    intSet result;
    for(int i = 0; i < size; i++){
        result.add(data[i]);
    }
    for(int i = 0; i < size; i++){
        result.add(other.data[i]);
    }
    return result;
}

intSet intSet::operator&(const intSet& other) const {
    intSet result;
    for(int i = 0; i < size; i++){
        if(other.contains(data[i])){
            result.add(data[i]);
        }
    }
    return result;
}

bool intSet::operator==(const intSet& other) const {
    if(size != other.size){
        return false;
    }
    for(int i = 0; i < size; i++){
        if (!other.contains(data[i])){
            return false;
        }
    }
    return true;
}

bool intSet::isSubset(const intSet& s) const {
    for(int i = 0; i < s.size; i++){
        if(!contains(s.data[i])){
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream& out, const intSet& is) {
    out << "(";

    if (is.size > 0) {
        int *copy = new int[is.size];

        for (int i = 0; i < is.size; ++i) {
            copy[i] = is.data[i];
        }

        // bubble sort
        for (int i = 0; i < is.size - 1; ++i) {
            for (int j = 0; j < is.size - 1 - i; ++j) {
                if (copy[j] > copy[j + 1]) {
                    int temp = copy[j];
                    copy[j] = copy[j + 1];
                    copy[j + 1] = temp;
                }
            }
        }

        out << copy[0];
        for (int i = 1; i < is.size; ++i) {
            out << ", " << copy[i];
        }

        delete[] copy;
    }

    out << ")";
    return out;
}
