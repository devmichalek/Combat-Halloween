<?php
  session_start();

  if(!isset($_SESSION['logged']))
  {
    header('Location: http://combathalloween.netne.net/user/loginform.php');
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
                <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
                <li><a class="nav btn red lighten-1 nav-button" href="index.php">Back</a></li>
            </ul>
        </div>
    </div>
    </nav>
    <ul class="nav-main sidenav" id="mobile-demo">
        <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
        <li><a class="nav btn red lighten-1 nav-button" href="index.php">Back</a></li>
    </ul>
    <!-- END OF NAVBAR -->

  <div class="container center">
    <div class="row">
      <h2 class="center">Documentation</h2>
      <h4 class="modcon">Some text.</h4>

      <h5>Bug Types</h5>
      <p>New - </p>
      <p></p>
      <p></p>
      <p></p>
      <p></p>

      <h5>Bug Resolutions</h5>
      <p>Deffered - </p>
      <p></p>
      <p></p>
      <p></p>
      <p></p>
      <p></p>
      <p></p>
      <p></p>

    </div>
  </div>

<?php require_once("../footer.php"); ?>