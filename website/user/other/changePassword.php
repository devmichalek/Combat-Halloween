<?php
	
	// Start session.
	session_start();

	// Check if user is logged.
	require_once("../../user/login/isLogged.php");

	// Just in case.
	unset($_SESSION['errorPassword']);

    function backToProfile()
    {
        header('Location: profile.php');
    	exit();
    }

	$success = true;
	$oldpassword =  $_POST['oldpassword'];
	$newpassword =  $_POST['password'];
	$newpasswordcon =  $_POST['passwordcon'];
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
		    	if(!password_verify($oldpassword, $row['password']))
		    	{
		        	$success = false;
		        	$_SESSION['errorPassword'] = "Password is incorrect.";
		    	}
		    }
		}
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
	}

    if((strlen($newpassword)) < 8)
    {
      $success = false;
      $_SESSION['errorPassword'] = "Please choose a password with at least 8 characters.";
    }
    else if((strlen($newpassword)) > 20)
    {
      $success = false;
      $_SESSION['errorPassword'] = "Password may contain at the maximum 20 characters.";
    }
    else if($newpassword != $newpasswordcon)
    {
      $success = false;
      $_SESSION['errorPassword'] = "Passwords do not match.";
    }
    $password_hashed = password_hash($newpassword, PASSWORD_DEFAULT);


	// RECAPTCHA
	$mysecret = "6Lcs3GIUAAAAAG9qpx2wImGLmkhzh_KF2Y0YZrNV";
	$confirm = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$mysecret.'&response='.$_POST['g-recaptcha-response']);
	if(!json_decode($confirm)->success)
	{
		$success = false;
		$_SESSION['errorPassword'] = "Confirm humanity.";
	}

	// REMEMBER DATA
	$_SESSION['rem_oldpassword'] = $oldpassword;
	$_SESSION['rem_password'] = $newpassword;
	$_SESSION['rem_passwordcon'] = $newpasswordcon;

	if(!$success)
	{
		backToProfile();
	}
	else
	{
		if(!$connection->query("UPDATE users SET password='$password_hashed' WHERE email='$email'"))
		{
			throw new Exception($connection->error);
		}
		else
		{
			$_SESSION['successPassword'] = "The password was changed correctly! Log In again to check results.";
			header('Location: profile.php');
			exit();
		}
	}

	$connection->close();
?>