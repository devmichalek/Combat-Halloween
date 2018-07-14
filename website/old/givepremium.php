<?php
	session_start();

	if(!isset($_SESSION['logged']))
	{
		header('Location: login_form.php');
		exit();
	}

	if( $_SESSION['premium'] == 0 )
	{
		$_SESSION['premium'] = 1;
	}
	else if( $_SESSION['premium'] == 1 )
	{
		$_SESSION['premium'] = 2;
	}


	// Connect.
	require_once "connect.php";
	mysqli_report(MYSQLI_REPORT_STRICT);
	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno != 0)
		{
			throw new Exception(mysqli_connect_errno());
		}
		else
		{

			$premium_now = $_SESSION['premium'];
			$username_now = $_SESSION['username'];

			$connection->query("UPDATE users SET premium='$premium_now' WHERE username='$username_now'");

			$connection->close();
		}
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
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">

	<!-- Site Properties -->
	<title>Premium Status</title>
	<link rel="stylesheet" href="skeleton.css">
	<link rel="stylesheet" href="normalize.css">
	<link rel="stylesheet" href="main.css">
	<link rel="shortcut icon" href="images/icon.png">

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

</head>
<body>
	<div class="container">
		<!-- Header and upgrade section -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 5em;">
				<?php
					// First time.
					if( $_SESSION['premium'] == 1 )
					{
						echo '<h3>Congratulations <span class="redspan">';
						echo $_SESSION['username'];
						echo "</span>! You've got premium account!</h3>";
					}
					else
					{
						echo '<h3>Heeeeyaa <span class="redspan">';
						echo $_SESSION['username'];
						echo "</span>! You've already got premium account! Go away!</h3>";
					}
				?>
			</div>
		</div>
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center;">
				<a class="button" href="home.php">Back to home site</a>
			</div>
		</div>


		<!-- Footer -->
		<div class="twelve columns" style="text-align: center; margin-top: 10em;">
			<footer>
				<h6 class="myfont nobotmargin notopmargin">
					<span style="display: inline-block;">&nbsp;&nbsp;&nbsp;Visit my github: <a href="https://github.com/Adriqun" style="color: #444444;">Adrian Michalek</a>&nbsp;&nbsp;&nbsp;</span>
					<span style="display: inline-block;">Back to <a href="home.php" style="color: #444444;">main site</a></span>
				</h6>
				<h6 class="myfont nobotmargin notopmargin">
					Contact me: adrmic98@gmail.com or contact@adrianmichalek.pl
				</h6>
			</footer>
		</div>

	</div>
</body>
</html>