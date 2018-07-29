<?php
	
	session_start();

	$success = true;

	//if errors...
	if($_FILES['file']['error'])
	{
		$success = false;
	    $_SESSION['errorAvatar'] = "Error while uploading file.";
	}
	

	// Check if image file is a actual image or fake image
    /*$check = getimagesize($_FILES["file"]["tmp_name"]);
    if($check !== false)
    {
    	$success = false;
        $_SESSION['errorAvatar'] = "File is not an image.";
    }*/

	// Check file size
	if($_FILES['file']['size'] > (1024000)) //can't be larger than 1 MB
	{
		$success = false;
		$_SESSION['errorAvatar'] = 'Your file\'s size is to large.';
	}

	// Allow certain file formats
	$imageFileType = strtolower(pathinfo($_FILES["file"]["name"],PATHINFO_EXTENSION));
	if($imageFileType != "jpg")
	{
		$success = false;
	    $_SESSION['errorAvatar'] = "Sorry, only JPG files are allowed.";
	}

	if (!move_uploaded_file($_FILES["file"]["tmp_name"], '../../images/users/'.$_SESSION['email'].".jpg"))
	{
    	$success = false;
        $_SESSION['errorAvatar'] = "Error while uploading file.";
    }

    if($success)
    {
    	$_SESSION['successAvatar'] = "The file ".basename($_FILES["file"]["name"]). " has been uploaded.";
    }

	header('Location: profile.php');
	exit();
?>