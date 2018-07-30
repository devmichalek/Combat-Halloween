<?php
	// Start session.
	session_start();

	// Check if user is logged.
	require_once("../../user/login/isLogged.php");

	$success = true;

	//if errors...
	if($_FILES['file']['error'])
	{
		$success = false;
	    $_SESSION['errorAvatar'] = "Error while uploading file.";
	}
	

	// Check if image file is a actual image or fake image
    list($width, $height) = getimagesize($_FILES["file"]["tmp_name"]);
    if($width > 150 || $height > 150)
    {
    	$success = false;
        $_SESSION['errorAvatar'] = "Image size must be less than 150x150!";
    }

	// Check file size
	if($_FILES['file']['size'] > (1024000)) //can't be larger than 1 MB
	{
		$success = false;
		$_SESSION['errorAvatar'] = 'Your image\'s size is to large!';
	}

	// Allow certain file formats
	$imageFileType = strtolower(pathinfo($_FILES["file"]["name"],PATHINFO_EXTENSION));
	if($imageFileType != "jpg")
	{
		$success = false;
	    $_SESSION['errorAvatar'] = "Sorry, only JPG files are allowed.";
	}
    
    if($success)
    {
        if (!move_uploaded_file($_FILES["file"]["tmp_name"], '../../images/users/'.$_SESSION['email'].".jpg"))
    	{
        	$success = false;
            $_SESSION['errorAvatar'] = "Error while uploading file.";
        }
    }
	
    if($success)
    {
    	$_SESSION['successAvatar'] = "The file ".basename($_FILES["file"]["name"]). " has been uploaded.";
    }

	header('Location: profile.php');
	exit();
?>