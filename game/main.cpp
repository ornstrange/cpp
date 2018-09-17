#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Ent {
    double hp;
    int x;
    int y;
} player;

int main(void) {

    player.x = 5;
    player.y = 10;
    player.hp = 90.5;

    cout << "player {x, y} = {" << player.x << ", " << player.y << "}" << endl;
    cout << "player health = " << player.hp << endl;

    return 0;
}
