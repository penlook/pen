# Framework Design
Author: Loi Nguyen <loint@penlook.com>  |  Date: 05/10/2015

### CLI
After create a new application, you need to go into your application directory for the next manipulation.

+ Create new application

```bash
pen new app
```

+ Create new action

```bash
pen new home:index
```

+ Create new repository

```bash
pen new mysql-user
```

+ Create new view

```bash
pen new home/index
```

+ Run application under hot-code reload mode

```bash
pen run
```

+ Build application and ready for production

```bash
pen build
```

+ Analyze application for debugging mode

```bash
pen debug router
```
```bash
pen debug controller
```
```bash
pen debug model
```

+ Unit testing

```bash
pen test unit
```

+ Benchmark testing

```bash
pen test benchmark
```

### Controller

+ Include library
```
#include <iostream>
#include <string>
```

+ Using namespace
```
using namespace std;
using namespace http;
```

+ Controller declaration
```go
@controller app
```

+ Controller declaration and extend from base controller

```go
@controller app base
```

+ Router - Method - Action mapping

```go
@Router /hello/:userid/:password
@Method GET POST PUT
Login(userid int, password string) {
}
```

+ Custom template path

```go
@Router /hello/:userid/:password
@Template /hello/custom/path
Login(userid int, password string) {
}
```

### Model

+ Select user who has id = 3 from user table (full)

```go
user := mysql>User
listUser := user.Find({
	Id: 3
})
```

+ Select user who has id = 3 from user table (short)

```go
listUser := mysql>User.Find({
	Id: 3
})
```

+ Create new status

```go
status := mongo>Status {
	Username: "loint",
	Content: "Have a nice day !",
}
status.Create()
```

+ Save login information using session

```go
session>Username = "loint"
session>Login = true
```

+ Assign and retrieve custom key with redis

```go
redis>"abc" = "hello"
fmt.Println(redis>"abc")
```

+ Graph query with cayley

```go
vertex := cayley>"Vertex_AtoB"
vertex.All()
```

### Template

+ Assign function variable to template

```go
$compress = func(html string) {
	return html + " is using compress function"
}
```

+ Assign normal variable to template

```go
$title = "Skeleton Application"
$message = "Hello World"
```

+ Template manipulation

```html
<html>
	<title>{{ title }}</title>
<body>
	<h1>{{ message }}</h1>
	<p>{{ "abc" | compress }}</p>
</body>
</html>
```

### Testing

+ Setup

```go
Setup() {
}
```

+ Testing

```go
@Test
Login() {
}
```

+ Teardown

```go
Teardown() {
}
```

+ Assertion Equal (assert.Equal)

```go
person := Person {
	Name: "Loi Nguyen",
	Age: 21,
}
person.Age == 21 ?
```

+ Assertion Not Nil (assert.NotNil)

```go
person.Age != nil ?
```

+ Assertion True

```go
person.Age ?
```

+ Assertion False

```go
! person.Age ?
```
