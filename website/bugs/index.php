<?php

  // Start session.
  session_start();

  // Check if user is logged.
  require_once("../user/login/isLogged.php");

  // Check if user has admin permissions.
  require_once("../user/other/isAdmin.php");

  if($connection->connect_errno == 0)
  {
        $sql = "SELECT * FROM bugs";
        $records = $connection->query($sql);
    	

    	// Counters.
        $allbugs = 0;
        $finishedbugs = 0;
        $unresolvedbugs = 0;

    	$numarray = array("all" => 0, "finished" => 0, "unresolved" => 0);
    	$peoplearray = array('devmichalek@gmail.com' => $numarray, 'sebastek321@gmail.com' => $numarray, 'kamilgawlik@icloud.com' => $numarray);

        while($row=$records->fetch_assoc())
        {
        	$cemail = $row['developer'];
        	++$allbugs;
        	++$peoplearray[$cemail]['all'];
            if($row['resolution'] == "Fixed" || $row['resolution'] == "Implemented" || $row['resolution'] == "Revised")
            {
                ++$peoplearray[$cemail]['finished'];
                ++$finishedbugs;
            }
            else
            {
                ++$peoplearray[$cemail]['unresolved'];
                ++$unresolvedbugs;
            }
        }
        $records->free_result();

    

        // Set resolution and developer select.
        $rselect = "unresolved";
        $dselect = "mine";
        if(isset($_GET['rselect']))  $rselect = $_GET['rselect'];
        if(isset($_GET['dselect']))  $dselect = $_GET['dselect'];
        
        $rresult = "WHERE 1";
        if($rselect == "finished")        $rresult = "WHERE resolution IN ('fixed', 'revised', 'implemented')";
        else if($rselect == "unresolved") $rresult = "WHERE NOT resolution IN ('fixed', 'revised', 'implemented')";
    
        $dresult = " AND 1";
        $author = $_SESSION['email'];
        if($dselect == "mine")        $dresult = " AND developer='$author'";
        else if($dselect == "their")  $dresult = " AND NOT developer='$author'";
        
        $records = $connection->query("SELECT * FROM bugs ".$rresult.$dresult);
    }
    else
    {
        die("Could not connect: ".mysql_error());
    }
  
    require_once("../common/head.php");
?>
    <!-- NAVBAR -->
    <div class="navbar-fixed">
    <nav>
    <div class="nav-wrapper">
        <div class="row">
            <a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
            <a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
            <ul id="nav-mobile" class="right hide-on-med-and-down">
                <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
                <li><a class="btn-floating btn-medium pulse deep-orange lighten-1" href="other/modules.php"><i class="material-icons">view_module</i></a></li>
                <li><a class="nav btn amber lighten-1 nav-button" href="https://drive.google.com/uc?authuser=0&id=1ICi0LeAdMGU-SH1oENlz-cR86b6AEmYx&export=download">Sprite Tester</a></li>
                <li><a class="nav btn red lighten-1 nav-button" href="add/addbug.php"><i class="material-icons right">bug_report</i>Add</a></li>
            </ul>
        </div>
    </div>
    </nav>
    </div>
    <?php require_once("../common/sidenav-b.php"); ?>
        <li><a href="../home.php"><i class="material-icons">home</i>Home</a></li>
        <li><a href="other/modules.php"><i class="material-icons">view_module</i>Modules</a></li>
        <li><a href="https://drive.google.com/uc?authuser=0&id=1ICi0LeAdMGU-SH1oENlz-cR86b6AEmYx&export=download"><i class="material-icons">file_download</i>Sprite Tester</a></li>
        <li><a href="add/addbug.php"><i class="material-icons">bug_report</i>Add Bug</a></li>
    <?php require_once("../common/sidenav-e.php"); ?>
    <!-- END OF NAVBAR -->

  <div class="container center">
    <div class="row">
      <h2 class="center">Combat Halloween Bugs</h2>
		
		<!-- Print stats-->
      	<h4 class="modcon"><?php echo "Finished: ".$finishedbugs." Unresolved: ".$unresolvedbugs." All: ".$allbugs;?></h4>
    	<?php
    	echo '<h4 class="modcon">';
    		foreach($peoplearray as $key => $v)
    		{
    			echo '<div class="chip"><img src="../images/users/';
    			echo $key.'.jpg" alt="Contact Person">';
    			echo "Finished: ".$v['finished'];
    			echo " Unresolved: ".$v['unresolved'];
    			echo " All: ".$v['all'];
    			echo '</div>';
    		}
    		echo "</h4>";
    	?>
		
        <!-- SORT BY-->
        <form action="index.php" method="get">
          <div class="row">
            <div class="input-field col s6 m3 push-m3">
            <select name="rselect">
                <?php
                echo "<option "; if($rselect=="all")   echo " selected "; echo 'value="all">All</option>';
                echo "<option "; if($rselect=="finished")   echo " selected "; echo 'value="finished">Finished</option>';
                echo "<option "; if($rselect=="unresolved")   echo " selected "; echo 'value="unresolved">Unresolved</option>';
                ?>
            </select>
                <label>Sort by resolution</label>
            </div>
            
            <div class="input-field col s6 m3 push-m3">
            <select name="dselect">
                <?php
                echo "<option "; if($dselect=="all")   echo " selected "; echo 'value="all">All</option>';
                echo "<option "; if($dselect=="mine")   echo " selected "; echo 'value="mine">Mine</option>';
                echo "<option "; if($dselect=="their")   echo " selected "; echo 'value="their">Their</option>';
                ?>
            </select>
                <label>Sort by developer</label>
            </div>
          </div>

            <div class="center col s8 m4 push-m4 push-s2">
            <button class="waves-effect waves-light btn green lighten-1 japokki" type="submit"><i class="material-icons right">redo</i>Reload </button>
            </div>
        </form>
        <!-- ------ -->
      
        <!-- TABLE -->
        <?php require_once("other/table.php"); ?>
        <!-- ----- -->
    </div>
    
    <!-- Documentation Button -->
    <div class="fixed-action-btn"><a class="btn-floating btn-large red lighten-1" href="other/documentation.php" target="_blank"><i class="large material-icons">chat</i></a></div>
  </div>

<?php require_once("../common/footer.php"); ?>