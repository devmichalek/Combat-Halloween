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
						@$connection->query(sprintf("UPDATE users SET activated='1' WHERE email='$s'", mysqli_real_escape_string($connection, $email)))
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
	<?php require_once("../../common/navbar-b.php"); ?>
				<li><a class='nav japokki-white A3' href='../../index.php'>Start</a></li>
				<li><a class='btn blue-grey darken-1 japokki-white' href='../register/registerform.php'>Sign Up</a></li>
	<?php require_once("../../common/navbar-e.php"); ?>
	<?php require_once("../../common/sidenav-b.php"); ?>
		<li><a href="../../index.php" class="japokki-black"><i class="material-icons">stay_primary_portrait</i>Start</a></li>
		<li><a class='btn blue-grey darken-1 japokki-white' href='../register/registerform.php'>Sign Up</a></li>
	<?php require_once("../../common/sidenav-e.php"); ?>
	<!-- END OF NAVBAR-->

	<div class="container center japokki-black">
		<!-- Header -->
		<div class="col s12"><h2 class="A22">Congratulations!</h2></div>

		<!-- The rest-->
		<div class="col s12">
			<h5 class="A22">Now you're a part of our society!</h5>
			<h5 class="A22">Go to logging <a href="../login/loginform.php">page</a></h5>
		</div>
	</div>

<?php require_once("../../common/footer.php"); ?>