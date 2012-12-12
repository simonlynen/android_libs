/* ============================================================
 *
 * This file is a part of the RSC project.
 *
 * Copyright (C) 2010 by Johannes Wienke <jwienke at techfak dot uni-bielefeld dot de>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include <iostream>

int print() {
    std::cout << "CONSTRUCTOR" << std::endl;
    return 0;
}

typedef int cb(void);

#pragma data_seg(".CRT$XCU")
static cb *autostart1[] = { print };
#pragma data_seg()

int main(int argc, char **argv) {
    return 1;
}
