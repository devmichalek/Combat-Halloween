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
		header('Location: http://combathalloween.netne.net/bugs/index.php');
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
	<title>Combat Halloween Add Bug</title>
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
	      	<a href="" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
	      	<ul id="nav-mobile" class="right hide-on-med-and-down">
	      		<li><a class="nav" href="../home.php">Home</a></li>
	        	<li><a class="nav btn red lighten-1 nav-button" href="index.php">Bugs</a></li>
	      	</ul>
	    </div>
  	</nav>
  	</div>
  	<ul class="nav-main sidenav" id="mobile-demo">
	    <li><a class="nav" href="../home.php">Home</a></li>
      	<li><a class="nav btn red lighten-1 nav-button" href="index.php">Bugs</a></li>
	</ul>

	<div class="container center">
		
		<!-- Header -->
		<div class="s12">
					<h2>Combat Halloween Add Bug</h2>
		</div>
		
		


		<form class="col s6 push-s3" method="post" action="add.php" style="margin-bottom: 20px;">

			<!-- NAME -->
			<div class="row">
	        <div class="input-field col s6 push-s3">
	          <input id="name" type="text" class="validate" name="name" value="None">
	          <label for="name"><h5 class="modcon2">Name</h5></label>
	        </div>
	      	</div>
			
			<!-- TYPE -->
	      	<div class="row col s6">
			<div class="input-field col s3 push-s3">
		    <select name="type">
	        	<option value="Bug">Bug</option>
	        	<option value="Change">Change</option>
	        	<option value="New Feature">New Feature</option>
	        	<option value="Syntax Error">Syntax Error</option>
	        	<option value="Other">Other</option>
		    </select>
		    	<label>Type</label>
		  	</div>
			
			<!-- ACTION -->
			<div class="input-field col s3 push-s3">
		    <select name="actiontodo">
	        	<option value="Repair">Repair</option>
	        	<option value="Add">Add</option>
	        	<option value="Create">Create</option>
	        	<option value="Modify">Modify</option>
	        	<option value="Correct">Correct</option>
	        	<option value="Remove">Remove</option>
		    </select>
		    	<label>Action to do</label>
		  	</div>
		  	</div>

		  	<!-- DESCRIPTION -->
		     <div class="row">
		       	<div class="input-field col s6 push-s3">
		          	<textarea class="materialize-textarea" name="description">None</textarea>
		          	<label>Description</label>
		       	</div>
		    </div>

		    <!-- LOCATION OF THE BUG -->
			<div class="row">
	        <div class="input-field col s6 push-s3">
	          <input id="location" type="text" class="validate" name="location" value="None">
	          <label for="location"><h5 class="modcon2">Location</h5></label>
	        </div>
	      	</div>
	      	
	      	<!-- SEVERITY  -->
	      	<div class="row col s6">
			<div class="input-field col s3 push-s3">
		    <select name="severity">
	        	<option value="Fatal">Fatal</option>
	        	<option value="Serious">Serious</option>
	        	<option value="Minor">Minor</option>
		    </select>
		    	<label>Severity</label>
		  	</div>
		  	
		  	<!-- PRIORITY  -->
			<div class="input-field col s3 push-s3">
		    <select name="priority">
	        	<option value="Must Do">Must Do</option>
	        	<option value="Low">Low</option>
	        	<option value="Normal">Normal</option>
	        	<option value="High">High</option>
		    </select>
		    	<label>Priority</label>
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

	      	<!-- RESOLUTION -->
			<div class="row s6">
		  	<div class="input-field col s3 push-s3">
		    <select name="resolution">
		        <option value="Deferred">Deferred</option>
		        <option value="Disagree With Suggestion">Disagree With Suggestion</option>
		        <option value="Duplicated">Duplicated</option>
		        <option value="Fixed">Fixed</option>
		        <option value="Hold">Hold</option>
		        <option value="Implemented">Implemented</option>
		        <option value="In Development">In Development</option>
		        <option value="Irreproducible">Irreproducible</option>
		        <option value="Known Problem">Known Problem</option>
	        	<option value="Need More Info">Need More Info</option>
	        	<option value="New">New</option>
	        	<option value="Obsolete">Obsolete</option>
	        	<option value="Reeopen">Reeopen</option>
	        	<option value="Revised">Revised</option>
	        	<option value="Suggestion Not To Correct">Suggestion Not To Correct</option>
	        	<option value="Support Action Required">Support Action Required</option>
	        	<option value="Withdrawn">Withdrawn</option>
		    </select>
		    	<label>Resolution</label>
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
            <div class="col s4">
                <h5 class="white-text">Admins:</h5>
                <p class="white-text">Adrian Michałek (devmichalek@gmail.com)</p>
            </div>
            <div class="col s4">
                <h5 class="white-text">Moderators:</h5>
                <p class="white-text">Sebastian Bialucha (sebastek321@gmail.com)</p>
                <p class="white-text">Kamil Gawlik (kamilgawlik@icloud.com)</p>
            </div>
            <div class="col s4">
                <h5 class="white-text">About:</h5>
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