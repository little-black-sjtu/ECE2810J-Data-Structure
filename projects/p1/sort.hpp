#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <vector>
#include <stdlib.h>
#include <functional>

//--------------------------------bubble Sort--------------------------------

template<typename T, typename Compare>
void bubble_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    for(int i=int(vector.size())-2; i>=0; i--){
        for(int j=0; j<=i; j++){
            if (comp(vector[j+1], vector[j])){
                T temp = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = temp;
            }
        }
    }
}


//--------------------------------insertion Sort--------------------------------

template<typename T, typename Compare>
void insertion_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    for(int i=1; i<int(vector.size()); i++){
        T now = vector[i];
        int j=i-1;
        for(; j>=0; j--){
            if(comp(now, vector[j])) vector[j+1] = vector[j];
            else break;
        }
        vector[j+1] = now;
    }
}

//--------------------------------selection Sort--------------------------------

template<typename T, typename Compare>
void selection_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    for(int i=0; i<int(vector.size())-1; i++){
        int smallest = i;
        for(int j=i+1; j<int(vector.size()); j++){
            if (comp(vector[j], vector[smallest])) smallest = j;
        }
        T temp = vector[smallest];
        vector[smallest] = vector[i];
        vector[i] = temp;
    }
}

//--------------------------------Merge Sort-------------------------------------

template<typename T, typename Compare>
void merge(std::vector<T> &vector, int mid, int left, int right, Compare comp = std::less<T>()){
    int length = right - left + 1;
    int begin = left;
    int middle = mid+1;
    std::vector<T> merged;
    while(left<=mid&&middle<=right){
        if(comp(vector[middle], vector[left])){
            merged.push_back(vector[middle++]);
            
        }
        else
            merged.push_back(vector[left++]);
    }
    if(left<=mid){
        for(;left<=mid;){
            merged.push_back(vector[left++]);
        }
    }
    if(middle<=right){
        for(;middle<=right;){
            merged.push_back(vector[middle++]);
        }
    }
    for (int i = 0; i < length;i++){
        vector[i+begin] = merged[i];
    }
}

template<typename T, typename Compare>
void merge_sort_helper(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()){
    if (left>=right) return;
    int mid = (left+right)/2;
    merge_sort_helper(vector, left, mid, comp);
    merge_sort_helper(vector, mid+1, right, comp);
    merge(vector, mid, left, right, comp);
}

template<typename T, typename Compare>
void merge_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    merge_sort_helper(vector, 0, int(vector.size())-1, comp);
}

//--------------------------------Quick Sort-------------------------------------
template<typename T, typename Compare>
int partition_inplace(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()){
    int first = left++;
    while(true){
        while(!comp(vector[first], vector[left])){
            left++;
            if(left==int(vector.size())) break;
        }
        while(!comp(vector[right], vector[first])){
            right--;
            if(right==first) break;
        }
        if(right>left){
            T temp = vector[left];
            vector[left] = vector[right];
            vector[right] = temp;
        }
        else break;
    }
    T temp = vector[right];
    vector[right] = vector[first];
    vector[first] = temp;
    return right;
}

template<typename T, typename Compare>
int partition_extra(std::vector<T> &vector, int left, int right, Compare comp = std::less<T>()){
    std::vector<T> extra;
    int num = left;
    T first = vector[left];
    extra.push_back(first);
    for (int i = left+1; i <= right; i++){
        if(comp(vector[i], first)){
            extra.insert(extra.begin(), vector[i]);
            num++;
        }
        else extra.push_back(vector[i]);
    }
    for (int i = left; i <= right; i++) vector[i] = extra[i-left];
    return num;
}

template<typename T, typename Compare>
void quick_sort_helper(std::vector<T> &vector, int left, int right, int (*partition)(std::vector<T> &, int , int , Compare), Compare comp = std::less<T>()){
    if(left >= right) return;
    int pivot = partition(vector, left, right, comp);
    quick_sort_helper(vector, left, pivot-1, partition, comp);
    quick_sort_helper(vector, pivot+1, right, partition, comp);
}

template<typename T, typename Compare>
void quick_sort_extra(std::vector<T> &vector, Compare comp = std::less<T>()) {
    quick_sort_helper(vector, 0, int(vector.size())-1, partition_extra, comp);
}
template<typename T, typename Compare>
void quick_sort_inplace(std::vector<T> &vector, Compare comp = std::less<T>()) {
    quick_sort_helper(vector, 0, int(vector.size())-1, partition_inplace, comp);
}

#endif //VE281P1_SORT_HPP