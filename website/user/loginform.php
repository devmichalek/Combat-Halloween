<?php
	session_start();
	unset($_SESSION['e_username']);
	unset($_SESSION['e_email']);
	unset($_SESSION['e_password']);
	unset($_SESSION['e_passwordcon']);
	unset($_SESSION['e_bot']);
	if(isset($_SESSION['logged']))
	{
		header('Location: ../home.php');
		exit();
	}
?>

<!DOCTYPE html>
<html lang="en">
<head>
	<!-- Standard Meta -->
	<meta charset="UTF-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
	<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=1.0">

	<!-- Site Properties -->
	<title>Account - Combat Halloween</title>
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0-rc.2/css/materialize.min.css">
  	<link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
	<link rel="stylesheet" type="text/css" href="../main.css">
	<link rel="icon" href="https://user-images.githubusercontent.com/19840443/42683508-c8c24644-868d-11e8-9a8a-cbde02588774.png">

	<meta http-equiv="cache-control" content="max-age=0" />
    <meta http-equiv="cache-control" content="no-cache" />
    <meta http-equiv="cache-control" content="no-store" />
    <meta http-equiv="cache-control" content="must-revalidate" />
    <meta http-equiv="expires" content="0" />
    <meta http-equiv="expires" content="Tue, 01 Jan 1980 1:00:00 GMT" />
    <meta http-equiv="pragma" content="no-cache" />
</head>
<body>
	<!-- NAVBAR -->
	<div id="home" class="header scrollspy">
	<div class="navbar-fixed">
		<nav>
		    <div class="nav-wrapper">
		      	<a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
		      	<a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
		      	<ul id="nav-mobile" class="right hide-on-med-and-down">
			      	<a class='dropdown-trigger btn nav-button' href='../index.php'>Home</a>
			      	<a class='dropdown-trigger btn nav-button' href='register.php'>Sign In</a>
		    	</ul>
		    </div>
		</nav>
		
	</div>
	<ul class="nav-main sidenav" id="mobile-demo">
      	<a class='dropdown-trigger btn nav-button' href='../index.php'>Home</a>
		<a class='dropdown-trigger btn nav-button' href='register.php'>Sign In</a>
	</ul>
	</div>


	<div class="container center">
		<!-- Header -->
		<div class="col s12 m12 l12 xl12">
			<section>
				<div>
					<h2>Account - Log In</h2>
				</div>
			</section>
		</div>
			

		<div class="row">
	    <form class="col s6 push-s3" action="login.php" method="post">

	      <div class="row">
	        <div class="input-field col s12">
	          <input id="username" type="text" class="validate" name="username">
	          <label for="username">
	          <h5 class="modcon2">Username</h5>
	      		</label>
	        </div>
	      </div>

	      <div class="row">
	        <div class="input-field col s12">
	          <input id="password" type="password" class="validate" name="password">
	          <label for="password">
	          	<h5 class="modcon2">Password</h5>
	      	</label>
	        </div>
	      </div>
	      
	      <button class="btn waves-effect waves-light nav-button" type="submit" name="action">Login
		    <i class="material-icons right">send</i>
		  </button>

	    
		<?php
			echo '<h4 class="errorColor">';
			if(isset($_SESSION['error']) )
			{
				echo $_SESSION['error'];
				unset($_SESSION['error']);
			}
			echo '</h4>';
		?>
		</form>
	</div>
	</div>

	<!-- Footer -->
	<footer class="page-footer">
      <div class="container">
        <div class="row">
          <div class="col l6 s12">
            <h5 class="white-text">Adrian Michałek </h5>
            <p class="grey-text text-lighten-4">Project of SFML & QT.</p>
          </div>
        </div>
      </div>
      <div class="footer-copyright">
        <div class="container"><a class="modal-trigger waves-effect waves-light btn" href="#license">©2018 Terms of Use</a></div>
      </div>
    </footer>


    <!-- LICENSE -->
  <div id="license" class="modal modal-fixed-footer">
    <div class="modal-content">
      <h4 class="modcon">GNU GENERAL PUBLIC LICENSE</h4>
      <div><p><?php include('LICENSE.txt'); ?></p></div>
    </div>
    <div class="modal-footer">
      <a href="#!" class="modal-action modal-close waves-effect waves-green btn-flat">Agree</a>
    </div>
  </div>


	<!-- Compiled and minified JavaScript -->
	<script type="text/javascript" src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
  	<script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0-rc.2/js/materialize.min.js"></script>
	<script type="text/javascript" src="../main.js"></script>
</body>
</html>