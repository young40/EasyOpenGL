//
//  EasyOpenGL_Math.cpp
//  EasyOpenGL
//
//  Created by Peter Young on 12/01/2018.
//  Copyright © 2018 Peter Young. All rights reserved.
//

#include <stdio.h>
#include "EasyOpenGL.hpp"

std::string string_format(const std::string fmt, ...) {
    int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
    std::string str;
    va_list ap;
    while (1) {     // Maximum two passes on a POSIX system...
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {  // Everything worked
            str.resize(n);
            return str;
        }
        if (n > -1)  // Needed size returned
            size = n + 1;   // For null char
        else
            size *= 2;      // Guess at a larger size (OS specific)
    }
    return str;
}

void dump(vec2 &v2, int len)
{
    string s2 = string_format("(%%0.%df, %%0.%df)", len, len);
    cout << "vec2:" << endl;
    cout << string_format(s2, v2.x, v2.y) << endl;
}

void dump(vec3 &v3, int len)
{
    string s3 = string_format("(%%0.%df, %%0.%df, %%0.%df)", len, len, len);
    cout << "vec3:" << endl;
    cout << string_format(s3, v3.x, v3.y, v3.z) << endl;
}

void dump(vec4 &v4, int len)
{
    string s4 = string_format("(%%0.%df, %%0.%df, %%0.%df, %%0.%df)", len, len, len, len);
    cout << "vec4:" << endl;
    cout << string_format(s4, v4.x, v4.y, v4.z, v4.w) << endl;
}

void dump(mat2 &m2, int len)
{
    string s2 = string_format("(%%0.%df %%0.%df)", len, len);
    cout << "mat 2x2:" << endl;
    cout << string_format(s2, m2[0].x, m2[0].y) << endl;
    cout << string_format(s2, m2[1].x, m2[1].y) << endl;
}

void dump(mat3 &m3, int len)
{
    string s3 = string_format("(%%0.%df %%0.%df %%0.%df)", len, len, len);
    cout << "mat 3x3:" << endl;
    cout << string_format(s3, m3[0].x, m3[0].y, m3[0].z) << endl;
    cout << string_format(s3, m3[1].x, m3[1].y, m3[1].z) << endl;
    cout << string_format(s3, m3[2].x, m3[2].y, m3[2].z) << endl;
}

void dump(mat4 &m4, int len)
{
    string s4 = string_format("(%%0.%df %%0.%df %%0.%df %%0.%df)", len, len, len, len);
    cout << "mat 4x4:" << endl;
    cout << string_format(s4, m4[0].x, m4[0].y, m4[0].z, m4[0].w) << endl;
    cout << string_format(s4, m4[1].x, m4[1].y, m4[1].z, m4[1].w) << endl;
    cout << string_format(s4, m4[2].x, m4[2].y, m4[2].z, m4[2].w) << endl;
    cout << string_format(s4, m4[3].x, m4[3].y, m4[3].z, m4[3].w) << endl;
}


