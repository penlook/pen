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

#include <sys/core.h>
#include <sys/debug.h>
#include <cli/handler.h>

using namespace std;
using namespace http;

namespace cli {
	
	// Application structure generator
	void Handler::create(string name)
	{
		//Creator creator = Creator(name);
	}
	
	// Unit test
	// Benchmark
	void Handler::test(string type)
	{
		cout << "Test pengo application";
	}
	
	// Debug application components
	void Handler::debug(string app)
	{
		cout << "Debug mode";
	}
	
	// Build application
	void Handler::build(string app)
	{	
		executeCommand("pkill pendev");
		string cwd = getCwd();
		if (app.length() > 0) {
			cwd += "/" + app;
		}
		changeDirectory(cwd + "/build/production");
		executeCommand("./config.sh");
		int ret = executeCommand("./build.sh");
		cout << ret;
		cout.flush();
	}
	
	// Run application under hot-code reload
	void Handler::run(string app)
	{	
		string cwd = getCwd();
		
		if (app.length() > 0) {
			cwd += "/" + app;
		}
		
		changeDirectory(cwd + "/build/development");		
		executeCommand("sync && echo 3 > /proc/sys/vm/drop_caches");
		executeCommand("pkill pendev");
		executeCommand("service nginx stop");
		executeCommand("./prepare.sh");
		
		HttpRequest proxyRequest;
		HttpResponse proxyResponse;
		Http server(proxyRequest, proxyResponse);
		
		server.get("/", [&cwd](Request* _request, Response* _response) {
			Debug debug;
			debug.setResponse(_response)
				 .setViewPath(cwd + "/view")
				 .compile();
		});

		server.listen(80);
	}
	
	// Cli documentation
	void Handler::help(string doc)
	{
		cout << "Pengo help !";
	}

}