<?php
	
	// Start session.
	session_start();

	// Just in case.
	unset($_SESSION['passwordError']);

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
  $oldpassword = $_POST['oldpassword'];
  $newpassword = $_POST['newpassword'];
  $newpasswordcon = $_POST['newpasswordcon'];

  // Get current password from database.
  require_once ("../connect.php");
  mysqli_report(MYSQLI_REPORT_STRICT);
  $currentpassword = "";
  $email = $_SESSION['email'];
  try
  {
    $connection = @new mysqli($host, $db_user, $db_password, $db_name);
    if($connection->connect_errno != 0)
    {
      throw new Exception(mysqli_connect_errno());
    }
    else
    {
        $result = $connection->query("SELECT * FROM users WHERE email='$email'");
        if(!$result)
        {
          throw new Exception($connection->error);
        }
        else
        {
          $row = $result->fetch_assoc();
          if(password_verify($oldpassword, $row['password']))
          {
            $success = false;
            $_SESSION['passwordError'] = "Old password is incorrect.";
          }
        }
    }
  }
  catch(Exception $e)
  {
    echo 'Error';
    // echo 'Error: '.$e;
  }

  if((strlen($newpassword)) < 8)
  {
    $success = false;
    $_SESSION['passwordError'] = "Please choose a new password with at least 8 characters.";
  }
  else if((strlen($newpassword)) > 20)
  {
    $success = false;
    $_SESSION['passwordError'] = "New password may contain at the maximum 20 characters.";
  }
  else if($newpassword != $newpasswordcon)
  {
    $success = false;
    $_SESSION['passwordError'] = "Passwords do not match.";
  }

  $password_hashed = password_hash($newpassword, PASSWORD_DEFAULT);


  // RECAPTCHA
  $mysecret = "6Lcs3GIUAAAAAG9qpx2wImGLmkhzh_KF2Y0YZrNV";
  $confirm = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$mysecret.'&response='.$_POST['g-recaptcha-response']);
  if(!json_decode($confirm)->success)
  {
    $success = false;
    $_SESSION['passwordError'] = "Confirm humanity.";
  }

  // REMEMBER DATA
  $_SESSION['rem_oldpassword'] = $oldpassword;
  $_SESSION['rem_newpassword'] = $newpassword;
  $_SESSION['rem_newpasswordcon'] = $newpasswordcon;

  if(!$success)
  {
    backToProfile();
  }
  else
  {
    if(!$connection->query("UPDATE users SET password='$newpassword' WHERE email='$email'"))
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