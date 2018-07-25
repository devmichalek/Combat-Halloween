<?php
	
	// Start session.
	session_start();

	// Just in case.
	unset($_SESSION['emailError']);

	function generateCode($length = 30)
  {
      $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
      $charactersLength = strlen($characters);
      $randomString = '';
      for ($i = 0; $i < $length; ++$i)
      {
         $randomString .= $characters[rand(0, $charactersLength - 1)];
      }
      return $randomString;
  }

  function backToProfile()
  {
    header('Location: profile.php');
	   exit();
  }

  $success = true;
  $newemail = $_POST['newemail'];
  $email = $_SESSION['email'];

  // Check if this username is not occupied.
  require_once ("../connect.php");
  mysqli_report(MYSQLI_REPORT_STRICT);
  try
  {
    $connection = @new mysqli($host, $db_user, $db_password, $db_name);
    if($connection->connect_errno != 0)
    {
      throw new Exception(mysqli_connect_errno());
    }
    else
    {
      $result = $connection->query("SELECT ID FROM users WHERE email='$newemail'");
      if(!$result)
      {
        throw new Exception($connection->error);
      }
      $how_many_emails = $result->num_rows;
      if($how_many_emails > 0)
      {
        $success = false;
        $_SESSION['emailError'] = "This email already exists.";
      }
    }
  }
  catch(Exception $e)
  {
    echo 'Error';
    // echo 'Error: '.$e;
  }

  // SQL Injection Barier.
  $email_safe = filter_var($newemail, FILTER_SANITIZE_EMAIL);
  if(!filter_var($email_safe, FILTER_VALIDATE_EMAIL) || $email_safe != $newemail)
  {
    $success = false;
    $_SESSION['emailError'] = "Valid adress email required.";
  }


  // RECAPTCHA
  $mysecret = "6Lcs3GIUAAAAAG9qpx2wImGLmkhzh_KF2Y0YZrNV";
  $confirm = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$mysecret.'&response='.$_POST['g-recaptcha-response']);
  if(!json_decode($confirm)->success)
  {
    $success = false;
    $_SESSION['passwordError'] = "Confirm humanity.";
  }

  // REMEMBER DATA
  $_SESSION['rem_newemail'] = $newemail;

  if(!$success)
  {
    backToProfile();
  }
  else
  {
    if(!$connection->query("UPDATE users SET email='$newemail' WHERE email='$email'"))
    {
      throw new Exception($connection->error);
    }
    else
    {
      header('Location: profile.php');
      exit();
    }
  }

  $connection->close();
?>