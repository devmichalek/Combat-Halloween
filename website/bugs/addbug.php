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



<?php require_once("../head.php"); ?>

	<nav><div class="nav-wrapper">
    	<div class="row">
      		<a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
      		<a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
	      	<ul id="nav-mobile" class="right hide-on-med-and-down">
	      		<li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
	        	<li><a class="nav btn red lighten-1 nav-button" href="index.php">Back</a></li>
	      	</ul>
      	</div>
	</div></nav>
  	<ul class="nav-main sidenav" id="mobile-demo">
	    <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
      	<li><a class="nav btn red lighten-1 nav-button" href="index.php">Back</a></li>
	</ul>

	<div class="container center">
		
		<!-- Header -->
		<div class="s12"><h2>Combat Halloween Add Bug</h2></div>
		
		<!-- FORM -->
		<form class="col s12 m6 push-m3" method="post" action="add.php" style="margin-bottom: 20px;">

			<!-- NAME -->
			<div class="row">
			<div class="input-field col s12 m6 push-m3">
	          	<input id="name" type="text" class="validate" name="name" value="None" >
	            <label for="name"><h5 class="modcon2">Name</h5></label>
	        </div>
	    	</div>
			
			<!-- TYPE, ACTION -->
	      	<div class="row">
				<div class="input-field col s6 m3 push-m3">
			    <select name="type">
		        	<option value="Bug">Bug</option>
		        	<option value="Change">Change</option>
		        	<option value="New Feature">New Feature</option>
		        	<option value="Syntax Error">Syntax Error</option>
		        	<option value="Other">Other</option>
			    </select>
					<label>Type</label>
			  	</div>
				<div class="input-field col s6 m3 push-m3">
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
		     <div class="row"><div class="input-field col s12 m6 push-m3">
		    	<textarea class="materialize-textarea" name="description">None</textarea>
		        <label>Description</label>
		    </div></div>

		    <!-- LOCATION OF THE BUG -->
			<div class="row"><div class="input-field col s12 m6 push-m3">
	        	<input id="location" type="text" class="validate" name="location" value="None">
	        	<label for="location"><h5 class="modcon2">Location</h5></label>
	        </div></div>
	      	
	      	<!-- SEVERITY, PRIORITY -->
	      	<div class="row">
			<div class="input-field col s6 m3 push-m3">
		    <select name="severity">
	        	<option value="Fatal">Fatal</option>
	        	<option value="Serious">Serious</option>
	        	<option value="Minor">Minor</option>
		    </select>
		    	<label>Severity</label>
		  	</div>
			<div class="input-field col s6 m3 push-m3">
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
			<div class="row"><div class="input-field col s12 m6 push-m3">
	        	<input id="deadline" type="text" class="datepicker" name="deadline" value="Not scheduled">
	          <label for="deadline"><h5 class="modcon2">Deadline</h5></label>
	        </div></div>

	      	<!-- AUTHOR -->
			<div class="row"><div class="disabled input-field col s12 m6 push-m3">
	        	<input id="author" type="text" class="validate" name="author" value="<?php echo $_SESSION['email'];?>">
	        	<label for="author"><h5 class="modcon2">Author</h5></label>
	        </div></div>

	      	<!-- RESOLUTION, DEVELOPER -->
			<div class="row">
		  	<div class="input-field col s6 m3 push-m3">
		    <select name="resolution">
		        <option value="Deferred">Deferred</option>
		        <option value="Disagree">Disagree</option>
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
	        	<option value="Not To Correct">Not To Correct</option>
	        	<option value="Support Needed">Support Needed</option>
	        	<option value="Withdrawn">Withdrawn</option>
		    </select>
		    	<label>Resolution</label>
		  	</div>
		  	<div class="input-field col s6 m3 push-m3">
		    <select name="developer">
	        	<option value="devmichalek@gmail.com">devmichalek@gmail.com</option>
	        	<option value="sebastek321@gmail.com">sebastek321@gmail.com</option>
	        	<option value="kamilgawlik@icloud.com">kamilgawlik@icloud.com</option>
		    </select>
		    	<label>Choose developer</label>
		  	</div>
		  	</div>

			<!-- BUTTON -->
			<a href="http://combathalloween.netne.net/bugs" class="waves-effect waves-light btn red lighten-1"><i class="material-icons right">clear</i>Cancel </a>
			<button class="btn waves-effect waves-light green lighten-1 nav-button" type="submit" name="action">Add
		    <i class="material-icons right">send</i>
			</button>
			
		</form>
	</div>

<?php require_once("../footer.php"); ?>