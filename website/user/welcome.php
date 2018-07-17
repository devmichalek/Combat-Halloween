<?php

	session_start();

	if(!isset($_SESSION['wellregistered']))
	{
		header('Location: home.php');
		exit();
	}
	else
	{
		unset($_SESSION['wellregistered']);
	}

	$username = $_SESSION['temporaryusername'];
	$email = $_SESSION['temporaryemail'];
	$activation_code = $_SESSION['activation_code'];
	unset($_SESSION['temporaryusername']);
	unset($_SESSION['temporaryemail']);
	unset($_SESSION['activation_code']);

	// DELETE TEMPORARY DATA
	if(isset($_SESSION['rem_username'])) 	unset($_SESSION['rem_username']);
	if(isset($_SESSION['rem_email'])) 		unset($_SESSION['rem_email']);
	if(isset($_SESSION['rem_password'])) 	unset($_SESSION['rem_password']);
	if(isset($_SESSION['rem_passwordcon'])) unset($_SESSION['rem_passwordcon']);

	// DELETE ERROR DATA
	if(isset($_SESSION['e_username'])) 		unset($_SESSION['e_username']);
	if(isset($_SESSION['e_email'])) 		unset($_SESSION['e_email']);
	if(isset($_SESSION['e_password'])) 		unset($_SESSION['e_password']);
	if(isset($_SESSION['e_passwordcon'])) 	unset($_SESSION['e_passwordcon']);
	if(isset($_SESSION['e_bot'])) 			unset($_SESSION['e_bot']);

	

	// Send email
	$subject = 'Combat Halloween - Confirm Email';

	$headers = "From: devmichalek@gmail.com"."\r\n";
	$headers .= "MIME-Version: 1.0\r\n";
	$headers .= "Content-Type: text/html; charset=ISO-8859-1\r\n";

	$message = '<html><body><h3 style="text-align: center;">';
	$message .= 'Dear '.$username.',</h3><p style="text-align: center;">';
	$message .= "Thank You for registration, I appreciate that you want to be part of Combat Halloween community. It is really uplifting to have a new player because I know I aroused interest of another person. Programming gives me the opportunity to see effects of my work, like a moving and fighting foe or responsive environment. For any advice about game, about found bug or chating stuff contact me via devmichalek@gmail.com. Thank you for your support by playing!</p>";
	$message .= '<p style="text-align: center;">Activation link: ';
	$message .= "</a>";
	$message .= 'combathalloween.netne.net/confirmemail.php?email='.$email.'&code='.$activation_code;
	$message .= "</a>";
	$message .= "</p>";
	$message .= '<p style="text-align: right;">Best Regards, Adrian.</p>';


	$message .= "</body></html>";
	
	mail($email, $subject, $message, $headers);
?>

<!DOCTYPE html>
<html lang="en">
<head>
	<!-- Standard Meta -->
	<meta charset="UTF-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">

	<!-- Site Properties -->
	<title>Welcome - Combat Halloween</title>
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
					<h2>Check Your Email</h2>
				</div>
			</section>
		</div>

		<!-- The rest-->
		<div class="twelve columns myfont" style="text-align: center;">
			<h5 class="nobotmargin">
			<?php
				echo 'An email was sent to ';
				echo '<span style="color: #F2583E; margin-right: 0em; margin-left: 0em;"><b>';
				echo $email;
				echo '</b></span>';
				echo '.';
			?>
			</h5>
			<h5 class="notopmargin nobotmargin">It has a link to sign you in. Check your spam!</h5>
			<h5 class="notopmargin">Go to logging <a href="login_form.php">page</a></h5>
		</div>
	</div>
</body>
</html>