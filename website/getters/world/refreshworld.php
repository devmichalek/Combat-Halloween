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
			$username = htmlentities($username, ENT_QUOTES, "UTF-8");

			// Check how many worlds are there.
			if($result = @$connection->query(sprintf("SELECT * FROM worlds WHERE username='%s'", mysqli_real_escape_string($connection, $username))))
			{
				$how_many = $result->num_rows;
				if($how_many <= 0)
				{
					echo '2';
				}
				else
				{
					while($row=$result->fetch_assoc())
					{
						echo $row['title']."\n";
					}
				}

				$result->free_result();
			}
			else
			{
				echo '1';
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
	0 - Correctly get worlds.
	1 - Could not find user with this username.
	2 - There are no worlds.
*/
?>