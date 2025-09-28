//UMN CSCI 5607 2D Geometry Library Homework [HW0]
//TODO: For the 18 functions below, replace their sub function with a working version that matches the desciption.

#ifndef GEOM_LIB_H
#define GEOM_LIB_H

#include "pga.h"

//Displace a point p on the direction d
//The result is a point
Point2D move(Point2D p, Dir2D d){
  return Point2D(p.x + d.x, p.y + d.y);
}

//Compute the displacement vector between points p1 and p2
//The result is a direction 
Dir2D displacement(Point2D p1, Point2D p2){
  return Dir2D(p2.x - p1.x, p2.y - p1.y);
}

//Compute the distance between points p1 and p2
//The result is a scalar 
float dist(Point2D p1, Point2D p2){
  return displacement(p1, p2).magnitude();
}

//Compute the perpendicular distance from the point p the the line l
//The result is a scalar 
float dist(Line2D l, Point2D p){
  return abs(p.x * l.x + p.y * l.y + l.w) / l.magnitude();
}

//Compute the perpendicular distance from the point p the the line l
//The result is a scalar 
float dist(Point2D p, Line2D l){
  return abs(p.x * l.x + p.y * l.y + l.w) / l.magnitude();
}

//Compute the intersection point between lines l1 and l2
//You may assume the lines are not parallel
//The results is a a point that lies on both lines
Point2D intersect(Line2D l1, Line2D l2){
  return wedge(l1, l2).normalized();
}

//Compute the line that goes through the points p1 and p2
//The result is a line 
Line2D join(Point2D p1, Point2D p2){
  return vee(p1, p2);
}

//Compute the projection of the point p onto line l
//The result is the closest point to p that lies on line l
Point2D project(Point2D p, Line2D l){
  return dot(dot(p, l.normalized()), l.normalized()) + wedge(dot(p, l.normalized()), l.normalized());
}

//Compute the projection of the line l onto point p
//The result is a line that lies on point p in the same direction of l
Line2D project(Line2D l, Point2D p){
  return dot(dot(l, p), p) + wedge(dot(l, p), p);
}

//Compute the angle point between lines l1 and l2 in radians
//You may assume the lines are not parallel
//The results is a scalar
float angle(Line2D l1, Line2D l2){
  return asin(wedge(l1.normalized(), l2.normalized()).magnitude());
}

//Compute if the line segment p1->p2 intersects the line segment a->b
//The result is a boolean
bool segmentSegmentIntersect(Point2D p1, Point2D p2, Point2D a, Point2D b){
  float ep = 0.0000001;


  float seg1XMin = std::min(p1.x, p2.x);
  float seg1XMax = std::max(p1.x, p2.x);

  float seg2XMin = std::min(a.x, b.x);
  float seg2XMax = std::max(a.x, b.x);

  float seg1YMin = std::min(p1.y, p2.y);
  float seg1YMax = std::max(p1.y, p2.y);

  float seg2YMin = std::min(a.y, b.y);
  float seg2YMax = std::max(a.y, b.y);

  float intersectX = intersect(join(p1, p2), join(a, b)).x;
  float intersectY = intersect(join(p1, p2), join(a, b)).y;

  return (seg1XMin < intersectX || abs(seg1XMin - intersectX) < ep) && (intersectX < seg1XMax || abs(intersectX - seg1XMax) < ep) &&
         (seg2XMin < intersectX || abs(seg2XMin - intersectX) < ep) && (intersectX < seg2XMax || abs(intersectX - seg2XMax) < ep) &&
         (seg1YMin < intersectY || abs(seg1YMin - intersectY) < ep) && (intersectY < seg1YMax || abs(intersectY - seg1YMax) < ep) &&
         (seg2YMin < intersectY || abs(seg2YMin - intersectY) < ep) && (intersectY < seg2YMax || abs(intersectY - seg2YMax) < ep);
}

//Compute if the point p lies inside the triangle t1,t2,t3
//Your code should work for both clockwise and counterclockwise windings
//The result is a bool
bool pointInTriangle(Point2D p, Point2D t1, Point2D t2, Point2D t3){
  float xMin = std::min(t1.x, std::min(t2.x, t3.x));
  float xMax = std::max(t1.x, std::max(t2.x, t3.x));
  float yMin = std::min(t1.y, std::min(t2.y, t3.y));
  float yMax = std::max(t1.y, std::max(t2.y, t3.y));

  bool endsCheck = xMin <= p.x && p.x <= xMax &&
                   yMin <= p.y && p.y <= yMax;

  bool check1 = segmentSegmentIntersect(p, t1, t2, t3);
  bool check2 = segmentSegmentIntersect(p, t2, t1, t3);
  bool check3 = segmentSegmentIntersect(p, t3, t1, t2);

  bool intersectionCheck = check1 == false && check2 == false && check3 == false;

  return endsCheck && intersectionCheck;
}

//Compute the area of the triangle t1,t2,t3
//The result is a scalar
float areaTriangle(Point2D t1, Point2D t2, Point2D t3){
  return 0.5 * vee(t1.normalized(), vee(t2.normalized(), t3.normalized()));
}

