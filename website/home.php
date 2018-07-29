<?php
    // Start session.
	session_start();

	// Check if user is logged.
	require_once("user/login/isLogged.php");
	
	require_once("common/head.php");
?>
    
    <div class="navbar-fixed">
    <nav><div class="nav-wrapper">
      <div class="row">
            <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
            <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
            <ul id="nav-mobile" class="right hide-on-med-and-down">
                <li><a class="btn-floating btn-medium pulse indigo lighten-1" href="index.php"><i class="material-icons">stay_primary_portrait</i></a></li>
                <?php
                    echo "<li><a class='dropdown-trigger btn nav-button' href='bugs/index.php'";
                    if($_SESSION['permissions'] == "user")
                        echo " disabled ";
                    echo '><i class="material-icons right">bug_report</i>Bugs</a></li>';
                ?>
                <li><a class='dropdown-trigger btn nav-button' href='user/login/logout.php'>Log Out</a></li>
            </ul>
        </div>
    </div></nav>
    </div>
    <?php require_once("common/sidenav-b.php"); ?>
        <li><a href="index.php"><i class="material-icons">stay_primary_portrait</i>Start</a></li>
        <?php
            echo '<li><a href="bugs/index.php"';
            if($_SESSION['permissions'] == "user")
                echo " class='disabled' ";
            echo '><i class="material-icons">bug_report</i>Bugs</a></li>';
        ?>
        <li><a href="user/login/logout.php"><i class="material-icons">exit_to_app</i>Log Out</a></li>
    <?php require_once("common/sidenav-e.php"); ?>
    
<?php require_once("common/footer.php"); ?>