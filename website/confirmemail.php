<?php
	
	session_start();

	if( isset( $_GET['email'] ) && isset( $_GET['code'] ) )
	{
    	// Connect.
		require_once "connect.php";
		mysqli_report(MYSQLI_REPORT_STRICT);

		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno == 0)
		{
			$email = $_GET['email'];
			$code = $_GET['code'];
			unset( $_GET['email'] );
			unset( $_GET['code'] );

			$email = htmlentities($email, ENT_QUOTES, "UTF-8");
			if($result = @$connection->query(
			sprintf("SELECT * FROM users WHERE email='%s'",
			mysqli_real_escape_string($connection, $email))))
			{
				$how_many = $result->num_rows;
				if($how_many > 0)
				{
					$row = $result->fetch_assoc();
					if($row['activation_code'] == $code && $row['activated'] == 0)
					{
						$result->free_result();
						$connection->query("UPDATE users SET activated='1' WHERE email='$email'");
						$_SESSION['confirmedemail'] = true;
						header('Location: confirmedemail.php');
					}
					else
				  	{
				  		header('Location: home.php');
				  	}
				}
			}

			$connection->close();
		}
  	}
  	else
  	{
  		header('Location: home.php');
  	}
?>