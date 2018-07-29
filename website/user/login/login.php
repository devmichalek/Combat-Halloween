<?php
    
	session_start();
	
	if(!isset($_POST['username']) || !isset($_POST['password']))
	{
		header('Location: http://combathalloween.netne.net/login/loginform.php');
		exit();
	}
	
	require_once("../../connect.php");
	
	mysqli_report(MYSQLI_REPORT_STRICT);

	// RECAPTCHA
    $mysecret = "6Lcs3GIUAAAAAG9qpx2wImGLmkhzh_KF2Y0YZrNV";
    $confirm = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$mysecret.'&response='.$_POST['g-recaptcha-response']);
    if(!json_decode($confirm)->success)
    {
    	$_SESSION['error'] = "Confirm humanity.";
    	header('Location: http://combathalloween.netne.net/user/login/loginform.php');
    	exit();
    }
    
    // REMEMBER DATA
    $username = $_POST['username'];
	$password = $_POST['password'];
    $_SESSION['rem_username'] = $username;
    $_SESSION['rem_password'] = $password;
	
	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno != 0)
		{
			throw new Exception(mysqli_connect_errno());
		}
		else
		{
			$username = htmlentities($username, ENT_QUOTES, "UTF-8");

			if($result = @$connection->query(sprintf("SELECT * FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $username))))
			{
				$how_many = $result->num_rows;
				if($how_many > 0)
				{
					$row = $result->fetch_assoc();
					if(password_verify($password, $row['password']))
					{
						if($row['activated'] == 0)
						{
							$_SESSION['error'] = 'Confirm your address email.';
							header('Location: http://combathalloween.netne.net/user/login/loginform.php');
    						exit();
						}
						else
						{
							$_SESSION['logged'] = true;
							$_SESSION['username'] = $row['username'];
							$_SESSION['email'] = $row['email'];
							$_SESSION['permissions'] = $row['permissions'];
							unset($_SESSION['error']);
							$result->free_result();
							header('Location: http://combathalloween.netne.net/home.php');
						}
					}
					else
					{
						$_SESSION['error'] = 'Wrong username or password.';
						header('Location: http://combathalloween.netne.net/user/login/loginform.php');
    					exit();
					}
				}
				else
				{
					$_SESSION['error'] = 'Wrong username or password.';
					header('Location: http://combathalloween.netne.net/user/login/loginform.php');
    				exit();
				}
			}
			$connection->close();
		}
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
	}
?>