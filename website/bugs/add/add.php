<?php
	
	// Start session.
	session_start();

	// Funtion to generate ID name.
	function generateIDname($email, $number)
	{
		$basic = "nn";
		if($email == "devmichalek@gmail.com")		$basic = "am";
		else if($email == "sebastek321@gmail.com")	$basic = "sb";
		else if($email == "kamilgawlik@icloud.com") $basic = "kg";

		$temp = str_repeat("0", 4 - strlen(strval($number)));
		return $basic.$temp.strval($number + 1);
	}

	// Check if user is logged.
	require_once("../../user/login/isLogged.php");

	// Check if user has admin/moderator permissions.
	require_once("../../user/other/isModerator.php");

	// Check if all fields are filled.
	$error_msg = "";
	if(strlen($_POST['name']) <= 0)					$error_msg = "Field 'name' is empty!";
	else if(strlen($_POST['type']) <= 0)			$error_msg = "Field 'type' is empty!";
	else if(strlen($_POST['actiontodo']) <= 0)	    $error_msg = "Field 'action' is empty!";
	else if(strlen($_POST['description']) <= 0)     $error_msg = "Field 'description' is empty!";
	else if(strlen($_POST['location']) <= 0)		$error_msg = "Field 'location' is empty!";
	else if(strlen($_POST['severity']) <= 0)		$error_msg = "Field 'severity' is empty!";
	else if(strlen($_POST['priority']) <= 0)		$error_msg = "Field 'priority' is empty!";
	else if(strlen($_POST['deadline']) <= 0)		$error_msg = "Field 'deadline' is empty!";
	else if(strlen($_POST['author']) <= 0)			$error_msg = "Field 'author' is empty!";
	else if(strlen($_POST['developer']) <= 0)	    $error_msg = "Field 'developer' is empty!";

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
		    $author = addslashes($_POST['author']);
		    
			// Send query.
			$sql = "SELECT * FROM bugs WHERE author='$author'";
			$result = $connection->query($sql);
			$sum = mysqli_num_rows($result);

			// Set variables.
			$IDname =		generateIDname($author, $sum);
			$name =			addslashes($_POST['name']);
			$type =			$_POST['type'];
			$action =		$_POST['actiontodo'];
			$description =	nl2br(addslashes($_POST['description']));
			$location =		addslashes($_POST['location']);
			$severity =		$_POST['severity'];
			$priority =		$_POST['priority'];
			$deadline =		addslashes($_POST['deadline']);
			$developer =	$_POST['developer'];
			$resolution =	$_POST['resolution'];

			if(!$connection->query("INSERT INTO bugs VALUES (NULL, '$IDname', '$name', '$type', '$action', '$description', '$location', '$severity', '$priority', '$deadline', '$author', '$developer', '$resolution')"))
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