<?php
	if(!isset($_SESSION['logged']))
	{
		header('Location: http://combathalloween.netne.net/user/loginform.php');
		exit();
	}
?>