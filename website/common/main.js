// preloader
document.addEventListener("DOMContentLoaded", function(){
	$('.preloader-background').delay(1000).fadeOut('slow');
	$('.preloader-wrapper').delay(1000).fadeOut();
});

$(document).ready(function(){
  $('.modal').modal();
});



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

$(document).ready(function(){
    $('.fixed-action-btn').floatingActionButton();
  });

$('.dropdown-trigger').dropdown();

$(".button-collapse").sideNav();


$('select').material_select();


$(document).ready(function() {
    M.updateTextFields();
  });

$(document).ready(function(){
    $('.scrollspy').scrollSpy();
  });
  
$(document).ready(function(){
    $('.tap-target').tapTarget();
  });