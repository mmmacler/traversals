# Traversals / Group 116
A simple visualization and comparison of A* and Dijkstra's algorithm.
## How do I run this project myself?
1. Ensure you have SFML installed
2. Clone the repo
```
git clone https://github.com/mmmacler/traversals.git
```
3. Run the makefile
```
cd traversals/
make
```
4. Run `./traversals` with a command line argument
- You can use preset sizes "small", "medium", "large", and "100k"
- Or define your own, with the first value being the maximum width in the x-direction, and the second being the maximum height in the y-direction
  - If you define your own, it's best to keep the x and y values in a roughly 16:9 aspect ratio; otherwise, everything might appear stretched
```
./traversals medium
./traversals 160 90
