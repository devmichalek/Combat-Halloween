<?php
	session_start();

	unset($_SESSION['e_username']);
	unset($_SESSION['e_mail']);
	unset($_SESSION['e_password']);
	unset($_SESSION['e_passwordcon']);
	unset($_SESSION['e_bot']);

	if(isset($_SESSION['logged']))
	{
		header('Location: home.php');
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
	<title>Logging - Combat Halloween</title>
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
					<h2>You are logging into Combat <span style="color: #F2583E; margin-right: 0em; margin-left: 0em; display: inline-block;">Halloween</span></h2>
				</div>
			</section>
		</div>

		<form action="login.php" method="post">
			<div class="row myfont">
			    <div class="offset-by-three six columns">
			      <label for="exampleEmailInput" style="text-align: center; margin-top: 3em;">Your username</label>
			      <input class="u-full-width" type="text" placeholder="username" id="exampleEmailInput" name="username">
			    </div>
			    <div class="offset-by-three six columns">
			      <label for="exampleEmailInput" style="text-align: center; margin-top: 1em;">Your password</label>
			      <input class="u-full-width" type="password" placeholder="password" id="exampleEmailInput" name="password">
			    </div>
		  	</div>
			
			<div style="text-align: center; margin-top: 1em;">
				<input class="button-primary myfont" type="submit" value="Login">
			</div>
		</form>

		<?php
			echo '<div class="twelve columns myfont" style="text-align: center; color: red;">';
			if(isset($_SESSION['error']) )
			{
				echo $_SESSION['error'];
				unset($_SESSION['error']);
			}
			echo '</div>';
		?>
		
		<!-- Footer -->
		<div class="twelve columns" style="text-align: center; margin-top: 3em;">
			<footer>
				<h6 class="myfont nobotmargin notopmargin">
					<span style="display: inline-block;">&nbsp;&nbsp;&nbsp;Back to <a href="index.php" style="color: #444444;">main site</a>&nbsp;&nbsp;&nbsp;</span>
					<span style="display: inline-block;">New to us? <a href="registration_form.php" style="color: #444444;">Sign Up</a></span>
				</h6>
			</footer>
		</div>

	</div>
</body>
</html>