<?php
  	session_start();
	require_once("../common/head.php");
?>
    
    <!-- NAVBAR -->
    <div class="navbar-fixed">
    <nav><div class="nav-wrapper">
        <div class="row">
            <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
            <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
            <ul id="nav-mobile" class="right hide-on-med-and-down">
            	<li><a class="btn-floating btn-medium pulse indigo lighten-1" href="../index.php"><i class="material-icons">stay_primary_portrait</i></a></li>
                <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
                <?php
                if(isset($_SESSION['logged']))
                {
                    echo "<li><a class='btn nav-button' href='bugs/index.php'";
                    if($_SESSION['permissions'] == "user")
                        echo " disabled ";
                    echo '><i class="material-icons right">bug_report</i>Bugs</a></li>';
                }
                ?>
            </ul>
        </div>
    </div></nav>
    </div>
    <?php require_once("../common/sidenav-b.php"); ?>
    	<li><a href="../index.php"><i class="material-icons">stay_primary_portrait</i>Start</a></li>
        <li><a href="../home.php"><i class="material-icons">home</i>Home</a></li>
        <?php
    	if(isset($_SESSION['logged']))
    	{
    		echo '<li><a href="bugs/index.php"';
        	if($_SESSION['permissions'] == "user")
            	echo " class='disabled' ";
        	echo '><i class="material-icons">bug_report</i>Bugs</a></li>';
    	}
        ?>
    <?php require_once("../common/sidenav-e.php"); ?>
    <!-- END OF NAVBAR -->

	<div class="container center">
    <div class="row">
    	<h2>Commands</h2>
    	<h4 class="modcon">Some text.</h4>

    	<h2>Global Commands</h2>
    	<h4 class="modcon">
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
        	<span style="color: #ef5350;">Blah</span> - blah blah<br>
    	</h4>

    	<h2>Menu Commands</h2>
    	<h4 class="modcon">
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
        	<span style="color: #ef5350;">Blah</span> - blah blah<br>
    	</h4>

    	<h2>Level Menu Commands</h2>
    	<h4 class="modcon">
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
        	<span style="color: #ef5350;">Blah</span> - blah blah<br>
    	</h4>

    	<h2>Platform Commands</h2>
    	<h4 class="modcon">
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
        	<span style="color: #ef5350;">Blah</span> - blah blah<br>
    	</h4>

    	<h2>Results Scene Commands</h2>
    	<h4 class="modcon">
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
    		<span style="color: #ef5350;">Blah</span> - blah blah<br>
        	<span style="color: #ef5350;">Blah</span> - blah blah<br>
    	</h4>
    </div>
	</div>

<?php require_once("../common/footer.php"); ?>