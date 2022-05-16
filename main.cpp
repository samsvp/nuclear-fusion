#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>


#include "include/brush.hpp"
#include "include/window.hpp"


/**
 * Reads in the data.csv file into a vector of points
 * @return vector of points
 *
 */
std::vector<nf::Vec2> readcsv() {
    std::vector<nf::Vec2> points;
    std::string line;
    std::ifstream file("mall_data.csv");

    while (getline(file, line)) {
        std::stringstream lineStream(line);
        std::string bit;
        double x, y;
        getline(lineStream, bit, ',');
        x = stof(bit);
        getline(lineStream, bit, '\n');
        y = stof(bit);

        points.push_back({x, y});
    }

    return points;
}


void write_csv(const std::vector<nf::Vec2>& points)
{
    std::ofstream myfile;
    myfile.open("output.csv");
    myfile << "x,y,c" << std::endl;

    std::vector<nf::Vec2> centroids = nf::KMeans(points, 5);
    for (auto& p: points) {
        myfile << p.x << "," << p.y << "," << nf::assign_centroid_id(p, centroids) << std::endl;
    }
    myfile.close();
}


int main(int argc, char **argv) 
{
    // test kmeans
    std::cout << "start read" << std::endl;
    auto p = readcsv();
    std::cout << "read" << std::endl;
    write_csv(p);
    std::cout << "written" << std::endl;

    // test brush
    nf::Window window;

    nf::Brush brush = nf::Brush("../brushes/3.png", {50,50});
    brush.setColor({255,0,0,8});
    brush.draw_line(&window, 100, 250, 1, 1);
    brush.draw_line(&window, 300, 350, 100, 250);
    brush.draw_circle(&window, 400, 400, 100);
    brush.draw_ellipse(&window, 400, 300, 100, 200);

    return 0;
}