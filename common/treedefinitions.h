#pragma once
#include <boost/foreach.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

// bg, bgi, bgm
namespace bg = boost::geometry;
namespace bgi = bg::index;
namespace bgm = bg::model;

// Point
typedef bgm::point<float, 2, bg::cs::cartesian> Point;

// Box
typedef bgm::box<Point> Box;