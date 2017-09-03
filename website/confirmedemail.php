<?php

	session_start();

	if(!isset($_SESSION['confirmedemail']))
	{
		header('Location: home.php');
		exit();
	}
	else
	{
		unset($_SESSION['confirmedemail']);
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
	<title>Confirmed Email - Combat Halloween</title>
	<link rel="stylesheet" href="skeleton.css">
	<link rel="stylesheet" href="normalize.css">
	<link rel="stylesheet" href="main.css">
	<link rel="shortcut icon" href="images/icon.png">
</head>
<body>
	<div class="container">
		
		<!-- Header -->
		<div class="twelve columns">
			<section class="header" style="text-align: center; margin-top: 6em;">
				<div class="title myfont">
					<h2>Congratulations!</h2>
				</div>
			</section>
		</div>

		<!-- The rest-->
		<div class="twelve columns myfont" style="text-align: center;">
			<h5 class="nobotmargin">Now you're a part of our society!</h5>
			<h5 class="notopmargin">Go to logging <a href="login_form.php">page</a></h5>
		</div>
	</div>
</body>
</html>