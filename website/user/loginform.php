<?php
    session_start();
    
    // Reset errors.
    unset($_SESSION['e_username']);
    unset($_SESSION['e_email']);
    unset($_SESSION['e_password']);
    unset($_SESSION['e_passwordcon']);
    unset($_SESSION['e_bot']);

    // If user is logged.
    if(isset($_SESSION['logged']))
    {
        header('Location: ../home.php');
        exit();
    }
    
    require_once("../head.php");
?>

    <!-- NAVBAR -->
    <nav>
    <div class="nav-wrapper">
        <div class="row">
            <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
            <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
            <ul id="nav-mobile" class="right hide-on-med-and-down">
                <li><a class='nav' href='../index.php'>Start</a></li>
                <li><a class='btn nav-button' href='register.php'>Sign In</a></li>
            </ul>
        </div>
    </div>
    </nav>
    <ul class="nav-main sidenav" id="mobile-demo">
        <li><a class='nav' href='../index.php'>Start</a></li>
        <li><a class='btn nav-button' href='register.php'>Sign In</a></li>
    </ul>
    <!-- END OF NAVBAR-->
    

  <div class="container center">

    <!-- Header -->
    <div class="col s12 m12 l12 xl12"><section><div><h2>Account - Log In</h2></div></section></div>
      
    <div class="row">
      <form class="col s6 push-s3" action="login.php" method="post">

        <div class="row"><div class="input-field col s12">
            <input id="username" type="text" class="validate" name="username">
            <label for="username"><h5 class="modcon2">Username</h5></label>
        </div></div>

        <div class="row"><div class="input-field col s12">
          <input id="password" type="password" class="validate" name="password">
          <label for="password"><h5 class="modcon2">Password</h5></label>
        </div></div>
        
        <button class="btn waves-effect waves-light nav-button" type="submit" name="action">Login
        <i class="material-icons right">send</i>
        </button>

      <?php
        echo '<h5 class="errorColor">';
        if(isset($_SESSION['error']) )
        {
          echo $_SESSION['error'];
          unset($_SESSION['error']);
        }
        echo '</h5>';
      ?>
    </form>
  </div>
  </div>

<?php require_once("../footer.php"); ?>