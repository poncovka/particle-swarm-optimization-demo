#include "particle.h"
#include "driver.h"

Particle::Particle(const Point &p, const Point &v)
{
    position = p;
    velocity = v;
}

std::string Particle::str()
{
    std::ostringstream stream;
    stream << "Particle{" << position.str() << "}";
    return stream.str();
}




