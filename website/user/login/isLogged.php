<?php
	if(!isset($_SESSION['logged']))
	{
		header('Location: http://combathalloween.netne.net/user/login/loginform.php');
		exit();
	}
?>