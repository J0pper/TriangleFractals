#ifndef PATTERN_H
#define PATTERN_H

#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line
{
    float point1[2];
    float point2[2];
} Line;


void print_lines(Line *line_array, int size);
float line_length(Line line);
float line_slope(Line line);
void line_midpoint(Line line, float *midpoint);
float perp_line_slope(float slope);
float slope_to_deg_angle(float slope);
void split_line(Line line, Line *new_lines, int working_header);
void generate_fractal(Line start_line, int depth, Line *line_array, int final_array_size);

#endif // !PATTERN_H
