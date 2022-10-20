#pragma once

#include "Vec3.h"

class Vec3f :
    public Vec3<float>
{
    using Vec3<float>::Vec3; //inherit the constructors of the template
};

