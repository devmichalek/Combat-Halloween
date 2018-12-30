<?php
	session_start();

	require_once("../../connect.php");

	mysqli_report(MYSQLI_REPORT_STRICT);
	
	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno != 0)
			echo '-1';
		else
		{
			$username = $_POST['username'];
			$password = $_POST['password'];
			$title = $_POST['title'];
			$username = htmlentities($username, ENT_QUOTES, "UTF-8");

			if($result = @$connection->query(sprintf("SELECT * FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $username))))
			{
				$how_many = $result->num_rows;
				$row = $result->fetch_assoc();

				if($how_many > 0 && !password_verify($password, $row['password']))
					echo '2';
				else
				{
					$result->free_result();
					if($result = @$connection->query(sprintf("SELECT * FROM worlds WHERE username='%s' AND title='%s'",mysqli_real_escape_string($connection, $username), mysqli_real_escape_string($connection, $title))))
					{
						$how_many = $result->num_rows;
						if($how_many != 1)
							echo '1';
						else
						{
							$row = $result->fetch_assoc();
							echo $row['data'];
						}
					}
				}

				$result->free_result();
			}

			$connection->close();
		}
	}
	catch(Exception $e)
	{
		echo '-1';
	}

/*	Output
	-1 - Cannot connect with database.
	0 - Correctly copied world.
	1 - Could not find user with this username and title.
	2 - Incorrect password.
*/
?>