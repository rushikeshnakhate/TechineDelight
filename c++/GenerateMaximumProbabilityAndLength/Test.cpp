#include <cmath>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <iostream>

#define _USE_MATH_DEFINES

//representing the plane
// We create a data structure Plane to represent the Plane, characterized by the distance Y

struct Plane {
    Plane(double distanceBetweenGridsOnPlane) : Y{distanceBetweenGridsOnPlane} {
    }

    double Y;
};

//representing a Line
//The position and orientation of a Line on the Plane is described by the Cartesian coordinates
//(x,y) of its center and the angle  θ it makes with the vertical axis
// Note that the  y coordinate of a line does not influence whether it intersects a line on the plane or not.
// Therefore, we do not need to consider it for our calculations; we only need to keep track of the
//x -coordinate and angle θ  of a Drawing Line during the simulation.
//We create a data structure line to represent a Drawing Line, storing its state  x,theta and its attribute L

struct Line {
    Line(double _x, double _theta, double L) : x{_x}, theta{_theta}, attributeL{L} {}

    double x;
    double theta;
    double attributeL;
};


//the state space of a DrawingLine
//The problem concerns a Line being drawn anywhere on an infinite plane with repeating lines.
// But, it is impractical to create an infinite plane for the simulation. Instead, we only toss DrawingLines between
// two successive lines on the plane i.e.  //0 ≤ x ≤ l . The estimate of the probability that the DrawingLine crosses a
// line is the same as for an infinite plane, owing to the symmetry of the plane.
//It would be proper to allow the angle with the vertical 0 ≤ theta ≤ 2pi however we can take advantage of some 
// rotational symmetry. A DrawingLine with angle theta  appears equivalent to a DrawingLine with the same coordinates and angle of 
// theta + pi . We therefore only allow 0 ≤ theta ≤ pi // in our calculations.


//simulation of DrawingLine
//For the simulation, we created a DrawLine function that returns a Line uniformly distributed in the state space.
// The function takes in as arguments the length of the line L to draw and the plane


std::unique_ptr<Line> DrawLine(double lengthOfDrawingLine, std::unique_ptr<Plane> &plane) {
    auto x = rand() * plane->Y;
    auto theta = rand() * M_PI;
    return std::move(std::make_unique<Line>(x, theta, lengthOfDrawingLine));
}

//checking a Line for intersection with a line on the plane
bool CrossLines(std::unique_ptr<Line> &pLine, std::unique_ptr<Plane> &floor) {
    auto x_right_tip = pLine->x + (pLine->attributeL / 2) * std::sin(pLine->theta);
    auto x_left_tip = pLine->x - (pLine->attributeL / 2) * std::sin(pLine->theta);
    return x_right_tip > floor->Y || x_left_tip < 0.0;
}

//estimating the probability through a Monte Carlo simulation
double EstimateProbLineCrossesLine(std::unique_ptr<Plane> &plane,
                                   double L,
                                   double numberOfTimeDrawingLine) {
    auto countCrossedLine = 0;
    int counter = 0;
    while (counter < numberOfTimeDrawingLine) {
        auto pLine = DrawLine(L, plane);
        if (CrossLines(pLine, plane))
            countCrossedLine += 1;
        counter++;
    }
    return countCrossedLine / numberOfTimeDrawingLine;
}

//I think there is no exact answer to this question
// For each given X you need to generate lets say a million random
//locations of the line and count how many time that condition (crossing only two lines of that grid) was satisfied.
std::tuple<double, double> GenerateMaximumProbabilityAndLength() {
    auto lengthOfDrawingLine = 0.123123;
    std::unique_ptr<Plane> pPlane = std::make_unique<Plane>(0.111);
    // Need to consider the case when line is drawn with length less distance between grids on plane
    auto probability = EstimateProbLineCrossesLine(pPlane, lengthOfDrawingLine, 1000);
    return std::make_tuple(probability, lengthOfDrawingLine);

}

//int main() {
//    GenerateMaximumProbabilityAndLength();
//    return 0;
//}