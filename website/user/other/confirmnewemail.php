<?php
	
	session_start();

	if(isset($_GET['email']) && isset($_GET['code']) && isset($_GET['newemail']))
	{
		// Connect.
		require_once("../../connect.php");
		mysqli_report(MYSQLI_REPORT_STRICT);

		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno == 0)
		{
			$email = $_GET['email'];
			$newemail = $_GET['newemail'];
			$code = $_GET['code'];
			unset($_GET['email']);
			unset($_GET['newemail']);
			unset($_GET['code']);

			$email = htmlentities($email, ENT_QUOTES, "UTF-8");
			if($result = @$connection->query(sprintf("SELECT * FROM users WHERE email='%s'", mysqli_real_escape_string($connection, $email))))
			{
				$how_many = $result->num_rows;
				if($how_many > 0)
				{
					$row = $result->fetch_assoc();
					if($row['activationcode'] == $code)
					{
						$result->free_result();
						$newemail = mysqli_real_escape_string($connection, $newemail);
						$sql_query = "UPDATE users SET email='$newemail', activationcode='0' WHERE email='$email'";
						$connection->query($sql_query);
						$_SESSION['email'] = $newemail;
					}
				}
			}

			$connection->close();
		}
	}


	header('Location: https://amichalek.pl/combathalloween/home.php');
	exit();
?>