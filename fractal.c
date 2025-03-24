#include "fractal.h"


void print_lines(Line *line_array, int size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        //printf("HELLO %d\n", line_array[i]);
        printf("%d:  %f, %f, %f, %f\n", i,
                                   line_array[i].point1[0],
                                   line_array[i].point1[1],
                                   line_array[i].point2[0],
                                   line_array[i].point2[1]);
    }
    printf("\n");
}

void print_line(Line line)
{
    printf("%f, %f, %f, %f\n", line.point1[0], line.point1[1], line.point2[0], line.point2[1]);
}

float line_length(Line line)
{
    return sqrt(pow(line.point2[0] - line.point1[0], 2) + pow(line.point2[1] - line.point1[1], 2));
}

float line_slope(Line line)
{
    float y = line.point2[1] - line.point1[1];
    float x = line.point2[0] - line.point1[0];
    if (!y) return 0;
    if (!x) return FLT_MAX;
    return y / x;
}

float perp_line_slope(float slope)
{
    if (!slope) return FLT_MAX;
    return -1.f / slope;
}

float slope_to_deg_angle(float slope)
{
    return atan(slope) * 180 / M_PI;
}

void line_midpoint(Line line, float *midpoint)
{
    midpoint[0] = ((line.point2[0] - line.point1[0]) / 2) + line.point1[0];
    midpoint[1] = ((line.point2[1] - line.point1[1]) / 2) + line.point1[1];
}

void split_line(Line line, Line *new_lines, int working_head)
{
    float offset = line_length(line) / sqrt(12); // Perpendicular offset from the current line.
    float slope = line_slope(line);              // Slope of the current line.
    float perp_slope = perp_line_slope(slope);   // Slope of the line perpendicular to the current line.

    float midpoint[2];
    line_midpoint(line, midpoint);

    float h_offset = cos(atan(perp_slope)) * offset;
    float v_offset = sin(atan(perp_slope)) * offset;

    float point1[2] = {};
    float point2[2] = {};

    int slope_bool = 1;
    int switch_p1_p2_bool = 1;
    int max_slope_bool = 1;

    if (slope <= 0) slope_bool *= -1;
    if (line.point2[0] < line.point1[0]) switch_p1_p2_bool *= -1;
    if (slope == FLT_MAX && line.point1[1] > line.point2[1]) max_slope_bool *= -1;

    /*point1[0] = midpoint[0] + h_offset * slope_bool * switch_p1_p2_bool * max_slope_bool;*/
    /*point1[1] = midpoint[1] + v_offset * slope_bool * switch_p1_p2_bool * max_slope_bool;*/
    /*point2[0] = midpoint[0] - h_offset * slope_bool * switch_p1_p2_bool * max_slope_bool;*/
    /*point2[1] = midpoint[1] - v_offset * slope_bool * switch_p1_p2_bool * max_slope_bool;*/
    point1[0] = round(midpoint[0] + h_offset * slope_bool * switch_p1_p2_bool * max_slope_bool);
    point1[1] = round(midpoint[1] + v_offset * slope_bool * switch_p1_p2_bool * max_slope_bool);
    point2[0] = round(midpoint[0] - h_offset * slope_bool * switch_p1_p2_bool * max_slope_bool);
    point2[1] = round(midpoint[1] - v_offset * slope_bool * switch_p1_p2_bool * max_slope_bool);

    /*if (slope <= 0)*/
    /*{*/
    /*    printf("Old: ");*/
    /*    print_line(line);*/
    /*    point1[0] = round(midpoint[0] - h_offset);*/
    /*    point1[1] = round(midpoint[1] - v_offset);*/
    /*    point2[0] = round(midpoint[0] + h_offset);*/
    /*    point2[1] = round(midpoint[1] + v_offset);*/
    /*} */
    /*else*/
    /*{*/
    /*    // print_line(line);*/
    /*    // printf("  %f\n", slope);*/
    /*    point1[0] = round(midpoint[0] + h_offset);*/
    /*    point1[1] = round(midpoint[1] + v_offset);*/
    /*    point2[0] = round(midpoint[0] - h_offset);*/
    /*    point2[1] = round(midpoint[1] - v_offset);*/
    /*}*/

    new_lines[(working_head * 3) + 0] = (Line){ { line.point1[0], line.point1[1] }, { point1[0], point1[1] } };
    new_lines[(working_head * 3) + 1] = (Line){ { point1[0], point1[1] }, { point2[0], point2[1] } };
    new_lines[(working_head * 3) + 2] = (Line){ { point2[0], point2[1] }, { line.point2[0], line.point2[1] } };
}

void generate_fractal(Line start_line, int depth, Line *line_array, int final_array_size)
{
    if (!depth) return;

    Line working_line_array[final_array_size];

    for (int i = 0; i < depth; i++)
    {
        int lines_per_depth = (int)pow(3, i);
        for (int j = 0; j < lines_per_depth; j++)
        {
            split_line(line_array[j], working_line_array, j);
        }

        for (int j = 0; j < final_array_size; j++)
        {
            line_array[j] = working_line_array[j];
        }
    }
}
