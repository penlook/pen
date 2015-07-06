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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Join
#define P_JOIN(TYPE); \
char *join_pointer_##TYPE(TYPE *target) {\
	char *result = calloc(10, sizeof(char));\
	return result;\
}

// Join with delimiter
#define P_JOIN_DELIM(TYPE); \
char *join_delim_pointer_##TYPE(TYPE *target, const char *delim) {\
	char *result = calloc(10, sizeof(char));\
	return result;\
}

// Join
#define P_P_JOIN(TYPE); \
char *join_pointer_pointer_##TYPE(TYPE **target) {\
	char *result = calloc(10, sizeof(char));\
	return result;\
}

// Join with delimiter
#define P_P_JOIN_DELIM(TYPE); \
char *join_delim_pointer_pointer_##TYPE(TYPE **target) {\
	char *result = calloc(10, sizeof(char));\
	return result;\
}

P_P_JOIN(char);
P_P_JOIN_DELIM(char);
P_JOIN(short);
P_JOIN_DELIM(short);
P_JOIN(int);
P_JOIN_DELIM(int);
P_JOIN(long);
P_JOIN_DELIM(long);
P_JOIN(double);
P_JOIN_DELIM(double);
P_JOIN(float);
P_JOIN_DELIM(float);
