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


	if($connection->connect_errno == 0)
	{
		$sql = "SELECT * FROM bugs";
		$records = $connection->query($sql);
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
	      		<li><a class="nav" href="../home.php">Home</a></li>
	        	<li><a class="nav" href="addreport.php">Add Report</a></li>
	        	<li><a class="nav" href="modifyreport.php">Modify Report</a></li>
	      	</ul>
	    </div>
  	</nav>
  	</div>
  	<ul class="nav-main sidenav" id="mobile-demo">
	    <li><a class="nav" href="../home.php">Home</a></li>
      	<li><a class="nav" href="addreport.php">Add Report</a></li>
      	<li><a class="nav" href="modifyreport.php">Modify Report</a></li>
	</ul>

	<div class="container center">
		<div class="row">
			<h2 class="center">Combat Halloween Reports</h2>
			<h4 class="modcon">Below is the list of things to repair, modify, add or create. What we called bug is a thing that need to be repair, It is usually memory leak or GUI errors. New feature is like: it would be nice to add this feature to the GUI, It is not necessary but rather sth that would ease users to interact with game or would make more fun while playing, so new files (png, wav etc.), new options inside GUI etc. Syntax Error, this type informs about language mistakes, It can be also a proposal to rename sth. Other Report is just ambigious type of report. Revised means thing is done and has to be checked, fixed means thing has been tested. If you revised report, go to the tab 'Modify report'. This site is private-like you should not share link to others that are not with it.</h4>
			<div class="center col s12">
				<table class="striped centered responsive-table bordered">
			        <thead class="tableheader">
			          <tr>
			          	  <th>Name</th>
			              <th>Type</th>
			              <th>Action to do</th>
			              <th>Description</th>
						  <th>Location</th>
			              <th>Deadline</th>
			              <th>Reported by</th>
			              <th>Developer</th>
			              <th>Status</th>
			          </tr>
			        </thead>
					<tbody class="member">
					
					<?php

						while($row=$records->fetch_assoc())
						{
							echo "<tr>";

							// Bug name
							echo "<td>".$row['name']."</td>";

							// Type
							$type = $row['type'];
							if($type == "Bug")					echo "<td class='red lighten-2'>";
							else if($type == "New feature")		echo "<td class='green lighten-1'>";
							else if($type == "Syntax Error")	echo "<td class='amber lighten-1'>";
							else 								echo "<td class='grey lighten-1'>";
							echo $type."</td>";

							// Action to do
							echo "<td>".$row['action']."</td>";

							// Description (button + form)
							echo "<td><a class='waves-effect waves-light btn modal-trigger' href='#".$row['name']."'>";
							echo "Info</a></td>";
							echo "<div id='".$row['name']."' class='modal'>";
						    echo "<div class='modal-content'>";
						    echo "<h4>".$row['name']."</h4>";
						    echo "<p>".$row['description']."</p>";
						    echo "</div>";
						    echo '<div class="modal-footer">';
						    echo '<a href="#!" class="modal-close waves-effect waves-green btn-flat">Ok</a>';
						    echo "</div>";
						    echo "</div>";

						    // Location - link
							echo "<td><a target='_blank' href='".$row['location']."'>link</a></td>";

							// Deadline
							$deadline = $row['deadline'];
							if($deadline != "Not scheduled")	echo "<td class='red lighten-2'>";
							else 								echo "<td>";
							echo $deadline."</td>";

							// Author of the bug and developer.
							echo "<td>".$row['author']."</td>";
							echo "<td>".$row['developer']."</td>";

							// Status
							$status = $row['status'];
							if($status == "New")					echo "<td class='red lighten-2'>";
							else if($status == "Fixed")				echo "<td class='green lighten-1'>";
							else if($status == "Revised")			echo "<td class='blue  lighten-1'>";
							else if($status == "In development")	echo "<td class='amber lighten-1'>";
							else 									echo "<td class='grey lighten-1'>";
							echo $status."</td>";

							echo "</tr>";
						}

						$records->free_result()
					?>
					</tbody>
			     </table>
			</div>
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
	<script type="text/javascript" src="main.js"></script>
</body>
</html>