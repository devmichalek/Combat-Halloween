<?php

	// Start session.
	session_start();

	// Check if user is logged.
	require_once("../../user/login/isLogged.php");

	// Check if user has admin/moderator permissions.
	require_once("../../user/other/isModerator.php");

	// Check if all fields are filled.
	$error_msg = "";
	if(strlen($_POST['name']) <= 0)				$error_msg = "Field 'name' is empty!";
	else if(strlen($_POST['type']) <= 0)		$error_msg = "Field 'type' is empty!";
	else if(strlen($_POST['actiontodo']) <= 0)	$error_msg = "Field 'action' is empty!";
	else if(strlen($_POST['description']) <= 0) $error_msg = "Field 'description' is empty!";
	else if(strlen($_POST['location']) <= 0)	$error_msg = "Field 'location' is empty!";
	else if(strlen($_POST['severity']) <= 0)	$error_msg = "Field 'severity' is empty!";
	else if(strlen($_POST['priority']) <= 0)	$error_msg = "Field 'priority' is empty!";
	else if(strlen($_POST['deadline']) <= 0)	$error_msg = "Field 'deadline' is empty!";
	else if(strlen($_POST['author']) <= 0)		$error_msg = "Field 'author' is empty!";
	else if(strlen($_POST['developer']) <= 0)	$error_msg = "Field 'developer' is empty!";

	// Change location if there is an error and does not allow to add new bug to the table.
	if(strlen($error_msg) > 0)
	{
		header('Location: ../index.php');
		exit();
	}

	// Get $host, $db_user, $db_password and $db_name
	require_once("../../connect.php");

	// Set flag to see more details about errors.
	mysqli_report(MYSQLI_REPORT_STRICT);

	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno != 0)
			throw new Exception(mysqli_connect_errno());
		else
		{
			$ID =			mysqli_real_escape_string($connection, $_POST['ID']);;
			$name =			mysqli_real_escape_string($connection, addslashes($_POST['name']));
			$type =			mysqli_real_escape_string($connection, $_POST['type']);
			$action =		mysqli_real_escape_string($connection, $_POST['actiontodo']);
			$description =	mysqli_real_escape_string($connection, nl2br(addslashes($_POST['description'])));
			$location =		mysqli_real_escape_string($connection, addslashes($_POST['location']));
			$severity =		mysqli_real_escape_string($connection, $_POST['severity']);
			$priority =		mysqli_real_escape_string($connection, $_POST['priority']);
			$deadline =		mysqli_real_escape_string($connection, addslashes($_POST['deadline']));
			$author =		mysqli_real_escape_string($connection, addslashes($_POST['author']));
			$developer =	mysqli_real_escape_string($connection, $_POST['developer']);
			$resolution =	mysqli_real_escape_string($connection, $_POST['resolution']);

			$sql_query = "UPDATE bugs SET name='$name', type='$type', action='$action', description='$description', location='$location', severity='$severity', priority='$priority', deadline='$deadline', author='$author', developer='$developer', resolution='$resolution' WHERE ID='$ID'";

			if(!$connection->query($sql_query))
			{
				throw new Exception($connection->error);
			}
			else
			{
				header('Location: ../index.php');
				exit();
			}

			$connection->close();
		}
	}
	catch(Exception $e)
	{
		//echo 'Error';
		echo 'Error: '.$e;
	}
?>