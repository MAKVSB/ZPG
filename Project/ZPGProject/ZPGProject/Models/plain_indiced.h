/**
 * @file plain.h
 *
 * @brief Plain model
 *
 * @author Daniel Makovský
 *
 * @year 2023
 **/


#include <cstdint>

const float plain_indiced[24] = {
    1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
};
const uint32_t plain_indices[6] = {
    0,
    1,
    2,
    3,
    0,
    2
};