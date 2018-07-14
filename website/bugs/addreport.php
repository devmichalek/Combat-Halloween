<?php
	session_start();

	if(!isset($_SESSION['logged']))
	{
		header('Location: http://combathalloween.netne.net/user/loginform.php');
		exit();
	}

	require_once "../connect.php";
	mysqli_report(MYSQLI_REPORT_STRICT);
	$connection = @new mysqli($host, $db_user, $db_password, $db_name);

	if($result = @$connection->query( sprintf("SELECT * FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $_SESSION['username']))))
	{
		$row = $result->fetch_assoc();
		
		if($row['permissions'] != "admin" && $row['permissions'] != "moderator")
		{
			$result->free_result();
			$connection->close();
			header('Location: http://combathalloween.netne.net/home.php');
		}

		$result->free_result();
	}
	else
	{
		$result->free_result();
		$connection->close();
		header('Location: http://combathalloween.netne.net/home.php');
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
	<title>Combat Halloween Add Report</title>
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
	<div class="navbar-fixed">
	<nav>
	    <div class="nav-wrapper">
	      	<a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
	      	<a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
	      	<ul id="nav-mobile" class="right hide-on-med-and-down">
	      		<li><a class="nav" href="../home.php">Home</a></li>
	        	<li><a class="nav" href="index.php">Reports</a></li>
	        	<li><a class="nav" href="modifyreport.php">Modify Report</a></li>
	      	</ul>
	    </div>
  	</nav>
  	</div>
  	<ul class="nav-main sidenav" id="mobile-demo">
	    <li><a class="nav" href="../home.php">Home</a></li>
      	<li><a class="nav" href="index.php">Reports</a></li>
      	<li><a class="nav" href="modifyreport.php">Modify Report</a></li>
	</ul>

	<div class="container center">
		
		<!-- Header -->
		<div class="s12">
					<h2>Combat Halloween Add Report</h2>
		</div>
		
		


		<form class="col s6 push-s3" method="post" action="addrep.php">

			<!-- NAME -->
			<div class="row">
	        <div class="input-field col s6 push-s3">
	          <input id="name" type="text" class="validate" name="name">
	          <label for="name"><h5 class="modcon2">Name</h5></label>
	        </div>
	      	</div>
			
			<!-- TYPE -->
	      	<div class="row col s6">
			<div class="input-field col s3 push-s3">
		    <select name="type">
	        	<option value="Bug">Bug</option>
	        	<option value="New Feature">New Feature</option>
	        	<option value="Syntax Error">Syntax Error</option>
	        	<option value="Other Report">Other Report</option>
		    </select>
		    	<label>Type</label>
		  	</div>
			
			<!-- ACTION -->
			<div class="input-field col s3 push-s3">
		    <select name="actiontodo">
	        	<option value="Repair">Repair</option>
	        	<option value="Add">Add</option>
	        	<option value="Correct">Correct</option>
	        	<option value="Modify">Modify</option>
	        	<option value="Suggestion not to correct">Suggestion not to correct</option>
	        	<option value="Remove">Remove</option>
	        	<option value="Create">Create</option>
		    </select>
		    	<label>Action to do</label>
		  	</div>
		  	</div>

		  	<!-- DESCRIPTION -->
		     <div class="row">
		       	<div class="input-field col s6 push-s3">
		          	<textarea id="description" class="materialize-textarea" name="description" value=""></textarea>
		          	<label for="description">Description</label>
		       	</div>
		    </div>

		    <!-- LOCATION OF THE REPORT -->
			<div class="row">
	        <div class="input-field col s6 push-s3">
	          <input id="location" type="text" class="validate" name="location">
	          <label for="location"><h5 class="modcon2">Location</h5></label>
	        </div>
	      	</div>

	      	<!-- DEADLINE -->
			<div class="row">
	        <div class="input-field col s6 push-s3">
	        	<input id="deadline" type="text" class="datepicker" name="deadline" value="Not scheduled">
	          <label for="deadline"><h5 class="modcon2">Deadline</h5></label>
	        </div>
	      	</div>

	      	<!-- AUTHOR -->
			<div class="row">
	        <div class="disabled input-field col s6 push-s3">
	        	<input id="author" type="text" class="validate" name="author" value="<?php echo $_SESSION['email'];?>">
	          <label for="author"><h5 class="modcon2">Author</h5></label>
	        </div>
	      	</div>

	      	<!-- STATUS -->
			<div class="row s6">
		  	<div class="input-field col s3 push-s3">
		    <select name="status">
	        	<option value="New">New</option>
	        	<option value="In development">In development</option>
	        	<option value="Revised">Revised</option>
	        	<option value="Fixed">Fixed</option>
		    </select>
		    	<label>Status</label>
		  	</div>
			
			<!-- DEVELOPER -->
		  	<div class="input-field col s3 push-s3">
		    <select name="developer">
	        	<option value="devmichalek@gmail.com">devmichalek@gmail.com</option>
	        	<option value="sebastek321@gmail.com">sebastek321@gmail.com</option>
	        	<option value="kamilgawlik@icloud.com">kamilgawlik@icloud.com</option>
		    </select>
		    	<label>Choose developer</label>
		  	</div>
		  	</div>

			<!-- BUTTON -->
			<button class="btn waves-effect waves-light red lighten-1 nav-button" type="submit" name="action">Add
		    <i class="material-icons right">send</i>
		  </button>
		</form>
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
	<script type="text/javascript" src="main.js"></script>
</body>
</html>