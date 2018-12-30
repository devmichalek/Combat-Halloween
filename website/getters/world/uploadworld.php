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
			$oryginal = 0; // false
			$data = $_POST['data'];
			$username = htmlentities($username, ENT_QUOTES, "UTF-8");

			if($result = @$connection->query(sprintf("SELECT * FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $username))))
			{
				$how_many = $result->num_rows;
				$row = $result->fetch_assoc();

				if($how_many > 0 && !password_verify($password, $row['password']))
					echo '2';
				else
				{
					$permissions = $row['permissions'];
					$result->free_result();

					$MAX_NUMBER_OF_WORLDS = 5;
					if($permissions != 'user') {
						$MAX_NUMBER_OF_WORLDS = 100;
					}

					// Check how many worlds are still available
					if($result = @$connection->query(sprintf("SELECT * FROM worlds WHERE username='%s'",mysqli_real_escape_string($connection, $username))))
					{
						$how_many = $result->num_rows;
						$result->free_result();
						if($how_many >= $MAX_NUMBER_OF_WORLDS)
							echo '3';
						else
						{
							// Check if there is no world with the same title.
							if($result = @$connection->query(sprintf("SELECT * FROM worlds WHERE title='%s' AND username='%s'",mysqli_real_escape_string($connection, $username), mysqli_real_escape_string($connection, $title))))
							{
								$how_many = $result->num_rows;
								$result->free_result();
								if($how_many > 0)
									echo '4';
								else
								{
									if(!$connection->query("INSERT INTO worlds VALUES (NULL, '$username', '$title', '$oryginal', '$data')"))
										echo '-1';
									else
										echo '0'; // SUCCESS
								}
							}
						}
					}
				}
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
	0 - Correctly added new world.
	1 - Found more/less than one user with the same username.
	2 - Incorrect password.
	3 - Reached max number of worlds.
	4 - Found world with existing title.
*/
?>