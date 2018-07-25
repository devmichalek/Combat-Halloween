<!-- SIDENAV BEGGINING -->
<ul class="nav-main sidenav" id="mobile-demo">
	
	<?php
	    if(isset($_SESSION['logged']))
	    {
	        require_once("sidenav-b-logged.php");
	    }
	?>
    
    <li><div class="divider"></div></li>
    <li>
        <a class="subheader teal lighten-3" style="margin-top: -10px;">
            <i class="material-icons right">near_me</i>Navigation 
        </a>
    </li>