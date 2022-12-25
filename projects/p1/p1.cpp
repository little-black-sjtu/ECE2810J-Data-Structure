#include <iostream>
#include <vector>
#include "sort.hpp"
#include <algorithm>

//Point struct definition
typedef struct point{
    int x;
    int y;
} Point;

//cww function
int ccw(Point a, Point b, Point c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

//Compare function object
struct CompareLess{
    Point p0;
    bool operator()(const Point &lhs, const Point &rhs) const {
        if (lhs.x==p0.x&&lhs.y==p0.y) return true; 
        return ccw(p0, lhs, rhs)>0;
    }
};

//Read from input and return p0
Point read(std::istream &in, std::vector<Point> &points, int num){

    Point smallest;
    if(num>=1) in>>smallest.x>>smallest.y;
    points.push_back(smallest);

    for (int i=1;i<num;i++){
        Point temp;
        in>>temp.x>>temp.y;
        if (temp.y<smallest.y) smallest = temp;
        else if(temp.y==smallest.y){
            if(temp.x<smallest.x) smallest = temp;
        }
        points.push_back(temp);
    }
    return smallest;
}

int main(){
    //Read points from std::in and get p0
    std::vector<Point> points;
    int num;
    std::cin>>num;
    if (num<=0) return 0;
    Point p0 = read(std::cin, points, num);

    //sort
    CompareLess compressless = {p0};
    std::sort(points.begin(), points.end(), compressless);

    //iterate
    std::vector<Point> S;
    for (auto i = points.begin(); i<points.end(); i++){
        while(S.size()>1 && ccw(S[S.size()-2], S[S.size()-1], *i)<=0){
            S.pop_back();
        }
        S.push_back(*i);
    }

    //special cases
    if(S.size()==2&&(S[0].x==S[1].x&&S[0].y==S[1].y)) S.pop_back();

    //output
    for(auto i = S.begin(); i<S.end();i++){
        std::cout<<i->x<<" "<<i->y<<"\n";
    }

    return 0;
}