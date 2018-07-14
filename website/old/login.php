<?php

	session_start();

	if(!isset($_POST['username']) || !isset($_POST['password']))
	{
		header('Location: login_form.php');
		exit();
	}

	require_once "connect.php";
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
			$username = $_POST['username']; // poniewaz w login_form.php tak ustawilismy
			$password = $_POST['password'];

			$username = htmlentities($username, ENT_QUOTES, "UTF-8");

			if($result = @$connection->query(
			sprintf("SELECT * FROM users WHERE username='%s'",
			mysqli_real_escape_string($connection, $username))))
			{
				$how_many = $result->num_rows;
				if($how_many > 0)
				{
					$row = $result->fetch_assoc();
					if(password_verify($password, $row['password']))
					{
						if($row['activated'] == 0)
						{
							$_SESSION['error'] = 'Confirm your adress email.';
							header('Location: login_form.php');
						}
						else
						{
							$_SESSION['logged'] = true;
							$_SESSION['username'] = $row['username'];
							$_SESSION['first_time'] = $row['first_time'];
							$_SESSION['premium'] = $row['premium'];

							unset($_SESSION['error']);
							$result->free_result();
							header('Location: home.php');
						}
					}
					else
					{
						$_SESSION['error'] = 'Wrong username or password.';
						header('Location: login_form.php');
					}
				}
				else
				{
					$_SESSION['error'] = 'Wrong username or password.';
					header('Location: login_form.php');
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