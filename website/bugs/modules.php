<?php

  	session_start();

	require_once("../user/isLogged.php");

	require_once("../user/isAdmin.php");

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
      <h2>About Modules</h2>
      <h4 class="modcon">The module is a part of the application that has its own life during program execution. We divide application because only then it's easier to find a single bug. During testing try to do anything that's in your mind, try to crash the application, make undefined behavior, anything you like. Our method of making the application better is a spiral method. We upload module, the module is being tested, any errors are caught and added into the bug list, the module is updated and the loop starts again. Also, we work with agile software development, we don't have one single deadline for the project, we do small tasks and small updates so at the end, we have a final product. Please check out current modules and try to find bugs. Ascribe new bug to devmichalek@gmail.com.</h4>

    	<h2>List Of <a target="_blank" href="https://drive.google.com/drive/folders/11UgUFJxFb2fVNwL4eFe3pMbAtwE80hTQ">Modules</a></h2>
    	<h4 class="modcon">Map Editor (add/edit/remove map) Update(-) - Download</h4>
    	<h4 class="modcon">Introduction (1st scene, intro, logging system) Update(2018.07.22) - <a target="_blank" href="https://drive.google.com/uc?authuser=0&id=1Djm1aTlERKb9O6UG7L0AkKK2DXMHTzaw&export=download">Download</a></h4>
		<h4 class="modcon">Menu (2nd scene, main menu) Update(-) - Download</h4>
		<h4 class="modcon">Level Menu (3rd scene, level menu, chosing level) Update(-) - Download</h4>
		<h4 class="modcon">Platform (4th scene, that's where game starts ) Update(-) - Download</h4>
		<h4 class="modcon">End Scene (5th scene, user died etc., shows stats) Update(-) - Download</h4>
    </div>
  </div>

<?php require_once("../footer.php"); ?>