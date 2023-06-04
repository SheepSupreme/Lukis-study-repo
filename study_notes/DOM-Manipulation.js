// DOM Manipulation




// getElementById()

let title = document.getElementById('main-heading');
console.log(title);


// getElementByClassName()

let listItem = document.getElementsByClassName('list-items')
console.log(listItem);


// querySelector()

const container = document.querySelector('div');
console.log(container);


// querySelectorAll()

const all_containers = document.querySelectorAll('div');
console.log(all_containers);

const listItems = document.querySelectorAll('.list-items');
for (i=0; i < listItems.length; i++) {
    listItems[i].style.fontSize = '2rem';
}

const ul = document.querySelector('ul');
const li = document.createElement('li');
ul.append(li) // Adding Elements
li.innerText = "X-Men"; // Modifying the text
//Modifying Attributes & Methods
li.setAttribute('id', 'main-heading');
li.removeAttribute('id');
const title = document.querySelector('#main-heading');
console.log(title.getAttribute('id'));
li.classList.add('list-items')
li.classList.remove('list-items')
console.log(li.classList.contains('list-items')); //boolean if class contains such a class



//Traversing the DOM

// Parents & children
let ul = document.querySelector('ul');
console.log(ul.parentNode); // outputs parent
console.log(ul.childNodes); // outputs children including <p>
console.log(ul.firstChild); // outputs first child
console.log(ul.lastchild);  // outputs last child

ul.childNodes[1].style.backgroundColor = 'blue'; // to change Attributes a Elements needs to be selected
console.log(ul.children); // outputs children excluding <p>
console.log(ul.firstElementChild); // first child Element
console.log(ul.lastElementChild); // last child Element

// Siblings
let ul = document.querySelector('ul');
const div = document.querySelector('div');
console.log(div.childNodes);
console.log(ul.previousElementSibling);
console.log(ul.nextSibling);

// Event-Listeners