//Compute the distance from the point p to the triangle t1,t2,t3 as defined 
//by it's distance from the edge closest to p.
//The result is a scalar
//NOTE: There are some tricky cases to consider here that do not show up in the test cases!
float pointTriangleEdgeDist(Point2D p, Point2D t1, Point2D t2, Point2D t3){
  //Create the lines and get the bounds of the line segments
  Line2D line1 = join(t1, t2);
  float line1XMin = std::min(t1.x, t2.x);
  float line1XMax = std::max(t1.x, t2.x);
  float line1YMin = std::min(t1.y, t2.y);
  float line1YMax = std::max(t1.y, t2.y);

  Line2D line2 = join(t2, t3);
  float line2XMin = std::min(t2.x, t3.x);
  float line2XMax = std::max(t2.x, t3.x);
  float line2YMin = std::min(t2.y, t3.y);
  float line2YMax = std::max(t2.y, t3.y);

  Line2D line3 = join(t1, t3);
  float line3XMin = std::min(t1.x, t3.x);
  float line3XMax = std::max(t1.x, t3.x);
  float line3YMin = std::min(t1.y, t3.y);
  float line3YMax = std::max(t1.y, t3.y);

  //Get nearest points on the line (not line segment) to p
  Point2D p1 = project(p, line1);
  Point2D p2 = project(p, line2);
  Point2D p3 = project(p, line3);

  //If the result of the projection is not within the line segment, then the nearest point on the segment must be one of the two ends of the segment.
  //This part of the code determines if thats the case and then chooses the correct end of the segment to consider
  if (!(line1XMin <= p1.x && p1.x <= line1XMax && line1YMin <= p1.y && p1.y <= line1YMax))
  {
    float dist1 = dist(p, t1);
    float dist2 = dist(p, t2);

    if (std::min(dist1, dist2) == dist1)
    {
      p1 = Point2D(t1.x, t1.y);
    }

    else
    {
      p1 = Point2D(t3.x, t3.y);
    }
  }

  if (!(line2XMin <= p2.x && p2.x <= line2XMax && line2YMin <= p2.y && p2.y <= line2YMax))
  {
    float dist1 = dist(p, t2);
    float dist2 = dist(p, t3);

    if (std::min(dist1, dist2) == dist1)
    {
      p2 = Point2D(t2.x, t2.y);
    }

    else
    {
      p2 = Point2D(t3.x, t3.y);
    }
  }

  if (!(line3XMin <= p3.x && p3.x <= line3XMax && line3YMin <= p3.y && p3.y <= line3YMax))
  {
    float dist1 = dist(p, t1);
    float dist2 = dist(p, t3);

    if (std::min(dist1, dist2) == dist1)
    {
      p3 = Point2D(t1.x, t1.y);
    }

    else
    {
      p3 = Point2D(t3.x, t3.y);
    }
  }

  return std::min(dist(p, p1), std::min(dist(p, p2), dist(p, p3)));
}

//Compute the distance from the point p to the closest of three corners of
// the triangle t1,t2,t3
//The result is a scalar
float pointTriangleCornerDist(Point2D p, Point2D t1, Point2D t2, Point2D t3){
  return std::min(dist(p, t1), std::min(dist(p, t2), dist(p, t3)));
}

//Compute if the quad (p1,p2,p3,p4) is convex.
//Your code should work for both clockwise and counterclockwise windings
//The result is a boolean
bool isConvex_Quad(Point2D p1, Point2D p2, Point2D p3, Point2D p4){
  bool ret = true;

  Line2D line1 = join(p1, p2);
  Line2D line2 = join(p2, p3);
  Line2D line3 = join(p3, p4);
  Line2D line4 = join(p4, p1);

  //A convex quad will have at least one pair of non adjacent edges whose extended lines intersect.
  //The intersect function can be used to check for this. The intersect function behaves a bit strangely
  //if used on two lines that don't intersect. If they don't intersect the returned point will have either
  //an INF or NAN value. These if statements check if the returned point has valid values. If it does that
  //means they intersect and the quad must be concave.
  if (!(std::isnan(intersect(line1, line3).x) or std::isinf(intersect(line1, line3).x)))
  {
    ret = false;
  }
  if (!(std::isnan(intersect(line1, line3).y) or std::isinf(intersect(line1, line3).y)))
  {
    ret = false;
  }
  if (!(std::isnan(intersect(line2, line4).x) or std::isinf(intersect(line2, line4).x)))
  {
    ret = false;
  }
  if (!(std::isnan(intersect(line2, line4).y) or std::isinf(intersect(line2, line4).y)))
  {
    ret = false;
  }

  return ret;
}

//Compute the reflection of the point p about the line l
//The result is a point
Point2D reflect(Point2D p, Line2D l){
  Point2D mid = project(p, l);
  Dir2D dis = displacement(p, mid);
  return move(mid, dis);
}

//Compute the reflection of the line d about the line l
//The result is a line
Line2D reflect(Line2D d, Line2D l){
  Point2D knownPoint = Point2D(0, 0);

  if (d.y == 0)
  {
    knownPoint = Point2D((-1 * (d.w)) / (d.x), 0);
  }
  else
  {
    knownPoint = Point2D(0, (-1 * (d.w)) / (d.y));
  }

  return project(d, reflect(knownPoint, l));
}

#endif