#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include <iterator>
#include <chrono>
#include <map>
#include <SFML/Graphics.hpp>
#include "graph.h"
using namespace::std;

// settings for how to draw vertices and edges
#define multiplier 14
#define vertex_radius 6.5
#define line_thickness 4

// a utility function to draw lines with SFML since one isn't included
void draw_line(pair<int, int> p1, pair<int, int> p2, sf::Color color, sf::RenderWindow& window) {
    int a2 = (p1.first-p2.first)*(p1.first-p2.first);
    int b2 = (p1.second-p2.second)*(p1.second-p2.second);
    float c2 = sqrt(a2+b2);
    
    float y = p2.second - p1.second;
    float x = p2.first - p1.first;
    float rotation = (atan2(y, x))*57.3;

    sf::RectangleShape rectangle;
    rectangle.setSize({c2*multiplier, line_thickness});
    rectangle.setPosition((p1.first*multiplier), (p1.second*multiplier));
    rectangle.setRotation(rotation);
    rectangle.setFillColor(color);
    window.draw(rectangle);
};


int main(int argc, char* argv[]) {
    // the maximum width (x-direction) and height (y-direction)
    // in which to draw vertices
    int xmax, ymax;

    if (argc >= 4 || argc == 1) {
        cout << "Bad arguments." << endl;
        return 1;
    } else if (argc == 2) {
        // given a preset size
        if (string(argv[1]) == "small") {
            xmax = 60;
            ymax = 40;
        } else if (string(argv[1]) == "medium") {
            xmax = 100;
            ymax = 50;
        } else if (string(argv[1]) == "large") {
            xmax = 600;
            ymax = 400;
        } else if (string(argv[1]) == "100k") {
            xmax = 2200;
            ymax = 1200;
        } else {
            cout << "Bad arguments." << endl;
            return 1;
        }
    } else {
        // given xmax and ymax
        xmax = stoi(string(argv[1]));
        ymax = stoi(string(argv[2]));
    }

    // allocate on the heap
    Graph* my_graph = new Graph(xmax, ymax);
 
    // opens the window at 1840x1000 resolution with the title "Traversals"
    sf::RenderWindow window(sf::VideoMode(1840, 1000), "Traversals");
    int rand1 = (rand() % my_graph->vertices.size() - 1) + 1;
    int rand2 = (rand() % my_graph->vertices.size() - 1) + 1;

    auto p1 = my_graph->vertices.begin();
    advance(p1, rand1);
    auto p2 = my_graph->vertices.begin();
    advance(p2, rand2);

    //run and time our searches
    //timing taken from 
    //https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c
    auto start = std::chrono::high_resolution_clock::now();
    auto bfs_path = my_graph->BFS(p1->first, p2->first);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double seconds = duration.count() / 1000.0;
    cout << "BFS Time: " << seconds << " milliseconds" << endl;


    start = std::chrono::high_resolution_clock::now();
    auto dfs_path = my_graph->DFS(p1->first, p2->first);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    seconds = duration.count() / 1000.0;

    cout << "DFS Time: " << seconds << " milliseconds" << endl;
    // have the window display a 'View' rather than the raw objects
    // this is like having a movable camera show what's being rendered
    const int x_max = xmax*multiplier;
    const int y_max = ymax*multiplier;
    const sf::Vector2f dimensions(x_max, y_max);

    sf::View view({0, 0}, dimensions);
    window.setView(view);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }          
        }
        window.clear();
        for(auto iter: my_graph->vertices) {
            
            // draw vertices
            sf::CircleShape temp(vertex_radius, 20);
            temp.setOrigin(temp.getRadius(), temp.getRadius());
            temp.setPosition(iter.first.first*multiplier, iter.first.second*multiplier);
            window.draw(temp);

            //draw edges
            for (auto edge: iter.second) {
                draw_line(iter.first, edge.first, sf::Color::White, window);
            }
        }
            //draw bfs and dfs path
            vector<pair<int, int>>::iterator it;
            for(it = dfs_path.begin(); it != dfs_path.end(); it++) {
            
                sf::CircleShape temp(vertex_radius, 20);
                temp.setOrigin(temp.getRadius(), temp.getRadius());
                temp.setPosition(it->first*multiplier, it->second*multiplier);

                //draw DFS path in green
                temp.setFillColor(sf::Color(0, 255, 0, 128));
                window.draw(temp);
            }

            //draw bfs and dfs path
            vector<pair<int, int>>::iterator it2;
            for(it2 = dfs_path.begin(); it2 != dfs_path.end(); it2++) {
            
                sf::CircleShape temp(vertex_radius, 20);
                temp.setOrigin(temp.getRadius(), temp.getRadius());
                temp.setPosition(it2->first*multiplier, it2->second*multiplier);

                //draw DFS path in green
                temp.setFillColor(sf::Color(0, 0, 255, 128));
                window.draw(temp);
            }

            //draw start and end vertices
                sf::CircleShape temp(vertex_radius, 20);
                temp.setOrigin(temp.getRadius(), temp.getRadius());
                temp.setPosition(p1->first.first*multiplier, p1->first.second*multiplier);
                temp.setFillColor(sf::Color(156, 0, 255, 255));
                window.draw(temp);

                sf::CircleShape temp2(vertex_radius, 20);
                temp.setOrigin(temp.getRadius(), temp.getRadius());
                temp.setPosition(p2->first.first*multiplier, p2->first.second*multiplier);
                temp.setFillColor(sf::Color(156, 0, 255, 255));
                window.draw(temp);

        window.display();
    }
    return 0;
}
