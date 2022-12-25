#include <iostream>
#include "sort.hpp"
#include <functional>

typedef struct point{
    int x;
    int y;
} Point;
bool compare(const Point &a, const Point &b){
    return a.y<b.y;
}
int main(){
    std::vector<Point> a = {{7,2},{4,3},{1,2},{1,2},{2,3},{6,1}, {2,1}};
    quick_sort_inplace(a, compare);
    for(auto i = a.begin(); i<a.end(); i++){
        std::cout<<"{"<<i->x<<","<<i->y<<"}"<<", ";
    }
    std::cout<<std::endl;

    std::vector<int> b = {2,1,5,3,4,7,6,9,10,8};
    quick_sort_inplace<int ,std::less<int>>(b);
    for(auto i = b.begin(); i<b.end(); i++){
        std::cout<<*i<<", ";
    }
    std::cout<<std::endl;
    return 0;
}