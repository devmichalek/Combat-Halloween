<?php

    // Start session.
    session_start();

    // Check if user is logged.
    require_once("../user/login/isLogged.php");

    // Check if user has admin/moderator permissions.
    require_once("../user/other/isModerator.php");

    // Set flag to see more details about errors.
	mysqli_report(MYSQLI_REPORT_STRICT);

	$connection = @new mysqli($host, $db_user, $db_password, $db_name);

    if($connection->connect_errno == 0)
    {
        $sql = "SELECT * FROM bugs";
        $records = $connection->query($sql);
        
        
    	// Counters.
        $allCounter = 0;
        $resolvedCounter = 0;
        $unresolvedCounter = 0;
        
        $deferredCounter = 0;
        $disagreeCounter = 0;
        $duplicatedCounter = 0;
        $fixedCounter = 0;
        $heldCounter = 0;
        $implementedCounter = 0;
        $indevelopmentCounter = 0;
        $irreproducibleCounter = 0;
        $knownproblemCounter = 0;
        $needmoreinfoCounter = 0;
        $newCounter = 0;
        $obsoleteCounter = 0;
        $reopenCounter = 0;
        $revisedCounter = 0;
        $nottocorrectCounter = 0;
        $supportneededCounter = 0;
        $withdrawnCounter = 0;

        // Person stats
    	$numarray = array("all" => 0, "resolved" => 0, "unresolved" => 0);
    	$peoplearray = array('devmichalek@gmail.com' => $numarray, 'sebastek321@gmail.com' => $numarray, 'kamilgawlik@icloud.com' => $numarray);

        while($row=$records->fetch_assoc())
        {
            ++$allCounter;
            ++$peoplearray[$row['developer']]['all'];
            
            switch($row['resolution'])
            {
                case "Deferred":        ++$deferredCounter;         break;
                case "Disagree":        ++$disagreeCounter;         break;
                case "Duplicated":      ++$duplicatedCounter;       break;
                case "Fixed":           ++$fixedCounter;            break;
                case "Held":            ++$heldCounter;             break;
                case "Implemented":     ++$implementedCounter;      break;
                case "In Development":  ++$indevelopmentCounter;    break;
                case "Irreproducible":  ++$irreproducibleCounter;   break;
                case "Known Problem":   ++$knownproblemCounter;     break;
                case "Need More Info":  ++$needmoreinfoCounter;     break;
                case "New":             ++$newCounter;              break;
                case "Obsolete":        ++$obsoleteCounter;         break;
                case "Reopen":         ++$reopenCounter;           break;
                case "Revised":         ++$revisedCounter;          break;
                case "Not To Correct":  ++$nottocorrectCounter;     break;
                case "Support Needed":  ++$supportneededCounter;    break;
                case "Withdrawn":       ++$withdrawnCounter;        break;
            }
            
        	
            if($row['resolution'] == "Fixed" || $row['resolution'] == "Implemented" || $row['resolution'] == "Revised")
            {
                ++$peoplearray[$row['developer']]['resolved'];
                ++$resolvedCounter;
            }
            else
            {
                ++$peoplearray[$row['developer']]['unresolved'];
                ++$unresolvedCounter;
            }
        }
        $records->free_result();

    

        // Set resolution and developer select.
        $rselect = "unresolved";
        $dselect = "mine";
        if(isset($_GET['rselect']))  $rselect = $_GET['rselect'];
        if(isset($_GET['dselect']))  $dselect = $_GET['dselect'];
        
        $rresult = "WHERE 1";
        if($rselect == "resolved")        $rresult = "WHERE resolution IN ('fixed', 'revised', 'implemented')";
        else if($rselect == "unresolved") $rresult = "WHERE NOT resolution IN ('fixed', 'revised', 'implemented')";
    
        $dresult = " AND 1";
        $author = $_SESSION['email'];
        if($dselect == "mine")        $dresult = " AND developer='$author'";
        else if($dselect == "their")  $dresult = " AND NOT developer='$author'";
        
        $sql_query = "SELECT * FROM bugs ".$rresult.$dresult;
        $records = $connection->query($sql_query);
    }
    else
    {
        die("Could not connect: ".mysql_error());
    }
  
    require_once("../common/head.php");
