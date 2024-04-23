#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <SFML/Graphics.hpp>
#include "graph.h"
using namespace::std;
//#define x_max 1840
//#define y_max 1000
#define x_max 200
#define y_max 200

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

int main() {
    // allocate on the heap
    Graph* my_graph = new Graph();
    
    // opens the window at 1840x1000 resolution with the title "Traversals"
    sf::RenderWindow window(sf::VideoMode(1840, 1000), "Traversals");
    int rand1 = (rand() % my_graph->vertices.size() - 1) + 1;
    int rand2 = (rand() % my_graph->vertices.size() - 1) + 1;

    auto p1 = my_graph->vertices.begin();
    advance(p1, rand1);
    auto p2 = my_graph->vertices.begin();
    advance(p2, rand2);

    // have the window display a 'View' rather than the raw objects
    // this is like having a movable camera show what's being rendered
    sf::View view({0, 0}, {x_max*multiplier, y_max*multiplier});
    window.setView(view);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            // listen for keypresses and do certain things
            // when certain keys are pressed
            if(event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    cout << "A*" << endl;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    cout << "Dijkstra's Algorithm" << endl;
                }
            }
            else if(event.type == sf::Event::Closed) {
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
        window.display();
    }
    return 0;
}
