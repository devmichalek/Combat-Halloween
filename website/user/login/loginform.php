<?php
	// Start session.
	session_start();
	
	// Reset errors.
	unset($_SESSION['e_username']);
	unset($_SESSION['e_email']);
	unset($_SESSION['e_password']);
	unset($_SESSION['e_passwordcon']);
	unset($_SESSION['e_bot']);

	if(isset($_SESSION['logged']))
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
	

	<div class="container center">

	<!-- Header -->
	<div class="col s12"><section><div><h2 class="japokki-black A22">Account - Log In</h2></div></section></div>

		<form action="login.php" method="post" class="japokki-black">

		<div class="row"><div class="input-field col s12 m6 push-m3">
			<input id="username" type="text" class="validate" name="username" value="<?php
			if(isset($_SESSION['rem_username']))
			{
				echo $_SESSION['rem_username'];
				unset($_SESSION['rem_username']);
			}?>">
			<label for="username"><h5 class="A2">Username</h5></label>
		</div></div>

		<div class="row"><div class="input-field col s12 m6 push-m3">
			<input id="password" type="password" class="validate" name="password" value="<?php
			if(isset($_SESSION['rem_password']))
			{
				echo $_SESSION['rem_password'];
				unset($_SESSION['rem_password']);
			}?>">
			<label for="password"><h5 class="A2">Password</h5></label>
		</div></div>
		
		<div class="row"><div class="col s12 m6 push-m3" style="margin-bottom: 10px;">
		<div class="g-recaptcha" data-sitekey="6Lf9NWgUAAAAAOLFVsbFykwsfSLCnZAE6TQi584V"></div>
		</div></div>

		<div class="row"><div class="col s12">
		<button class="btn waves-effect waves-light japokki-white blue-grey darken-1" type="submit" name="action">Log In
		<i class="material-icons right">send</i>
		</button></div></div>

		<?php
		echo '<h5 class="errorColor">';
		if(isset($_SESSION['error']) )
		{
			echo $_SESSION['error'];
			unset($_SESSION['error']);
		}
		echo '</h5>';
		?>
	</form>
	</div>

<?php require_once("../../common/footer.php"); ?>