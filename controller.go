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
package pengo

import (
	engine "github.com/flosch/pongo2"
	. "github.com/penlook/pengo/builtin"
	"fmt"
)

type Controller struct {
	Name string
	ActionName string
	Http Http
	Router Router
	ViewData engine.Context
	View chan Data
	Template View
	TotalDeclared int
	TotalEmit int
	Translator Translator
	Signal chan int
	StopOnSignal chan bool
	End chan bool

	Model Model
	Module Module
}

// Share properties with View
type ViewBridge struct {
	Name string
	ActionName string
	Http Http
	Router Router
	ViewData engine.Context
}

// MVC -------------------------------------

// Controller initialization
func (controller *Controller) Initialize() {

	// Properties initialization
	controller.View = make(chan Data, 20)
	controller.ViewData = engine.Context {}
	controller.TotalDeclared = 0
	controller.TotalEmit = 0

	// Setup for template
	controller.Template = View {
		Controller: ViewBridge {
			Name: controller.Name,
			ActionName: controller.ActionName,
			Http: controller.Http,
			Router: controller.Router,
			ViewData: controller.ViewData,
		},
		Directory: "view",
	}

	// Setup for model
	controller.Model = Model {}
	controller.Model.Connect()

	// Setup for module
	controller.Module = Module {}

	// Multiple signal in life cycle
	controller.Signal = make(chan int, 10)

	// End flag for signal
	controller.StopOnSignal = make(chan bool, 1)

	// End flag for controller
	controller.End = make(chan bool, 1)

	// Listen system signal
	controller.OnSignal()
}

// Action initialization
func (controller Controller) InitAction() {

	// Broadcast signal
	controller.Signal <- SignalInitAction
}

// Add data to View
func (controller *Controller) AddDataToView(data Data) {
	for key, value := range data {
		controller.ViewData[key] = value
	}
	// Remember number variable was passed
	controller.TotalEmit = controller.TotalEmit + 1
}

// Listen signal from system
func (controller *Controller) OnSignal() {
	go func(controller *Controller) {
		loop := true
		for {
			select {
				case data := <- controller.View :
					controller.AddDataToView(data)
				case signal := <- controller.Signal :
					controller.ProcessSignal(signal, &loop)
			}
			if ! loop {
				break
			}
		}
	}(controller)
}

func (controller Controller) ProcessSignal(signal int, loop *bool) {
	switch (signal) {
		case SignalResponse :
			*loop = false
			controller.End <- true
	}
}

func (controller Controller) BeforeAction() {
	// Broadcast signal
	controller.Signal <- SignalBeforeAction

}

func (controller *Controller) AfterAction() {
	controller.TotalDeclared = len(controller.View)
	go func(controller *Controller) {
		for {
			if controller.TotalEmit == controller.TotalDeclared {
				controller.RenderTemplate()
				break
			}
		}
		fmt.Println(" --> AfterAction Done")
	}(controller)
}

func (controller Controller) RenderTemplate() {
	controller.Template.Render()
    controller.Signal <- SignalResponse
}

func (controller Controller) WaitResponse() {
	select {
		case <- controller.End:
	}
}

// MODULE ----------------------------------

func (controller Controller) Service(service string) string {
	return "Service"
}

func (controller Controller) Session(key string, value string) string {
	return "Session values"
}

func (controller Controller) Cookie(key string, value string) string {
	return "Cookie values"
}

func (controller Controller) Translate(word string) string {
	return "ABC"
}

// MODEL Alias --------------------------------

func (controller Controller) Table(table string) interface {} {
	return controller.Model.Table(table)
}

func (controller Controller) Document(document string) interface {} {
	return controller.Model.Document(document)
}

func (controller Controller) Key(key string) interface {} {
	return controller.Model.Key(key)
}

func (controller Controller) Graph(graph string) interface {} {
	return controller.Model.Graph(graph)
}

// Http Alias -----------------------------------

func (controller Controller) GET(key string) string {
	return controller.Http.GET(key)
}

func (controller Controller) POST(key string) string {
	return controller.Http.POST(key)
}

func (controller Controller) PUT(key string) string {
	return controller.Http.PUT(key)
}

func (controller Controller) PATCH(key string) string {
	return controller.Http.PATCH(key)
}

func (controller Controller) DELETE(key string) string {
	return controller.Http.DELETE(key)
}



