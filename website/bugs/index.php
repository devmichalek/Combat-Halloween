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
		$sql = "SELECT * FROM bugs";
		$records = $connection->query($sql);

		$donenum = 0;
		$opennum = 0;
		$sumnum = 0;
		while($row=$records->fetch_assoc())
		{
			++$sumnum;
			if($row['resolution'] == "Fixed" ||
			   $row['resolution'] == "Implemented" ||
			   $row['resolution'] == "Revised")
				++$donenum;
			else
				++$opennum;
		}
		mysqli_data_seek($records, 0);
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
	<link rel="stylesheet" type="text/css" href="../main.css">
	<link rel="icon" href="https://user-images.githubusercontent.com/19840443/42683508-c8c24644-868d-11e8-9a8a-cbde02588774.png">
	<link rel = "stylesheet" href = "https://fonts.googleapis.com/icon?family=Material+Icons">
	
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
	      	
	      	<ul id="nav-mobile" class="right hide-on-med-and-down">
	      		<li><a class="nav" href="../home.php">Home</a></li>
	        	<li><a class="nav btn red lighten-1 nav-button" href="addbug.php">Add</a></li>
	      	</ul>
	    </div>
  	</nav>
  	</div>
  	<ul class="nav-main sidenav" id="mobile-demo">
	    <li><a class="nav" href="../home.php">Home</a></li>
      	<li><a class="nav btn red lighten-1 nav-button" href="addbug.php">Add</a></li>
	</ul>

	<div class="container center">
		<div class="row">
			<h2 class="center">Combat Halloween Bugs</h2>
			<h4 class="modcon">The list of things to repair, modify, add, create or remove is below. What we called bug is a thing that need to be repair, It is usually memory leak or GUI errors. New feature is like: it would be nice to add this feature to the GUI, It is not necessary but rather sth that would ease users to interact with game or would make more fun while playing, so new files (png, wav etc.), new options inside GUI etc. Syntax Error, this type informs about language mistakes, It can be also a proposal to rename sth. If the info button is red that means it is your task.</h4>
			<h4 class="modcon">Done: <?php echo $donenum;?> Open: <?php echo $opennum;?> All: <?php echo $sumnum;?></h4>
			<div class="center col s12">
				<table class="striped centered responsive-table bordered">
			        <thead class="tableheader">
			          <tr>
			          	  <th>Name</th>
			              <th>Type</th>
			              <th>Description</th>
						  <th>Location</th>
						  <th>Severity</th>
						  <th>Priority</th>
			              <th>Deadline</th>
			              <th>Resolution</th>
			          </tr>
			        </thead>
					<tbody class="member">
					
					<?php

						while($row=$records->fetch_assoc())
						{
							echo "<tr>";
							
							// Color
							$color = "''";
							$resolution = $row['resolution'];
							if($resolution == "Fixed" ||
							   $resolution == "Revised" ||
							   $resolution == "Implemented")
							$color = "'grey lighten-2'";

							// Name
							echo "<td class=".$color.">";
							echo '<form action="editbug.php" method="get">';
							echo $row['name'];
							echo '<input type="hidden" name="name" value="';
							echo $row['name'].'"> ';
							$descolor = ltrim($color, "'");
							if($descolor == "")
							    $descolor = "amber lighten-1'";
							echo "<button type='submit' class='btn ".$descolor.">Edit</button>";
							echo '</form>'."</td>";

							// Type
							$type = $row['type'];
							if($color == "''")
							{
							    switch($type)
							    {
							        case "Bug":             echo "<td class='red lighten-1'>".$type."</td>";   break;
							        case "Change":          echo "<td class='amber lighten-1'>".$type."</td>"; break;
							        case "New Feature":     echo "<td class='green lighten-1'>".$type."</td>"; break;
							        case "Syntax Error":    echo "<td class='red lighten-1'>".$type."</td>";   break;
							        default:                echo "<td class='grey lighten-1'>".$type."</td>";  break;
							    }
							}
							else
							    echo "<td class=".$color.">".$type."</td>";

							// Description (button + form)
							echo "<td class=".$color.">";
							$descolor = ltrim($color, "'");
							
							if($descolor == "")
							{
							    $descolor = "'";
							    if($row['developer'] == $_SESSION['email'])
							        $descolor = "red lighten-1'";
							    
							}
							
							echo "<a class='waves-effect waves-light btn modal-trigger ".$descolor." ";
							echo "href='#".$row['name']."'>";
							echo "Info</a></td>";
							echo "<div id='".$row['name']."' class='modal'>";
						    echo "<div class='modal-content'>";
						    echo "<h4 class='modcon'>".$row['name']."</h4>";
						    echo "<p class='japokki'>Reported by: ".$row['author']."</p>";
						    echo "<p class='japokki'>Developer: ".$row['developer']."</p>";
						    echo "<p class='japokki'>Action to do: ".$row['action']."</p>";
						    echo "<p class='japokki'>".$row['description']."</p>";
						    echo "</div>";
						    echo '<div class="modal-footer">';
						    echo '<a href="#!" class="modal-close waves-effect waves-green btn-flat japokki">Ok</a>';
						    echo "</div>";
						    echo "</div>";

						    // Location - link
						    $location = $row['location'];
						    echo "<td class=".$color.">";
						    if($location == "None")
							    echo "None</td>";
						    else
						        echo "<a target='_blank' href='".$location."'>Link</a></td>";
							
							// Severity
							$severity = $row['severity'];
							if($color == "''")
    							switch($severity)
    							{
    							    case "Fatal":   echo "<td class='deep-purple'>";    break;
    							    case "Serious": echo "<td class='red lighten-1'>";  break;
    							    default:        echo "<td class='grey lighten-1'>"; break;
    							}
							else
							    echo "<td class=".$color.">";
							echo $severity."</td>";
							
							// Priority
							$priority = $row['priority'];
							if($color == "''")
    							switch($priority)
    							{
    							    case "Must Do":   echo "<td class='deep-purple'>";    break;
    							    case "Medium": echo "<td class='orange lighten-1'>";  break;
    							    case "High": echo "<td class='red lighten-1'>";  break;
    							    default:        echo "<td class='grey lighten-1'>"; break;
    							}
    						else
    						    echo "<td class=".$color.">";
							echo $priority."</td>";

							// Deadline
							$deadline = $row['deadline'];
							if($color == "''")
							{
							    if($deadline != "Not scheduled")	echo "<td class='red lighten-1'>";
							    else 								echo "<td class='grey lighten-1'>";
							}
							else
							    echo "<td class=".$color.">";
							echo $deadline."</td>";

							// Resolution
							switch($resolution)
							{
							    case "Deferred":                    echo "<td class='red lighten-1'>";          break;
							    case "Disagree With Suggestion":    echo "<td class='deep-orange lighten-1'>";  break;
							    case "Duplicated":                  echo "<td class='red lighten-1'>";          break;
							    case "Fixed":                       echo "<td class='green lighten-1'>";        break;
							    case "Hold":                        echo "<td class='red lighten-1'>";          break;
							    case "Implemented":                 echo "<td class='green lighten-1'>";        break;
							    case "In Development":              echo "<td class='amber lighten-1'>";        break;
							    case "Known Problem":               echo "<td class='amber lighten-1'>";        break;
							    case "Need More Info":              echo "<td class='purple lighten-1'>";       break;
							    case "New":                         echo "<td class='red lighten-1'>";          break;
							    case "Obsolete":                    echo "<td class='brown lighten-1'>";        break;
							    case "Reeopen":                     echo "<td class='red lighten-1'>";          break;
							    case "Revised":                     echo "<td class='blue lighten-1'>";         break;
							    case "Suggestion Not To Correct":   echo "<td class='deep-orange lighten-1'>";  break;
							    case "Support Action Required":     echo "<td class='purple lighten-1'>";       break;
							    case "Withdrawn":                   echo "<td class='green lighten-1'>";        break;
							    default:                            echo "<td class='grey lighten-1'>";         break;
							}
							echo $resolution."</td>";
                            
                            // End
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