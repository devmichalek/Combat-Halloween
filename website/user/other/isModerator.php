<?php
	require_once("/home/adrmic2/domains/amichalek.pl/public_html/combathalloween/connect.php");
	mysqli_report(MYSQLI_REPORT_STRICT);
	$connection = @new mysqli($host, $db_user, $db_password, $db_name);

	if($result = @$connection->query( sprintf("SELECT * FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $_SESSION['username']))))
	{
		$row = $result->fetch_assoc();
		
		if($row['permissions'] == "user")
		{
			$result->free_result();
			$connection->close();
			header('Location: https://amichalek.pl/combathalloween/home.php');
			exit();
		}

		$result->free_result();
	}
	else
	{
		$result->free_result();
		$connection->close();
		header('Location: https://amichalek.pl/combathalloween/home.php');
		exit();
	}
?>