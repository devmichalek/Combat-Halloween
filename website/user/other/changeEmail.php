<?php
	
	// Start session.
	session_start();

	// Check if user is logged.
	require_once("../../user/login/isLogged.php");

	// Just in case.
	unset($_SESSION['errorEmail']);

	require_once("generateCode.php");

	function backToProfile()
	{
		header('Location: profile.php');
		exit();
	}

	$success = true;
	$newemail = $_POST['email'];
	$password =	$_POST['password'];
	$email = $_SESSION['email'];

	// Get current password from database.
	require_once ("../../connect.php");
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
			if($result = @$connection->query(sprintf("SELECT * FROM users WHERE email='%s'", mysqli_real_escape_string($connection, $email))))
			{
				$row = $result->fetch_assoc();
				if(!password_verify($password, $row['password']))
				{
					$success = false;
					$_SESSION['errorEmail'] = "Password is incorrect. ";
				}
			}
		}
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
	}

	// Check if this email is not occupied.
	try
	{
		$result = @$connection->query(sprintf("SELECT ID FROM users WHERE email='%s'", mysqli_real_escape_string($connection, $newemail)));
		if(!$result)
		{
			throw new Exception($connection->error);
		}

		$how_many_emails = $result->num_rows;

		if($how_many_emails > 0)
		{
			$success = false;
			$_SESSION['errorEmail'] = "This email already exists.";
		}
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
	}

	$email_safe = filter_var($newemail, FILTER_SANITIZE_EMAIL);
	if(!filter_var($email_safe, FILTER_VALIDATE_EMAIL) || $email_safe != $newemail)
	{
		$success = false;
		$_SESSION['errorEmail'] = "Valid address email required.";
	}


	// RECAPTCHA
	$mysecret = "6Lf9NWgUAAAAAAe-lNJAcxTOubIdu_KUe-cSMwTU";
	$confirm = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$mysecret.'&response='.$_POST['g-recaptcha-response']);
	if(!json_decode($confirm)->success)
	{
		$success = false;
		$_SESSION['errorEmail'] = "Confirm humanity.";
	}

	// REMEMBER DATA
	$_SESSION['rem_email'] = $newemail;
	$_SESSION['rem_passwordEmail'] = $password;

	if(!$success)
	{
		backToProfile();
	}
	else
	{
		$activationcode = generateCode();
		$activationcode =	mysqli_real_escape_string($connection, $activationcode);
		$email =			mysqli_real_escape_string($connection, $email);
		$sql_query = "UPDATE users SET activationcode='$activationcode' WHERE email='$email'";
		$connection->query($sql_query);
		
		// Send email
		$subject = 'Combat Halloween - New Email';

		$headers = "From: devmichalek@gmail.com"."\r\n";
		$headers .= "MIME-Version: 1.0\r\n";
		$headers .= "Content-Type: text/html; charset=ISO-8859-1\r\n";

		$message = '<html><body><h3 style="text-align: center;">';
		$message .= 'Dear '.$_SESSION['username'].',</h3><p style="text-align: center;">';
		$message .= "If this email reached your mailbox without your interference contact me: devmichalek@gmail.com. If you want to change the email you have to confirm it by clicking on the link below.</p>";
		$message .= '<p style="text-align: center;">Activation link: ';
		$message .= "</a>";
		$message .= 'amichalek.pl/combathalloween/user/other/confirmnewemail.php?email='.$email.'&code='.$activationcode.'&newemail='.$newemail;
		$message .= "</a>";
		$message .= "</p>";
		$message .= '<p style="text-align: right;">Best Regards, Adrian.</p>';


		$message .= "</body></html>";
		
		mail($email, $subject, $message, $headers);
		


		$_SESSION['successEmail'] = "The activation link was send to ".$email;
		header('Location: profile.php');
		exit();
	}

	$connection->close();
?>