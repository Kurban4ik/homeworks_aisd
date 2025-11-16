#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
#include <chrono>

using namespace std;

class circle {
public:
    double x, y, r;
    
    void input() {
        cin >> x >> y >> r;
    }
    
     bool dotInside(double a, double b) const {
        return (sqrt((x - a) * (x - a) + (y - b) * (y - b)) <= r);
    }
};

double exactArea() {
    return 0.25 * M_PI + 1.25 * asin(0.8) - 1;
}

double monteCarloArea(const vector<circle>& circles, 
                     double x_min, double x_max, 
                     double y_min, double y_max, 
                     int n_points) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> x_dist(x_min, x_max);
    uniform_real_distribution<double> y_dist(y_min, y_max);
    
    int inside_count = 0;
    
    for (int i = 0; i < n_points; i++) {
        double x = x_dist(gen);
        double y = y_dist(gen);
        
        bool in_all_circles = true;
        for (const auto& circle : circles) {
            if (!(circle.dotInside(x, y))) {
                in_all_circles = false;
                break;
            }
        }
        
        if (in_all_circles) {
            inside_count++;
        }
    }
    
    double area_rect = (x_max - x_min) * (y_max - y_min);
    return ((double)(inside_count) / n_points) * area_rect;
}

void runExperiment(const vector<circle>& circles, 
                  const string& filename,
                  double x_min, double x_max,
                  double y_min, double y_max) {
    ofstream file(filename);
    file << "N,ApproximateArea,RelativeError,TimeMs\n";
    
    double exact_area = exactArea();
    
    for (int n = 100; n <= 100000; n += 500) {
        auto start = chrono::high_resolution_clock::now();
        
        double approx_area = monteCarloArea(circles, x_min, x_max, y_min, y_max, n);
        double relative_error = abs(approx_area - exact_area) / exact_area;
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        file << n << "," << approx_area << "," << relative_error << "," 
             << duration.count() << "\n";
        
        if (n % 10000 == 0) {
            cout << "N=" << n << ", Area=" << approx_area 
                 << ", Error=" << relative_error * 100 << "%\n";
        }
    }
    
    file.close();
}

int main() {
    vector<circle> circles(3);
    circles[0].x = 1.0; circles[0].y = 1.0; circles[0].r = 1.0;
    circles[1].x = 1.5; circles[1].y = 2.0; circles[1].r = sqrt(5)/2;
    circles[2].x = 2.0; circles[2].y = 1.5; circles[2].r = sqrt(5)/2;
    
    double exact_area = exactArea();
    cout << "Exact area: " << exact_area << "\n\n";
    
    // широкая [0, 3] x [0, 3]
    cout << "Running wide area experiment...\n";
    runExperiment(circles, "wide_area_results.csv", 0, 3, 0, 3);
    
    // узкая [0.7, 2.1] x [0.7, 2.1] 
    cout << "\nRunning narrow area experiment...\n";
    runExperiment(circles, "narrow_area_results.csv", 0.7, 2.1, 0.7, 2.1);
    
}