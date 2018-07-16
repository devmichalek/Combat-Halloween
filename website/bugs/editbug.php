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
			exit();
		}

		$result->free_result();
	}
	else
	{
		$result->free_result();
		$connection->close();
		header('Location: http://combathalloween.netne.net/home.php');
		exit();
	}


	if($connection->connect_errno == 0)
	{
		$name = $_GET['name'];

		$sql = "SELECT * FROM bugs WHERE name='$name'";
		$records = $connection->query($sql);
		$row=$records->fetch_assoc();

		$type = $row['type'];
		$actiontodo = $row['action'];

		$description = $row['description'];
		$breaks = array("<br />","<br>","<br/>");  
    	$description = str_ireplace($breaks, "", $description); 
		
		$location = $row['location'];
		$severity = $row['severity'];
		$priority = $row['priority'];
		$deadline = $row['deadline'];
		$author = $row['author'];
		$developer = $row['developer'];
		$resolution = $row['resolution'];
	}
	else
	{
		die("Could not connect: ".mysql_error());
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
	<title>Combat Halloween</title>
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
	        	<li><a class="nav btn red lighten-1 nav-button" href="index.php">Back</a></li>
	      	</ul>
	    </div>
  	</nav>
  	</div>
  	<ul class="nav-main sidenav" id="mobile-demo">
      	<li><a class="nav btn red lighten-1 nav-button" href="index.php">Back</a></li>
	</ul>

	<div class="container center">
		
		<!-- Header -->
		<div class="s12"><h2>Combat Halloween Edit Bug</h2></div>
		
		<form class="col s6 push-s3" method="post" action="edit.php" style="margin-bottom: 20px;">

			<!-- NAME -->
			<div class="row">
	        <div class="input-field col s6 push-s3">
	        	<input id="name" type="text" class="validate" name="name" value="<?php echo $name; ?>" selected hidden>
	        	<input id="name" type="text" class="validate" name="name" value="<?php echo $name; ?>" disabled>
	        	<label for="name"><h5 class="modcon2">Name</h5></label>
	        </div>
	      	</div>
			
			<!-- TYPE -->
	      	<div class="row col s6">
			<div class="input-field col s3 push-s3">
		    <select name="type">
		    	<?php
		    		echo "<option "; if($type=="Bug")	echo " selected "; echo 'value="Bug">Bug</option>';
		    		echo "<option "; if($type=="Change")	echo " selected "; echo 'value="Change">Change</option>';
		    		echo "<option "; if($type=="New Feature")	echo " selected "; echo 'value="New Feature">New Feature</option>';
		    		echo "<option "; if($type=="Syntax Error")	echo " selected "; echo 'value="Syntax Error">Syntax Error</option>';
		    		echo "<option "; if($type=="Other")	echo " selected "; echo 'value="Other">Other</option>';
		    	?>
		    </select>
		    	<label>Type</label>
		  	</div>
			
			<!-- ACTION -->
			<div class="input-field col s3 push-s3">
		    <select name="actiontodo">
		    	<?php
		    		echo "<option "; if($type=="Repair")	echo " selected "; echo 'value="Repair">Repair</option>';
		    		echo "<option "; if($type=="Add")	echo " selected "; echo 'value="Add">Add</option>';
		    		echo "<option "; if($type=="Create")	echo " selected "; echo 'value="Create">Create</option>';
		    		echo "<option "; if($type=="Modify")	echo " selected "; echo 'value="Modify">Modify</option>';
		    		echo "<option "; if($type=="Correct")	echo " selected "; echo 'value="Correct">Correct</option>';
		    		echo "<option "; if($type=="Remove")	echo " selected "; echo 'value="Remove">Remove</option>';
		    	?>
		    </select>
		    	<label>Action to do</label>
		  	</div>
		  	</div>

		  	<!-- DESCRIPTION -->
		     <div class="row">
		       	<div class="input-field col s6 push-s3">
		          	<textarea class="materialize-textarea" name="description"><?php echo $description; ?></textarea>
		          	<label>Description</label>
		       	</div>
		    </div>

		    <!-- LOCATION OF THE REPORT -->
			<div class="row">
	        <div class="input-field col s6 push-s3">
	          <input id="location" type="text" class="validate" name="location" value="<?php echo $location; ?>">
	          <label for="location"><h5 class="modcon2">Location</h5></label>
	        </div>
	      	</div>
	      	
	      	<!-- SEVERITY  -->
	      	<div class="row col s6">
			<div class="input-field col s3 push-s3">
		    <select name="severity">
		    	<?php
		    		echo "<option "; if($severity=="Fatal")	echo " selected "; echo 'value="Fatal">Fatal</option>';
		    		echo "<option "; if($severity=="Serious")	echo " selected "; echo 'value="Serious">Serious</option>';
		    		echo "<option "; if($severity=="Minor")	echo " selected "; echo 'value="Minor">Minor</option>';
		    	?>
		    </select>
		    	<label>Severity</label>
		  	</div>
		  	
		  	<!-- PRIORITY  -->
			<div class="input-field col s3 push-s3">
		    <select name="priority">
		    	<?php
		    		echo "<option "; if($priority=="Must Do")	echo " selected "; echo 'value="Must Do">Must Do</option>';
		    		echo "<option "; if($priority=="Low")	echo " selected "; echo 'value="Low">Low</option>';
		    		echo "<option "; if($priority=="Normal")	echo " selected "; echo 'value="Normal">Normal</option>';
		    		echo "<option "; if($priority=="High")	echo " selected "; echo 'value="High">High</option>';
		    	?>
		    </select>
		    	<label>Priority</label>
		  	</div>
            </div>
            
	      	<!-- DEADLINE -->
			<div class="row">
	        <div class="input-field col s6 push-s3">
	        	<input id="deadline" type="text" class="datepicker" name="deadline" value="<?php echo $deadline; ?>">
	          <label for="deadline"><h5 class="modcon2">Deadline</h5></label>
	        </div>
	      	</div>

	      	<!-- AUTHOR -->
			<div class="row">
	        <div class="disabled input-field col s6 push-s3">
	        	<input id="author" type="text" class="validate" name="author" value="<?php echo $author;?>">
	          <label for="author"><h5 class="modcon2">Author</h5></label>
	        </div>
	      	</div>

	      	<!-- RESOLUTION -->
			<div class="row s6">
		  	<div class="input-field col s3 push-s3">
		    <select name="resolution">
		    	<?php
		    		echo "<option "; if($resolution=="Deferred")	echo " selected "; echo 'value="Deferred">Deferred</option>';
		    		echo "<option "; if($resolution=="Disagree With Suggestion")	echo " selected "; echo 'value="Disagree With Suggestion">Disagree With Suggestion</option>';
		    		echo "<option "; if($resolution=="Duplicated")	echo " selected "; echo 'value="Duplicated">Duplicated</option>';
		    		echo "<option "; if($resolution=="Fixed")	echo " selected "; echo 'value="Fixed">Fixed</option>';
		    		echo "<option "; if($resolution=="Hold")	echo " selected "; echo 'value="Hold">Hold</option>';
		    		echo "<option "; if($resolution=="Implemented")	echo " selected "; echo 'value="Implemented">Implemented</option>';
		    		echo "<option "; if($resolution=="In Development")	echo " selected "; echo 'value="In Development">In Development</option>';
		    		echo "<option "; if($resolution=="Irreproducible")	echo " selected "; echo 'value="Irreproducible">Irreproducible</option>';
		    		echo "<option "; if($resolution=="Known Problem")	echo " selected "; echo 'value="Known Problem">Known Problem</option>';
		    		echo "<option "; if($resolution=="Need More Info")	echo " selected "; echo 'value="Need More Info">Need More Info</option>';
		    		echo "<option "; if($resolution=="New")	echo " selected "; echo 'value="New">New</option>';
		    		echo "<option "; if($resolution=="Obsolete")	echo " selected "; echo 'value="Obsolete">Obsolete</option>';
		    		echo "<option "; if($resolution=="Reeopen")	echo " selected "; echo 'value="Reeopen">Reeopen</option>';
		    		echo "<option "; if($resolution=="Revised")	echo " selected "; echo 'value="Revised">Revised</option>';
		    		echo "<option "; if($resolution=="Suggestion Not To Correct")	echo " selected "; echo 'value="Suggestion Not To Correct">Suggestion Not To Correct</option>';
		    		echo "<option "; if($resolution=="Support Action Required")	echo " selected "; echo 'value="Support Action Required">Support Action Required</option>';
		    		echo "<option "; if($resolution=="Withdrawn")	echo " selected "; echo 'value="Withdrawn">Withdrawn</option>';
		    	?>
		    </select>
		    	<label>Resolution</label>
		  	</div>
			
			<!-- DEVELOPER -->
		  	<div class="input-field col s3 push-s3">
		    <select name="developer">
		    	<?php
		    		echo "<option "; if($developer=="devmichalek@gmail.com")	echo " selected "; echo 'value="devmichalek@gmail.com">devmichalek@gmail.com</option>';
		    		echo "<option "; if($developer=="sebastek321@gmail.com")	echo " selected "; echo 'value="sebastek321@gmail.com">sebastek321@gmail.com</option>';
		    		echo "<option "; if($developer=="kamilgawlik@icloud.com")	echo " selected "; echo 'value="kamilgawlik@icloud.com">kamilgawlik@icloud.com</option>';
		    	?>
		    </select>
		    	<label>Choose developer</label>
		  	</div>
		  	</div>

			<!-- BUTTON -->
			<button class="btn waves-effect waves-light red lighten-1 nav-button" type="submit" name="action">Update
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