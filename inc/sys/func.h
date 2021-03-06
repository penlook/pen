/**
 * Pengo Project
 *
 * Copyright (c) 2015 Penlook Development Team
 *
 * --------------------------------------------------------------------
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * --------------------------------------------------------------------
 *
 * Author:
 *     Loi Nguyen       <loint@penlook.com>
 */

#ifndef SYS_FUNC_H
#define SYS_FUNC_H

// C Interface
#ifdef __cplusplus
extern "C" {
#endif
// C Library
#include <func/gen.h>
#include <func/strlib.h>
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// C/C++ GERNERIC FUNCTION
#include <sys/type.h>
#include <sys/gen.h>

// Export
using namespace sys::func;

#endif