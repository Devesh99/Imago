#include "stringsglobals.h"

// string vectors updated upon initialization in image.cpp

QString morphology("Morphology");

QString canny("Canny");

QString flip_image("Flip image");

std::vector<QString> morphology_operations;

QString lpf("LPF");
std::vector<QString> lpf_operations;

QString salt_and_pepper("Salt and pepper");

QString equalize_hist("Equalize histogram");

QString hough_circles("Hough circles");

std::vector<QString> hough_lines_operations;
QString hough_lines("Hough lines");

std::vector<QString> hpf_operations;
QString hpf("HPF");
