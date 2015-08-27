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

#ifndef APP_COMMAND_INPUT_H_
#define APP_COMMAND_INPUT_H_

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace app
{
	namespace command
	{
		class InputArgument
		{
			private:
				string name;
				string description;
				string value;
				string defaultValue;
			public:
				// Name
				InputArgument *setName(string);
				string getName();
				// Description
				InputArgument *setDescription(string);
				string getDescription();
				// Value
				InputArgument *setValue(string);
				string getValue();
				// Default
				InputArgument *setDefault(string);
				string getDefault();
		};

		class InputOption
		{
			private:
				string name;
				string description;
				string value;
				string defaultValue;
				int    mode;
			public:
				// Mode
				const static int OPTIONAL;
				const static int REQUIRED;
				const static int VALUE_NONE;
				// Name
				InputOption *setName(string);
				string getName();
				// Description
				InputOption *setDescription(string);
				string getDescription();
				// Value
				InputOption *setValue(string);
				string getValue();
				// Default
				InputOption *setDefault(string);
				string getDefault();
				// Mode
				InputOption *setMode(int);
				int getMode();
		};

		class Input
		{
			private:
				vector<InputArgument*> arguments;
				vector<InputOption*> options;
			public:
				Input *parser();
				// Option
				Input setOption(InputOption*);
				InputOption *getOption(string);
				vector<InputOption*> getOptions();
				// Argument
				Input setArgument(InputArgument*);
				InputArgument *getArgument(string);
				vector<InputArgument*> getArguments();
		};
	}
}

// Export
using app::command::Input;
using app::command::InputArgument;
using app::command::InputOption;

#endif