#ifndef NBODY_HPP
#define NBODY_HPP

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <string>
#include <cmath>
#include <sstream>
#include <new>
#include <memory>

#define UGRAV - 6.67E-11

template <typename T>
std::string to_string(T value) 
{
	std::ostringstream os;
	os << value;
	return os.str();
}

//planetary body
class Body : sf::Drawable 
{
protected:
	sf::Vector2f univ_pos, vel, renderPos, accel, f_net;
	double mass;
	std::string filename;
	sf::Sprite sprite;
public:
	sf::Texture tex;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void detPos(double& radius, sf::Vector2u wSize);
	void setUnivPos(sf::Vector2f _pos);
	void setVel(sf::Vector2f _vel);
	void setRenderPos(sf::Vector2f _renderPos);
	void setSprite();
	void setMass(double _mass);
	void setAccel(sf::Vector2f _acc);
	void setfNet(sf::Vector2f __fnet);
	
	double getMass();
	sf::Vector2f get_fNet();
	sf::Vector2f getAccel();
	sf::Sprite getSprite();
	sf::Vector2f getRenderPos()const;
	sf::Vector2f getUnivPos()const;
	sf::Vector2f getVel()const;
	std::string getName();
	Body(sf::Vector2f _pos, sf::Vector2f _vel, double _mass, std::string _planet);
	Body();
	~Body();
};

void setBodyVelocity(double _time, Body* pBody);
void setBodyPosition(double _time, Body* pBody);
void setBodyAccel(Body* pBody);

struct variables 
{
	sf::Text _timeStamp;
	sf::Image _backg;
};

typedef struct variables vars;

double scaleRadius(double& uRadius);
void close(std::vector<Body*>vBody);
void set_time(double, double);
sf::Vector2f pForce(Body* b1, Body* b2);
vars setEnv(sf::Font font);
void printVariables(std::vector<Body*> vBody);
void close(std::vector<Body*>vBody);
void step(double __time, double _rad, sf::Vector2u _wSize, Body* pBody);

#endif
