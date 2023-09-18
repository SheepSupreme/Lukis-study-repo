// let ul = document.querySelector('ul');
// const div = document.querySelector('div');

// console.log(div.childNodes);

// console.log(ul.previousElementSibling);
// console.log(ul.nextSibling);



// const button = document.querySelector('.btn');
// function alertBtn() {
//     alert('I love JavaScript');
// };
// button.addEventListener("click",alertBtn);

// let newBgcolor = document.querySelector('.container');
// function _changeBGcolor(){
//     newBgcolor.style.backgroundColor = 'blue';
// };
// newBgcolor.addEventListener("mouseover",_changeBGcolor);



const hidden_text = document.querySelector('.text');
const _button = document.querySelector('.btn');

function revealContent(){
    if(hidden_text.classList.contains('reveal')){
        hidden_text.classList.remove('reveal');
    } else {
        hidden_text.classList.add('reveal');
    }
};

_button.addEventListener('click', revealContent);