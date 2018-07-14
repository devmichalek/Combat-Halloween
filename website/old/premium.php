<?php
	session_start();

	if(!isset($_SESSION['logged']))
	{
		header('Location: login_form.php');
		exit();
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
	<title>Get Combat Halloween Premium</title>
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

		<!-- Back -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: left; margin-top: 1em;">
				<a class="button primary-button" href="home.php">Back</a>
			</div>
		</div>

		<!-- Header and upgrade section -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 5em;">
				<h3>Get Combat <span class="redspan">Halloween</span> Premium</h3>
			</div>
		</div>
		
		<!-- Paypal -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 2.5em;">
				<h4>1. Donate via PayPal</h4>
			</div>
		</div>
		<!-- Paypal button -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center;">
				<form action="https://www.paypal.com/cgi-bin/webscr" method="post" target="_top">
					<input type="hidden" name="cmd" value="_s-xclick">
					<input type="hidden" name="hosted_button_id" value="BH2D9U7ACBGBN">
					<input type="image" src="https://www.paypalobjects.com/en_US/PL/i/btn/btn_donateCC_LG.gif" border="0" name="submit" alt="PayPal - The safer, easier way to pay online!">
					<img border="0" src="https://www.paypalobjects.com/pl_PL/i/scr/pixel.gif">
				</form>
			</div>
		</div>

		<!-- Bank -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 2.5em;">
				<h4>2. Bank Account - Getin Bank</h4>
				<h5>89 1560 0013 2002 1141 4000 0001</h5>
			</div>
		</div>

		<!-- Free -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 2.5em;">
				<h4>3. Free</h4>
				<h5>Nobody likes to pay, anyway thanks for support by playing!</h5>
				<a class="button primary-button" href="givepremium.php" style="background-color: gold;">Get Premium</a>
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