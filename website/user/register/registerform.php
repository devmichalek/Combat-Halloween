<?php
	
	// Start session.
	session_start();

	require_once("../../common/head.php"); 
?>

    <!-- NAVBAR -->
    <?php require_once("../../common/navbar-b.php"); ?>
            <li><a class='nav japokki-white A3' href='../../index.php'>Start</a></li>
            <li><a class='btn blue-grey darken-1 japokki-white' href='../login/loginform.php'>Log In</a></li>
    <?php require_once("../../common/navbar-e.php"); ?>
    <?php require_once("../../common/sidenav-b.php"); ?>
        <li><a href="../../index.php" class="japokki-black"><i class="material-icons">stay_primary_portrait</i>Start</a></li>
        <li><a class='btn blue-grey darken-1 japokki-white' href='../login/loginform.php'>Log In</a></li>
    <?php require_once("../../common/sidenav-e.php"); ?>
  <!-- END OF NAVBAR -->
    
    <div class="container center">
    <!-- Header -->
    <div class="col s12 m12">
          <h2 class="japokki-black A22">Account - Sign Up</h2>
    </div>


    <form action="register.php" method="post" class="japokki-black">
		
		<div class="row"><div class="input-field col s12 m6 push-m3">
          <input id="username" type="text" class="validate" name="username" value="<?php
          if(isset($_SESSION['rem_username']))
          {
            echo $_SESSION['rem_username'];
            unset($_SESSION['rem_username']);
          }?>">
          <label for="username"><h5 class="A2">Username</h5></label>
        </div></div>

        <div class="row"><div class="input-field col s12 m6 push-m3">
          <input id="email" type="email" class="validate" name="email" value="<?php
          if(isset($_SESSION['rem_email']))
          {
            echo $_SESSION['rem_email'];
            unset($_SESSION['rem_email']);
          }?>">
          <label for="email"><h5 class="A2">Email</h5></label>
        </div></div>

		<div class="row"><div class="input-field col s12 m6 push-m3">
          <input id="password" type="password" class="validate" name="password" value="<?php
          if(isset($_SESSION['rem_password']))
          {
            echo $_SESSION['rem_password'];
            unset($_SESSION['rem_password']);
          }?>">
          <label for="password"><h5 class="A2">Password</h5></label>
        </div></div>

        <div class="row"><div class="input-field col s12 m6 push-m3">
          <input id="passwordcon" type="password" class="validate" name="passwordcon" value="<?php
          if(isset($_SESSION['rem_passwordcon']))
          {
            echo $_SESSION['rem_passwordcon'];
            unset($_SESSION['rem_passwordcon']);
          }?>">
          <label for="passwordcon"><h5 class="A2">Confirm Password</h5></label>
        </div></div>
		
		<div class="row"><div class="col s6 m3 push-m3" style="margin-bottom: 10px;">
        <div class="g-recaptcha" data-sitekey="6Lcs3GIUAAAAAPOX9QzHOA_farHU1IKYvWrWpB-Z"></div>
		</div></div>

		<div class="row"><div class="col s12">
        <button class="btn waves-effect waves-light blue-grey darken-1 japokki-white" type="submit" name="action">Sign Up
        <i class="material-icons right">send</i>
        </button></div></div>
    </form>


       <?php
      // Errors.
      echo '<h5 class="errorColor">';
      if( isset($_SESSION['e_username']))
      {
        echo $_SESSION['e_username'];
        unset($_SESSION['e_username']);
      }
      else if( isset($_SESSION['e_email']))
      {
        echo $_SESSION['e_email'];
        unset($_SESSION['e_email']);
      }
      else if( isset($_SESSION['e_password']))
      {
        echo $_SESSION['e_password'];
        unset($_SESSION['e_password']);
      }
      else if( isset($_SESSION['e_passwordcon']))
      {
        echo $_SESSION['e_passwordcon'];
        unset($_SESSION['e_passwordcon']);
      }
      else if( isset($_SESSION['e_bot']))
      {
        echo $_SESSION['e_bot'];
        unset($_SESSION['e_bot']);
      }
      echo '</h5>';
    ?>
    </div>
    
<?php require_once("../../common/footer.php"); ?>