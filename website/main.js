  $(document).ready(function(){
    $('.sidenav').sidenav();
  });


$('.dropdown-trigger').dropdown();

$(".button-collapse").sideNav();


document.addEventListener('DOMContentLoaded', function() {
    var elems = document.querySelectorAll('.parallax');
    var instances = M.Parallax.init(elems, options);
  });

$(document).ready(function(){
    $('.parallax').parallax();
  });

$(document).ready(function(){
    $('.scrollspy').scrollSpy();
  });

$(document).ready(function(){
// the "href" attribute of .modal-trigger must specify the modal ID that wants to be triggered
$('.modal').modal();
});

$('#modal1').modal('open');

$('#modal1').modal('close');

$(document).ready(function() {
    M.updateTextFields();
  });