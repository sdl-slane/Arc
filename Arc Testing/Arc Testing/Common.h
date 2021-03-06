#pragma once

#ifndef __COMMON_H__
#define __COMMON_H__

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <Arc/Functions.h>
#include <Arc/Geom.h>

using namespace Arc;
using std::fstream;
using std::ios;
using std::cout;
using std::string;
using std::stringstream;

#ifndef GRID_SIZE
#define GRID_SIZE 61.0f
#endif // GRID_SIZE

#endif // __COMMON_H__
