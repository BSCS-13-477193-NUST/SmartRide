#ifndef MISC_H
#define MISC_H

typedef enum Rating {
    NONE = 0,
    POOR = 1,
    AVERAGE = 2,
    GOOD = 3,
    VERY_GOOD = 4,
    EXCELLENT = 5
} Rating;

class Coordinate {
   private:
    int x;
    int y;

   public:
    Coordinate(int x, int y);
    int getX() const;
    int getY() const;
};
#endif  // MISC_H