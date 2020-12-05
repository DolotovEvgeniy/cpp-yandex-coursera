#include "Common.h"

#include <iostream>

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`
class Shape : public IShape {
public:
  virtual void SetPosition(Point position) {
    position_ = position;
  }

  virtual Point GetPosition() const {
    return position_;
  }

  virtual void SetSize(Size size) {
    size_ = size;
  }

  virtual Size GetSize() const {
    return size_;
  }

  virtual void SetTexture(std::shared_ptr<ITexture> texture) {
    texture_ = texture;
  }

  virtual ITexture* GetTexture() const {
    return texture_.get();
  }

  virtual void Draw(Image& image) const {
    if (image.empty()) {
      return;
    }

    const int minX = std::max(position_.x, 0);
    const int maxX = std::min(position_.x + size_.width, static_cast<int>(image[0].size()));
    const int minY = std::max(position_.y, 0);
    const int maxY = std::min(position_.y + size_.height, static_cast<int>(image.size()));

    for (int x = minX; x < maxX; x++) {
      for (int y = minY; y < maxY; y++) {
        if (InShape(x, y)) {
          char pixel = '.';
          if (texture_ != nullptr) {
            int textureX = x - minX;
            int textureY = y - minY;
            if (textureX < texture_->GetSize().width
                && textureY < texture_->GetSize().height)
            {
              pixel = texture_->GetImage()[textureY][textureX];
            }
          }
          image[y][x] = pixel;
        }
      }
    }
  }

protected:
  virtual bool InShape(int x, int y) const = 0;

  Point position_;
  Size size_;
  std::shared_ptr<ITexture> texture_;
};

class Rectangle : public Shape {
public:
  virtual std::unique_ptr<IShape> Clone() const {
    return make_unique<Rectangle>(*this);
  }

private:
  virtual bool InShape(int x, int y) const {
    return true;
  }
};

class Ellipse : public Shape {
public:
  virtual std::unique_ptr<IShape> Clone() const {
    return make_unique<Ellipse>(*this);
  }

private:
  virtual bool InShape(int x, int y) const {
    return IsPointInEllipse(Point{x - position_.x, y - position_.y}, size_);
  }
};


// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
  switch (shape_type) {
    case ShapeType::Rectangle:
      return make_unique<Rectangle>();
    case ShapeType::Ellipse:
      return make_unique<Ellipse>();
  }
}