?>
    <!-- NAVBAR -->
    <?php require_once("../common/navbar-b.php"); ?>
        <li><a class="btn-floating btn-medium pulse blue lighten-1" href="../home.php"><i class="material-icons">home</i></a></li>
        <li><a class="btn-floating btn-medium pulse deep-orange lighten-1" href="other/modules.php"><i class="material-icons">view_module</i></a></li>
        <li><a class="nav btn amber lighten-1 japokki-white" href="https://drive.google.com/uc?authuser=0&id=1ICi0LeAdMGU-SH1oENlz-cR86b6AEmYx&export=download">Sprite Tester</a></li>
        <li><a class="nav btn white japokki-black" href="add/addbug.php"><i class="material-icons right">bug_report</i>Add</a></li>
    <?php require_once("../common/navbar-e.php"); ?>
    <?php require_once("../common/sidenav-b.php"); ?>
        <li><a class="japokki-black" href="../home.php"><i class="material-icons">home</i>Home</a></li>
        <li><a class="japokki-black" href="other/modules.php"><i class="material-icons">view_module</i>Modules</a></li>
        <li><a class="japokki-black" href="https://drive.google.com/uc?authuser=0&id=1ICi0LeAdMGU-SH1oENlz-cR86b6AEmYx&export=download"><i class="material-icons">file_download</i>Sprite Tester</a></li>
        <li><a class="japokki-black" href="add/addbug.php"><i class="material-icons">bug_report</i>Add Bug</a></li>
    <?php require_once("../common/sidenav-e.php"); ?>
    <!-- END OF NAVBAR -->

  <div class="container center">
    <div class="row">
      	<!-- chart -->
        <canvas id="myChart" style="height: 370px; width: 100%; font-family: japokki;"></canvas>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.4.0/Chart.min.js"></script>
        <div class="service-con" data-service="<?php echo 40; ?>"></div>
        <script>
            var js_deferred =       <?php echo json_encode($deferredCounter); ?>;
            var js_disagree =       <?php echo json_encode($disagreeCounter); ?>;
            var js_duplicated =     <?php echo json_encode($duplicatedCounter); ?>;
            var js_fixed =          <?php echo json_encode($fixedCounter); ?>;
            var js_held =           <?php echo json_encode($heldCounter); ?>;
            var js_implemented =    <?php echo json_encode($implementedCounter); ?>;
            var js_indevelopment =  <?php echo json_encode($indevelopmentCounter); ?>;
            var js_irreproducible = <?php echo json_encode($irreproducibleCounter); ?>;
            var js_knownproblem =   <?php echo json_encode($knownproblemCounter); ?>;
            var js_needmoreinfo =   <?php echo json_encode($needmoreinfoCounter); ?>;
            var js_new =            <?php echo json_encode($newCounter); ?>;
            var js_obsolete =       <?php echo json_encode($obsoleteCounter); ?>;
            var js_reopen =         <?php echo json_encode($reopenCounter); ?>;
            var js_revised =        <?php echo json_encode($revisedCounter); ?>;
            var js_nottocorrect =   <?php echo json_encode($nottocorrectCounter); ?>;
            var js_supportneeded =  <?php echo json_encode($supportneededCounter); ?>;
            var js_withdrawn =      <?php echo json_encode($withdrawnCounter); ?>;
            
            var ctx = document.getElementById('myChart').getContext('2d');
            var chart = new Chart(ctx, {
                // The type of chart we want to create
                type: 'line',
            
                // The data for our dataset
                data: {
                    labels: ["Deferred", "Disagree", "Duplicated", "Fixed", "Held", "Implemented", "In Development", "Irreproducible", "Known Problem", "Need More Info", "New", "Obsolete", "Reopen", "Revised", "Not To Correct", "Support Needed", "Withdrawn"],
                    datasets:
                    [   {label: "Resolved",
                        backgroundColor: '#66BB6A',
                        borderColor: '#66BB6A',
                        data: [0, 0, 0, js_fixed, 0, js_implemented, 0, 0, 0, 0, 0, 0, 0, js_revised, 0, 0, 0]},
                        
                        {label: "Pending",
                        backgroundColor: '#FFCA28',
                        borderColor: '#FFCA28',
                        data: [0, 0, 0, 0, 0, 0, js_indevelopment, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],},
                        
                        {label: "Unresolved",
                        backgroundColor: '#EF5350',
                        borderColor: '#EF5350',
                        data: [-js_deferred, 0, 0, 0, -js_held, 0, 0, 0, -js_knownproblem, 0, -js_new, 0, -js_reopen, 0, 0, 0, 0],},
                        
                        {label: "Fatal",
                        backgroundColor: '#673AB7',
                        borderColor: '#673AB7',
                        data: [0, 0, 0, 0, 0, 0, 0, -js_irreproducible, 0, 0, 0, -js_obsolete, 0, 0, 0, 0, -js_withdrawn],},
                        
                        {label: "Support Needed",
                        backgroundColor: '#AB47BC',
                        borderColor: '#AB47BC',
                        data: [0, 0, 0, 0, 0, 0, 0, 0, 0, -js_needmoreinfo, 0, 0, 0, 0, 0, -js_supportneeded, 0],},
                        
                        {label: "Conflicts",
                        backgroundColor: '#EC407A',
                        borderColor: '#EC407A',
                        data: [0, -js_disagree, -js_duplicated, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -js_nottocorrect, 0, 0],}
                    ]
                },
                
                options: {
                    
                    title: {
                        display: true,
                        text: "Combat Halloween Bugs",
                        fontFamily: "japokki",
                        fontSize: 30
                    },
                    
                    legend: {
                        labels: {
                            fontFamily: "japokki"
                        }
                    },
                    
                    scales: {
                        yAxes: [{
                                ticks: {
                                    fontFamily: "japokki"
                                }
                        }],
                        xAxes: [{
                                ticks: {
                                    fontFamily: "japokki"
                                }
                        }]
                    }
                }
            });
        </script>
        <!-- ---------------------------------- -->
        
        
        <!-- Print stats-->
      	<h4 class="japokki-black A4"><?php echo "Resolved: ".$resolvedCounter." Unresolved: ".$unresolvedCounter." All: ".$allCounter;?></h4>
        
    	<?php
    	echo '<h4>';
    		foreach($peoplearray as $key => $v)
    		{
    			echo '<div class="chip japokki-black"><img src="../images/users/';
    			echo $key.'.jpg" alt="Contact Person">';
    			echo "Resolved: ".$v['resolved'];
    			echo " Unresolved: ".$v['unresolved'];
    			echo " All: ".$v['all'];
    			echo '</div>';
    		}
    		echo "</h4>";
    	?>
		
        <!-- SORT BY-->
        <form action="index.php" method="get">
            <div class="row japokki-black">
                <div class="input-field col s6 m3 push-m3">
                <select name="rselect">
                    <?php
                    echo "<option "; if($rselect=="all")   echo " selected "; echo 'value="all">All</option>';
                    echo "<option "; if($rselect=="resolved")   echo " selected "; echo 'value="resolved">Resolved</option>';
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
                <button class="waves-effect waves-light btn green lighten-1 japokki" type="submit" style="margin-bottom: 15px;"><i class="material-icons right">redo</i>Reload </button>
            </div>
        </form>
        <!-- ------ -->
      
        <!-- TABLE -->
        <?php require_once("other/table.php"); ?>
        <!-- ----- -->
    </div>

<?php require_once("../common/footer.php"); ?>