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

int line_length(Line line)
{
    return sqrt(pow(line.point2[0] - line.point1[0], 2) + pow(line.point2[1] - line.point1[1], 2));
}

void split_line(Line line, Line **new_lines)
{
    printf("Line to split\n");
    printf("%d, %d, %d, %d\n", line.point1[0],
                               line.point1[1],
                               line.point2[0],
                               line.point2[1]);

    printf("%f\n", line_length(line) / sqrt(12));

    int point1[2] = { (line.point2[0] - line.point1[0]) / 2 + line.point1[0],
                      (line.point2[1] - line.point1[1]) / 2 + line.point1[1] -
                      line_length(line) / sqrt(12) };

    int point2[2] = { (line.point2[0] - line.point1[0]) / 2 + line.point1[0],
                      (line.point2[1] - line.point1[1]) / 2 + line.point1[1] +
                      line_length(line) / sqrt(12) };

    printf("%d, %d\n", point1[0], point1[1]);
    printf("%d, %d\n", point2[0], point2[1]);

    Line line1 = { { line.point1[0], line.point1[1] }, { point1[0], point1[1] } };
    Line line2 = { { point1[0], point1[1] }, { point2[0], point2[1] } };
    Line line3 = { { point2[0], point2[1] }, { line.point2[0], line.point2[1] } };

    printf("%d, %d, %d, %d\n", line1.point1[0], line1.point1[1], line1.point2[0], line1.point2[1]);

    Line *some_line = malloc(sizeof(Line) * 3);

    some_line[0] = line1;
    some_line[1] = line2;
    some_line[2] = line3;

    print_lines(some_line, 3);

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
        printf("Depth %d:\n", i);
        for (int j = 0; j < (int)pow(3, i); j++)
        {
            split_line(temp_lines1[j], &new_lines);

            /*
            printf("Temp Lines");
            print_lines(temp_lines1, (int)pow(3, i));
            printf("New Lines");
            print_lines(new_lines, 3);
            */

            temp_lines2[j * 3 + 0] = new_lines[0];
            temp_lines2[j * 3 + 1] = new_lines[1];
            temp_lines2[j * 3 + 2] = new_lines[2];
        }
        Line *temp = temp_lines1;
        temp_lines1 = temp_lines2;
        temp_lines2 = temp;

        printf("\n");
    }

    free(*line_array);
    *line_array = temp_lines1;
    *final_array_size = (int)pow(3, depth + 1);
    print_lines(temp_lines1, *final_array_size);
    print_lines(*line_array, *final_array_size);


    free(temp_lines1);
    free(temp_lines2);
    free(new_lines);
}
