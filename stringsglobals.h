#ifndef STRINGSGLOBALS_H
#define STRINGSGLOBALS_H
#include <QString>
#include <iostream>
#include <vector>

// variables for technique names
// used in display to list widget as well updating parameters of selected algorithm (string comparison)
QString flip_image("Flip image");

QString morphology("Morphology");
std::vector<QString> morphology_operations;

QString lpf("LPF");
std::vector<QString> lpf_operations;

QString salt_and_pepper("Salt and pepper");

QString equalize_hist("Equalize histogram");


#endif // STRINGSGLOBALS_H

