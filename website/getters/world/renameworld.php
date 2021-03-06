<?php
	session_start();

	require_once("../../connect.php");

	mysqli_report(MYSQLI_REPORT_STRICT);
	
	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno != 0)
		{
			echo '-1';
		}
		else
		{
			$username = $_POST['username'];
			$password = $_POST['password'];
			$oldtitle = $_POST['oldtitle'];
			$newtitle = $_POST['newtitle'];
			$username = htmlentities($username, ENT_QUOTES, "UTF-8");

			if($result = @$connection->query(sprintf("SELECT * FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $username))))
			{
				$how_many = $result->num_rows;
				$row = $result->fetch_assoc();

				if($how_many > 0 && !password_verify($password, $row['password']))
				{
					$result->free_result();
					echo '3';
				}
				else
				{
					$result->free_result();
					if($result = @$connection->query(sprintf("SELECT * FROM worlds WHERE username='%s'", mysqli_real_escape_string($connection, $username))))
					{
						$how_many = $result->num_rows;
						$result->free_result();
						if($how_many <= 0)
							echo '1';
						else
						{
							if($result = @$connection->query(sprintf("SELECT * FROM worlds WHERE title='%s'",mysqli_real_escape_string($connection, $oldtitle))))
							{
								$how_many = $result->num_rows;
								$result->free_result();
								if($how_many <= 0)
									echo '2';
								else
								{
									// Prepare strings.
									$username = mysqli_real_escape_string($connection, $_POST['username']);
									$oldtitle = mysqli_real_escape_string($connection, $_POST['oldtitle']);
									$newtitle = mysqli_real_escape_string($connection, $_POST['newtitle']);

									$sql_query = "UPDATE worlds SET title='$newtitle' WHERE username='$username' AND title='$oldtitle'";
									if(!$connection->query($sql_query))
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
	0 - Correctly renamed world.
	1 - Could not find user with this username.
	2 - Found more/less than one world with this title.
	3 - Incorrect password.
*/
?>