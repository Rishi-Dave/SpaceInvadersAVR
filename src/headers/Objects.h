#include <stdlib.h>

#ifndef OBJECTS_H
#define OBJECTS_H

class Alien; // Forward declaration for Alien
class Bullet;

class Ship {
    private:
        int x;
        int y;
        int speed;
    
    public:
    // Public methods to access and modify private data (getters/setters)
        Ship() : x(60), y(110), speed(5) {}

        void moveRight() {
            x += speed;
        }

        void moveLeft() {
            x -= speed;
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

};

class Bullet {
    private:
        int x;
        int y;
        int state;
    
    public:
    // Public methods to access and modify private data (getters/setters)
        Bullet(int x, int y, int state) : x(x), y(y), state(state) {}

        void moveDown() {
            y -= 12;
        }

        void changeState() {
            state = state+1;
            state = state % 4;
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

        int getState() {
            return state;
        }
        bool hit(Alien alien);
};

class Alien {
    private:
        int x;
        int y;
        int state;
    
    public:
    // Public methods to access and modify private data (getters/setters)
        Alien(int x, int y, int state) : x(x), y(y), state(state) {}
        Alien() : x(0), y(0), state(0) {}

        void moveDown() {
            y -= 12;
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

        void setX(int newX) {
            x = newX;
        }

        void setY(int newY) {
            y = newY;
        }


        //is hit: is hit by a laser

        bool isHit(Bullet bullet) {
            int bX = bullet.getX();
            int bY = bullet.getY();
            if(abs(x - bX) <= 15 && abs(y - bY) <=15) {
                return true;
            }
            return false;
        }

};

inline bool Bullet::hit(Alien alien) {
    int aX = alien.getX();
    int aY = alien.getY();
    if(abs(x - aX) <= 15 && abs(y - aY) <=15) {
        return true;
    }
    return false;
}


#endif