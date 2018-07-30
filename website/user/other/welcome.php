<?php

	session_start();

	if(!isset($_SESSION['wellregistered']))
	{
		// header('Location: home.php');
		// exit();
	}
	else
	{
		unset($_SESSION['wellregistered']);
	}

	$username = $_SESSION['rem_username'];
	$email = $_SESSION['rem_email'];
	$activation_code = $_SESSION['activation_code'];
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
	$message .= "Thank You for registration, I appreciate that you want to be part of Combat Halloween community. It is really uplifting to have a new player because I know I aroused the interest of another person. Programming gives me the opportunity to see effects of my work, like a moving and fighting foe or the responsive environment. For any advice about the game, about found bug or chatting stuff contact me via devmichalek@gmail.com. Thank you for your support by playing!</p>";
	$message .= '<p style="text-align: center;">Activation link: ';
	$message .= "</a>";
	$message .= 'combathalloween.netne.net/user/other/confirmemail.php?email='.$email.'&code='.$activation_code;
	$message .= "</a>";
	$message .= "</p>";
	$message .= '<p style="text-align: right;">Best Regards, Adrian.</p>';


	$message .= "</body></html>";
	
	mail($email, $subject, $message, $headers);
	
	require_once("../../common/head.php");
?>

	<!-- NAVBAR -->
	<?php require_once("../../common/navbar-b.php"); ?>
        <li><a class='btn blue-grey darken-1 japokki-white' href='../../index.php'>Start</a></li>
    <?php require_once("../../common/navbar-e.php"); ?>
    <?php require_once("../../common/sidebar-b.php"); ?>
        <li><a href="../../index.php" class="japokki-black"><i class="material-icons">stay_primary_portrait</i>Start</a></li>
    <?php require_once("../../common/sidebar-e.php"); ?>
    <!-- END OF NAVBAR-->

	<div class="container center">
		
		<!-- Header -->
		<div class="col s12"><h2 class="japokki-black A22">Check Your Email</h2></div>

		<!-- The rest-->
		<div class="row">
			<h5 class="col s12 japokki-black A7">An email was sent to<div style="color: #EF5350;"><b>
			<?php echo $email.'.</div>'; ?></h5>
		</div>
		<div class="row">
			<h5 class="col s12 japokki-black A7">It has a link to sign you in. Check your spam!</h5>
			<h5>Go to logging <a href="../login/loginform.php">page</a></h5>
		</div>
	</div>

<?php require_once("../../common/footer.php"); ?>