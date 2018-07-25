<?php
	
	// Start session.
	session_start();

	// Just in case.
	unset($_SESSION['usernameError']);

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
  $newusername = $_POST['newusername'];
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
      $result = $connection->query("SELECT ID FROM users WHERE username='$newusername'");
      if(!$result)
      {
        throw new Exception($connection->error);
      }
      $how_many_usernames = $result->num_rows;
      if($how_many_usernames > 0)
      {
        $success = false;
        $_SESSION['usernameError'] = "This username already exists.";
      }
    }
  }
  catch(Exception $e)
  {
    echo 'Error';
    // echo 'Error: '.$e;
  }

  if((strlen($newusername)) < 4)
  {
    $success = false;
    $_SESSION['usernameError'] = "Please choose a name with at least 4 characters.";
  }
  else if((strlen($username)) > 12)
  {
    $success = false;
    $_SESSION['usernameError'] = "Maximum number of characters is 12.";
  }
  else if(!ctype_alnum($username))
  {
    $success = false;
    $_SESSION['usernameError'] = "This name is unavailable.";
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
  $_SESSION['rem_newusername'] = $newusername;

  if(!$success)
  {
    backToProfile();
  }
  else
  {
    if(!$connection->query("UPDATE users SET username='$newusername' WHERE email='$email'"))
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