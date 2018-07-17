$(document).ready(function(){
  $('.modal').modal();
});

$('#modal1').modal('open');

$('#modal1').modal('close');



$(document).ready(function(){
  $('select').formSelect();
});

$(document).ready(function(){
    $('.parallax').parallax();
  });


$(document).ready(function(){
  $('.datepicker').datepicker();
});



$(document).ready(function(){
  $('.sidenav').sidenav();
});

$('.dropdown-trigger').dropdown();

document.addEventListener('DOMContentLoaded', function() {
    var elems = document.querySelectorAll('.dropdown-trigger');
    var instances = M.Dropdown.init(elems, options);
  });

$(".button-collapse").sideNav();


$('select').material_select();


$(document).ready(function() {
    M.updateTextFields();
  });

$(document).ready(function(){
    $('.scrollspy').scrollSpy();
  });