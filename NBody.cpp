#include "NBody.hpp"

Body::Body(sf::Vector2f _pos, sf::Vector2f _vel, double _mass, std::string _planet) 
{
	//initialize planet's members
	univ_pos = _pos;
	vel = _vel;
	mass = _mass;
	filename = _planet;
	this->setSprite();\
}

//setters & mutators
void Body::setSprite() 
{
	//create sf::image for planet
	sf::Image planet;
	if (!planet.loadFromFile(filename)) 
	{
		std::cout << "Error! Couldn’t load planet image!" << std::endl;
		exit(EXIT_FAILURE);
	}

	tex.loadFromImage(planet);
	
	this->sprite.setTexture(tex);
	this->sprite.setPosition(getRenderPos().x, getRenderPos().y);
}

sf::Sprite Body::getSprite() 
{
	return this->sprite;
}

void Body::setUnivPos(sf::Vector2f coord) 
{
	this->univ_pos = coord;
}

sf::Vector2f Body::getUnivPos() const 
{
	return this->univ_pos;
}

void Body::setVel(sf::Vector2f _vel) 
{
	this->vel = _vel;
}

sf::Vector2f Body::getVel()const 
{
	return this->vel;
}

void Body::setRenderPos(sf::Vector2f _renderPos) 
{
	this->renderPos = _renderPos;
}

sf::Vector2f Body::getRenderPos()const 
{
	return this->renderPos;
}

std::string Body::getName() 
{
	return filename;
}

sf::Vector2f Body::getAccel() 
{
	return accel;
}

void Body::setAccel(sf::Vector2f _acc) 
{
	this->accel = _acc;
}

//Class draw function
void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(this->sprite);
}

//determine the position of the planet in the window
void Body::detPos(double& radius, sf::Vector2u wSize) 
{
	sf::Vector2f r;
	r.x = ((wSize.x / 2) + ((this->univ_pos.x / radius)*(wSize.x / 2)));
	r.y = ((wSize.y / 2) - ((this->univ_pos.y / radius)*(wSize.y / 2)));
	this->setRenderPos(r);
	sprite.setPosition(this->renderPos.x, this->renderPos.y);
}

void Body::setMass(double _mass) 
{
	this->mass = _mass;
}

double Body::getMass() 
{
	return this->mass;
}

sf::Vector2f Body::get_fNet() 
{
	return this->f_net;
}

void Body::setfNet(sf::Vector2f __fnet) 
{
	this->f_net = __fnet;
}

Body::Body() { }

Body::~Body() 
{
	std::cout << "Body destructor called" << std::endl;
}

double scaleRadius(double& uRadius)
{
	return (uRadius / 10e+9);
}

void close(std::vector<Body*>vBody) 
{
	for (std::vector<Body*>::iterator it = vBody.begin(); it != vBody.end(); ++it) 
	{
		delete[](*it);
		(*it) = NULL;
	}
}

//caculate and set body velocity

void setBodyVelocity(double _time, Body* pBody) 
{
	sf::Vector2f velocity;
	velocity.x = pBody->getVel().x + (_time*pBody->getAccel().x);
	velocity.y = pBody->getVel().y + (_time*pBody->getAccel().y);
	pBody->setVel(velocity);
}

//calculate and set body position
void setBodyPosition(double _time, Body* pBody) 
{
	sf::Vector2f pos__;
	pos__.x = pBody->getUnivPos().x + (_time*pBody->getVel().x);
	pos__.y = pBody->getUnivPos().y + (_time*pBody->getVel().y);
	pBody->setUnivPos(pos__);
}

//set the bosy's acceleration
void setBodyAccel(Body* pBody) 
{
	sf::Vector2f __acc;
	__acc.x = pBody->get_fNet().x / pBody->getMass();
	__acc.y = pBody->get_fNet().y / pBody->getMass();
	pBody->setAccel(__acc);
}

void set_time(double _time, double _delta_T) 
{
	return;
}

sf::Vector2f pForce(Body* b1, Body* b2) 
{
	sf::Vector2f _force;
	double dx, dy, radius, total_pForce;

	//changed radius between the two bodies
	dx = (b1->getUnivPos().x) - (b2->getUnivPos().x);
	dy = (b1->getUnivPos().y) - (b2->getUnivPos().y);
	radius = sqrt(pow(dx, 2) + (pow(dy, 2)));
	
	total_pForce = (UGRAV*b1->getMass()*b2->getMass()) / pow(radius, 2);
	_force.x = total_pForce*(dx / radius);
	_force.y = total_pForce*(dy / radius);
	
	return _force;
}

	//draw body at each time unit
void step(double __time, double _rad, sf::Vector2u _wSize, Body* pBody) 
{
	setBodyAccel(pBody);
	setBodyVelocity(__time, pBody);
	setBodyPosition(__time, pBody);
	pBody->detPos(_rad, _wSize);
}

vars setEnv(sf::Font font) 
{
	vars v;
	sf::Text timeStamp;
	timeStamp.setFont(font);
	
	timeStamp.setPosition(0.f, 0.f);
	v._timeStamp = timeStamp;

	sf::Image backg;
	if (!backg.loadFromFile("starfield.jpg")) 
	{
		std::cout << "Couldn't load background image!" << std::endl;
		exit(EXIT_FAILURE);
	}
	v._backg = backg;
	return v;
}

void printVariables(std::vector<Body*> vBody) 
{
	for (std::vector<Body*>::iterator it = vBody.begin(); it != vBody.end(); ++it)
	{
		std::cout << (*it)->getRenderPos().x << "\t" << (*it)->getRenderPos().y << "\t";
		std::cout << (*it)->getVel().x << "\t" << (*it)->getVel().y << "\t";
		std::cout << (*it)->getMass() << "\t" << (*it)->getName() << std::endl;
	}
}
