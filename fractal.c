#include "fractal.h"


void print_lines(Line *line_array, int size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        //printf("HELLO %d\n", line_array[i]);
        printf("%d:  %d, %d, %d, %d\n", i,
                                   line_array[i].point1[0],
                                   line_array[i].point1[1],
                                   line_array[i].point2[0],
                                   line_array[i].point2[1]);
    }
    printf("\n");
}

float line_length(Line line)
{
    return sqrt(pow(line.point2[0] - line.point1[0], 2) + pow(line.point2[1] - line.point1[1], 2));
}

float line_slope(Line line)
{
    float y = (float)(line.point2[1] - line.point1[1]);
    float x = (float)(line.point2[0] - line.point1[0]);
    if (!x) return FLT_MAX;
    return y / x;
}

float perp_line_slope(float slope)
{
    if (!slope) slope = FLT_MIN;
    return -1.f / slope;
}

float slope_to_deg_angle(float slope)
{
    return atan(slope) * 180 / M_PI;
}

void line_midpoint(Line line, float *midpoint)
{
    midpoint[0] = (line.point2[0] - line.point1[0]) / 2 + line.point1[0];
    midpoint[1] = (line.point2[1] - line.point1[1]) / 2 + line.point1[1];
}

void split_line(Line line, Line **new_lines)
{
    /*printf("Line to split\n");*/
    /*printf("%d, %d, %d, %d\n", line.point1[0],*/
    /*                           line.point1[1],*/
    /*                           line.point2[0],*/
    /*                           line.point2[1]);*/

    float offset = line_length(line) / sqrt(12);
    
    float slope = line_slope(line);
    float perp_slope = perp_line_slope(slope);
    
    // printf("%f, %f, %f, %f, %f\n", slope, perp_slope, offset, cos(atan(perp_slope)), sin(atan(perp_slope)));

    float midpoint[2];
    line_midpoint(line, midpoint);

    float h_offset = cos(atan(perp_slope)) * offset;
    float v_offset = sin(atan(perp_slope)) * offset;

    float point1[2] = {};
    float point2[2] = {};

    if (slope > 0)
    {
        point1[0] = midpoint[0] - h_offset;
        point1[1] = midpoint[1] - v_offset;
        point2[0] = midpoint[0] + h_offset;
        point2[1] = midpoint[1] + v_offset;
    } 
    else
    {
        point1[0] = midpoint[0] + h_offset;
        point1[1] = midpoint[1] + v_offset;
        point2[0] = midpoint[0] - h_offset;
        point2[1] = midpoint[1] - v_offset;
    }

    Line line1 = { { line.point1[0], line.point1[1] }, { point1[0], point1[1] } };
    Line line2 = { { point1[0], point1[1] }, { point2[0], point2[1] } };
    Line line3 = { { point2[0], point2[1] }, { line.point2[0], line.point2[1] } };

    Line *some_line = malloc(sizeof(Line) * 3);

    some_line[0] = line1;
    some_line[1] = line2;
    some_line[2] = line3;

    // print_lines(some_line, 3);

    free(*new_lines);

    *new_lines = some_line;
}

void generate_fractal(Line start_line, int depth, Line **line_array, int *final_array_size)
{
    Line *temp_lines1 = malloc((int)(sizeof(Line) * pow(3, depth + 1)));
    Line *temp_lines2 = malloc((int)(sizeof(Line) * pow(3, depth + 1)));
    Line *new_lines = malloc((int)(sizeof(Line) * 3));

    temp_lines1[0] = start_line;

    for (int i = 0; i <= depth; i++)
    {
        // printf("Depth %d:\n", i);
        for (int j = 0; j < (int)pow(3, i); j++)
        {
            split_line(temp_lines1[j], &new_lines);

            temp_lines2[j * 3 + 0] = new_lines[0];
            temp_lines2[j * 3 + 1] = new_lines[1];
            temp_lines2[j * 3 + 2] = new_lines[2];
        }
        Line *temp = temp_lines1;
        temp_lines1 = temp_lines2;
        temp_lines2 = temp;

        // printf("\n");
    }

    *line_array = temp_lines1;
    *final_array_size = (int)pow(3, depth + 1);
    print_lines(*line_array, *final_array_size);

    free(temp_lines1);
    free(temp_lines2);
    free(new_lines);
}
