#include<bits/stdc++.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class circle {
    double x, y, r;
    public:
    void input(){
        std::cin >> x >> y >> r;
    }
    bool dotInside(double a, double b){
        return (sqrt((x - a) * (x - a) + (y - b) * (y - b)) <= r);
    }
};



int main(){
    circle a, b, c;
    srand(time(NULL));
    int inside = 0, outside = 0;
    a.input(), b.input(), c.input();
    for (int i = 0; i < 1e7; i++){
        double q = rand() / (double)(RAND_MAX) * 4 - 1;
        double p = rand() / (double)(RAND_MAX) * 4 - 1;
        if (a.dotInside(p, q) && b.dotInside(p, q) && c.dotInside(p, q)){
            inside++;
        } else {
            outside++;
        }
    }
    cout << ((double)inside / (double)(outside + inside)) * 16;

}