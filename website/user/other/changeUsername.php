<?php
	
	// Start session.
	session_start();

	// Check if user is logged.
	require_once("../../user/login/isLogged.php");

	// Just in case.
	unset($_SESSION['errorUsername']);

    function backToProfile()
    {
        header('Location: profile.php');
    	exit();
    }

	$success = true;
	$username = $_POST['username'];
	$password =  $_POST['password'];
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
		        	$_SESSION['errorUsername'] = "Password is incorrect. ";
		    	}
		    }
		}
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
	}

	// Check if this username is not occupied.
	try
	{
		$result = $connection->query("SELECT ID FROM users WHERE username='$username'");
		if(!$result)
		{
		    throw new Exception($connection->error);
		}

		$how_many_usernames = $result->num_rows;

		if($how_many_usernames > 0)
		{
		    $success = false;
		    $_SESSION['errorUsername'] = "This username already exists.";
		}
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
	}

	if((strlen($username)) < 4)
	{
		$success = false;
		$_SESSION['errorUsername'] = "Please choose a name with at least 4 characters.";
	}
	else if((strlen($username)) > 12)
	{
		$success = false;
		$_SESSION['errorUsername'] = "Maximum number of characters is 12.";
	}
	else if(!ctype_alnum($username))
	{
		$success = false;
		$_SESSION['errorUsername'] = "This name is unavailable.";
	}


	// RECAPTCHA
	$mysecret = "6Lcs3GIUAAAAAG9qpx2wImGLmkhzh_KF2Y0YZrNV";
	$confirm = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$mysecret.'&response='.$_POST['g-recaptcha-response']);
	if(!json_decode($confirm)->success)
	{
		$success = false;
		$_SESSION['errorUsername'] = "Confirm humanity.";
	}

	// REMEMBER DATA
	$_SESSION['rem_username'] = $username;
	$_SESSION['rem_passwordUsername'] = $password;

	if(!$success)
	{
		backToProfile();
	}
	else
	{
		if(!$connection->query("UPDATE users SET username='$username' WHERE email='$email'"))
		{
			throw new Exception($connection->error);
		}
		else
		{
			$_SESSION['successUsername'] = "The username was changed correctly! Log In again to see results.";
			header('Location: profile.php');
			exit();
		}
	}

	$connection->close();
?>