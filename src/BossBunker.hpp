#include "Bunker.hpp"

using namespace sf;
using namespace std;

class BossBunker: public Bunker{
protected:
    const int DAMAGE = 10;
    const int SPEED = 10;
    const int N_BUNKER = 3;
    double radius;
    Vector2f centre;
    Vector2f newPosition(double angle);
    void updatePosition(double angle);
public:
    BossBunker();
    BossBunker(Resources *src, double radius, Vector2f centre = Vector2f());
};