<?php
  session_start();

  if(!isset($_SESSION['logged']))
  {
    header('Location: user/loginform.php');
    exit();
  }
  
  /*
  require_once "connect.php";

  mysqli_report(MYSQLI_REPORT_STRICT);
  try
  {
    $connection = @new mysqli($host, $db_user, $db_password, $db_name);

    $connection->close();
  }
  catch(Exception $e)
  {
    echo 'Error';
    // echo 'Error: '.$e;
  }
  */
?>


<?php require_once("head.php"); ?>
  
  <div class="navbar-fixed"><nav><div class="nav-wrapper">
      <div class="row">
          <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
          <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
          <ul id="nav-mobile" class="right hide-on-med-and-down">
            <li><a class='nav' href='../index.php'>Start</a></li>
            <li><a class='dropdown-trigger btn nav-button' href='bugs/index.php'>Bugs</a></li>
            <li><a class='dropdown-trigger btn nav-button' href='user/logout.php'>Log Out</a></li>
          </ul>
        </div>
  </div></nav></div>
  <ul class="nav-main sidenav" id="mobile-demo">
    <li><a class='nav' href='../index.php'>Start</a></li>
    <li><a class='dropdown-trigger btn nav-button' href='bugs/index.php'>Bugs</a></li>
    <li><a class='dropdown-trigger btn nav-button' href='user/logout.php'>Log Out</a></li>
  </ul>

<?php require_once("footer.php"); ?>