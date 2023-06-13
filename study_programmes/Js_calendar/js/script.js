
const weekdays = [
    'Monday',
    'Tuesday',
    'Wednesday',
    'Thursday',
    'Friday',
    'Saturday',
    'Sunday'
  ];

const numbr_divs = 7;
const days = document.querySelector('.days__container');

for(let i = 1; i <= numbr_divs; i++) {
    const day = document.createElement('button');
    day.className = 'day';
    day.innerHTML = weekdays[i-1].substring(0,3);
    days.appendChild(day);
}

const _day = document.querySelectorAll('.day');

_day.addEventListener('mouseenter',function(){
    _day.classList.add('hover');
})

_day.addEventListener('mouseleave',function(){
    _day.classList.remove('hover');
})