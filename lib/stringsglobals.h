#ifndef STRINGSGLOBALS_H
#define STRINGSGLOBALS_H
#include <QString>
#include <iostream>
#include <vector>

// variables for technique names
// used in display to list widget as well updating parameters of selected algorithm (string comparison)
extern QString flip_image;

extern QString morphology;
extern std::vector<QString> morphology_operations;

extern QString lpf;
extern std::vector<QString> lpf_operations;

extern QString salt_and_pepper;

extern QString equalize_hist;

extern QString canny;

extern QString hough_circles;

extern std::vector<QString> hough_lines_operations;
extern QString hough_lines;

extern std::vector<QString> hpf_operations;
extern QString hpf;
#endif // STRINGSGLOBALS_H

