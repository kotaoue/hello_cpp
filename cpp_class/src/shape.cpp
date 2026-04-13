/**
 * shape.cpp — Shape クラス階層の実装
 */

#include "shape.hpp"

#include <cmath>
#include <sstream>

// ─────────────────────────────────────────────
// Shape
// ─────────────────────────────────────────────

// static メンバー変数の定義（宣言はヘッダ、定義は .cpp に書く）
int Shape::instance_count_ = 0;

Shape::Shape(std::string name)
    : name_(std::move(name))
{
    increment_count();
}

Shape::~Shape()
{
    decrement_count();
}

std::string Shape::describe() const
{
    std::ostringstream oss;
    oss << name_ << " [area=" << area()
        << ", perimeter=" << perimeter() << "]";
    return oss.str();
}

const std::string& Shape::name() const noexcept
{
    return name_;
}

int Shape::instance_count() noexcept
{
    return instance_count_;
}

void Shape::increment_count() noexcept
{
    ++instance_count_;
}

void Shape::decrement_count() noexcept
{
    --instance_count_;
}

std::ostream& operator<<(std::ostream& os, const Shape& shape)
{
    return os << shape.describe();
}

// ─────────────────────────────────────────────
// Circle
// ─────────────────────────────────────────────

Circle::Circle(double radius)
    : Shape("Circle"), radius_(radius)
{
}

double Circle::area() const
{
    return M_PI * radius_ * radius_;
}

double Circle::perimeter() const
{
    return 2.0 * M_PI * radius_;
}

std::string Circle::describe() const
{
    std::ostringstream oss;
    oss << "Circle(r=" << radius_
        << ", area=" << area()
        << ", perimeter=" << perimeter() << ")";
    return oss.str();
}

double Circle::radius() const noexcept
{
    return radius_;
}

// ─────────────────────────────────────────────
// Rectangle
// ─────────────────────────────────────────────

Rectangle::Rectangle(double width, double height)
    : Shape("Rectangle"), width_(width), height_(height)
{
}

double Rectangle::area() const
{
    return width_ * height_;
}

double Rectangle::perimeter() const
{
    return 2.0 * (width_ + height_);
}

std::string Rectangle::describe() const
{
    std::ostringstream oss;
    oss << "Rectangle(w=" << width_ << ", h=" << height_
        << ", area=" << area()
        << ", perimeter=" << perimeter() << ")";
    return oss.str();
}

double Rectangle::width() const noexcept
{
    return width_;
}

double Rectangle::height() const noexcept
{
    return height_;
}
