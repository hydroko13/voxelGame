#pragma once
#include <glad/glad.h>
#include <iostream>

void _glCheckErrorBefore(const char* label);

void _glCheckErrorAfter(const char* label);




#define glCheckErrorBefore(label) _glCheckErrorBefore(label)
#define glCheckErrorAfter(label) _glCheckErrorAfter(label)

//#define glCheckErrorBefore(x)
//#define glCheckErrorAfter(x)

