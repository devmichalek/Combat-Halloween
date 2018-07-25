<?php
	
	session_start();

	$confirmedemail = false;

	if(isset($_GET['email']) && isset($_GET['code']))
	{
    	// Connect.
		require_once("../../connect.php");
		mysqli_report(MYSQLI_REPORT_STRICT);

		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno == 0)
		{
			$email = $_GET['email'];
			$code = $_GET['code'];
			unset($_GET['email']);
			unset($_GET['code']);

			$email = htmlentities($email, ENT_QUOTES, "UTF-8");
			if($result = @$connection->query(sprintf("SELECT * FROM users WHERE email='%s'", mysqli_real_escape_string($connection, $email))))
			{
				$how_many = $result->num_rows;
				if($how_many > 0)
				{
					$row = $result->fetch_assoc();
					if($row['activationcode'] == $code && $row['activated'] == 0)
					{
						$result->free_result();
						$connection->query("UPDATE users SET activated='1' WHERE email='$email'");
						$confirmedemail = true;
					}
					else
				  	{
				  		header('Location: ../../home.php');
				  	}
				}
			}

			$connection->close();
		}
  	}
  	else
  	{
  		header('Location: ../../home.php');
  		exit();
  	}

	if(!$confirmedemail)
	{
		header('Location: ../../home.php');
		exit();
	}

	require_once("../../common/head.php");
?>

	<!-- NAVBAR -->
	<div class="navbar-fixed">
    <nav><div class="nav-wrapper">
        <div class="row">
            <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
            <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
            <ul id="nav-mobile" class="right hide-on-med-and-down">
                <li><a class='btn nav-button red lighten-1' href='../../index.php'>Start</a></li>
                <li><a class='btn nav-button' href='../register/registerform.php'>Sign In</a></li>
            </ul>
        </div>
    </div></nav>
    </div>
    <ul class="nav-main sidenav" id="mobile-demo">
        <li><a class='btn nav-button red lighten-1' href='../../index.php'>Start</a></li>
        <li><a class='btn nav-button' href='../register/registerform.php'>Sign In</a></li>
    </ul>
    <!-- END OF NAVBAR-->

	<div class="container center">
		<!-- Header -->
		<div class="col s12"><h2 class="modcon2">Congratulations!</h2></div>

		<!-- The rest-->
		<div class="col s12">
			<h5 class="modcon2">Now you're a part of our society!</h5>
			<h5 class="modcon2">Go to logging <a href="../login/loginform.php">page</a></h5>
		</div>
	</div>

<?php require_once("../../common/footer.php"); ?>