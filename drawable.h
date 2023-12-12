#pragma once
#include <string>
using namespace std;
#include "CMUgraphicsLib\CMUgraphics.h"

class game;     //forward declaration

struct point
{
    int x, y;
};

// Enum to distinguish between drawing images and shapes
enum DrawType {
    DRAW_IMAGE,
    DRAW_SHAPE
};

// Base class for any drawable object in the game including bricks, ball, toolbar icons,... etc
// Each drawable object is bounded by a rectangular boundary
class drawable
{
protected:
    DrawType drawType;  // Enum to indicate whether to draw an image or a shape
    string imageName;   // Path to its image
    string shapeType;   // Type of shape
    point uprLft;       // Upper left corner of the drawable object
    int width, height;

protected:
    game* pGame;        // Pointer to game object

public:
    // Constructor for drawing images
    drawable(point r_uprleft, int r_width, int r_height, game* r_pGame);

    // Constructor for drawing shapes
    drawable(point r_uprleft, int r_width, int r_height, game* r_pGame, const string& shapeType);

    virtual void draw() const;  // For a drawable object to draw itself on the screen
    void setImageName(const string& path);
};
