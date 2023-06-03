# Java Script

## table of contents
- [Java Script](#java-script)
  - [table of contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Output](#output)
  - [Statements](#statements)
  - [functions](#functions)
  - [Objects](#objects)
  - [Events](#events)

---
## Introduction
With the `document.getElementById()` method it is possible to change attributes of a object and even change the source.<br>

```javascript
//Example:
document.getElementById("demo").style.fontSize = "35px";
```
The `.innerHTML` function right after that allows you to change the text of that object.

## Output
```javascript
.innerHTML
document.write()
window.alert()
console.log()
```
## Statements
`let` defines a variable. Different from the command `var` it defines the variable only inside of the block(loop) it currently is in.<br>
`const` does define a global variable. This variable can not be changed again.

## functions
function is a block of code that is designed to perform a certain task.
**Syntax:**
```javascript
function name(parameter1, parameter2, parameter3) {
  // code to be executed
}
```
## Objects
In real life, a car is an object.

A car has properties like weight and color, and methods like start and stop.
```javascript
const person = {
  firstName: "John", //the object person got assigned the property first Name with the value "John"
  lastName: "Doe",
  age: 50,
  eyeColor: "blue"
};
```
functions can be stored as the value of a property: `fullName : function(){return this.firstName}`

**this** refers to the person object.
Detailed explenation at [W3Schools/Objects](https://www.w3schools.com/js/js_objects.asp)

## Events
An HTML event can be something the browser does, or something a user does.

Event handlers like `onclick = "document.getElementById('demo').innerHTML = Date()"` allow to integrate javascript code into **HTML** elements.

| Event       | Description                                        |
|-------------|----------------------------------------------------|
| onchange    | An HTML element has been changed                   |
| onclick     | The user clicks an HTML element                    |
| onmouseover | The user moves the mouse over an HTML element      |
| onmouseout  | The user moves the mouse away from an HTML element |
| onkeydown   | The user pushes a keyboard key                     |
| onload      | The browser has finished loading the page          |
