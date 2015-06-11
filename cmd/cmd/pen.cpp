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

#include <cli/handler.h>

using namespace cli;

int main(int argc, char* argv[]) 
{
	Cmd pen = Cmd(argc, argv);
	Handler func;
	pen.addOption("new",   "Create new application",         (cli_callback) func.create)
	   .addOption("run",   "Run app under hot-code reload",  (cli_callback) func.run)
	   .addOption("build", "Build app for production mode",  (cli_callback) func.build)
	   .addOption("debug", "Debug application components",   (cli_callback) func.debug)
	   .addOption("test",  "Run unit or benchmark testing",  (cli_callback) func.test)
	   .addOption("help",  "Pengo show help for options",    (cli_callback) func.help)
	   .run();
	return 0;
}