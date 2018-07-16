<?php
	session_start();
	if(!isset($_SESSION['logged']))
	{
		header('Location: user/loginform.php');
		exit();
	}

	require_once "connect.php";
	mysqli_report(MYSQLI_REPORT_STRICT);
	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);

		/*if($connection->connect_errno != 0)
		{
			throw new Exception(mysqli_connect_errno());
		}
		else if($result = @$connection->query( sprintf("SELECT * FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $_SESSION['username']))))
		{
			$row = $result->fetch_assoc();
			$_SESSION['money'] = $row['money'];
			$_SESSION['diamonds'] = $row['diamonds'];
			$_SESSION['helmet'] = $row['helmet'];
			$_SESSION['body'] = $row['body'];
			$_SESSION['shield'] = $row['shield'];
			$_SESSION['sword'] = $row['sword'];
			$_SESSION['boots'] = $row['boots'];
			$result->free_result();
		}*/

		$connection->close();
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
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
	<title>Home - Combat Halloween</title>
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0-rc.2/css/materialize.min.css">
  	<link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
	<link rel="stylesheet" type="text/css" href="main.css">
	<link rel="icon" href="https://user-images.githubusercontent.com/19840443/42683508-c8c24644-868d-11e8-9a8a-cbde02588774.png">

	<meta http-equiv="cache-control" content="max-age=0" />
    <meta http-equiv="cache-control" content="no-cache" />
    <meta http-equiv="cache-control" content="no-store" />
    <meta http-equiv="cache-control" content="must-revalidate" />
    <meta http-equiv="expires" content="0" />
    <meta http-equiv="expires" content="Tue, 01 Jan 1980 1:00:00 GMT" />
    <meta http-equiv="pragma" content="no-cache" />
<!--
	<style>
		body
		{
			<?php
				if( $_SESSION['premium'] > 0 )
				{
					echo 'background-image: url("images/premiumbg.png") !important;';
					echo 'background-size: 20px 108px;';
					echo 'background-repeat: repeat-y !important;';
				}
			?>
		}
	</style>
-->
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
			      	<li><a class='nav' href='../index.php'>Start</a></li>
			      	<li><a class='dropdown-trigger btn nav-button' href='bugs/index.php'>Bugs</a></li>
			      	<li><a class='dropdown-trigger btn nav-button' href='user/logout.php'>Log Out</a></li>
		    	</ul>
		    </div>
		</nav>
		
	</div>
	<ul class="nav-main sidenav" id="mobile-demo">
        <li><a class='nav' href='../index.php'>Start</a></li>
      	<li><a class='dropdown-trigger btn nav-button' href='bugs/index.php'>Bugs</a></li>
		<li><a class='dropdown-trigger btn nav-button' href='user/logout.php'>Log Out</a></li>
	</ul>
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